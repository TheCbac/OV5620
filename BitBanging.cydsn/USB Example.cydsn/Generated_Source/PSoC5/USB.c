/*******************************************************************************
* File Name: USB.c
* Version 2.50
*
* Description:
*  API for USBFS Component.
*
* Note:
*  Many of the functions use endpoint number.  RAM arrays are sized with 9
*  elements so they are indexed directly by epNumber.  The SIE and ARB
*  registers are indexed by variations of epNumber - 1.
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include <CyDmac.h>
#include "USB.h"
#include "USB_hid.h"
#if(USB_DMA1_REMOVE == 0u)
    #include "USB_ep1_dma.h"
#endif   /* End USB_DMA1_REMOVE */
#if(USB_DMA2_REMOVE == 0u)
    #include "USB_ep2_dma.h"
#endif   /* End USB_DMA2_REMOVE */
#if(USB_DMA3_REMOVE == 0u)
    #include "USB_ep3_dma.h"
#endif   /* End USB_DMA3_REMOVE */
#if(USB_DMA4_REMOVE == 0u)
    #include "USB_ep4_dma.h"
#endif   /* End USB_DMA4_REMOVE */
#if(USB_DMA5_REMOVE == 0u)
    #include "USB_ep5_dma.h"
#endif   /* End USB_DMA5_REMOVE */
#if(USB_DMA6_REMOVE == 0u)
    #include "USB_ep6_dma.h"
#endif   /* End USB_DMA6_REMOVE */
#if(USB_DMA7_REMOVE == 0u)
    #include "USB_ep7_dma.h"
#endif   /* End USB_DMA7_REMOVE */
#if(USB_DMA8_REMOVE == 0u)
    #include "USB_ep8_dma.h"
#endif   /* End USB_DMA8_REMOVE */


/***************************************
* External data references
***************************************/

extern volatile uint8 USB_configuration;
extern volatile uint8 USB_interfaceNumber;
extern volatile uint8 USB_configurationChanged;
extern volatile uint8 USB_interfaceSetting[];
extern volatile uint8 USB_interfaceSetting_last[];
extern volatile uint8 USB_deviceAddress;
extern volatile uint8 USB_deviceStatus;
extern volatile uint8 USB_device;
extern volatile uint8 USB_transferState;
extern volatile uint8 USB_lastPacketSize;

extern volatile T_USB_EP_CTL_BLOCK USB_EP[];

#if defined(USB_ENABLE_HID_CLASS)
    extern volatile uint8 USB_hidProtocol[];
#endif /* USB_ENABLE_HID_CLASS */


/***************************************
* External function references
***************************************/

CY_ISR_PROTO(USB_EP_0_ISR);
#if(USB_EP1_ISR_REMOVE == 0u)
    CY_ISR_PROTO(USB_EP_1_ISR);
#endif /* End USB_EP1_ISR_REMOVE */
#if(USB_EP2_ISR_REMOVE == 0u)
    CY_ISR_PROTO(USB_EP_2_ISR);
#endif /* End USB_EP2_ISR_REMOVE */
#if(USB_EP3_ISR_REMOVE == 0u)
    CY_ISR_PROTO(USB_EP_3_ISR);
#endif /* End USB_EP3_ISR_REMOVE */
#if(USB_EP4_ISR_REMOVE == 0u)
    CY_ISR_PROTO(USB_EP_4_ISR);
#endif /* End USB_EP4_ISR_REMOVE */
#if(USB_EP5_ISR_REMOVE == 0u)
    CY_ISR_PROTO(USB_EP_5_ISR);
#endif /* End USB_EP5_ISR_REMOVE */
#if(USB_EP6_ISR_REMOVE == 0u)
    CY_ISR_PROTO(USB_EP_6_ISR);
#endif /* End USB_EP6_ISR_REMOVE */
#if(USB_EP7_ISR_REMOVE == 0u)
    CY_ISR_PROTO(USB_EP_7_ISR);
#endif /* End USB_EP7_ISR_REMOVE */
#if(USB_EP8_ISR_REMOVE == 0u)
    CY_ISR_PROTO(USB_EP_8_ISR);
#endif /* End USB_EP8_ISR_REMOVE */
CY_ISR_PROTO(USB_BUS_RESET_ISR);
#if(USB_SOF_ISR_REMOVE == 0u)
    CY_ISR_PROTO(USB_SOF_ISR);
#endif /* End USB_SOF_ISR_REMOVE */
#if(USB_EP_MM != USB__EP_MANUAL)
    CY_ISR_PROTO(USB_ARB_ISR);
#endif /* End USB_EP_MM */


/***************************************
* Global data allocation
***************************************/

uint8 USB_initVar = 0u;
#if(USB_EP_MM != USB__EP_MANUAL)
    uint8 USB_DmaChan[USB_MAX_EP];
    uint8 USB_DmaTd[USB_MAX_EP];
#endif /* End USB_EP_MM */


/*******************************************************************************
* Function Name: USB_Start
********************************************************************************
*
* Summary:
*  This function initialize the USB SIE, arbiter and the
*  endpoint APIs, including setting the D+ Pullup
*
* Parameters:
*  device: Contains the device number of the desired device descriptor.
*          The device number can be found in the Device Descriptor Tab of 
*          "Configure" dialog, under the settings of desired Device Descriptor,
*          in the "Device Number" field.
*  mode: The operating voltage. This determines whether the voltage regulator
*        is enabled for 5V operation or if pass through mode is used for 3.3V
*        operation. Symbolic names and their associated values are given in the
*        following table.
*       USB_3V_OPERATION - Disable voltage regulator and pass-thru
*                                       Vcc for pull-up
*       USB_5V_OPERATION - Enable voltage regulator and use
*                                       regulator for pull-up
*       USB_DWR_VDDD_OPERATION - Enable or Disable voltage
*                         regulator depend on Vddd Voltage configuration in DWR.
*
* Return:
*   None.
*
* Global variables:
*  The USB_intiVar variable is used to indicate initial
*  configuration of this component. The variable is initialized to zero (0u)
*  and set to one (1u) the first time USB_Start() is called.
*  This allows for component Re-Start without unnecessary re-initialization
*  in all subsequent calls to the USB_Start() routine.
*  If re-initialization of the component is required the variable should be set
*  to zero before call of UART_Start() routine, or the user may call
*  USB_Init() and USB_InitComponent() as done
*  in the USB_Start() routine.
*
* Side Effects:
*   This function will reset all communication states to default.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void USB_Start(uint8 device, uint8 mode) 
{
    /* If not Initialized then initialize all required hardware and software */
    if(USB_initVar == 0u)
    {
        USB_Init();
        USB_initVar = 1u;
    }
    USB_InitComponent(device, mode);
}


