/*******************************************************************************
* File Name: USB_pm.c
* Version 2.50
*
* Description:
*  This file provides Suspend/Resume APIs functionality.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include <device.h>
#include "USB.h"


/***************************************
* Custom Declarations
***************************************/
/* `#START PM_CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */


/***************************************
* Local data allocation
***************************************/

static USB_BACKUP_STRUCT  USB_backup;


/***************************************
* External data references
***************************************/

extern volatile uint8 USB_configuration;


/***************************************
* External function references
***************************************/

extern void USB_ConfigReg(void) ;
#if(USB_EP_MM != USB__EP_MANUAL)
    extern void USB_Stop_DMA(uint8 epNumber) ;
#endif   /* End USB_EP_MM != USB__EP_MANUAL */

#if((USB_DP_ISR_REMOVE == 0u) && (!CY_PSOC5A))


    /*******************************************************************************
    * Function Name: USB_DP_Interrupt
    ********************************************************************************
    *
    * Summary:
    *  This Interrupt Service Routine handles DP pin changes for wake-up from
    *  the sleep mode.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    CY_ISR(USB_DP_ISR)
    {
        /* `#START DP_USER_CODE` Place your code here */

        /* `#END` */

        /* Clears active interrupt */
        CY_GET_REG8(USB_DP_INTSTAT_PTR);
    }

#endif /* (USB_DP_ISR_REMOVE == 0u) && (!CY_PSOC5A) */


/*******************************************************************************
* Function Name: USB_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration.
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
void USB_SaveConfig(void) 
{

}


/*******************************************************************************
* Function Name: USB_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
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
void USB_RestoreConfig(void) 
{
    if(USB_configuration != 0)
    {
        USB_ConfigReg();    
    }
}


/*******************************************************************************
* Function Name: USB_Suspend
********************************************************************************
*
* Summary:
*  This function disables the USBFS block and prepares for power donwn mode.
*
* Parameters:
*  None.
*
* Return:
*   None.
*
* Global variables:
*  USB_backup.enable:  modified.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void USB_Suspend(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    if((CY_GET_REG8(USB_CR0_PTR) & USB_CR0_ENABLE) != 0u)
    {   /* USB block is enabled */
        USB_backup.enableState = 1u;

        #if(USB_EP_MM != USB__EP_MANUAL)
            USB_Stop_DMA(USB_MAX_EP);     /* Stop all DMAs */
        #endif   /* End USB_EP_MM != USB__EP_MANUAL */

        #if(CY_PSOC5A)
            /* Disable USBIO block */
            USB_PM_AVAIL_CR_REG &= ~USB_PM_AVAIL_EN_FSUSBIO;
        #endif /* End CY_PSOC5A */

        /* Power Down Sequencing for USBIO for TO4*/
        #if(!CY_PSOC5A)
            /* Ensure USB transmit enable is low (USB_USBIO_CR0.ten). - Manual Transmission - Disabled */
            USB_USBIO_CR0_REG &= ~USB_USBIO_CR0_TEN;
            CyDelayUs(0);  /*~50ns delay */

            /* Disable the USBIO by asserting PM.USB_CR0.fsusbio_pd_n(Inverted) and pd_pullup_hv(Inverted) high. */
            USB_PM_USB_CR0_REG &= \
                                    ~(USB_PM_USB_CR0_PD_N | USB_PM_USB_CR0_PD_PULLUP_N);
         #endif /* End !CY_PSOC5A */

        /* Disable the SIE */
        USB_CR0_REG &= ~USB_CR0_ENABLE;

        #if(!CY_PSOC5A)
            CyDelayUs(0);  /*~50ns delay */
            /* Store mode and Disable VRegulator*/
            USB_backup.mode = USB_CR1_REG & USB_CR1_REG_ENABLE;
            USB_CR1_REG &= ~USB_CR1_REG_ENABLE;

            CyDelayUs(1);  /* 0.5 us min delay */
            /* Disable the USBIO reference by setting PM.USB_CR0.fsusbio_ref_en.*/
            USB_PM_USB_CR0_REG &= ~USB_PM_USB_CR0_REF_EN;

            /* Switch DP and DM terminals to GPIO mode and disconnect 1.5k pullup*/
            USB_USBIO_CR1_REG |= USB_USBIO_CR1_IOMODE;

        #endif /* End !CY_PSOC5A*/

        /* Disable USB in ACT PM */
        USB_PM_ACT_CFG_REG &= ~USB_PM_ACT_EN_FSUSB;
        /* Disable USB block for Standby Power Mode */
        USB_PM_STBY_CFG_REG &= ~USB_PM_STBY_EN_FSUSB;
        CyDelayUs(1); /* min  0.5us delay required */

    }
    else
    {
        USB_backup.enableState = 0u;
    }
    CyExitCriticalSection(enableInterrupts);

    /* Set the DP Interrupt for wake-up from sleep mode. */
    #if((USB_DP_ISR_REMOVE == 0u) && (!CY_PSOC5A))
        CyIntSetVector(USB_DP_INTC_VECT_NUM,   USB_DP_ISR);
        CyIntSetPriority(USB_DP_INTC_VECT_NUM, USB_DP_INTC_PRIOR);
        CyIntClearPending(USB_DP_INTC_VECT_NUM);
        CyIntEnable(USB_DP_INTC_VECT_NUM);
    #endif /* (USB_DP_ISR_REMOVE == 0u) && (!CY_PSOC5A) */

}


