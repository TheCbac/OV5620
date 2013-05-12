/*******************************************************************************
* File Name: USB_std.c
* Version 2.50
*
* Description:
*  USB Standard request handler.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "USB.h"


/***************************************
* External references
***************************************/

extern const uint8 CYCODE USB_DEVICE0_DESCR[];
extern const uint8 CYCODE USB_DEVICE0_CONFIGURATION0_DESCR[];
extern const uint8 CYCODE USB_STRING_DESCRIPTORS[];
extern const uint8 CYCODE USB_MSOS_DESCRIPTOR[];
extern const uint8 CYCODE USB_SN_STRING_DESCRIPTOR[];

extern volatile uint8 USB_device;
extern volatile uint8 USB_configuration;
extern volatile uint8 USB_configurationChanged;
extern volatile uint8 USB_interfaceNumber;
extern volatile uint8 USB_interfaceSetting[];
extern volatile uint8 USB_interfaceSetting_last[];
extern volatile uint8 USB_deviceAddress;
extern volatile uint8 USB_deviceStatus;
extern volatile uint8 USB_interfaceStatus[];
extern uint8 CYCODE *USB_interfaceClass;
extern const T_USB_LUT CYCODE USB_TABLE[];
extern volatile T_USB_EP_CTL_BLOCK USB_EP[];
extern volatile T_USB_TD USB_currentTD;
#if defined(USB_ENABLE_CDC_CLASS)
    extern volatile uint8 USB_cdc_data_in_ep;
    extern volatile uint8 USB_cdc_data_out_ep;
#endif  /* End USB_ENABLE_CDC_CLASS*/
#if defined(USB_ENABLE_MIDI_STREAMING)
    extern volatile uint8 USB_midi_in_ep;
    extern volatile uint8 USB_midi_out_ep;
#endif /* End USB_ENABLE_MIDI_STREAMING */


/***************************************
*         Forward references
***************************************/

uint8 USB_InitControlRead(void) ;
uint8 USB_InitControlWrite(void) ;
uint8 USB_InitNoDataControlTransfer(void) ;
uint8 USB_DispatchClassRqst(void) ;

void USB_Config(uint8 clearAltSetting) ;
void USB_ConfigAltChanged(void) ;
T_USB_LUT *USB_GetConfigTablePtr(uint8 c)
                                                            ;
T_USB_LUT *USB_GetDeviceTablePtr(void)
                                                            ;
uint8 USB_ClearEndpointHalt(void) ;
uint8 USB_SetEndpointHalt(void) ;
uint8 USB_ValidateAlternateSetting(void) ;

/*DIE ID string descriptor for 8 bytes ID*/
#if defined(USB_ENABLE_IDSN_STRING)
    void USB_ReadDieID(uint8 *descr) ;
    uint8 USB_idSerialNumberStringDescriptor[0x22u]={0x22u, USB_DESCR_STRING};
#endif /* USB_ENABLE_IDSN_STRING */

#if(USB_EP_MM != USB__EP_MANUAL)
    void USB_Stop_DMA(uint8 epNumber) ;
#endif   /* End USB_EP_MM != USB__EP_MANUAL */
uint8 CYCODE *USB_GetInterfaceClassTablePtr(void)
                                                    ;


/***************************************
* Global data allocation
***************************************/

volatile uint8 USB_tBuffer[USB_EP_STATUS_LENGTH > USB_DEVICE_STATUS_LENGTH ? \
                               USB_EP_STATUS_LENGTH : USB_DEVICE_STATUS_LENGTH];
volatile uint8 *USB_fwSerialNumberStringDescriptor;
volatile uint8 USB_snStringConfirm = USB_FALSE;


/*******************************************************************************
* Function Name: USB_SerialNumString
********************************************************************************
*
* Summary:
*  Application firmware may supply the source of the USB device descriptors
*  serial number string during runtime.
*
* Parameters:
*  snString:  pointer to string.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void  USB_SerialNumString(uint8 *snString) 
{
    #if defined(USB_ENABLE_FWSN_STRING)
        USB_snStringConfirm = USB_FALSE;
        if(snString != NULL)
        {
            USB_fwSerialNumberStringDescriptor = snString;
            /* check descriptor validation */
            if( (USB_fwSerialNumberStringDescriptor[0u] > 1u ) &&  \
                (USB_fwSerialNumberStringDescriptor[1u] == USB_DESCR_STRING) )
            {
                USB_snStringConfirm = USB_TRUE;
            }
        }
    #else
        snString = snString;
    #endif  /* USB_ENABLE_FWSN_STRING */
}


