/*******************************************************************************
* File Name: USB_episr.c
* Version 2.50
*
* Description:
*  Data endpoint Interrupt Service Routines
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
* Custom Declarations
***************************************/
/* `#START CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */


/***************************************
* External function references
***************************************/

void USB_InitComponent(uint8 device, uint8 mode) ;
void USB_ReInitComponent(void) ;
#if defined(USB_ENABLE_MIDI_STREAMING) && (USB_ENABLE_MIDI_API != 0u)
    void USB_MIDI_OUT_EP_Service(void) ;
#endif /* End USB_ENABLE_MIDI_STREAMING*/


/***************************************
* External references
***************************************/

extern volatile T_USB_EP_CTL_BLOCK USB_EP[];
extern volatile uint8 USB_device;
#if defined(USB_ENABLE_MIDI_STREAMING) && (USB_ENABLE_MIDI_API != 0u)
    extern volatile uint8 USB_midi_out_ep;
    extern volatile uint8 USB_midi_in_ep;
    #if USB_MIDI_IN_BUFF_SIZE >= 256
        extern volatile uint16 USB_midiInPointer;     /* Input endpoint buffer pointer */
    #else
        extern volatile uint8 USB_midiInPointer;      /* Input endpoint buffer pointer */
    #endif /* End USB_MIDI_IN_BUFF_SIZE >=256 */    
#endif /* End USB_ENABLE_MIDI_STREAMING*/

#if(USB_EP1_ISR_REMOVE == 0u)


    /******************************************************************************
    * Function Name: USB_EP_1_ISR
    *******************************************************************************
    *
    * Summary:
    *  Endpoint 1 Interrupt Service Routine
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    ******************************************************************************/
    CY_ISR(USB_EP_1_ISR)
    {
        #if defined(USB_ENABLE_MIDI_STREAMING) && (USB_ENABLE_MIDI_API != 0u) && \
            (USB_EP_MM == USB__EP_DMAAUTO) && (CY_PSOC3)
            uint8 int_en;
        #endif /* CY_PSOC3 & ENABLE_MIDI_STREAMING */
    
        /* `#START EP1_USER_CODE` Place your code here */

        /* `#END` */

        #if defined(USB_ENABLE_MIDI_STREAMING) && (USB_ENABLE_MIDI_API != 0u) && \
            (USB_EP_MM == USB__EP_DMAAUTO) && (CY_PSOC3)
            int_en = EA;
            CyGlobalIntEnable;  /* Make sure nested interrupt is enabled */
        #endif /* CY_PSOC3 & ENABLE_MIDI_STREAMING */

        CY_GET_REG8(USB_SIE_EP1_CR0_PTR); /* Must read the mode reg */
        /* Do not toggle ISOC endpoint */
        if((USB_EP[USB_EP1].attrib & USB_EP_TYPE_MASK) !=
                                                                                    USB_EP_TYPE_ISOC)
        {
            USB_EP[USB_EP1].epToggle ^= USB_EPX_CNT_DATA_TOGGLE;
        }
        USB_EP[USB_EP1].apiEpState = USB_EVENT_PENDING;
        CY_SET_REG8(USB_SIE_EP_INT_SR_PTR, CY_GET_REG8(USB_SIE_EP_INT_SR_PTR)
                                                                            & ~USB_SIE_EP_INT_EP1_MASK);

        #if defined(USB_ENABLE_MIDI_STREAMING) && (USB_ENABLE_MIDI_API != 0u) && \
            (USB_EP_MM == USB__EP_DMAAUTO) 
            if(USB_midi_out_ep == USB_EP1)
            {
                USB_MIDI_OUT_EP_Service();
            }   
        #endif /* End USB_ENABLE_MIDI_STREAMING*/

        /* `#START EP1_END_USER_CODE` Place your code here */

        /* `#END` */

        #if defined(USB_ENABLE_MIDI_STREAMING) && (USB_ENABLE_MIDI_API != 0u) && \
            (USB_EP_MM == USB__EP_DMAAUTO) && (CY_PSOC3)
            EA = int_en;
        #endif /* CY_PSOC3 & ENABLE_MIDI_STREAMING */
    }

