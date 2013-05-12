/*******************************************************************************
* File Name: USB_cls.c
* Version 2.50
*
* Description:
*  USB Class request handler.
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

#if(USB_EXTERN_CLS == USB_FALSE)


/***************************************
* External references
***************************************/

#if defined(USB_ENABLE_HID_CLASS)
    uint8 USB_DispatchHIDClassRqst(void);
#endif /* End USB_ENABLE_HID_CLASS */
#if defined(USB_ENABLE_AUDIO_CLASS)
    uint8 USB_DispatchAUDIOClassRqst(void);
#endif /* End USB_ENABLE_HID_CLASS */
#if defined(USB_ENABLE_CDC_CLASS)
    uint8 USB_DispatchCDCClassRqst(void);
#endif /* End USB_ENABLE_CDC_CLASS */

extern uint8 CYCODE *USB_interfaceClass;
extern volatile T_USB_EP_CTL_BLOCK USB_EP[];


/***************************************
* User Implemented Class Driver Declarations.
***************************************/
/* `#START USER_DEFINED_CLASS_DECLARATIONS` Place your declaration here */

/* `#END` */


/*******************************************************************************
* Function Name: USB_DispatchClassRqst
********************************************************************************
* Summary:
*  This routine dispatches class specific requests depend on inteface class.
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
uint8 USB_DispatchClassRqst() 
{
    uint8 requestHandled = USB_FALSE;
    uint8 interfaceNumber = 0u;

    switch(CY_GET_REG8(USB_bmRequestType) & USB_RQST_RCPT_MASK)
    {
        case USB_RQST_RCPT_IFC:        /* class-specific request directed to an interface */
            interfaceNumber = CY_GET_REG8(USB_wIndexLo); /* wIndexLo contain Interface number */
            break;
        case USB_RQST_RCPT_EP:         /* class-specific request directed to the endpoint */
            /* find related intenface to the endpoint, wIndexLo contain EP number */
            interfaceNumber =
                USB_EP[CY_GET_REG8(USB_wIndexLo) & USB_DIR_UNUSED].interface;
            break;
        default:    /* requestHandled is initialized as FALSE by default */
            break;
    }
    /* Handle Class request depend on interface type */
    switch(USB_interfaceClass[interfaceNumber])
    {
        case USB_CLASS_HID:
            #if defined(USB_ENABLE_HID_CLASS)
                requestHandled = USB_DispatchHIDClassRqst();
            #endif /* USB_ENABLE_HID_CLASS */
            break;
        case USB_CLASS_AUDIO:
            #if defined(USB_ENABLE_AUDIO_CLASS)
                requestHandled = USB_DispatchAUDIOClassRqst();
            #endif /* USB_ENABLE_HID_CLASS */
            break;
        case USB_CLASS_CDC:
            #if defined(USB_ENABLE_CDC_CLASS)
                requestHandled = USB_DispatchCDCClassRqst();
            #endif /* USB_ENABLE_CDC_CLASS */
            break;
        default:    /* requestHandled is initialezed as FALSE by default */
            break;
    }

    /* `#START USER_DEFINED_CLASS_CODE` Place your Class request here */

    /* `#END` */

    return(requestHandled);
}


/*******************************************************************************
* Additional user functions supporting Class Specific Requests
********************************************************************************/

/* `#START CLASS_SPECIFIC_FUNCTIONS` Place any additional functions here */

/* `#END` */

#endif /* USB_EXTERN_CLS */


/* [] END OF FILE */