/*******************************************************************************
* Function Name: USB_HandleStandardRqst
********************************************************************************
*
* Summary:
*  This Routine dispatches standard requests
*
* Parameters:
*  None.
*
* Return:
*  TRUE if request handled.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 USB_HandleStandardRqst(void) 
{
    uint8 requestHandled = USB_FALSE;
    #if defined(USB_ENABLE_STRINGS)
        volatile uint8 *pStr = 0u;
        #if defined(USB_ENABLE_DESCRIPTOR_STRINGS)
            uint8 nStr;
        #endif /* USB_ENABLE_DESCRIPTOR_STRINGS */
    #endif /* USB_ENABLE_STRINGS */
    uint16 count;

    T_USB_LUT *pTmp;
    USB_currentTD.count = 0u;

    if ((CY_GET_REG8(USB_bmRequestType) & USB_RQST_DIR_MASK) == USB_RQST_DIR_D2H)
    {
        /* Control Read */
        switch (CY_GET_REG8(USB_bRequest))
        {
            case USB_GET_DESCRIPTOR:
                if (CY_GET_REG8(USB_wValueHi) == USB_DESCR_DEVICE)
                {
                    pTmp = USB_GetDeviceTablePtr();
                    USB_currentTD.pData = pTmp->p_list;
                    USB_currentTD.count = USB_DEVICE_DESCR_LENGTH;
                    requestHandled  = USB_InitControlRead();
                }
                else if (CY_GET_REG8(USB_wValueHi) == USB_DESCR_CONFIG)
                {
                    pTmp = USB_GetConfigTablePtr(CY_GET_REG8(USB_wValueLo));
                    USB_currentTD.pData = pTmp->p_list;
                    count = ((uint16)(USB_currentTD.pData)[ \
                                      USB_CONFIG_DESCR_TOTAL_LENGTH_HI] << 8u) | \
                                     (USB_currentTD.pData)[USB_CONFIG_DESCR_TOTAL_LENGTH_LOW];
                    USB_currentTD.count = count;
                    requestHandled  = USB_InitControlRead();
                }
                #if defined(USB_ENABLE_STRINGS)
                else if (CY_GET_REG8(USB_wValueHi) == USB_DESCR_STRING)
                {
                    /* Descriptor Strings*/
                    #if defined(USB_ENABLE_DESCRIPTOR_STRINGS)
                        nStr = 0u;
                        pStr = (volatile uint8 *)&USB_STRING_DESCRIPTORS[0u];
                        while ( (CY_GET_REG8(USB_wValueLo) > nStr) && (*pStr != 0u ))
                        {
                            pStr += *pStr;
                            nStr++;
                        };
                    #endif /* End USB_ENABLE_DESCRIPTOR_STRINGS */
                    /* Microsoft OS String*/
                    #if defined(USB_ENABLE_MSOS_STRING)
                        if( CY_GET_REG8(USB_wValueLo) == USB_STRING_MSOS )
                        {
                            pStr = (volatile uint8 *)&USB_MSOS_DESCRIPTOR[0u];
                        }
                    #endif /* End USB_ENABLE_MSOS_STRING*/
                    /* SN string*/
                    #if defined(USB_ENABLE_SN_STRING)
                        if( (CY_GET_REG8(USB_wValueLo) != 0) && 
                            (CY_GET_REG8(USB_wValueLo) == 
                            USB_DEVICE0_DESCR[USB_DEVICE_DESCR_SN_SHIFT]) )
                        {
                            pStr = (volatile uint8 *)&USB_SN_STRING_DESCRIPTOR[0u];
                            if(USB_snStringConfirm != USB_FALSE)
                            {
                                pStr = USB_fwSerialNumberStringDescriptor;
                            }
                            #if defined(USB_ENABLE_IDSN_STRING)
                                /* Read DIE ID and genarete string descriptor in RAM*/
                                USB_ReadDieID(USB_idSerialNumberStringDescriptor);
                                pStr = USB_idSerialNumberStringDescriptor;
                            #endif    /* End USB_ENABLE_IDSN_STRING */
                        }
                    #endif    /* End USB_ENABLE_SN_STRING */
                    if (*pStr != 0u)
                    {
                        USB_currentTD.count = *pStr;
                        USB_currentTD.pData = pStr;
                        requestHandled  = USB_InitControlRead();
                    }
                }
                #endif /* End USB_ENABLE_STRINGS */
                else
                {
                    requestHandled = USB_DispatchClassRqst();
                }
                break;
            case USB_GET_STATUS:
                switch ((CY_GET_REG8(USB_bmRequestType) & USB_RQST_RCPT_MASK))
                {
                    case USB_RQST_RCPT_EP:
                        USB_currentTD.count = USB_EP_STATUS_LENGTH;
                        USB_tBuffer[0] = USB_EP[ \
                                        CY_GET_REG8(USB_wIndexLo) & USB_DIR_UNUSED].hwEpState;
                        USB_tBuffer[1] = 0u;
                        USB_currentTD.pData = &USB_tBuffer[0u];
                        requestHandled  = USB_InitControlRead();
                        break;
                    case USB_RQST_RCPT_DEV:
                        USB_currentTD.count = USB_DEVICE_STATUS_LENGTH;
                        USB_tBuffer[0u] = USB_deviceStatus;
                        USB_tBuffer[1u] = 0u;
                        USB_currentTD.pData = &USB_tBuffer[0u];
                        requestHandled  = USB_InitControlRead();
                        break;
                    default:    /* requestHandled is initialezed as FALSE by default */
                        break;
                }
                break;
            case USB_GET_CONFIGURATION:
                USB_currentTD.count = 1u;
                USB_currentTD.pData = (uint8 *)&USB_configuration;
                requestHandled  = USB_InitControlRead();
                break;
            case USB_GET_INTERFACE:
                USB_currentTD.count = 1u;
                USB_currentTD.pData = (uint8 *)&USB_interfaceSetting[ \
                                                                            CY_GET_REG8(USB_wIndexLo)];
                requestHandled  = USB_InitControlRead();
                break;
            default: /* requestHandled is initialezed as FALSE by default */
                break;
        }
    }
    else {
        /* Control Write */
        switch (CY_GET_REG8(USB_bRequest))
        {
            case USB_SET_ADDRESS:
                USB_deviceAddress = CY_GET_REG8(USB_wValueLo);
                requestHandled = USB_InitNoDataControlTransfer();
                break;
            case USB_SET_CONFIGURATION:
                USB_configuration = CY_GET_REG8(USB_wValueLo);
                USB_configurationChanged = USB_TRUE;
                USB_Config(USB_TRUE);
                requestHandled = USB_InitNoDataControlTransfer();
                break;
            case USB_SET_INTERFACE:
                if (USB_ValidateAlternateSetting())
                {
                    USB_interfaceNumber = CY_GET_REG8(USB_wIndexLo);
                    USB_configurationChanged = USB_TRUE;
                    #if ((USB_EP_MA == USB__MA_DYNAMIC) && \
                         (USB_EP_MM == USB__EP_MANUAL) )
                        USB_Config(USB_FALSE);
                    #else
                        USB_ConfigAltChanged();
                    #endif /* End (USB_EP_MA == USB__MA_DYNAMIC) */
                    /* Update handled Alt setting changes status */
                    USB_interfaceSetting_last[USB_interfaceNumber] = 
                         USB_interfaceSetting[USB_interfaceNumber];
                    requestHandled = USB_InitNoDataControlTransfer();
                }
                break;
            case USB_CLEAR_FEATURE:
                switch (CY_GET_REG8(USB_bmRequestType) & USB_RQST_RCPT_MASK)
                {
                    case USB_RQST_RCPT_EP:
                        if (CY_GET_REG8(USB_wValueLo) == USB_ENDPOINT_HALT)
                        {
                            requestHandled = USB_ClearEndpointHalt();
                        }
                        break;
                    case USB_RQST_RCPT_DEV:
                        /* Clear device REMOTE_WAKEUP */
                        if (CY_GET_REG8(USB_wValueLo) == USB_DEVICE_REMOTE_WAKEUP)
                        {
                            USB_deviceStatus &= ~USB_DEVICE_STATUS_REMOTE_WAKEUP;
                            requestHandled = USB_InitNoDataControlTransfer();
                        }
                        break;
                    case USB_RQST_RCPT_IFC:
                        /* Validate interfaceNumber */
                        if (CY_GET_REG8(USB_wIndexLo) < USB_MAX_INTERFACES_NUMBER)
                        {
                            USB_interfaceStatus[CY_GET_REG8(USB_wIndexLo)] &= \
                                                                ~(CY_GET_REG8(USB_wValueLo)) ;
                            requestHandled = USB_InitNoDataControlTransfer();
                        }
                        break;
                    default:    /* requestHandled is initialezed as FALSE by default */
                        break;
                }
                break;
            case USB_SET_FEATURE:
                switch (CY_GET_REG8(USB_bmRequestType) & USB_RQST_RCPT_MASK)
                {
                    case USB_RQST_RCPT_EP:
                        if (CY_GET_REG8(USB_wValueLo) == USB_ENDPOINT_HALT)
                        {
                            requestHandled = USB_SetEndpointHalt();
                        }
                        break;
                    case USB_RQST_RCPT_DEV:
                        /* Set device REMOTE_WAKEUP */
                        if (CY_GET_REG8(USB_wValueLo) == USB_DEVICE_REMOTE_WAKEUP)
                        {
                            USB_deviceStatus |= USB_DEVICE_STATUS_REMOTE_WAKEUP;
                            requestHandled = USB_InitNoDataControlTransfer();
                        }
                        break;
                    case USB_RQST_RCPT_IFC:
                        /* Validate interfaceNumber */
                        if (CY_GET_REG8(USB_wIndexLo) < USB_MAX_INTERFACES_NUMBER)
                        {
                            USB_interfaceStatus[CY_GET_REG8(USB_wIndexLo)] &= \
                                                                ~(CY_GET_REG8(USB_wValueLo)) ;
                            requestHandled = USB_InitNoDataControlTransfer();
                        }
                        break;
                    default:    /* requestHandled is initialezed as FALSE by default */
                        break;
                }
                break;
            default:    /* requestHandled is initialezed as FALSE by default */
                break;
        }
    }
    return(requestHandled);
}