#endif   /* End USB_EP1_ISR_REMOVE */


#if(USB_EP2_ISR_REMOVE == 0u)

    /*******************************************************************************
    * Function Name: USB_EP_2_ISR
    ********************************************************************************
    *
    * Summary:
    *  Endpoint 2 Interrupt Service Routine
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    CY_ISR(USB_EP_2_ISR)
    {
        #if defined(USB_ENABLE_MIDI_STREAMING) && (USB_ENABLE_MIDI_API != 0u) && \
            (USB_EP_MM == USB__EP_DMAAUTO) && (CY_PSOC3)
            uint8 int_en;
        #endif /* CY_PSOC3 & ENABLE_MIDI_STREAMING */
    
        /* `#START EP2_USER_CODE` Place your code here */

        /* `#END` */

        #if defined(USB_ENABLE_MIDI_STREAMING) && (USB_ENABLE_MIDI_API != 0u) && \
            (USB_EP_MM == USB__EP_DMAAUTO) && (CY_PSOC3)
            int_en = EA;
            CyGlobalIntEnable;  /* Make sure nested interrupt is enabled */
        #endif /* CY_PSOC3 & ENABLE_MIDI_STREAMING */

        CY_GET_REG8(USB_SIE_EP2_CR0_PTR); /* Must read the mode reg */
        /* Do not toggle ISOC endpoint */
        if((USB_EP[USB_EP2].attrib & USB_EP_TYPE_MASK) !=
                                                                                    USB_EP_TYPE_ISOC)
        {
            USB_EP[USB_EP2].epToggle ^= USB_EPX_CNT_DATA_TOGGLE;
        }
        USB_EP[USB_EP2].apiEpState = USB_EVENT_PENDING;
        CY_SET_REG8(USB_SIE_EP_INT_SR_PTR, CY_GET_REG8(USB_SIE_EP_INT_SR_PTR)
                                                                        & ~USB_SIE_EP_INT_EP2_MASK);

        #if defined(USB_ENABLE_MIDI_STREAMING) && (USB_ENABLE_MIDI_API != 0u) && \
            (USB_EP_MM == USB__EP_DMAAUTO)
            if(USB_midi_out_ep == USB_EP2)
            {
                USB_MIDI_OUT_EP_Service();
            }   
        #endif /* End USB_ENABLE_MIDI_STREAMING*/

        /* `#START EP2_END_USER_CODE` Place your code here */

        /* `#END` */

        #if defined(USB_ENABLE_MIDI_STREAMING) && (USB_ENABLE_MIDI_API != 0u) && \
            (USB_EP_MM == USB__EP_DMAAUTO) && (CY_PSOC3)
            EA = int_en;
        #endif /* CY_PSOC3 & ENABLE_MIDI_STREAMING */
    }

#endif   /* End USB_EP2_ISR_REMOVE */