/*******************************************************************************
* Function Name: USB_Init
********************************************************************************
*
* Summary:
*  Initialize component's hardware. Usually called in USB_Start().
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
void USB_Init(void) 
{
    uint8 enableInterrupts;
    #if(USB_EP_MM != USB__EP_MANUAL)
        uint16 i;
    #endif   /* End USB_EP_MM != USB__EP_MANUAL */

    enableInterrupts = CyEnterCriticalSection();

    /* Enable USB block  */
    USB_PM_ACT_CFG_REG |= USB_PM_ACT_EN_FSUSB;
    /* Enable USB block for Standby Power Mode */
    USB_PM_STBY_CFG_REG |= USB_PM_STBY_EN_FSUSB;

    #if(CY_PSOC5A)
        /* Disable USBIO for TO3 */
        USB_PM_AVAIL_CR_REG &= ~USB_PM_AVAIL_EN_FSUSBIO;
    #endif /* End CY_PSOC5A */

    /* Enable core clock */
    USB_USB_CLK_EN_REG = USB_USB_CLK_ENABLE;

    USB_CR1_REG = USB_CR1_ENABLE_LOCK;

    #if(CY_PSOC5A)
        /* Enable USBIO for TO3 */
        USB_PM_AVAIL_CR_REG |= USB_PM_AVAIL_EN_FSUSBIO;
        /* Bus Reset Length, It has correct default value in ES3 */
        USB_BUS_RST_CNT_REG = USB_BUS_RST_COUNT;
    #endif /* End CY_PSOC5A */

    /* ENABLING USBIO PADS IN USB MODE FROM I/O MODE */
    #if(!CY_PSOC5A)
        /* Ensure USB transmit enable is low (USB_USBIO_CR0.ten). - Manual Transmission - Disabled */
        USB_USBIO_CR0_REG &= ~USB_USBIO_CR0_TEN;
        CyDelayUs(0);  /*~50ns delay */
        /* Disable the USBIO by asserting PM.USB_CR0.fsusbio_pd_n(Inverted)
        *  high. This will have been set low by the power manger out of reset.
        *  Also confirm USBIO pull-up disabled
        */
        USB_PM_USB_CR0_REG &= ~(USB_PM_USB_CR0_PD_N |USB_PM_USB_CR0_PD_PULLUP_N);

        /* Select iomode to USB mode*/
        USB_USBIO_CR1_REG &= ~ USB_USBIO_CR1_IOMODE;

        /* Enable the USBIO reference by setting PM.USB_CR0.fsusbio_ref_en.*/
        USB_PM_USB_CR0_REG |= USB_PM_USB_CR0_REF_EN;
        /* The reference will be available 1 us after the regulator is enabled */
        CyDelayUs(1);
        /* OR 40us after power restored */
        CyDelayUs(40);
        /* Ensure the single ended disable bits are low (PRT15.INP_DIS[7:6])(input receiver enabled). */
        USB_DM_INP_DIS_REG &= ~USB_DM_MASK;
        USB_DP_INP_DIS_REG &= ~USB_DP_MASK;

        /* Enable USBIO */
        USB_PM_USB_CR0_REG |= USB_PM_USB_CR0_PD_N;
        CyDelayUs(2);
        /* Set the USBIO pull-up enable */
        USB_PM_USB_CR0_REG |= USB_PM_USB_CR0_PD_PULLUP_N;

    #endif /* End !CY_PSOC5A */

    /* Write WAx */
    CY_SET_REG8(&USB_ARB_RW1_WA_PTR[0u],     0u);
    CY_SET_REG8(&USB_ARB_RW1_WA_MSB_PTR[0u], 0u);

    #if(USB_EP_MM != USB__EP_MANUAL)
        /* Init transfer descriptor. This will be used to detect the DMA state - initialized or not. */
        for (i = 0u; i < USB_MAX_EP; i++)
        {
            USB_DmaTd[i] = DMA_INVALID_TD;
        }
    #endif   /* End USB_EP_MM != USB__EP_MANUAL */

    CyExitCriticalSection(enableInterrupts);


    /* Set the bus reset Interrupt. */
    CyIntSetVector(USB_BUS_RESET_VECT_NUM,   USB_BUS_RESET_ISR);
    CyIntSetPriority(USB_BUS_RESET_VECT_NUM, USB_BUS_RESET_PRIOR);

    /* Set the SOF Interrupt. */
    #if(USB_SOF_ISR_REMOVE == 0u)
        CyIntSetVector(USB_SOF_VECT_NUM,   USB_SOF_ISR);
        CyIntSetPriority(USB_SOF_VECT_NUM, USB_SOF_PRIOR);
    #endif   /* End USB_SOF_ISR_REMOVE */

    /* Set the Control Endpoint Interrupt. */
    CyIntSetVector(USB_EP_0_VECT_NUM,   USB_EP_0_ISR);
    CyIntSetPriority(USB_EP_0_VECT_NUM, USB_EP_0_PRIOR);

    /* Set the Data Endpoint 1 Interrupt. */
    #if(USB_EP1_ISR_REMOVE == 0u)
        CyIntSetVector(USB_EP_1_VECT_NUM,   USB_EP_1_ISR);
        CyIntSetPriority(USB_EP_1_VECT_NUM, USB_EP_1_PRIOR);
    #endif   /* End USB_EP1_ISR_REMOVE */

    /* Set the Data Endpoint 2 Interrupt. */
    #if(USB_EP2_ISR_REMOVE == 0u)
        CyIntSetVector(USB_EP_2_VECT_NUM,   USB_EP_2_ISR);
        CyIntSetPriority(USB_EP_2_VECT_NUM, USB_EP_2_PRIOR);
    #endif   /* End USB_EP2_ISR_REMOVE */

    /* Set the Data Endpoint 3 Interrupt. */
    #if(USB_EP3_ISR_REMOVE == 0u)
        CyIntSetVector(USB_EP_3_VECT_NUM,   USB_EP_3_ISR);
        CyIntSetPriority(USB_EP_3_VECT_NUM, USB_EP_3_PRIOR);
    #endif   /* End USB_EP3_ISR_REMOVE */

    /* Set the Data Endpoint 4 Interrupt. */
    #if(USB_EP4_ISR_REMOVE == 0u)
        CyIntSetVector(USB_EP_4_VECT_NUM,   USB_EP_4_ISR);
        CyIntSetPriority(USB_EP_4_VECT_NUM, USB_EP_4_PRIOR);
    #endif   /* End USB_EP4_ISR_REMOVE */

    /* Set the Data Endpoint 5 Interrupt. */
    #if(USB_EP5_ISR_REMOVE == 0u)
        CyIntSetVector(USB_EP_5_VECT_NUM,   USB_EP_5_ISR);
        CyIntSetPriority(USB_EP_5_VECT_NUM, USB_EP_5_PRIOR);
    #endif   /* End USB_EP5_ISR_REMOVE */

    /* Set the Data Endpoint 6 Interrupt. */
    #if(USB_EP6_ISR_REMOVE == 0u)
        CyIntSetVector(USB_EP_6_VECT_NUM,   USB_EP_6_ISR);
        CyIntSetPriority(USB_EP_6_VECT_NUM, USB_EP_6_PRIOR);
    #endif   /* End USB_EP6_ISR_REMOVE */

     /* Set the Data Endpoint 7 Interrupt. */
    #if(USB_EP7_ISR_REMOVE == 0u)
        CyIntSetVector(USB_EP_7_VECT_NUM,   USB_EP_7_ISR);
        CyIntSetPriority(USB_EP_7_VECT_NUM, USB_EP_7_PRIOR);
    #endif   /* End USB_EP7_ISR_REMOVE */

    /* Set the Data Endpoint 8 Interrupt. */
    #if(USB_EP8_ISR_REMOVE == 0u)
        CyIntSetVector(USB_EP_8_VECT_NUM,   USB_EP_8_ISR);
        CyIntSetPriority(USB_EP_8_VECT_NUM, USB_EP_8_PRIOR);
    #endif   /* End USB_EP8_ISR_REMOVE */

    #if((USB_EP_MM != USB__EP_MANUAL) && (USB_ARB_ISR_REMOVE == 0u))
        /* Set the ARB Interrupt. */
        CyIntSetVector(USB_ARB_VECT_NUM,   USB_ARB_ISR);
        CyIntSetPriority(USB_ARB_VECT_NUM, USB_ARB_PRIOR);
    #endif   /* End USB_EP_MM != USB__EP_MANUAL */

}