#if defined(USB_ENABLE_IDSN_STRING)

    /***************************************************************************
    * Function Name: USB_ReadDieID
    ****************************************************************************
    *
    * Summary:
    *  This routine read Die ID and genarete Serian Number string descriptor.
    *
    * Parameters:
    *  descr:  pointer on string descriptor.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  No.
    *
    ***************************************************************************/
    void USB_ReadDieID(uint8 *descr) 
    {
        uint8 i,j;
        uint8 value;
        static char8 const hex[16u] = "0123456789ABCDEF";

        /* check descriptor validation */
        if( (descr[0u] > 1u ) && (descr[1u] == USB_DESCR_STRING) )
        {
            /* fill descriptor */
            for(j = 0u, i = 2u; i < descr[0u]; i += 2u)
            {
                value = CY_GET_XTND_REG8((void CYFAR *)(USB_DIE_ID + j++));
                descr[i] = (uint8)hex[value >> 4u];
                i += 2u;
                descr[i] = (uint8)hex[value & 0x0Fu];
            }
        }
    }

#endif /* End $INSTANCE_NAME`_ENABLE_IDSN_STRING*/


/*******************************************************************************
* Function Name: USB_ConfigReg
********************************************************************************
*
* Summary:
*  This routine configures hardware registers from the variables.
*  It is called from USB_Config() function and from RestoreConfig
*  after Wakeup.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void USB_ConfigReg(void) 
{
    uint8 ep;
    uint8 i;
    #if(USB_EP_MM == USB__EP_DMAAUTO)
        uint8 ep_type = 0u;
    #endif /* End USB_EP_MM == USB__EP_DMAAUTO */

    /* Set the endpoint buffer addresses */
    ep = USB_EP1;
    for (i = 0u; i < 0x80u; i+= 0x10u)
    {
        CY_SET_REG8(&USB_ARB_EP1_CFG_PTR[i], USB_ARB_EPX_CFG_CRC_BYPASS |
                                                          USB_ARB_EPX_CFG_RESET);

        #if(USB_EP_MM != USB__EP_MANUAL)
            /* Enable all Arbiter EP Interrupts : err, buf under, buf over, dma gnt(mode2 only), in buf full */
            USB_ARB_EP1_INT_EN_PTR[i] = USB_ARB_EPX_INT_MASK;
        #endif   /* End USB_EP_MM != USB__EP_MANUAL */

        if(USB_EP[ep].epMode != USB_MODE_DISABLE)
        {
            if((USB_EP[ep].addr & USB_DIR_IN) != 0u )
            {
                CY_SET_REG8(&USB_SIE_EP1_CR0_PTR[i], USB_MODE_NAK_IN);
            }
            else
            {
                CY_SET_REG8(&USB_SIE_EP1_CR0_PTR[i], USB_MODE_NAK_OUT);
                /* Prepare EP type mask for automatic memory allocation */
                #if(USB_EP_MM == USB__EP_DMAAUTO)
                    ep_type |= 0x01u << (ep - USB_EP1);
                #endif /* End USB_EP_MM == USB__EP_DMAAUTO */
            }
        }
        else
        {
            CY_SET_REG8(&USB_SIE_EP1_CR0_PTR[i], USB_MODE_STALL_DATA_EP);
        }

        #if(USB_EP_MM != USB__EP_DMAAUTO)
            CY_SET_REG8(&USB_SIE_EP1_CNT0_PTR[i],   USB_EP[ep].bufferSize >> 8u);
            CY_SET_REG8(&USB_SIE_EP1_CNT1_PTR[i],   USB_EP[ep].bufferSize & 0xFFu);

            CY_SET_REG8(&USB_ARB_RW1_RA_PTR[i],     USB_EP[ep].buffOffset & 0xFFu);
            CY_SET_REG8(&USB_ARB_RW1_RA_MSB_PTR[i], USB_EP[ep].buffOffset >> 8u);
            CY_SET_REG8(&USB_ARB_RW1_WA_PTR[i],     USB_EP[ep].buffOffset & 0xFFu);
            CY_SET_REG8(&USB_ARB_RW1_WA_MSB_PTR[i], USB_EP[ep].buffOffset >> 8u);
        #endif /* End USB_EP_MM != USB__EP_DMAAUTO */

        ep++;
    }

    #if(USB_EP_MM == USB__EP_DMAAUTO)
         /* BUF_SIZE depend on DMA_THRESS value: 55-32 bytes  44-16 bytes 33-8 bytes 22-4 bytes 11-2 bytes */
        USB_BUF_SIZE_REG = USB_DMA_BUF_SIZE;
        USB_DMA_THRES_REG = USB_DMA_BYTES_PER_BURST;   /* DMA burst threshold */
        USB_DMA_THRES_MSB_REG = 0u;
        USB_EP_ACTIVE_REG = USB_ARB_INT_MASK;
        USB_EP_TYPE_REG = ep_type;
        /* Cfg_cmp bit set to 1 once configuration is complete. */
        USB_ARB_CFG_REG = USB_ARB_CFG_AUTO_DMA | USB_ARB_CFG_AUTO_MEM |
                                       USB_ARB_CFG_CFG_CPM;
        /* Cfg_cmp bit set to 0 during configuration of PFSUSB Registers. */
        USB_ARB_CFG_REG = USB_ARB_CFG_AUTO_DMA | USB_ARB_CFG_AUTO_MEM;
    #endif /* End USB_EP_MM == USB__EP_DMAAUTO */

    CY_SET_REG8(USB_SIE_EP_INT_EN_PTR, 0xFFu);
}