#if(USB_EP3_ISR_REMOVE == 0u)

    /*******************************************************************************
    * Function Name: USB_EP_3_ISR
    ********************************************************************************
    *
    * Summary:
    *  Endpoint 3 Interrupt Service Routine
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    CY_ISR(USB_EP_3_ISR)
    {
        #if defined(USB_ENABLE_MIDI_STREAMING) && (USB_ENABLE_MIDI_API != 0u) && \
            (USB_EP_MM == USB__EP_DMAAUTO) && (CY_PSOC3)
            uint8 int_en;
        #endif /* CY_PSOC3 & ENABLE_MIDI_STREAMING */
    
        /* `#START EP3_USER_CODE` Place your code here */

        /* `#END` */

        #if defined(USB_ENABLE_MIDI_STREAMING) && (USB_ENABLE_MIDI_API != 0u) && \
            (USB_EP_MM == USB__EP_DMAAUTO) && (CY_PSOC3)
            int_en = EA;
            CyGlobalIntEnable;  /* Make sure nested interrupt is enabled */
        #endif /* CY_PSOC3 & ENABLE_MIDI_STREAMING */

        CY_GET_REG8(USB_SIE_EP3_CR0_PTR); /* Must read the mode reg */
        /* Do not toggle ISOC endpoint */
        if((USB_EP[USB_EP3].attrib & USB_EP_TYPE_MASK) !=
                                                                                    USB_EP_TYPE_ISOC)
        {
            USB_EP[USB_EP3].epToggle ^= USB_EPX_CNT_DATA_TOGGLE;
        }
        USB_EP[USB_EP3].apiEpState = USB_EVENT_PENDING;
        CY_SET_REG8(USB_SIE_EP_INT_SR_PTR, CY_GET_REG8(USB_SIE_EP_INT_SR_PTR)
                                                                        & ~USB_SIE_EP_INT_EP3_MASK);

        #if defined(USB_ENABLE_MIDI_STREAMING) && (USB_ENABLE_MIDI_API != 0u) && \
            (USB_EP_MM == USB__EP_DMAAUTO) 
            if(USB_midi_out_ep == USB_EP3)
            {
                USB_MIDI_OUT_EP_Service();
            }   
        #endif /* End USB_ENABLE_MIDI_STREAMING*/

        /* `#START EP3_END_USER_CODE` Place your code here */

        /* `#END` */

        #if defined(USB_ENABLE_MIDI_STREAMING) && (USB_ENABLE_MIDI_API != 0u) && \
            (USB_EP_MM == USB__EP_DMAAUTO) && (CY_PSOC3)
            EA = int_en;
        #endif /* CY_PSOC3 & ENABLE_MIDI_STREAMING */
    }

#endif   /* End USB_EP3_ISR_REMOVE */


#if(USB_EP4_ISR_REMOVE == 0u)

    /*******************************************************************************
    * Function Name: USB_EP_4_ISR
    ********************************************************************************
    *
    * Summary:
    *  Endpoint 4 Interrupt Service Routine
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    CY_ISR(USB_EP_4_ISR)
    {
        #if defined(USB_ENABLE_MIDI_STREAMING) && (USB_ENABLE_MIDI_API != 0u) && \
            (USB_EP_MM == USB__EP_DMAAUTO) && (CY_PSOC3)
            uint8 int_en;
        #endif /* CY_PSOC3 & ENABLE_MIDI_STREAMING */
    
        /* `#START EP4_USER_CODE` Place your code here */

        /* `#END` */

        #if defined(USB_ENABLE_MIDI_STREAMING) && (USB_ENABLE_MIDI_API != 0u) && \
            (USB_EP_MM == USB__EP_DMAAUTO) && (CY_PSOC3)
            int_en = EA;
            CyGlobalIntEnable;  /* Make sure nested interrupt is enabled */
        #endif /* CY_PSOC3 & ENABLE_MIDI_STREAMING */

        CY_GET_REG8(USB_SIE_EP4_CR0_PTR); /* Must read the mode reg */
        /* Do not toggle ISOC endpoint */
        if((USB_EP[USB_EP4].attrib & USB_EP_TYPE_MASK) !=
                                                                                    USB_EP_TYPE_ISOC)
        {
            USB_EP[USB_EP4].epToggle ^= USB_EPX_CNT_DATA_TOGGLE;
        }
        USB_EP[USB_EP4].apiEpState = USB_EVENT_PENDING;
        CY_SET_REG8(USB_SIE_EP_INT_SR_PTR, CY_GET_REG8(USB_SIE_EP_INT_SR_PTR)
                                                                        & ~USB_SIE_EP_INT_EP4_MASK);

        #if defined(USB_ENABLE_MIDI_STREAMING) && (USB_ENABLE_MIDI_API != 0u) && \
            (USB_EP_MM == USB__EP_DMAAUTO) 
            if(USB_midi_out_ep == USB_EP4)
            {
                USB_MIDI_OUT_EP_Service();
            }   
        #endif /* End USB_ENABLE_MIDI_STREAMING*/

        /* `#START EP4_END_USER_CODE` Place your code here */

        /* `#END` */

        #if defined(USB_ENABLE_MIDI_STREAMING) && (USB_ENABLE_MIDI_API != 0u) && \
            (USB_EP_MM == USB__EP_DMAAUTO) && (CY_PSOC3)
            EA = int_en;
        #endif /* CY_PSOC3 & ENABLE_MIDI_STREAMING */
    }

