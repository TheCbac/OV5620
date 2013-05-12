/*******************************************************************************
* File Name: USB_midi.h
* Version 2.50
*
* Description:
*  Header File for the USBFS MIDI module.
*  Contains prototypes and constant values.
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(USB_midi_H)
#define USB_midi_H

#include "cytypes.h"
#include "USB.h"


/***************************************
*    Data Struct Definition
***************************************/

/* The following structure is used to hold status information for
   building and parsing incoming MIDI messages. */
typedef struct _USB_MIDI_RX_STATUS
{
    uint8    length;        /* expected length */
    uint8    count;         /* current byte count */
    uint8    size;          /* complete size */
    uint8    runstat;       /* running status */
    uint8    msgBuff[4];    /* message buffer */
} USB_MIDI_RX_STATUS;


/***************************************
*           MIDI Constants.
***************************************/

#define USB_ONE_EXT_INTRF              (0x01u)
#define USB_TWO_EXT_INTRF              (0x02u)

/* Flag definitions for use with MIDI device inquiry */
#define USB_INQ_SYSEX_FLAG             (0x01u)
#define USB_INQ_IDENTITY_REQ_FLAG      (0x02u)

/* USB-MIDI Code Index Number Classifications (MIDI Table 4-1) */
#define USB_CIN_MASK                   (0x0Fu)
#define USB_RESERVED0                  (0x00u)
#define USB_RESERVED1                  (0x01u)
#define USB_2BYTE_COMMON               (0x02u)
#define USB_3BYTE_COMMON               (0x03u)
#define USB_SYSEX                      (0x04u)
#define USB_1BYTE_COMMON               (0x05u)
#define USB_SYSEX_ENDS_WITH1           (0x05u)
#define USB_SYSEX_ENDS_WITH2           (0x06u)
#define USB_SYSEX_ENDS_WITH3           (0x07u)
#define USB_NOTE_OFF                   (0x08u)
#define USB_NOTE_ON                    (0x09u)
#define USB_POLY_KEY_PRESSURE          (0x0Au)
#define USB_CONTROL_CHANGE             (0x0Bu)
#define USB_PROGRAM_CHANGE             (0x0Cu)
#define USB_CHANNEL_PRESSURE           (0x0Du)
#define USB_PITCH_BEND_CHANGE          (0x0Eu)
#define USB_SINGLE_BYTE                (0x0Fu)

#define USB_CABLE_MASK                 (0xF0u)
#define USB_MIDI_CABLE_00              (0x00u)
#define USB_MIDI_CABLE_01              (0x10u)

#define USB_EVENT_BYTE0                (0x00u)
#define USB_EVENT_BYTE1                (0x01u)
#define USB_EVENT_BYTE2                (0x02u)
#define USB_EVENT_BYTE3                (0x03u)
#define USB_EVENT_LENGTH               (0x04u)

#define USB_MIDI_STATUS_BYTE_MASK      (0x80u)
#define USB_MIDI_STATUS_MASK           (0xF0u)
#define USB_MIDI_SINGLE_BYTE_MASK      (0x08u)
#define USB_MIDI_NOTE_OFF              (0x80u)
#define USB_MIDI_NOTE_ON               (0x90u)
#define USB_MIDI_POLY_KEY_PRESSURE     (0xA0u)
#define USB_MIDI_CONTROL_CHANGE        (0xB0u)
#define USB_MIDI_PROGRAM_CHANGE        (0xC0u)
#define USB_MIDI_CHANNEL_PRESSURE      (0xD0u)
#define USB_MIDI_PITCH_BEND_CHANGE     (0xE0u)
#define USB_MIDI_SYSEX                 (0xF0u)
#define USB_MIDI_EOSEX                 (0xF7u)
#define USB_MIDI_QFM                   (0xF1u)
#define USB_MIDI_SPP                   (0xF2u)
#define USB_MIDI_SONGSEL               (0xF3u)
#define USB_MIDI_TUNEREQ               (0xF6u)
#define USB_MIDI_ACTIVESENSE           (0xFEu)

/* MIDI Universal System Exclusive defines */
#define USB_MIDI_SYSEX_NON_REAL_TIME   (0x7Eu)
#define USB_MIDI_SYSEX_REALTIME        (0x7Fu)
/* ID of target device */
#define USB_MIDI_SYSEX_ID_ALL          (0x7Fu)
/* Sub-ID#1*/
#define USB_MIDI_SYSEX_GEN_INFORMATION (0x06u)
#define USB_MIDI_SYSEX_GEN_MESSAGE     (0x09u)
/* Sub-ID#2*/
#define USB_MIDI_SYSEX_IDENTITY_REQ    (0x01u)
#define USB_MIDI_SYSEX_IDENTITY_REPLY  (0x02u)
#define USB_MIDI_SYSEX_SYSTEM_ON       (0x01u)
#define USB_MIDI_SYSEX_SYSTEM_OFF      (0x02u)

#define USB_CUSTOM_UART_TX_PRIOR_NUM   (0x04u)
#define USB_CUSTOM_UART_RX_PRIOR_NUM   (0x02u)

#endif /* End USB_midi_H */


/* [] END OF FILE */