/*******************************************************************************
* Function Name: USB_Config
********************************************************************************
*
* Summary:
*  This routine configures endpoints for the entire configuration by scanning
*  the configuration descriptor.
*
* Parameters:
*  clearAltSetting: It configures the bAlternateSetting 0 for each interface.
*
* Return:
*  None.
*
* USB_interfaceClass - Initialized class array for each interface.
*   It is used for hangling Class specific requests depend on interface class.
*   Different classes in multiple Alternate settings does not supported.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void USB_Config(uint8 clearAltSetting) 
{
    uint8 ep;
    uint8 cur_ep;
    uint8 i;
    uint8 iso;
    uint8 *pDescr;
    #if(USB_EP_MM != USB__EP_DMAAUTO)
        uint16 count = 0u;
    #endif /* End USB_EP_MM != USB__EP_DMAAUTO */
    
    T_USB_LUT *pTmp;
    T_USB_EP_SETTINGS_BLOCK *pEP;

    /* Clear all of the endpoints */
    for (ep = 0u; ep < USB_MAX_EP; ep++)
    {
        USB_EP[ep].attrib = 0u;
        USB_EP[ep].hwEpState = 0u;
        USB_EP[ep].apiEpState = USB_NO_EVENT_PENDING;
        USB_EP[ep].epToggle = 0u;
        USB_EP[ep].epMode = USB_MODE_DISABLE;
        USB_EP[ep].bufferSize = 0u;
        USB_EP[ep].interface = 0u;

    }

    /* Clear Alternate settings for all interfaces */
    if(clearAltSetting != 0u)
    {
        for (i = 0u; i < USB_MAX_INTERFACES_NUMBER; i++)
        {
            USB_interfaceSetting[i] = 0x00u;
            USB_interfaceSetting_last[i] = 0x00u;
        }
    }

    /* Init Endpoints and Device Status if configured */
    if(USB_configuration > 0u)
    {
        pTmp = USB_GetConfigTablePtr(USB_configuration - 1u);
        /* Set Power status for current configuration */
        pDescr = (uint8 *)pTmp->p_list;
        if((pDescr[USB_CONFIG_DESCR_ATTRIB] & USB_CONFIG_DESCR_ATTRIB_SELF_POWERED) != 0u)
        {
            USB_deviceStatus |=  USB_DEVICE_STATUS_SELF_POWERED;
        }
        else
        {
            USB_deviceStatus &=  ~USB_DEVICE_STATUS_SELF_POWERED;
        }
        pTmp++;
        ep = pTmp->c;  /* For this table, c is the number of endpoints configurations  */

        #if ((USB_EP_MA == USB__MA_DYNAMIC) && \
             (USB_EP_MM == USB__EP_MANUAL) )
            /* Config for dynamic EP memory allocation */
            /* p_list points the endpoint setting table. */
            pEP = (T_USB_EP_SETTINGS_BLOCK *) pTmp->p_list;
            for (i = 0u; i < ep; i++, pEP++)
            {
                /* compate current Alternate setting with EP Alt*/
                if(USB_interfaceSetting[pEP->interface] == pEP->altSetting)
                {
                    cur_ep = pEP->addr & USB_DIR_UNUSED;
                    iso  = ((pEP->attributes & USB_EP_TYPE_MASK) == USB_EP_TYPE_ISOC);
                    if (pEP->addr & USB_DIR_IN)
                    {
                        /* IN Endpoint */
                        USB_EP[cur_ep].apiEpState = USB_EVENT_PENDING;
                        USB_EP[cur_ep].epMode = \
                                                (iso ? USB_MODE_ISO_IN : USB_MODE_ACK_IN);
                        #if defined(USB_ENABLE_CDC_CLASS)
                            if(((pEP->bMisc == USB_CLASS_CDC_DATA) ||
                                (pEP->bMisc == USB_CLASS_CDC)) &&
                                ((pEP->attributes & USB_EP_TYPE_MASK) != USB_EP_TYPE_INT))
                            {
                                USB_cdc_data_in_ep = cur_ep;
                            }
                        #endif  /* End USB_ENABLE_CDC_CLASS*/
                        #if defined(USB_ENABLE_MIDI_STREAMING)
                            if((pEP->bMisc == USB_CLASS_AUDIO) &&
                               ((pEP->attributes & USB_EP_TYPE_MASK) == USB_EP_TYPE_BULK))
                            {
                                USB_midi_in_ep = cur_ep;
                            }
                        #endif  /* End USB_ENABLE_MIDI_STREAMING*/
                    }
                    else
                    {
                        /* OUT Endpoint */
                        USB_EP[cur_ep].apiEpState = USB_NO_EVENT_PENDING;
                        USB_EP[cur_ep].epMode = \
                                                (iso ? USB_MODE_ISO_OUT : USB_MODE_ACK_OUT);
                        #if defined(USB_ENABLE_CDC_CLASS)
                            if(((pEP->bMisc == USB_CLASS_CDC_DATA) ||
                                (pEP->bMisc == USB_CLASS_CDC)) &&
                                ((pEP->attributes & USB_EP_TYPE_MASK) != USB_EP_TYPE_INT))
                            {
                                USB_cdc_data_out_ep = cur_ep;
                            }
                        #endif  /* End USB_ENABLE_CDC_CLASS*/
                        #if defined(USB_ENABLE_MIDI_STREAMING)
                            if((pEP->bMisc == USB_CLASS_AUDIO) &&
                               ((pEP->attributes & USB_EP_TYPE_MASK) == USB_EP_TYPE_BULK))
                            {
                                USB_midi_out_ep = cur_ep;
                            }
                        #endif  /* End USB_ENABLE_MIDI_STREAMING*/
                    }
                    USB_EP[cur_ep].bufferSize = pEP->bufferSize;
                    USB_EP[cur_ep].addr = pEP->addr;
                    USB_EP[cur_ep].attrib = pEP->attributes;
                }
            }
        #else /* Config for static EP memory allocation  */
            for (i = USB_EP1; i < USB_MAX_EP; i++)
            {
                /* and p_list points the endpoint setting table. */
                pEP = (T_USB_EP_SETTINGS_BLOCK *) pTmp->p_list;
                /* find max length for each EP and select it (length could be different in different Alt settings) */
                /* but other settings should be correct with regards to Interface alt Setting */
                for (cur_ep = 0u; cur_ep < ep; cur_ep++, pEP++)
                {
                    /* EP count is equal to EP # in table and we found larger EP length than have before*/
                    if(i == (pEP->addr & USB_DIR_UNUSED))
                    {
                        if(USB_EP[i].bufferSize < pEP->bufferSize)
                        {
                            USB_EP[i].bufferSize = pEP->bufferSize;
                        }
                        /* compate current Alternate setting with EP Alt*/
                        if(USB_interfaceSetting[pEP->interface] == pEP->altSetting)
                        {
                            iso  = ((pEP->attributes & USB_EP_TYPE_MASK) == USB_EP_TYPE_ISOC);
                            if (pEP->addr & USB_DIR_IN)
                            {
                                /* IN Endpoint */
                                USB_EP[i].apiEpState = USB_EVENT_PENDING;
                                USB_EP[i].epMode =
                                                    (iso ? USB_MODE_ISO_IN : USB_MODE_ACK_IN);
                                /* Find and init CDC IN endpoint number */
                                #if defined(USB_ENABLE_CDC_CLASS)
                                    if(((pEP->bMisc == USB_CLASS_CDC_DATA) ||
                                        (pEP->bMisc == USB_CLASS_CDC)) &&
                                        ((pEP->attributes & USB_EP_TYPE_MASK) !=
                                                                                        USB_EP_TYPE_INT))
                                    {
                                        USB_cdc_data_in_ep = i;
                                    }
                                #endif  /* End USB_ENABLE_CDC_CLASS*/
                                #if defined(USB_ENABLE_MIDI_STREAMING)
                                    if((pEP->bMisc == USB_CLASS_AUDIO) &&
                                       ((pEP->attributes & USB_EP_TYPE_MASK) ==
                                                                                        USB_EP_TYPE_BULK))
                                    {
                                        USB_midi_in_ep = i;
                                    }
                                #endif  /* End USB_ENABLE_MIDI_STREAMING*/
                            }
                            else
                            {
                                /* OUT Endpoint */
                                USB_EP[i].apiEpState = USB_NO_EVENT_PENDING;
                                USB_EP[i].epMode =
                                                (iso ? USB_MODE_ISO_OUT : USB_MODE_ACK_OUT);
                                /* Find and init CDC IN endpoint number */
                                #if defined(USB_ENABLE_CDC_CLASS)
                                    if(((pEP->bMisc == USB_CLASS_CDC_DATA) ||
                                        (pEP->bMisc == USB_CLASS_CDC)) &&
                                        ((pEP->attributes & USB_EP_TYPE_MASK) !=
                                                                                    USB_EP_TYPE_INT))
                                    {
                                        USB_cdc_data_out_ep = i;
                                    }
                                #endif  /* End USB_ENABLE_CDC_CLASS*/
                                #if defined(USB_ENABLE_MIDI_STREAMING)
                                    if((pEP->bMisc == USB_CLASS_AUDIO) &&
                                       ((pEP->attributes & USB_EP_TYPE_MASK) ==
                                                                                        USB_EP_TYPE_BULK))
                                    {
                                        USB_midi_out_ep = i;
                                    }
                                #endif  /* End USB_ENABLE_MIDI_STREAMING*/
                            }
                            USB_EP[i].addr = pEP->addr;
                            USB_EP[i].attrib = pEP->attributes;

                            #if(USB_EP_MM == USB__EP_DMAAUTO)
                                break;      /* use first EP setting in Auto memory managment */
                            #endif /* End USB_EP_MM == USB__EP_DMAAUTO */
                        }
                    }
                }
            }
        #endif /* End (USB_EP_MA == USB__MA_DYNAMIC) */

        /* Init class array for each interface and interface number for each EP.
        *  It is used for hangling Class specific requests directed to either an
        *  interface or the endpoint.
        */
        /* p_list points the endpoint setting table. */
        pEP = (T_USB_EP_SETTINGS_BLOCK *) pTmp->p_list;
        for (i = 0u; i < ep; i++, pEP++)
        {
            /* config interface number for each EP*/
            USB_EP[pEP->addr & USB_DIR_UNUSED].interface = pEP->interface;
        }
        /* init pointer on interface class table*/
        USB_interfaceClass = USB_GetInterfaceClassTablePtr();
        /* Set the endpoint buffer addresses */
        
        #if(USB_EP_MM != USB__EP_DMAAUTO)
            for (ep = USB_EP1; ep < USB_MAX_EP; ep++)
            {
                USB_EP[ep].buffOffset = count;
                 count += USB_EP[ep].bufferSize;
            }
        #endif /* End USB_EP_MM != USB__EP_DMAAUTO */

        /* Congigure hardware registers */
        USB_ConfigReg();
    } /* USB_configuration > 0 */
}