#endif   /* End USB_EP4_ISR_REMOVE */


#if(USB_EP5_ISR_REMOVE == 0u)

    /*******************************************************************************
    * Function Name: USB_EP_5_ISR
    ********************************************************************************
    *
    * Summary:
    *  Endpoint 5 Interrupt Service Routine
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    CY_ISR(USB_EP_5_ISR)
    {
        #if defined(USB_ENABLE_MIDI_STREAMING) && (USB_ENABLE_MIDI_API != 0u) && \
            (USB_EP_MM == USB__EP_DMAAUTO) && (CY_PSOC3)
            uint8 int_en;
        #endif /* CY_PSOC3 & ENABLE_MIDI_STREAMING */
    
        /* `#START EP5_USER_CODE` Place your code here */

        /* `#END` */

        #if defined(USB_ENABLE_MIDI_STREAMING) && (USB_ENABLE_MIDI_API != 0u) && \
            (USB_EP_MM == USB__EP_DMAAUTO) && (CY_PSOC3)
            int_en = EA;
            CyGlobalIntEnable;  /* Make sure nested interrupt is enabled */
        #endif /* CY_PSOC3 & ENABLE_MIDI_STREAMING */

        CY_GET_REG8(USB_SIE_EP5_CR0_PTR); /* Must read the mode reg */
        /* Do not toggle ISOC endpoint */
        if((USB_EP[USB_EP5].attrib & USB_EP_TYPE_MASK) !=
                                                                                    USB_EP_TYPE_ISOC)
        {
            USB_EP[USB_EP5].epToggle ^= USB_EPX_CNT_DATA_TOGGLE;
        }
        USB_EP[USB_EP5].apiEpState = USB_EVENT_PENDING;
        CY_SET_REG8(USB_SIE_EP_INT_SR_PTR, CY_GET_REG8(USB_SIE_EP_INT_SR_PTR)
                                                                        & ~USB_SIE_EP_INT_EP5_MASK);

        #if defined(USB_ENABLE_MIDI_STREAMING) && (USB_ENABLE_MIDI_API != 0u) && \
            (USB_EP_MM == USB__EP_DMAAUTO) 
            if(USB_midi_out_ep == USB_EP5)
            {
                USB_MIDI_OUT_EP_Service();
            }   
        #endif /* End USB_ENABLE_MIDI_STREAMING*/

        /* `#START EP5_END_USER_CODE` Place your code here */

        /* `#END` */

        #if defined(USB_ENABLE_MIDI_STREAMING) && (USB_ENABLE_MIDI_API != 0u) && \
            (USB_EP_MM == USB__EP_DMAAUTO) && (CY_PSOC3)
            EA = int_en;
        #endif /* CY_PSOC3 & ENABLE_MIDI_STREAMING */
    }
#endif   /* End USB_EP5_ISR_REMOVE */