/*******************************************************************************
* Function Name: USB_InitComponent
********************************************************************************
*
* Summary:
*  Initialize the component, except for the HW which is done one time in
*  the Start function.  This function pulls up D+.
*
* Parameters:
*  device: Contains the device number of the desired device descriptor.
*          The device number can be found in the Device Descriptor Tab of 
*          "Configure" dialog, under the settings of desired Device Descriptor,
*          in the "Device Number" field.
*  mode: The operating voltage. This determines whether the voltage regulator
*        is enabled for 5V operation or if pass through mode is used for 3.3V
*        operation. Symbolic names and their associated values are given in the
*        following table.
*       USB_3V_OPERATION - Disable voltage regulator and pass-thru
*                                       Vcc for pull-up
*       USB_5V_OPERATION - Enable voltage regulator and use
*                                       regulator for pull-up
*       USB_DWR_VDDD_OPERATION - Enable or Disable voltage
*                         regulator depend on Vddd Voltage configuration in DWR.
*
* Return:
*   None.
*
* Global variables:
*   USB_device: Contains the device number of the desired device
*       descriptor. The device number can be found in the Device Descriptor Tab 
*       of "Configure" dialog, under the settings of desired Device Descriptor,
*       in the "Device Number" field.
*   USB_transferState: This variable used by the communication
*       functions to handle current transfer state. Initialized to
*       TRANS_STATE_IDLE in this API.
*   USB_configuration: Contains current configuration number
*       which is set by the Host using SET_CONFIGURATION request.
*       Initialized to zero in this API.
*   USB_deviceAddress: Contains current device address. This
*       variable is initialized to zero in this API. Host starts to communicate
*      to device with address 0 and then set it to whatever value using
*      SET_ADDRESS request.
*   USB_deviceStatus: initialized to 0.
*       This is two bit variable which contain power status in first bit
*       (DEVICE_STATUS_BUS_POWERED or DEVICE_STATUS_SELF_POWERED) and remote
*       wakeup status (DEVICE_STATUS_REMOTE_WAKEUP) in second bit.
*   USB_lastPacketSize initialized to 0;
*
* Reentrant:
*  No.
*
*******************************************************************************/
void USB_InitComponent(uint8 device, uint8 mode) 
{
    /* Initialize _hidProtocol variable to comply with
    *  HID 7.2.6 Set_Protocol Request:
    *  "When initialized, all devices default to report protocol."
    */
    #if defined(USB_ENABLE_HID_CLASS)
        uint8 interface;

        for (interface = 0u; interface < USB_MAX_INTERFACES_NUMBER; interface++)
        {
            USB_hidProtocol[interface] = USB_PROTOCOL_REPORT;
        }
    #endif /* USB_ENABLE_HID_CLASS */

    /* Enable Interrupts. */
    CyIntEnable(USB_BUS_RESET_VECT_NUM);
    CyIntEnable(USB_EP_0_VECT_NUM);
    #if(USB_EP1_ISR_REMOVE == 0u)
        CyIntEnable(USB_EP_1_VECT_NUM);
    #endif   /* End USB_EP1_ISR_REMOVE */
    #if(USB_EP2_ISR_REMOVE == 0u)
        CyIntEnable(USB_EP_2_VECT_NUM);
    #endif   /* End USB_EP2_ISR_REMOVE */
    #if(USB_EP3_ISR_REMOVE == 0u)
        CyIntEnable(USB_EP_3_VECT_NUM);
    #endif   /* End USB_EP3_ISR_REMOVE */
    #if(USB_EP4_ISR_REMOVE == 0u)
        CyIntEnable(USB_EP_4_VECT_NUM);
    #endif   /* End USB_EP4_ISR_REMOVE */
    #if(USB_EP5_ISR_REMOVE == 0u)
        CyIntEnable(USB_EP_5_VECT_NUM);
    #endif   /* End USB_EP5_ISR_REMOVE */
    #if(USB_EP6_ISR_REMOVE == 0u)
        CyIntEnable(USB_EP_6_VECT_NUM);
    #endif   /* End USB_EP6_ISR_REMOVE */
    #if(USB_EP7_ISR_REMOVE == 0u)
        CyIntEnable(USB_EP_7_VECT_NUM);
    #endif   /* End USB_EP7_ISR_REMOVE */
    #if(USB_EP8_ISR_REMOVE == 0u)
        CyIntEnable(USB_EP_8_VECT_NUM);
    #endif   /* End USB_EP8_ISR_REMOVE */
    #if((USB_EP_MM != USB__EP_MANUAL) && (USB_ARB_ISR_REMOVE == 0u))
        /* usb arb interrupt enable */
        USB_ARB_INT_EN_REG = USB_ARB_INT_MASK;
        CyIntEnable(USB_ARB_VECT_NUM);
    #endif   /* End USB_EP_MM != USB__EP_MANUAL */

    /* Arbiter congiguration for DMA transfers */
    #if(USB_EP_MM != USB__EP_MANUAL)

        #if(USB_EP_MM == USB__EP_DMAMANUAL)
            USB_ARB_CFG_REG = USB_ARB_CFG_MANUAL_DMA;
        #endif   /* End USB_EP_MM == USB__EP_DMAMANUAL */
        #if(USB_EP_MM == USB__EP_DMAAUTO)
            /*Set cfg cmplt this rises DMA request when the full configuration is done */
            USB_ARB_CFG_REG = USB_ARB_CFG_AUTO_DMA | USB_ARB_CFG_AUTO_MEM;
        #endif   /* End USB_EP_MM == USB__EP_DMAAUTO */
    #endif   /* End USB_EP_MM != USB__EP_MANUAL */

    USB_transferState = USB_TRANS_STATE_IDLE;

    /* USB Locking: Enabled, VRegulator: depend on mode or DWR Voltage configuration*/
    switch(mode)
    {
        case USB_3V_OPERATION:
            USB_CR1_REG = USB_CR1_ENABLE_LOCK;
            break;
        case USB_5V_OPERATION:
            USB_CR1_REG = USB_CR1_ENABLE_LOCK | USB_CR1_REG_ENABLE;
            break;
        default:   /*USB_DWR_VDDD_OPERATION */
            #if(USB_VDDD_MV < USB_3500MV)
                USB_CR1_REG = USB_CR1_ENABLE_LOCK;
            #else
                USB_CR1_REG = USB_CR1_ENABLE_LOCK | USB_CR1_REG_ENABLE;
            #endif /* End USB_VDDD_MV < USB_3500MV */
            break;
    }

    /* Record the descriptor selection */
    USB_device = device;

    /* Clear all of the component data */
    USB_configuration = 0u;
    USB_interfaceNumber = 0u;
    USB_configurationChanged = 0u;
    USB_deviceAddress  = 0u;
    USB_deviceStatus = 0u;

    USB_lastPacketSize = 0u;

    /*  ACK Setup, Stall IN/OUT */
    CY_SET_REG8(USB_EP0_CR_PTR, USB_MODE_STALL_IN_OUT);

    /* Enable the SIE with an address 0 */
    CY_SET_REG8(USB_CR0_PTR, USB_CR0_ENABLE);

    /* Workarond for PSOC5LP */
    CyDelayCycles(1);
    
    /* Finally, Enable d+ pullup and select iomode to USB mode*/
    CY_SET_REG8(USB_USBIO_CR1_PTR, USB_USBIO_CR1_USBPUEN);
}