/*******************************************************************************
* Function Name: USB_ConfigAltChanged
********************************************************************************
*
* Summary:
*  This routine undate configuration for the required endpoints only.
*  It is called after SET_INTERFACE request when Static memory allocation used.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void USB_ConfigAltChanged() 
{
    uint8 ep,cur_ep,i;
    uint8 iso;
    uint8 ri;

    T_USB_LUT *pTmp;
    T_USB_EP_SETTINGS_BLOCK *pEP;


    /* Init Endpoints and Device Status if configured */
    if(USB_configuration > 0u)
    {
        pTmp = USB_GetConfigTablePtr(USB_configuration - 1u);
        pTmp++;
        ep = pTmp->c;  /* For this table, c is the number of endpoints configurations  */

        /* Do not touch EP wich doesn't need reconfiguration */
        /* When Alt setting chaged, the only required endpoints need to be reconfigured */
        /* p_list points the endpoint setting table. */
        pEP = (T_USB_EP_SETTINGS_BLOCK *) pTmp->p_list;
        for (i = 0u; i < ep; i++, pEP++)
        {
            /*If Alt setting changed and new is same with EP Alt */
            if((USB_interfaceSetting[pEP->interface] !=
                USB_interfaceSetting_last[pEP->interface] ) &&
               (USB_interfaceSetting[pEP->interface] == pEP->altSetting) &&
                pEP->interface == CY_GET_REG8(USB_wIndexLo))
            {
                cur_ep = pEP->addr & USB_DIR_UNUSED;
                ri = ((cur_ep - USB_EP1) << USB_EPX_CNTX_ADDR_SHIFT);
                iso  = ((pEP->attributes & USB_EP_TYPE_MASK) == USB_EP_TYPE_ISOC);
                if (pEP->addr & USB_DIR_IN)
                {
                    /* IN Endpoint */
                    USB_EP[cur_ep].apiEpState = USB_EVENT_PENDING;
                    USB_EP[cur_ep].epMode =
                                            (iso ? USB_MODE_ISO_IN : USB_MODE_ACK_IN);
                }
                else
                {
                    /* OUT Endpoint */
                    USB_EP[cur_ep].apiEpState = USB_NO_EVENT_PENDING;
                    USB_EP[cur_ep].epMode =
                                            (iso ? USB_MODE_ISO_OUT : USB_MODE_ACK_OUT);
                }
                 /* Change the SIE mode for the selected EP to NAK ALL */
                 CY_SET_REG8(&USB_SIE_EP1_CR0_PTR[ri], USB_MODE_NAK_IN_OUT);
                USB_EP[cur_ep].bufferSize = pEP->bufferSize;
                USB_EP[cur_ep].addr = pEP->addr;
                USB_EP[cur_ep].attrib = pEP->attributes;

                /* Clear the data toggle */
                USB_EP[cur_ep].epToggle = 0u;

                /* Dynamic reconfiguration for mode 3 transfer */
                #if((USB_EP_MM == USB__EP_DMAAUTO) && (!CY_PSOC5A) )
                    /* In_data_rdy for selected EP should be set to 0 */
                    USB_ARB_EP1_CFG_PTR[ri] &= ~USB_ARB_EPX_CFG_IN_DATA_RDY;

                    /* write the EP number for which reconfiguration is required */
                    USB_DYN_RECONFIG_REG = (cur_ep - USB_EP1) << 
                                                        USB_DYN_RECONFIG_EP_SHIFT;
                    /* Set the dyn_config_en bit in dynamic reconfiguration register */
                    USB_DYN_RECONFIG_REG |= USB_DYN_RECONFIG_ENABLE;
                    /* wait for the dyn_config_rdy bit to set by the block,
                    *  this bit will be set to 1 when block is ready for reconfiguration.
                    */
                    while((USB_DYN_RECONFIG_REG & USB_DYN_RECONFIG_RDY_STS) == 0u);
                    /* Once dyn_config_rdy bit is set, FW can change the EP configuration. */
                    /* Change EP Type with new direction */
                    if((pEP->addr & USB_DIR_IN) == 0)
                    {
                        USB_EP_TYPE_REG |= 0x01u << (cur_ep - USB_EP1);
                    }
                    else
                    {
                        USB_EP_TYPE_REG &= ~(0x01u << (cur_ep - USB_EP1));
                    }
                    /* dynamic reconfiguration enable bit cleared, pointers and control/status
                    *  signals for the selected EP is cleared/re-initialized on negedge
                    *  of dynamic reconfiguration enable bit).
                    */
                    USB_DYN_RECONFIG_REG &= ~USB_DYN_RECONFIG_ENABLE;
                    /* The main loop has to reenable DMA and OUT endpoint*/
                #else
                CY_SET_REG8(&USB_SIE_EP1_CNT0_PTR[ri],   USB_EP[cur_ep].bufferSize >> 8u);
                CY_SET_REG8(&USB_SIE_EP1_CNT1_PTR[ri],   USB_EP[cur_ep].bufferSize & 0xFFu);

                CY_SET_REG8(&USB_ARB_RW1_RA_PTR[ri],     USB_EP[cur_ep].buffOffset & 0xFFu);
                CY_SET_REG8(&USB_ARB_RW1_RA_MSB_PTR[ri], USB_EP[cur_ep].buffOffset >> 8u);
                CY_SET_REG8(&USB_ARB_RW1_WA_PTR[ri],     USB_EP[cur_ep].buffOffset & 0xFFu);
                CY_SET_REG8(&USB_ARB_RW1_WA_MSB_PTR[ri], USB_EP[cur_ep].buffOffset >> 8u);
                #endif /* End USB_EP_MM == USB__EP_DMAAUTO */
            }
        }
    } /* USB_configuration > 0 */
}