#if(USB_EP6_ISR_REMOVE == 0u)

    /*******************************************************************************
    * Function Name: USB_EP_6_ISR
    ********************************************************************************
    *
    * Summary:
    *  Endpoint 6 Interrupt Service Routine
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    CY_ISR(USB_EP_6_ISR)
    {
        #if defined(USB_ENABLE_MIDI_STREAMING) && (USB_ENABLE_MIDI_API != 0u) && \
            (USB_EP_MM == USB__EP_DMAAUTO) && (CY_PSOC3)
            uint8 int_en;
        #endif /* CY_PSOC3 & ENABLE_MIDI_STREAMING */
    
        /* `#START EP6_USER_CODE` Place your code here */

        /* `#END` */

        #if defined(USB_ENABLE_MIDI_STREAMING) && (USB_ENABLE_MIDI_API != 0u) && \
            (USB_EP_MM == USB__EP_DMAAUTO) && (CY_PSOC3)
            int_en = EA;
            CyGlobalIntEnable;  /* Make sure nested interrupt is enabled */
        #endif /* CY_PSOC3 & ENABLE_MIDI_STREAMING */

        CY_GET_REG8(USB_SIE_EP6_CR0_PTR); /* Must read the mode reg */
        /* Do not toggle ISOC endpoint */
        if((USB_EP[USB_EP6].attrib & USB_EP_TYPE_MASK) !=
                                                                                    USB_EP_TYPE_ISOC)
        {
            USB_EP[USB_EP6].epToggle ^= USB_EPX_CNT_DATA_TOGGLE;
        }
        USB_EP[USB_EP6].apiEpState = USB_EVENT_PENDING;
        CY_SET_REG8(USB_SIE_EP_INT_SR_PTR, CY_GET_REG8(USB_SIE_EP_INT_SR_PTR)
                                                                        & ~USB_SIE_EP_INT_EP6_MASK);

        #if defined(USB_ENABLE_MIDI_STREAMING) && (USB_ENABLE_MIDI_API != 0u) && \
            (USB_EP_MM == USB__EP_DMAAUTO) 
            if(USB_midi_out_ep == USB_EP6)
            {
                USB_MIDI_OUT_EP_Service();
            }   
        #endif /* End USB_ENABLE_MIDI_STREAMING*/

        /* `#START EP6_END_USER_CODE` Place your code here */

        /* `#END` */

        #if defined(USB_ENABLE_MIDI_STREAMING) && (USB_ENABLE_MIDI_API != 0u) && \
            (USB_EP_MM == USB__EP_DMAAUTO) && (CY_PSOC3)
            EA = int_en;
        #endif /* CY_PSOC3 & ENABLE_MIDI_STREAMING */
    }

#endif   /* End USB_EP6_ISR_REMOVE */


#if(USB_EP7_ISR_REMOVE == 0u)

    /*******************************************************************************
    * Function Name: USB_EP_7_ISR
    ********************************************************************************
    *
    * Summary:
    *  Endpoint 7 Interrupt Service Routine
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    CY_ISR(USB_EP_7_ISR)
    {
        #if defined(USB_ENABLE_MIDI_STREAMING) && (USB_ENABLE_MIDI_API != 0u) && \
            (USB_EP_MM == USB__EP_DMAAUTO) && (CY_PSOC3)
            uint8 int_en;
        #endif /* CY_PSOC3 & ENABLE_MIDI_STREAMING */
    
        /* `#START EP7_USER_CODE` Place your code here */

        /* `#END` */

        #if defined(USB_ENABLE_MIDI_STREAMING) && (USB_ENABLE_MIDI_API != 0u) && \
            (USB_EP_MM == USB__EP_DMAAUTO) && (CY_PSOC3)
            int_en = EA;
            CyGlobalIntEnable;  /* Make sure nested interrupt is enabled */
        #endif /* CY_PSOC3 & ENABLE_MIDI_STREAMING */

        CY_GET_REG8(USB_SIE_EP7_CR0_PTR); /* Must read the mode reg */
        /* Do not toggle ISOC endpoint */
        if((USB_EP[USB_EP7].attrib & USB_EP_TYPE_MASK) !=
                                                                                    USB_EP_TYPE_ISOC)
        {
            USB_EP[USB_EP7].epToggle ^= USB_EPX_CNT_DATA_TOGGLE;
        }
        USB_EP[USB_EP7].apiEpState = USB_EVENT_PENDING;
        CY_SET_REG8(USB_SIE_EP_INT_SR_PTR, CY_GET_REG8(USB_SIE_EP_INT_SR_PTR)
                                                                        & ~USB_SIE_EP_INT_EP7_MASK);

        #if defined(USB_ENABLE_MIDI_STREAMING) && (USB_ENABLE_MIDI_API != 0u) && \
            (USB_EP_MM == USB__EP_DMAAUTO) 
            if(USB_midi_out_ep == USB_EP7)
            {
                USB_MIDI_OUT_EP_Service();
            }   
        #endif /* End USB_ENABLE_MIDI_STREAMING*/

        /* `#START EP7_END_USER_CODE` Place your code here */

        /* `#END` */

        #if defined(USB_ENABLE_MIDI_STREAMING) && (USB_ENABLE_MIDI_API != 0u) && \
            (USB_EP_MM == USB__EP_DMAAUTO) && (CY_PSOC3)
            EA = int_en;
        #endif /* CY_PSOC3 & ENABLE_MIDI_STREAMING */
    }