/*******************************************************************************
* Function Name: USB_ReInitComponent
********************************************************************************
*
* Summary:
*  This function reinitialize the component configuration and is
*  intend to be called from the Reset interrupt.
*
* Parameters:
*  None.
*
* Return:
*   None.
*
* Global variables:
*   USB_device: Contains the device number of the desired device 
*		descriptor. The device number can be found in the Device Descriptor Tab 
*       of "Configure" dialog, under the settings of desired Device Descriptor,
*       in the "Device Number" field.
*   USB_transferState: This variable used by the communication
*       functions to handle current transfer state. Initialized to
*       TRANS_STATE_IDLE in this API.
*   USB_configuration: Contains current configuration number
*       which is set by the Host using SET_CONFIGURATION request.
*       Initialized to zero in this API.
*   USB_deviceAddress: Contains current device address. This
*       variable is initialized to zero in this API. Host starts to communicate
*      to device with address 0 and then set it to whatever value using
*      SET_ADDRESS request.
*   USB_deviceStatus: initialized to 0.
*       This is two bit variable which contain power status in first bit
*       (DEVICE_STATUS_BUS_POWERED or DEVICE_STATUS_SELF_POWERED) and remote
*       wakeup status (DEVICE_STATUS_REMOTE_WAKEUP) in second bit.
*   USB_lastPacketSize initialized to 0;
*
* Reentrant:
*  No.
*
*******************************************************************************/
void USB_ReInitComponent() 
{
    /* Initialize _hidProtocol variable to comply with HID 7.2.6 Set_Protocol
    *  Request: "When initialized, all devices default to report protocol."
    */
    #if defined(USB_ENABLE_HID_CLASS)
        uint8 interface;

        for (interface = 0u; interface < USB_MAX_INTERFACES_NUMBER; interface++)
        {
            USB_hidProtocol[interface] = USB_PROTOCOL_REPORT;
        }
    #endif /* USB_ENABLE_HID_CLASS */

    USB_transferState = USB_TRANS_STATE_IDLE;

    /* Clear all of the component data */
    USB_configuration = 0u;
    USB_interfaceNumber = 0u;
    USB_configurationChanged = 0u;
    USB_deviceAddress  = 0u;
    USB_deviceStatus = 0u;

    USB_lastPacketSize = 0u;


    /*  ACK Setup, Stall IN/OUT */
    CY_SET_REG8(USB_EP0_CR_PTR, USB_MODE_STALL_IN_OUT);

    /* Enable the SIE with an address 0 */
    CY_SET_REG8(USB_CR0_PTR, USB_CR0_ENABLE);

}