/*******************************************************************************
* Function Name: USB_GetConfigTablePtr
********************************************************************************
*
* Summary:
*  This routine returns a pointer a configuration table entry
*
* Parameters:
*  c:  Configuration Index
*
* Return:
*  Device Descriptor pointer.
*
*******************************************************************************/
T_USB_LUT *USB_GetConfigTablePtr(uint8 c) \
                                                        
{
    /* Device Table */
    T_USB_LUT *pTmp;

    pTmp = USB_GetDeviceTablePtr();

    /* The first entry points to the Device Descriptor,
       the the configuration entries  */
    return(pTmp[c + 1u].p_list);
}


/*******************************************************************************
* Function Name: USB_GetDeviceTablePtr
********************************************************************************
*
* Summary:
*  This routine returns a pointer to the Device table
*
* Parameters:
*  None.
*
* Return:
*  Device Table pointer
*
*******************************************************************************/
T_USB_LUT *USB_GetDeviceTablePtr(void) 
{
    /* Device Table */
    return(USB_TABLE[USB_device].p_list);
}


/*******************************************************************************
* Function Name: USB_GetInterfaceClassTablePtr
********************************************************************************
*
* Summary:
*  This routine returns Interface Class table pointer, which contains
*  the relation between interface number and interface class.
*
* Parameters:
*  None.
*
* Return:
*  Interface Class table pointer.
*
*******************************************************************************/
uint8 CYCODE *USB_GetInterfaceClassTablePtr(void)
                                                        