#endif   /* End USB_EP7_ISR_REMOVE */


#if(USB_EP8_ISR_REMOVE == 0u)

    /*******************************************************************************
    * Function Name: USB_EP_8_ISR
    ********************************************************************************
    *
    * Summary:
    *  Endpoint 8 Interrupt Service Routine
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    CY_ISR(USB_EP_8_ISR)
    {
        #if defined(USB_ENABLE_MIDI_STREAMING) && (USB_ENABLE_MIDI_API != 0u) && \
            (USB_EP_MM == USB__EP_DMAAUTO) && (CY_PSOC3)
            uint8 int_en;
        #endif /* CY_PSOC3 & ENABLE_MIDI_STREAMING */
    
        /* `#START EP8_USER_CODE` Place your code here */

        /* `#END` */

        #if defined(USB_ENABLE_MIDI_STREAMING) && (USB_ENABLE_MIDI_API != 0u) && \
            (USB_EP_MM == USB__EP_DMAAUTO) && (CY_PSOC3)
            int_en = EA;
            CyGlobalIntEnable;  /* Make sure nested interrupt is enabled */
        #endif /* CY_PSOC3 & ENABLE_MIDI_STREAMING */

        CY_GET_REG8(USB_SIE_EP8_CR0_PTR); /* Must read the mode reg */
        /* Do not toggle ISOC endpoint */
        if((USB_EP[USB_EP8].attrib & USB_EP_TYPE_MASK) !=
                                                                                    USB_EP_TYPE_ISOC)
        {
            USB_EP[USB_EP8].epToggle ^= USB_EPX_CNT_DATA_TOGGLE;
        }
        USB_EP[USB_EP8].apiEpState = USB_EVENT_PENDING;
        CY_SET_REG8(USB_SIE_EP_INT_SR_PTR, CY_GET_REG8(USB_SIE_EP_INT_SR_PTR)
                                                                        & ~USB_SIE_EP_INT_EP8_MASK);

        #if defined(USB_ENABLE_MIDI_STREAMING) && (USB_ENABLE_MIDI_API != 0u) && \
            (USB_EP_MM == USB__EP_DMAAUTO) 
            if(USB_midi_out_ep == USB_EP8)
            {
                USB_MIDI_OUT_EP_Service();
            }   
        #endif /* End USB_ENABLE_MIDI_STREAMING*/

        /* `#START EP8_END_USER_CODE` Place your code here */

        /* `#END` */

        #if defined(USB_ENABLE_MIDI_STREAMING) && (USB_ENABLE_MIDI_API != 0u) && \
            (USB_EP_MM == USB__EP_DMAAUTO) && (CY_PSOC3)
            EA = int_en;
        #endif /* CY_PSOC3 & ENABLE_MIDI_STREAMING */
    }

#endif   /* End USB_EP8_ISR_REMOVE */