/*******************************************************************************
* Function Name: USB_Stop
********************************************************************************
*
* Summary:
*  This function shuts down the USB function including to release
*  the D+ Pullup and disabling the SIE.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*   USB_configuration: Contains current configuration number
*       which is set by the Host using SET_CONFIGURATION request.
*       Initialized to zero in this API.
*   USB_deviceAddress: Contains current device address. This
*       variable is initialized to zero in this API. Host starts to communicate
*      to device with address 0 and then set it to whatever value using
*      SET_ADDRESS request.
*   USB_deviceStatus: initialized to 0.
*       This is two bit variable which contain power status in first bit
*       (DEVICE_STATUS_BUS_POWERED or DEVICE_STATUS_SELF_POWERED) and remote
*       wakeup status (DEVICE_STATUS_REMOTE_WAKEUP) in second bit.
*   USB_configurationChanged: This variable is set to one after
*       SET_CONFIGURATION request and cleared in this function.
*   USB_intiVar variable is set to zero
*
*******************************************************************************/
void USB_Stop(void) 
{

    #if(USB_EP_MM != USB__EP_MANUAL)
        USB_Stop_DMA(USB_MAX_EP);     /* Stop all DMAs */
    #endif   /* End USB_EP_MM != USB__EP_MANUAL */

    /* Disable the SIE */
    USB_CR0_REG &= ~USB_CR0_ENABLE;
    /* Disable the d+ pullup */
    USB_USBIO_CR1_REG &= ~USB_USBIO_CR1_USBPUEN;
    #if(CY_PSOC5A)
        /* Disable USBIO block*/
        USB_PM_AVAIL_CR_REG &= ~USB_PM_AVAIL_EN_FSUSBIO;
    #endif /* End CY_PSOC5A */    
    /* Disable USB in ACT PM */
    USB_PM_ACT_CFG_REG &= ~USB_PM_ACT_EN_FSUSB;
    /* Disable USB block for Standby Power Mode */
    USB_PM_STBY_CFG_REG &= ~USB_PM_STBY_EN_FSUSB;

    /* Disable the reset and EP interrupts */
    CyIntDisable(USB_BUS_RESET_VECT_NUM);
    CyIntDisable(USB_EP_0_VECT_NUM);
    #if(USB_EP1_ISR_REMOVE == 0u)
        CyIntDisable(USB_EP_1_VECT_NUM);
    #endif   /* End USB_EP1_ISR_REMOVE */
    #if(USB_EP2_ISR_REMOVE == 0u)
        CyIntDisable(USB_EP_2_VECT_NUM);
    #endif   /* End USB_EP2_ISR_REMOVE */
    #if(USB_EP3_ISR_REMOVE == 0u)
        CyIntDisable(USB_EP_3_VECT_NUM);
    #endif   /* End USB_EP3_ISR_REMOVE */
    #if(USB_EP4_ISR_REMOVE == 0u)
        CyIntDisable(USB_EP_4_VECT_NUM);
    #endif   /* End USB_EP4_ISR_REMOVE */
    #if(USB_EP5_ISR_REMOVE == 0u)
        CyIntDisable(USB_EP_5_VECT_NUM);
    #endif   /* End USB_EP5_ISR_REMOVE */
    #if(USB_EP6_ISR_REMOVE == 0u)
        CyIntDisable(USB_EP_6_VECT_NUM);
    #endif   /* End USB_EP6_ISR_REMOVE */
    #if(USB_EP7_ISR_REMOVE == 0u)
        CyIntDisable(USB_EP_7_VECT_NUM);
    #endif   /* End USB_EP7_ISR_REMOVE */
    #if(USB_EP8_ISR_REMOVE == 0u)
        CyIntDisable(USB_EP_8_VECT_NUM);
    #endif   /* End USB_EP8_ISR_REMOVE */

    /* Clear all of the component data */
    USB_configuration = 0u;
    USB_interfaceNumber = 0u;
    USB_configurationChanged = 0u;
    USB_deviceAddress  = 0u;
    USB_deviceStatus = 0u;
    USB_initVar = 0u;

}


/*******************************************************************************
* Function Name: USB_CheckActivity
********************************************************************************
*
* Summary:
*  Returns the activity status of the bus.  Clears the status hardware to
*  provide fresh activity status on the next call of this routine.
*
* Parameters:
*  None.
*
* Return:
*  1 - If bus activity was detected since the last call to this function
*  0 - If bus activity not was detected since the last call to this function
*
*******************************************************************************/
uint8 USB_CheckActivity(void) 
{
    uint8 r;

    r = CY_GET_REG8(USB_CR1_PTR);
    CY_SET_REG8(USB_CR1_PTR, (r & ~USB_CR1_BUS_ACTIVITY));

    return((r & USB_CR1_BUS_ACTIVITY) >> USB_CR1_BUS_ACTIVITY_SHIFT);
}


/*******************************************************************************
* Function Name: USB_GetConfiguration
********************************************************************************
*
* Summary:
*  Returns the current configuration setting
*
* Parameters:
*  None.
*
* Return:
*  configuration.
*
*******************************************************************************/
uint8 USB_GetConfiguration(void) 
{
    return(USB_configuration);
}


/*******************************************************************************
* Function Name: USB_IsConfigurationChanged
********************************************************************************
*
* Summary:
*  Returns the clear on read configuration state. It is usefull when PC send
*  double SET_CONFIGURATION request with same configuration number.
*
* Parameters:
*  None.
*
* Return:
*  Not zero value when new configuration has been changed, otherwise zero is
*  returned.
*
* Global variables:
*   USB_configurationChanged: This variable is set to one after
*       SET_CONFIGURATION request and cleared in this function.
*
*******************************************************************************/
uint8 USB_IsConfigurationChanged(void) 
{
    uint8 res = 0u;

    if(USB_configurationChanged != 0u)
    {
        res = USB_configurationChanged;
        USB_configurationChanged = 0u;
    }

    return(res);
}


/*******************************************************************************
* Function Name: USB_GetInterfaceSetting
********************************************************************************
*
* Summary:
*  Returns the alternate setting from current interface
*
* Parameters:
*  uint8 interfaceNumber, interface number
*
* Return:
*  Alternate setting.
*
*******************************************************************************/
uint8  USB_GetInterfaceSetting(uint8 interfaceNumber)
                                                    
{
    return(USB_interfaceSetting[interfaceNumber]);
}


/*******************************************************************************
* Function Name: USB_GetEPState
********************************************************************************
*
* Summary:
*  Returned the state of the requested endpoint.
*
* Parameters:
*  epNumber: Endpoint Number
*
* Return:
*  State of the requested endpoint.
*
*******************************************************************************/
uint8 USB_GetEPState(uint8 epNumber) 
{
    return(USB_EP[epNumber].apiEpState);
}


/*******************************************************************************
* Function Name: USB_GetEPCount
********************************************************************************
*
* Summary:
*  This function supports Data Endpoints only(EP1-EP8).
*  Returns the transfer count for the requested endpoint.  The value from
*  the count registers includes 2 counts for the two byte checksum of the
*  packet.  This function subtracts the two counts.
*
* Parameters:
*  epNumber: Data Endpoint Number.
*            Valid values are between 1 and 8.
*
* Return:
*  Returns the current byte count from the specified endpoin or 0 for an
*  invalid endpoint.
*
*******************************************************************************/
uint16 USB_GetEPCount(uint8 epNumber) 
{
    uint8 ri;
    uint16 count = 0u;

    if((epNumber > USB_EP0) && (epNumber < USB_MAX_EP))
    {
        ri = ((epNumber - USB_EP1) << USB_EPX_CNTX_ADDR_SHIFT);

        count = ((uint16)((CY_GET_REG8(&USB_SIE_EP1_CNT0_PTR[ri]) & USB_EPX_CNT0_MASK) << 8u)
                         | CY_GET_REG8(&USB_SIE_EP1_CNT1_PTR[ri]))
                         - USB_EPX_CNTX_CRC_COUNT;
    }
    return(count);
}