{
    T_USB_LUT *pTmp;
    uint8 currentInterfacesNum;

    pTmp = USB_GetConfigTablePtr(USB_configuration - 1u);
    currentInterfacesNum  = ((uint8 *) pTmp->p_list)[USB_CONFIG_DESCR_NUM_INTERFACES];
    /* Third entry in the LUT starts the Interface Table pointers */
    pTmp += 2;
    /* The INTERFACE_CLASS table is located after all interfaces*/
    pTmp += currentInterfacesNum;
    return(pTmp->p_list);
}


/*******************************************************************************
* Function Name: USB_TerminateEP
********************************************************************************
*
* Summary:
*  This function terminates the specified USBFS endpoint. 
*  This function should be used before endpoint reconfiguration.
*
* Parameters:
*  Endpoint number.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void USB_TerminateEP(uint8 ep) 
{
    uint8 ri;

    ep &= USB_DIR_UNUSED;
    ri = ((ep - USB_EP1) << USB_EPX_CNTX_ADDR_SHIFT);

    if ((ep > USB_EP0) && (ep < USB_MAX_EP))
    {
        /* Set the endpoint Halt */
        USB_EP[ep].hwEpState |= (USB_ENDPOINT_STATUS_HALT);

        /* Clear the data toggle */
        USB_EP[ep].epToggle = 0u;
        USB_EP[ep].apiEpState = USB_NO_EVENT_ALLOWED;

        if (USB_EP[ep].addr & USB_DIR_IN)
        {
            /* IN Endpoint */
            CY_SET_REG8(&USB_SIE_EP1_CR0_PTR[ri], USB_MODE_NAK_IN);
        }
        else
        {
            /* OUT Endpoint */
            CY_SET_REG8(&USB_SIE_EP1_CR0_PTR[ri], USB_MODE_NAK_OUT);
        }
    }
}