/*******************************************************************************
* Function Name: USB_SOF_ISR
********************************************************************************
*
* Summary:
*  Start of Frame Interrupt Service Routine
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
CY_ISR(USB_SOF_ISR)
{
    /* `#START SOF_USER_CODE` Place your code here */

    /* `#END` */
}


/*******************************************************************************
* Function Name: USB_BUS_RESET_ISR
********************************************************************************
*
* Summary:
*  USB Bus Reset Interrupt Service Routine.  Calls _Start with the same
*  parameters as the last USER call to _Start
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
CY_ISR(USB_BUS_RESET_ISR)
{
    /* `#START BUS_RESET_USER_CODE` Place your code here */

    /* `#END` */

    USB_ReInitComponent();
}


#if((USB_EP_MM != USB__EP_MANUAL) && (USB_ARB_ISR_REMOVE == 0u))


    /*******************************************************************************
    * Function Name: USB_ARB_ISR
    ********************************************************************************
    *
    * Summary:
    *  Arbiter Interrupt Service Routine
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Side effect:
    *  Search for EP8 int_status will be much slower than search for EP1 int_status.
    *
    *******************************************************************************/
    CY_ISR(USB_ARB_ISR)
    {
        uint8 int_status;
        uint8 ep_status;
        uint8 ep = USB_EP1;
        uint8 ptr = 0u;

        /* `#START ARB_BEGIN_USER_CODE` Place your code here */

        /* `#END` */

        int_status = USB_ARB_INT_SR_REG;                   /* read Arbiter Status Register */
        USB_ARB_INT_SR_REG = int_status;                   /* Clear Serviced Interrupts */

        while(int_status != 0u)
        {
            if(int_status & 1u)  /* If EpX interrupt present */
            {
                ep_status  = USB_ARB_EP1_SR_PTR[ptr];       /* read Endpoint Status Register */
                /* If In Buffer Full */
                if(ep_status & USB_ARB_EPX_SR_IN_BUF_FULL)
                {
                   if(USB_EP[ep].addr & USB_DIR_IN)
                    {
                        /* Write the Mode register */
                        USB_SIE_EP1_CR0_PTR[ptr] = USB_EP[ep].epMode;
                        /* Clear Data ready status*/
                        USB_ARB_EP1_CFG_PTR[ptr] &= ~USB_ARB_EPX_CFG_IN_DATA_RDY;
                        #if defined(USB_ENABLE_MIDI_STREAMING) && (USB_ENABLE_MIDI_API != 0u)
                            if(ep == USB_midi_in_ep)
                            {   /* Clear MIDI input pointer*/
                                USB_midiInPointer = 0u;
                            }
                        #endif /* End USB_ENABLE_MIDI_STREAMING*/
                    }
                }
                /* (re)arm Out EP only for mode2 */
                #if(USB_EP_MM != USB__EP_DMAAUTO)
                    /* If DMA Grant */
                    if(ep_status & USB_ARB_EPX_SR_DMA_GNT)
                    {
                        if((USB_EP[ep].addr & USB_DIR_IN) == 0u)
                        {
                                USB_EP[ep].apiEpState = USB_NO_EVENT_PENDING;
                                /* Write the Mode register */
                                USB_SIE_EP1_CR0_PTR[ptr] = USB_EP[ep].epMode;
                        }
                    }
                #endif /* End USB_EP_MM */

                /* `#START ARB_USER_CODE` Place your code here for handle Buffer Underflow/Overflow */

                /* `#END` */

                USB_ARB_EP1_SR_PTR[ptr] = ep_status;       /* Clear Serviced events */
            }
            ptr += USB_EPX_CNTX_ADDR_OFFSET;               /* prepare pointer for next EP */
            ep++;
            int_status >>= 1;
        }

        /* `#START ARB_END_USER_CODE` Place your code here */

        /* `#END` */
    }

#endif /* End USB_EP_MM */


/* [] END OF FILE */