#if(USB_EP_MM != USB__EP_MANUAL)


    /*******************************************************************************
    * Function Name: USB_InitEP_DMA
    ********************************************************************************
    *
    * Summary: This function allocate and initializes a EP DMA chanel to be used
    *     by the USB_LoadInEP() or USB_ReadOutEP() APIs.
    *
    * Parameters:
    *  epNumber: Contains the data endpoint number.
    *            Valid values are between 1 and 8.
    *  *pData: A pointer to a data array which will be related to the EP transfers
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void USB_InitEP_DMA(uint8 epNumber, uint8 *pData) 
    {
        uint16 src;
        uint16 dst;
        #if (defined(__C51__))          /* PSoC 3 - Source is Flash */
            src = HI16(CYDEV_SRAM_BASE);
            dst = HI16(CYDEV_PERIPH_BASE);
            pData = pData;
        #else                           /* PSoC 5 */
            if((USB_EP[epNumber].addr & USB_DIR_IN) != 0u )
            {   /* for the IN EP source is the flash memory buffer */
                src = HI16(pData);
                dst = HI16(CYDEV_PERIPH_BASE);
            }
            else
            {   /* for the OUT EP source is the SIE register */
                src = HI16(CYDEV_PERIPH_BASE);
                dst = HI16(pData);
            }
        #endif  /* End C51 */
        switch(epNumber)
        {
            case USB_EP1:
                #if(USB_DMA1_REMOVE == 0u)
                    USB_DmaChan[epNumber] = USB_ep1_DmaInitialize(
                        USB_DMA_BYTES_PER_BURST, USB_DMA_REQUEST_PER_BURST, src, dst);
                #endif   /* End USB_DMA1_REMOVE */
                break;
            case USB_EP2:
                #if(USB_DMA2_REMOVE == 0u)
                    USB_DmaChan[epNumber] = USB_ep2_DmaInitialize(
                        USB_DMA_BYTES_PER_BURST, USB_DMA_REQUEST_PER_BURST, src, dst);
                #endif   /* End USB_DMA2_REMOVE */
                break;
            case USB_EP3:
                #if(USB_DMA3_REMOVE == 0u)
                    USB_DmaChan[epNumber] = USB_ep3_DmaInitialize(
                        USB_DMA_BYTES_PER_BURST, USB_DMA_REQUEST_PER_BURST, src, dst);
                #endif   /* End USB_DMA3_REMOVE */
                break;
            case USB_EP4:
                #if(USB_DMA4_REMOVE == 0u)
                    USB_DmaChan[epNumber] = USB_ep4_DmaInitialize(
                        USB_DMA_BYTES_PER_BURST, USB_DMA_REQUEST_PER_BURST, src, dst);
                #endif   /* End USB_DMA4_REMOVE */
                break;
            case USB_EP5:
                #if(USB_DMA5_REMOVE == 0u)
                    USB_DmaChan[epNumber] = USB_ep5_DmaInitialize(
                        USB_DMA_BYTES_PER_BURST, USB_DMA_REQUEST_PER_BURST, src, dst);
                #endif   /* End USB_DMA5_REMOVE */
                break;
            case USB_EP6:
                #if(USB_DMA6_REMOVE == 0u)
                    USB_DmaChan[epNumber] = USB_ep6_DmaInitialize(
                        USB_DMA_BYTES_PER_BURST, USB_DMA_REQUEST_PER_BURST, src, dst);
                #endif   /* End USB_DMA6_REMOVE */
                break;
            case USB_EP7:
                #if(USB_DMA7_REMOVE == 0u)
                    USB_DmaChan[epNumber] = USB_ep7_DmaInitialize(
                        USB_DMA_BYTES_PER_BURST, USB_DMA_REQUEST_PER_BURST, src, dst);
                #endif   /* End USB_DMA7_REMOVE */
                break;
            case USB_EP8:
                #if(USB_DMA8_REMOVE == 0u)
                    USB_DmaChan[epNumber] = USB_ep8_DmaInitialize(
                        USB_DMA_BYTES_PER_BURST, USB_DMA_REQUEST_PER_BURST, src, dst);
                #endif   /* End USB_DMA8_REMOVE */
                break;
            default:
                /* Do not support EP0 DMA transfers */
                break;
        }
        if((epNumber > USB_EP0) && (epNumber < USB_MAX_EP))
        {
            USB_DmaTd[epNumber] = CyDmaTdAllocate();
        }
    }


    /*******************************************************************************
    * Function Name: USB_Stop_DMA
    ********************************************************************************
    *
    * Summary: Stops and free DMA
    *
    * Parameters:
    *  epNumber: Contains the data endpoint number or
    *           USB_MAX_EP to stop all DMAs
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void USB_Stop_DMA(uint8 epNumber) 
    {
        uint8 i;
        i = (epNumber < USB_MAX_EP) ? epNumber : USB_EP1;
        do
        {
            if(USB_DmaTd[i] != DMA_INVALID_TD)
            {
                CyDmaChDisable(USB_DmaChan[i]);
                CyDmaTdFree(USB_DmaTd[i]);
                USB_DmaTd[i] = DMA_INVALID_TD;
            }
            i++;
        }while((i < USB_MAX_EP) && (epNumber == USB_MAX_EP));
    }

#endif /* End USB_EP_MM != USB__EP_MANUAL */