/*******************************************************************************
* Function Name: USB_SetEndpointHalt
********************************************************************************
*
* Summary:
*  This routine handles set endpoint halt.
*
* Parameters:
*  None.
*
* Return:
*  requestHandled.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 USB_SetEndpointHalt(void) 
{
    uint8 ep, ri;
    uint8 requestHandled = USB_FALSE;

    /* Set endpoint halt */
    ep = CY_GET_REG8(USB_wIndexLo) & USB_DIR_UNUSED;
    ri = ((ep - USB_EP1) << USB_EPX_CNTX_ADDR_SHIFT);

    if ((ep > USB_EP0) && (ep < USB_MAX_EP))
    {
        /* Set the endpoint Halt */
        USB_EP[ep].hwEpState |= (USB_ENDPOINT_STATUS_HALT);

        /* Clear the data toggle */
        USB_EP[ep].epToggle = 0u;
        USB_EP[ep].apiEpState |= USB_NO_EVENT_ALLOWED;

        if (USB_EP[ep].addr & USB_DIR_IN)
        {
            /* IN Endpoint */
            CY_SET_REG8(&USB_SIE_EP1_CR0_PTR[ri], USB_MODE_STALL_DATA_EP |
                                                               USB_MODE_ACK_IN);
        }
        else
        {
            /* OUT Endpoint */
            CY_SET_REG8(&USB_SIE_EP1_CR0_PTR[ri], USB_MODE_STALL_DATA_EP |
                                                               USB_MODE_ACK_OUT);
        }
        requestHandled = USB_InitNoDataControlTransfer();
    }

    return(requestHandled);
}


/*******************************************************************************
* Function Name: USB_ClearEndpointHalt
********************************************************************************
*
* Summary:
*  This routine handles clear endpoint halt.
*
* Parameters:
*  None.
*
* Return:
*  requestHandled.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 USB_ClearEndpointHalt(void) 
{
    uint8 ep, ri;
    uint8 requestHandled = USB_FALSE;

    /* Clear endpoint halt */
    ep = CY_GET_REG8(USB_wIndexLo) & USB_DIR_UNUSED;
    ri = ((ep - USB_EP1) << USB_EPX_CNTX_ADDR_SHIFT);

    if ((ep > USB_EP0) && (ep < USB_MAX_EP))
    {
        /* Clear the endpoint Halt */
        USB_EP[ep].hwEpState &= ~(USB_ENDPOINT_STATUS_HALT);

        /* Clear the data toggle */
        USB_EP[ep].epToggle = 0u;
        /* Clear toggle bit for already armed packet */
        CY_SET_REG8(&USB_SIE_EP1_CNT0_PTR[ri], 
                    CY_GET_REG8(&USB_SIE_EP1_CNT0_PTR[ri]) & ~USB_EPX_CNT_DATA_TOGGLE);
        /* Return api State as it was defined before */
        USB_EP[ep].apiEpState &= ~USB_NO_EVENT_ALLOWED;

        if (USB_EP[ep].addr & USB_DIR_IN)
        {
            /* IN Endpoint */
            if(USB_EP[ep].apiEpState == USB_IN_BUFFER_EMPTY)
            {       /* Wait for next packet from application */
                CY_SET_REG8(&USB_SIE_EP1_CR0_PTR[ri], USB_MODE_NAK_IN);
            }
            else    /* Continue armed transfer */
            {
                CY_SET_REG8(&USB_SIE_EP1_CR0_PTR[ri], USB_MODE_ACK_IN);
            }
        }
        else
        {
            /* OUT Endpoint */
            if(USB_EP[ep].apiEpState == USB_OUT_BUFFER_FULL)
            {       /* Allow application to read full buffer */
                CY_SET_REG8(&USB_SIE_EP1_CR0_PTR[ri], USB_MODE_NAK_OUT);
            }
            else    /* Mark endpoint as empty, so it will be reloaded */
            {
                CY_SET_REG8(&USB_SIE_EP1_CR0_PTR[ri], USB_MODE_ACK_OUT);
            }
        }
        requestHandled = USB_InitNoDataControlTransfer();
    }

    return(requestHandled);
}


/*******************************************************************************
* Function Name: USB_ValidateAlternateSetting
********************************************************************************
*
* Summary:
*  Validates (and records) a SET INTERFACE request.
*
* Parameters:
*  None.
*
* Return:
*  requestHandled.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 USB_ValidateAlternateSetting(void) 
{
    uint8 requestHandled = USB_TRUE;
    uint8 interfaceNum;
    T_USB_LUT *pTmp;
    uint8 currentInterfacesNum;

    interfaceNum = CY_GET_REG8(USB_wIndexLo);
    /* Validate interface setting, stall if invalid. */
    pTmp = USB_GetConfigTablePtr(USB_configuration - 1u);
    currentInterfacesNum  = ((uint8 *) pTmp->p_list)[USB_CONFIG_DESCR_NUM_INTERFACES];

    if((interfaceNum >= currentInterfacesNum) || (interfaceNum >= USB_MAX_INTERFACES_NUMBER))
    {   /* wrong interface number */
        requestHandled = USB_FALSE;
    }
    else
    {
        /* save current Alt setting to find out the difference in Config() function */
        USB_interfaceSetting_last[interfaceNum] = USB_interfaceSetting[interfaceNum];
        USB_interfaceSetting[interfaceNum] = CY_GET_REG8(USB_wValueLo);
    }

    return (requestHandled);
}


/* [] END OF FILE */
