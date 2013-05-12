/*******************************************************************************
* File Name: USB_cdc.c
* Version 2.50
*
* Description:
*  USB HID Class request handler.
*
* Note:
*
********************************************************************************
* Copyright 2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "USB.h"

#if defined(USB_ENABLE_CDC_CLASS)

#include <string.h>
#include "USB_cdc.h"


/***************************************
*    CDC Variables
***************************************/

volatile uint8 USB_lineCoding[USB_LINE_CODING_SIZE];
volatile uint8 USB_lineChanged;
volatile uint16 USB_lineControlBitmap;
volatile uint8 USB_cdc_data_in_ep;
volatile uint8 USB_cdc_data_out_ep;


/***************************************
* Custom Declarations
***************************************/

/* `#START CDC_CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */


/***************************************
* External data references
***************************************/

extern volatile T_USB_EP_CTL_BLOCK USB_EP[];
extern volatile T_USB_TD USB_currentTD;
extern volatile uint8 USB_transferState;


/***************************************
* External function references
***************************************/

uint8 USB_InitControlRead(void) ;
uint8 USB_InitControlWrite(void) ;
uint8 USB_InitNoDataControlTransfer(void) ;


/*******************************************************************************
* Function Name: USB_DispatchCDCClassRqst
********************************************************************************
*
* Summary:
*  This routine dispatches CDC class requests.
*
* Parameters:
*  None.
*
* Return:
*  requestHandled
*
* Global variables:
*   USB_lineCoding: Contains the current line coding structure.
*     It is set by the Host using SET_LINE_CODING request and returned to the
*     user code by the USBFS_GetDTERate(), USBFS_GetCharFormat(),
*     USBFS_GetParityType(), USBFS_GetDataBits() APIs.
*   USB_lineControlBitmap: Contains the current control signal
*     bitmap. It is set by the Host using SET_CONTROL_LINE request and returned
*     to the user code by the USBFS_GetLineControl() API.
*   USB_lineChanged: This variable is used as a flag for the
*     USBFS_IsLineChanged() API, to be aware that Host has been sent request
*     for changing Line Coding or Control Bitmap.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 USB_DispatchCDCClassRqst() 
{
    uint8 requestHandled = USB_FALSE;

    if ((CY_GET_REG8(USB_bmRequestType) & USB_RQST_DIR_MASK) == USB_RQST_DIR_D2H)
    {   /* Control Read */
        switch (CY_GET_REG8(USB_bRequest))
        {
            case USB_CDC_GET_LINE_CODING:
                USB_currentTD.count = USB_LINE_CODING_SIZE;
                USB_currentTD.pData = USB_lineCoding;
                requestHandled  = USB_InitControlRead();
                break;

            /* `#START CDC_READ_REQUESTS` Place other request handler here */

            /* `#END` */

            default:    /* requestHandled is initialezed as FALSE by default */
                break;
        }
    }
    else if ((CY_GET_REG8(USB_bmRequestType) & USB_RQST_DIR_MASK) == \
                                                                            USB_RQST_DIR_H2D)
    {   /* Control Write */
        switch (CY_GET_REG8(USB_bRequest))
        {
            case USB_CDC_SET_LINE_CODING:
                USB_currentTD.count = USB_LINE_CODING_SIZE;
                USB_currentTD.pData = USB_lineCoding;
                USB_lineChanged |= USB_LINE_CODING_CHANGED;
                requestHandled = USB_InitControlWrite();
                break;

            case USB_CDC_SET_CONTROL_LINE_STATE:
                USB_lineControlBitmap = CY_GET_REG8(USB_wValueLo);
                USB_lineChanged |= USB_LINE_CONTROL_CHANGED;
                requestHandled = USB_InitNoDataControlTransfer();
                break;

            /* `#START CDC_WRITE_REQUESTS` Place other request handler here */

            /* `#END` */

            default:    /* requestHandled is initialezed as FALSE by default */
                break;
        }
    }
    else
    {   /* requestHandled is initialezed as FALSE by default */
    }

    return(requestHandled);
}