/*******************************************************************************
* Function Name: USB_LoadInEP
********************************************************************************
*
* Summary:
*  Loads and enables the specified USB data endpoint for an IN interrupt or bulk
*  transfer.
*
* Parameters:
*  epNumber: Contains the data endpoint number.
*            Valid values are between 1 and 8.
*  *pData: A pointer to a data array from which the data for the endpoint space
*          is loaded.
*  length: The number of bytes to transfer from the array and then send as a
*          result of an IN request. Valid values are between 0 and 512.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void USB_LoadInEP(uint8 epNumber, uint8 *pData, uint16 length)
                                                                        
{
    uint8 ri;
    uint8 *p;
    #if(USB_EP_MM == USB__EP_MANUAL)
        uint16 i;
    #endif /* End USB_EP_MM == USB__EP_MANUAL */

    if((epNumber > USB_EP0) && (epNumber < USB_MAX_EP))
    {
        ri = ((epNumber - USB_EP1) << USB_EPX_CNTX_ADDR_SHIFT);
        p = (uint8 *)&USB_ARB_RW1_DR_PTR[ri];

        #if(USB_EP_MM != USB__EP_DMAAUTO)
            /* Limits length to available buffer space, auto MM could send packets up to 1024 bytes */
            if(length > USB_EPX_DATA_BUF_MAX - USB_EP[epNumber].buffOffset)
            {
                length = USB_EPX_DATA_BUF_MAX - USB_EP[epNumber].buffOffset;
            }
        #endif /* End USB_EP_MM != USB__EP_DMAAUTO */

        /* Set the count and data toggle */
        CY_SET_REG8(&USB_SIE_EP1_CNT0_PTR[ri], (length >> 8u) | (USB_EP[epNumber].epToggle));
        CY_SET_REG8(&USB_SIE_EP1_CNT1_PTR[ri],  length & 0xFFu);

        #if(USB_EP_MM == USB__EP_MANUAL)
            if(pData != NULL)
            {
                /* Copy the data using the arbiter data register */
                for (i = 0u; i < length; i++)
                {
                    CY_SET_REG8(p, pData[i]);
                }
            }
            USB_EP[epNumber].apiEpState = USB_NO_EVENT_PENDING;
            /* Write the Mode register */
            USB_SIE_EP1_CR0_PTR[ri] = USB_EP[epNumber].epMode;
        #else
            /*Init DMA if it was not initialized */
            if(USB_DmaTd[epNumber] == DMA_INVALID_TD)
            {
                USB_InitEP_DMA(epNumber, pData);
            }
        #endif /* End USB_EP_MM == USB__EP_MANUAL */

        #if(USB_EP_MM == USB__EP_DMAMANUAL)
            if((pData != NULL) && (length > 0))
            {

                /* Enable DMA in mode2 for transfering data */
                CyDmaChDisable(USB_DmaChan[epNumber]);
                CyDmaTdSetConfiguration(USB_DmaTd[epNumber], length, DMA_INVALID_TD,\
                                                                                    TD_TERMIN_EN | TD_INC_SRC_ADR);
                CyDmaTdSetAddress(USB_DmaTd[epNumber],  LO16((uint32)pData), LO16((uint32)p));
                /* Enable the DMA */
                CyDmaChSetInitialTd(USB_DmaChan[epNumber], USB_DmaTd[epNumber]);
                CyDmaChEnable(USB_DmaChan[epNumber], 1);
                /* Generate DMA request */
                USB_ARB_EP1_CFG_PTR[ri] |= USB_ARB_EPX_CFG_DMA_REQ;
                USB_ARB_EP1_CFG_PTR[ri] &= ~USB_ARB_EPX_CFG_DMA_REQ;
                /* Mode register will be writen in arb ISR after DMA transfer copmlete */
            }
            else
            {
                /* When zero-length packet - write the Mode register directly */
                USB_SIE_EP1_CR0_PTR[ri] = USB_EP[epNumber].epMode;
            }
        #endif /* End USB_EP_MM == USB__EP_DMAMANUAL */

        #if(USB_EP_MM == USB__EP_DMAAUTO)
            if(pData != NULL)
            {
                /* Enable DMA in mode3 for transfering data */
                CyDmaChDisable(USB_DmaChan[epNumber]);
                CyDmaTdSetConfiguration(USB_DmaTd[epNumber], length, USB_DmaTd[epNumber],\
                                                                                    TD_TERMIN_EN | TD_INC_SRC_ADR);
                CyDmaTdSetAddress(USB_DmaTd[epNumber],  LO16((uint32)pData), LO16((uint32)p));
                /* Clear Any potential pending DMA requests before starting the DMA channel to transfer data */
                CyDmaClearPendingDrq(USB_DmaChan[epNumber]);
                /* Enable the DMA */
                CyDmaChSetInitialTd(USB_DmaChan[epNumber], USB_DmaTd[epNumber]);
                CyDmaChEnable(USB_DmaChan[epNumber], 1);
            }
            else
            {
                USB_EP[epNumber].apiEpState = USB_NO_EVENT_PENDING;
                if(length > 0)
                {
                    /* Set Data ready status, This will generate DMA request */
                    USB_ARB_EP1_CFG_PTR[ri] |= USB_ARB_EPX_CFG_IN_DATA_RDY;
                    /* Mode register will be writen in arb ISR(In Buffer Full) after first DMA transfer copmlete */
                }
                else
                {
                    /* When zero-length packet - write the Mode register directly */
                    USB_SIE_EP1_CR0_PTR[ri] = USB_EP[epNumber].epMode;
                }
            }
        #endif /* End USB_EP_MM == USB__EP_DMAAUTO */

    }
}


/*******************************************************************************
* Function Name: USB_ReadOutEP
********************************************************************************
*
* Summary:
*  Read data from an endpoint.  The application must call
*  USB_GetEPState to see if an event is pending.
*
* Parameters:
*  epNumber: Contains the data endpoint number.
*            Valid values are between 1 and 8.
*  pData: A pointer to a data array from which the data for the endpoint space
*         is loaded.
*  length: The number of bytes to transfer from the USB Out enpoint and loads
*          it into data array. Valid values are between 0 and 1023. The function
*          moves fewer than the requested number of bytes if the host sends
*          fewer bytes than requested.
*
* Returns:
*  Number of bytes received, 0 for an invalid endpoint.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint16 USB_ReadOutEP(uint8 epNumber, uint8 *pData, uint16 length)
                                                                        
{
    uint8 ri;
    uint8 *p;
    #if(USB_EP_MM == USB__EP_MANUAL)
        uint16 i;
    #endif /* End USB_EP_MM == USB__EP_MANUAL */
    #if(USB_EP_MM != USB__EP_DMAAUTO)
        uint16 xferCount;
    #endif /* End USB_EP_MM != $INSTANCE_NAME`__EP_DMAAUTO */

    if((epNumber > USB_EP0) && (epNumber < USB_MAX_EP) && (pData != NULL))
    {
        ri = ((epNumber - USB_EP1) << USB_EPX_CNTX_ADDR_SHIFT);
        p = (uint8 *)&USB_ARB_RW1_DR_PTR[ri];

        #if(USB_EP_MM != USB__EP_DMAAUTO)
            /* Determine which is smaller the requested data or the available data */
            xferCount = USB_GetEPCount(epNumber);
            if (length > xferCount)
            {
                length = xferCount;
            }
        #endif /* End USB_EP_MM != USB__EP_DMAAUTO */

        #if(USB_EP_MM == USB__EP_MANUAL)
            /* Copy the data using the arbiter data register */
            for (i = 0u; i < length; i++)
            {
                pData[i] = CY_GET_REG8(p);
            }

            /* (re)arming of OUT endpoint */
            USB_EnableOutEP(epNumber);
        #else
            /*Init DMA if it was not initialized */
            if(USB_DmaTd[epNumber] == DMA_INVALID_TD)
            {
                USB_InitEP_DMA(epNumber, pData);
            }
        #endif /* End USB_EP_MM == USB__EP_MANUAL */

        #if(USB_EP_MM == USB__EP_DMAMANUAL)
            /* Enable DMA in mode2 for transfering data */
            CyDmaChDisable(USB_DmaChan[epNumber]);
            CyDmaTdSetConfiguration(USB_DmaTd[epNumber], length, DMA_INVALID_TD,
                                                                                TD_TERMIN_EN | TD_INC_DST_ADR);
            CyDmaTdSetAddress(USB_DmaTd[epNumber],  LO16((uint32)p), LO16((uint32)pData));
            /* Enable the DMA */
            CyDmaChSetInitialTd(USB_DmaChan[epNumber], USB_DmaTd[epNumber]);
            CyDmaChEnable(USB_DmaChan[epNumber], 1);

            /* Generate DMA request */
            USB_ARB_EP1_CFG_PTR[ri] |= USB_ARB_EPX_CFG_DMA_REQ;
            USB_ARB_EP1_CFG_PTR[ri] &= ~USB_ARB_EPX_CFG_DMA_REQ;
            /* Out EP will be (re)armed in arb ISR after transfer complete */
        #endif /* End USB_EP_MM == USB__EP_DMAMANUAL */

        #if(USB_EP_MM == USB__EP_DMAAUTO)
            /* Enable DMA in mode3 for transfering data */
            CyDmaChDisable(USB_DmaChan[epNumber]);
            CyDmaTdSetConfiguration(USB_DmaTd[epNumber], length, USB_DmaTd[epNumber],
                                                                                TD_TERMIN_EN | TD_INC_DST_ADR);
            CyDmaTdSetAddress(USB_DmaTd[epNumber],  LO16((uint32)p), LO16((uint32)pData));

            /* Clear Any potential pending DMA requests before starting the DMA channel to transfer data */
            CyDmaClearPendingDrq(USB_DmaChan[epNumber]);
            /* Enable the DMA */
            CyDmaChSetInitialTd(USB_DmaChan[epNumber], USB_DmaTd[epNumber]);
            CyDmaChEnable(USB_DmaChan[epNumber], 1);
            /* Out EP will be (re)armed in arb ISR after transfer complete */
        #endif /* End USB_EP_MM == USB__EP_DMAAUTO */

    }
    else
    {
        length = 0;
    }

    return(length);
}