/*******************************************************************************
* Function Name: USB_Resume
********************************************************************************
*
* Summary:
*  This function enables the USBFS block after power down mode.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  USB_backup - checked.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void USB_Resume(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    if(USB_backup.enableState != 0u)
    {
        #if((USB_DP_ISR_REMOVE == 0u) && (!CY_PSOC5A))
            CyIntDisable(USB_DP_INTC_VECT_NUM);
        #endif /* End USB_DP_ISR_REMOVE */

        #if(CY_PSOC5A)
            /* Enable USBIO block */
            USB_PM_AVAIL_CR_REG |= USB_PM_AVAIL_EN_FSUSBIO;

            /* Bus Reset Length, It has correct default value in ES3 */
            USB_BUS_RST_CNT_REG = USB_BUS_RST_COUNT;
        #endif /* End CY_PSOC5A */

        /* Enable USB block */
        USB_PM_ACT_CFG_REG |= USB_PM_ACT_EN_FSUSB;
        /* Enable USB block for Standby Power Mode */
        USB_PM_STBY_CFG_REG |= USB_PM_STBY_EN_FSUSB;
        /* Enable core clock */
        USB_USB_CLK_EN_REG |= USB_USB_CLK_ENABLE;

        /* USBIO Wakeup Sequencing for TO4 */
        #if (!CY_PSOC5A)
            /* Enable the USBIO reference by setting PM.USB_CR0.fsusbio_ref_en.*/
            USB_PM_USB_CR0_REG |= USB_PM_USB_CR0_REF_EN;
            /* The reference will be available ~40us after power restored */
            CyDelayUs(40);
            /* Return VRegulator*/
            USB_CR1_REG |= USB_backup.mode;
            CyDelayUs(0);  /*~50ns delay */
            /* Enable USBIO */
            USB_PM_USB_CR0_REG |= USB_PM_USB_CR0_PD_N;
            CyDelayUs(2);
            /* Set the USBIO pull-up enable */
            USB_PM_USB_CR0_REG |= USB_PM_USB_CR0_PD_PULLUP_N;
        #endif /* End !CY_PSOC5A */

        /* Reinit Arbiter congiguration for DMA transfers */
        #if(USB_EP_MM != USB__EP_MANUAL)
            /* usb arb interrupt enable */
            USB_ARB_INT_EN_REG = USB_ARB_INT_MASK;
            #if(USB_EP_MM == USB__EP_DMAMANUAL)
                USB_ARB_CFG_REG = USB_ARB_CFG_MANUAL_DMA;
            #endif   /* End USB_EP_MM == USB__EP_DMAMANUAL */
            #if(USB_EP_MM == USB__EP_DMAAUTO)
                /*Set cfg cmplt this rises DMA request when the full configuration is done */
                USB_ARB_CFG_REG = USB_ARB_CFG_AUTO_DMA | USB_ARB_CFG_AUTO_MEM;
            #endif   /* End USB_EP_MM == USB__EP_DMAAUTO */
        #endif   /* End USB_EP_MM != USB__EP_MANUAL */

        /* STALL_IN_OUT */
        CY_SET_REG8(USB_EP0_CR_PTR, USB_MODE_STALL_IN_OUT);
        /* Enable the SIE with a last address */
        USB_CR0_REG |= USB_CR0_ENABLE;
        CyDelayCycles(1);
        /* Finally, Enable d+ pullup and select iomode to USB mode*/
        CY_SET_REG8(USB_USBIO_CR1_PTR, USB_USBIO_CR1_USBPUEN);

        /* Restore USB register settings */
        USB_RestoreConfig();
    
    }
    CyExitCriticalSection(enableInterrupts);
}

#if(CY_PSOC5A)


/*******************************************************************************
* Function Name: USB_Resume_Condition
********************************************************************************
* Summary:
*  This function enables the USBIO block after power down mode, reads the 
*  current state of the DP pin and disables the USBIO block backward when DP 
*  pin is not in low state.
 
*
* Parameters:  
*  void 
*
* Return: 
*  Zero for low level DP pin state and not zero for high level.
*  
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 USB_Resume_Condition(void) 
{
    uint8 pinVal;
    
    /* Enable USBIO block */
    USB_PM_AVAIL_CR_REG &= ~USB_PM_AVAIL_EN_FSUSBIO;
    
    /* Check DP pin for low level */
    pinVal = USB_USBIO_CR1_REG & USB_USBIO_CR1_DP0;
    
    if( pinVal != 0u)
    {
        /* Disable USBIO block */
        USB_PM_AVAIL_CR_REG &= ~USB_PM_AVAIL_EN_FSUSBIO;
    }    
    
    return (pinVal);
}

#endif /* End CY_PSOC5A */


/* [] END OF FILE */