/***************************************
* Optional CDC APIs
***************************************/
#if (USB_ENABLE_CDC_CLASS_API != 0u)


    /*******************************************************************************
    * Function Name: USB_CDC_Init
    ********************************************************************************
    *
    * Summary:
    *  This function initialize the CDC interface to be ready for the receive data
    *  from the PC.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global variables:
    *   USB_lineChanged: Initialized to zero.
    *   USB_cdc_data_out_ep: Used as an OUT endpoint number.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void USB_CDC_Init(void) 
    {
        USB_lineChanged = 0u;
        USB_EnableOutEP(USB_cdc_data_out_ep);
    }


    /*******************************************************************************
    * Function Name: USB_PutData
    ********************************************************************************
    *
    * Summary:
    *  Sends a specified number of bytes from the location specified by a
    *  pointer to the PC.
    *
    * Parameters:
    *  pData: pointer to the buffer containing data to be sent.
    *  length: Specifies the number of bytes to send from the pData
    *  buffer. Maximum length will be limited by the maximum packet
    *  size for the endpoint.
    *
    * Return:
    *  None.
    *
    * Global variables:
    *   USB_cdc_data_in_ep: CDC IN endpoint number used for sending
    *     data.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void USB_PutData(uint8* pData, uint16 length) 
    {
        /* Limits length to maximim packet size for the EP */
        if(length > USB_EP[USB_cdc_data_in_ep].bufferSize)
        {
            length = USB_EP[USB_cdc_data_in_ep].bufferSize;
        }
        USB_LoadInEP(USB_cdc_data_in_ep, pData, length);
    }


    /*******************************************************************************
    * Function Name: USB_PutString
    ********************************************************************************
    *
    * Summary:
    *  Sends a null terminated string to the PC.
    *
    * Parameters:
    *  string: pointer to the string to be sent to the PC
    *
    * Return:
    *  None.
    *
    * Global variables:
    *   USB_cdc_data_in_ep: CDC IN endpoint number used for sending
    *     data.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  This function will block if there is not enough memory to place the whole
    *  string, it will block until the entire string has been written to the
    *  transmit buffer.
    *
    *******************************************************************************/
    void USB_PutString(char8* string) 
    {
        uint16 str_length;
        uint16 send_length;

        /* Get length of the null terminated string */
        str_length = strlen(string);
        do
        {
            /* Limits length to maximim packet size for the EP */
            send_length = (str_length > USB_EP[USB_cdc_data_in_ep].bufferSize) ?
                          USB_EP[USB_cdc_data_in_ep].bufferSize : str_length;
             /* Enable IN transfer */
            USB_LoadInEP(USB_cdc_data_in_ep, (uint8 *)string, send_length);
            str_length -= send_length;

            /* If more data are present to send */
            if(str_length > 0)
            {
                string += send_length;
                /* Wait for the Host to read it. */
                while(USB_EP[USB_cdc_data_in_ep].apiEpState ==
                                          USB_IN_BUFFER_FULL);
            }
        }while(str_length > 0);
    }


    /*******************************************************************************
    * Function Name: USB_PutChar
    ********************************************************************************
    *
    * Summary:
    *  Writes a single character to the PC.
    *
    * Parameters:
    *  txDataByte: Character to be sent to the PC.
    *
    * Return:
    *  None.
    *
    * Global variables:
    *   USB_cdc_data_in_ep: CDC IN endpoint number used for sending
    *     data.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void USB_PutChar(char8 txDataByte) 
    {
        USB_LoadInEP(USB_cdc_data_in_ep, (uint8 *)&txDataByte, 1u);
    }


    /*******************************************************************************
    * Function Name: USB_PutCRLF
    ********************************************************************************
    *
    * Summary:
    *  Sends a carriage return (0x0D) and line feed (0x0A) to the PC
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global variables:
    *   USB_cdc_data_in_ep: CDC IN endpoint number used for sending
    *     data.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void USB_PutCRLF(void) 
    {
        const uint8 CYCODE txData[] = {0x0Du, 0x0Au};

        USB_LoadInEP(USB_cdc_data_in_ep, (uint8 *)txData, 2u);
    }


    /*******************************************************************************
    * Function Name: USB_GetCount
    ********************************************************************************
    *
    * Summary:
    *  This function returns the number of bytes that were received from the PC.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Returns the number of received bytes.
    *
    * Global variables:
    *   USB_cdc_data_out_ep: CDC OUT endpoint number used.
    *
    *******************************************************************************/
    uint16 USB_GetCount(void) 
    {
        uint8 bytesCount = 0u;

        if (USB_EP[USB_cdc_data_out_ep].apiEpState == USB_OUT_BUFFER_FULL)
        {
            bytesCount = USB_GetEPCount(USB_cdc_data_out_ep);
        }

        return(bytesCount);
    }


    /*******************************************************************************
    * Function Name: USB_DataIsReady
    ********************************************************************************
    *
    * Summary:
    *  Returns a nonzero value if the component received data or received
    *  zero-length packet. The GetAll() or GetData() API should be called to read
    *  data from the buffer and reinit OUT endpoint even when zero-length packet
    *  received.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  If the OUT packet received this function returns a nonzero value.
    *  Otherwise zero is returned.
    *
    * Global variables:
    *   USB_cdc_data_out_ep: CDC OUT endpoint number used.
    *
    *******************************************************************************/
    uint8 USB_DataIsReady(void) 
    {
        return(USB_EP[USB_cdc_data_out_ep].apiEpState);
    }


    /*******************************************************************************
    * Function Name: USB_CDCIsReady
    ********************************************************************************
    *
    * Summary:
    *  Returns a nonzero value if the component is ready to send more data to the
    *  PC. Otherwise returns zero. Should be called before sending new data to
    *  ensure the previous data has finished sending.This function returns the
    *  number of bytes that were received from the PC.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  If the buffer can accept new data then this function returns a nonzero value.
    *  Otherwise zero is returned.
    *
    * Global variables:
    *   USB_cdc_data_in_ep: CDC IN endpoint number used.
    *
    *******************************************************************************/
    uint8 USB_CDCIsReady(void) 
    {
        return(USB_EP[USB_cdc_data_in_ep].apiEpState);
    }


    /*******************************************************************************
    * Function Name: USB_GetData
    ********************************************************************************
    *
    * Summary:
    *  Gets a specified number of bytes from the input buffer and places it in a
    *  data array specified by the passed pointer.
    *  USB_DataIsReady() API should be called before, to be sure
    *  that data is received from the Host.
    *
    * Parameters:
    *  pData: Pointer to the data array where data will be placed.
    *  Length: Number of bytes to read into the data array from the RX buffer.
    *          Maximum length is limited by the the number of received bytes.
    *
    * Return:
    *  Number of bytes received.
    *
    * Global variables:
    *   USB_cdc_data_out_ep: CDC OUT endpoint number used.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint16 USB_GetData(uint8* pData, uint16 length) 
    {
        return(USB_ReadOutEP(USB_cdc_data_out_ep, pData, length));
    }


    /*******************************************************************************
    * Function Name: USB_GetAll
    ********************************************************************************
    *
    * Summary:
    *  Gets all bytes of received data from the input buffer and places it into a
    *  specified data array. USB_DataIsReady() API should be called
    *  before, to be sure that data is received from the Host.
    *
    * Parameters:
    *  pData: Pointer to the data array where data will be placed.
    *
    * Return:
    *  Number of bytes received.
    *
    * Global variables:
    *   USB_cdc_data_out_ep: CDC OUT endpoint number used.
    *   USB_EP[].bufferSize: EP max packet size is used as a length
    *     to read all data from the EP buffer.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint16 USB_GetAll(uint8* pData) 
    {
        return (USB_ReadOutEP(USB_cdc_data_out_ep, pData,
                                           USB_EP[USB_cdc_data_out_ep].bufferSize));
    }


    /*******************************************************************************
    * Function Name: USB_GetChar
    ********************************************************************************
    *
    * Summary:
    *  Reads one byte of received data from the buffer.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Received one character.
    *
    * Global variables:
    *   USB_cdc_data_out_ep: CDC OUT endpoint number used.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 USB_GetChar(void) 
    {
         uint8 rxData;

        USB_ReadOutEP(USB_cdc_data_out_ep, &rxData, 1u);

        return(rxData);
    }

    /*******************************************************************************
    * Function Name: USB_IsLineChanged
    ********************************************************************************
    *
    * Summary:
    *  This function returns clear on read status of the line.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  If SET_LINE_CODING or CDC_SET_CONTROL_LINE_STATE request received then not
    *  zero value returned. Otherwise zero is returned.
    *
    * Global variables:
    *  USB_transferState - it is checked to be sure then OUT data
    *    phase has been compleate, and data written to the lineCoding or Control
    *    Bitmap buffer.
    *  USB_lineChanged: used as a flag to be aware that Host has been
    *    sent request for changing Line Coding or Control Bitmap.
    *
    *******************************************************************************/
    uint8 USB_IsLineChanged(void) 
    {
        uint8 state = 0u;
        /* transferState is checked to be sure then OUT data phase has been compleate */
        if((USB_lineChanged != 0u) &&
           (USB_transferState == USB_TRANS_STATE_IDLE))
        {
            state = USB_lineChanged;
            USB_lineChanged = 0u;
        }
        return(state);
    }


    /*******************************************************************************
    * Function Name: USB_GetDTERate
    ********************************************************************************
    *
    * Summary:
    *  Returns the data terminal rate set for this port in bits per second.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Returns a uint32 value of the data rate in bits per second.
    *
    * Global variables:
    *  USB_lineCoding: First four bytes converted to uint32
    *    depend on compiler, and returned as a data rate.
    *
    *******************************************************************************/
    uint32 USB_GetDTERate(void) 
    {
        uint32 rate;
        /* Data terminal rate has little endian format. */
        #if defined(__C51__)
            /*   KEIL for the 8051 is a Big Endian compiler. This requires four bytes swapping. */
            ((uint8 *)&rate)[0u] = USB_lineCoding[USB_LINE_CODING_RATE + 3u];
            ((uint8 *)&rate)[1u] = USB_lineCoding[USB_LINE_CODING_RATE + 2u];
            ((uint8 *)&rate)[2u] = USB_lineCoding[USB_LINE_CODING_RATE + 1u];
            ((uint8 *)&rate)[3u] = USB_lineCoding[USB_LINE_CODING_RATE];
        #elif defined(__GNUC__) || defined(__ARMCC_VERSION)
            /* ARM compilers (GCC and RealView) are little-endian */
            USB_CONVERT_DWORD *convert =
                (USB_CONVERT_DWORD *)&USB_lineCoding[USB_LINE_CODING_RATE];
            rate = convert->dword;
        #endif /* End Compillers */
        return(rate);
    }


    /*******************************************************************************
    * Function Name: USB_GetCharFormat
    ********************************************************************************
    *
    * Summary:
    *  Returns the number of stop bits.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Returns the number of stop bits.
    *
    * Global variables:
    *  USB_lineCoding: used to get a parameter.
    *
    *******************************************************************************/
    uint8 USB_GetCharFormat(void) 
    {
        return(USB_lineCoding[USB_LINE_CODING_STOP_BITS]);
    }


    /*******************************************************************************
    * Function Name: USB_GetParityType
    ********************************************************************************
    *
    * Summary:
    *  Returns the parity type for the CDC port.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Returns the parity type.
    *
    * Global variables:
    *  USB_lineCoding: used to get a parameter.
    *
    *******************************************************************************/
    uint8 USB_GetParityType(void) 
    {
        return(USB_lineCoding[USB_LINE_CODING_PARITY]);
    }


    /*******************************************************************************
    * Function Name: USB_GetDataBits
    ********************************************************************************
    *
    * Summary:
    *  Returns the number of data bits for the CDC port.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Returns the number of data bits.
    *  The number of data bits can be 5, 6, 7, 8 or 16.
    *
    * Global variables:
    *  USB_lineCoding: used to get a parameter.
    *
    *******************************************************************************/
    uint8 USB_GetDataBits(void) 
    {
        return(USB_lineCoding[USB_LINE_CODING_DATA_BITS]);
    }


    /*******************************************************************************
    * Function Name: USB_GetLineControl
    ********************************************************************************
    *
    * Summary:
    *  Returns Line control bitmap.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Returns Line control bitmap.
    *
    * Global variables:
    *  USB_lineControlBitmap: used to get a parameter.
    *
    *******************************************************************************/
    uint16 USB_GetLineControl(void) 
    {
        return(USB_lineControlBitmap);
    }

#endif  /* End USB_ENABLE_CDC_CLASS_API*/


/*******************************************************************************
* Additional user functions supporting CDC Requests
********************************************************************************/

/* `#START CDC_FUNCTIONS` Place any additional functions here */

/* `#END` */

#endif  /* End USB_ENABLE_CDC_CLASS*/


/* [] END OF FILE */