/*******************************************************************************
* Function Name: USB_EnableOutEP
********************************************************************************
*
* Summary:
*  This function enables an OUT endpoint.  It should not be
*  called for an IN endpoint.
*
* Parameters:
*  epNumber: Endpoint Number
*            Valid values are between 1 and 8.
*
* Return:
*   None.
*
* Global variables:
*  USB_EP[epNumber].apiEpState - set to NO_EVENT_PENDING
*
* Reentrant:
*  No.
*
*******************************************************************************/
void USB_EnableOutEP(uint8 epNumber) 
{
    uint8 ri;

    if((epNumber > USB_EP0) && (epNumber < USB_MAX_EP))
    {
        ri = ((epNumber - USB_EP1) << USB_EPX_CNTX_ADDR_SHIFT);
        USB_EP[epNumber].apiEpState = USB_NO_EVENT_PENDING;
        /* Write the Mode register */
        CY_SET_REG8(&USB_SIE_EP1_CR0_PTR[ri], USB_EP[epNumber].epMode);
    }
}


/*******************************************************************************
* Function Name: USB_DisableOutEP
********************************************************************************
*
* Summary:
*  This function disables an OUT endpoint.  It should not be
*  called for an IN endpoint.
*
* Parameters:
*  epNumber: Endpoint Number
*            Valid values are between 1 and 8.
*
* Return:
*  None.
*
*******************************************************************************/
void USB_DisableOutEP(uint8 epNumber) 
{
    uint8 ri ;

    if((epNumber > USB_EP0) && (epNumber < USB_MAX_EP))
    {
        ri = ((epNumber - USB_EP1) << USB_EPX_CNTX_ADDR_SHIFT);
        /* Write the Mode register */
        CY_SET_REG8(&USB_SIE_EP1_CR0_PTR[ri], USB_MODE_NAK_OUT);
    }
}


/*******************************************************************************
* Function Name: USB_Force
********************************************************************************
*
* Summary:
*  Forces the bus state
*
* Parameters:
*  bState
*    USB_FORCE_J
*    USB_FORCE_K
*    USB_FORCE_SE0
*    USB_FORCE_NONE
*
* Return:
*  None.
*
*******************************************************************************/
void USB_Force(uint8 bState) 
{
    CY_SET_REG8(USB_USBIO_CR0_PTR, bState);
}


/*******************************************************************************
* Function Name: USB_GetEPAckState
********************************************************************************
*
* Summary:
*  Returns the ACK of the CR0 Register (ACKD)
*
* Parameters:
*  epNumber: Endpoint Number
*            Valid values are between 1 and 8.
*
* Returns
*  0 if nothing has been ACKD, non-=zero something has been ACKD
*
*******************************************************************************/
uint8 USB_GetEPAckState(uint8 epNumber) 
{
    uint8 ri;
    uint8 cr = 0;

    if((epNumber > USB_EP0) && (epNumber < USB_MAX_EP))
    {
        ri = ((epNumber - USB_EP1) << USB_EPX_CNTX_ADDR_SHIFT);
        cr = CY_GET_REG8(&USB_SIE_EP1_CR0_PTR[ri]) & USB_MODE_ACKD;
    }

    return(cr);
}


/*******************************************************************************
* Function Name: USB_SetPowerStatus
********************************************************************************
*
* Summary:
*  Sets the device power status for reporting in the Get Device Status
*  request
*
* Parameters:
*  powerStatus: USB_DEVICE_STATUS_BUS_POWERED(0) - Bus Powered,
*               USB_DEVICE_STATUS_SELF_POWERED(1) - Self Powered
*
* Return:
*   None.
*
* Global variables:
*  USB_deviceStatus - set power status
*
* Reentrant:
*  No.
*
*******************************************************************************/
void USB_SetPowerStatus(uint8 powerStatus) 
{
    if (powerStatus != USB_DEVICE_STATUS_BUS_POWERED)
    {
        USB_deviceStatus |=  USB_DEVICE_STATUS_SELF_POWERED;
    }
    else
    {
        USB_deviceStatus &=  ~USB_DEVICE_STATUS_SELF_POWERED;
    }
}


#if (USB_MON_VBUS == 1u)

    /*******************************************************************************
    * Function Name: USB_VBusPresent
    ********************************************************************************
    *
    * Summary:
    *  Determines VBUS presence for Self Powered Devices.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  1 if VBUS is present, otherwise 0.
    *
    *******************************************************************************/
    uint8 USB_VBusPresent(void) 
    {
        return((CY_GET_REG8(USB_VBUS_PS_PTR) & USB_VBUS_MASK) ? 1u : 0u);
    }

#endif /* USB_MON_VBUS */


/*******************************************************************************
* Function Name: USB_RWUEnabled
********************************************************************************
*
* Summary:
*  Returns TRUE if Remote Wake Up is enabled, otherwise FALSE
*
* Parameters:
*   None.
*
* Return:
*  TRUE -  Remote Wake Up Enabled
*  FALSE - Remote Wake Up Disabled
*
* Global variables:
*  USB_deviceStatus - checked to determine remote status
*
*******************************************************************************/
uint8 USB_RWUEnabled(void) 
{
    uint8 result = USB_FALSE;
    if((USB_deviceStatus & USB_DEVICE_STATUS_REMOTE_WAKEUP) != 0u)
    {
        result = USB_TRUE;
    }

    return(result);
}


/* [] END OF FILE */
