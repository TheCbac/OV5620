/*******************************************************************************
* File Name: pin_HREF_FALL.h  
* Version 1.80
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_pin_HREF_FALL_H) /* Pins pin_HREF_FALL_H */
#define CY_PINS_pin_HREF_FALL_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "pin_HREF_FALL_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_80 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 pin_HREF_FALL__PORT == 15 && ((pin_HREF_FALL__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    pin_HREF_FALL_Write(uint8 value) ;
void    pin_HREF_FALL_SetDriveMode(uint8 mode) ;
uint8   pin_HREF_FALL_ReadDataReg(void) ;
uint8   pin_HREF_FALL_Read(void) ;
uint8   pin_HREF_FALL_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define pin_HREF_FALL_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define pin_HREF_FALL_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define pin_HREF_FALL_DM_RES_UP          PIN_DM_RES_UP
#define pin_HREF_FALL_DM_RES_DWN         PIN_DM_RES_DWN
#define pin_HREF_FALL_DM_OD_LO           PIN_DM_OD_LO
#define pin_HREF_FALL_DM_OD_HI           PIN_DM_OD_HI
#define pin_HREF_FALL_DM_STRONG          PIN_DM_STRONG
#define pin_HREF_FALL_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define pin_HREF_FALL_MASK               pin_HREF_FALL__MASK
#define pin_HREF_FALL_SHIFT              pin_HREF_FALL__SHIFT
#define pin_HREF_FALL_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define pin_HREF_FALL_PS                     (* (reg8 *) pin_HREF_FALL__PS)
/* Data Register */
#define pin_HREF_FALL_DR                     (* (reg8 *) pin_HREF_FALL__DR)
/* Port Number */
#define pin_HREF_FALL_PRT_NUM                (* (reg8 *) pin_HREF_FALL__PRT) 
/* Connect to Analog Globals */                                                  
#define pin_HREF_FALL_AG                     (* (reg8 *) pin_HREF_FALL__AG)                       
/* Analog MUX bux enable */
#define pin_HREF_FALL_AMUX                   (* (reg8 *) pin_HREF_FALL__AMUX) 
/* Bidirectional Enable */                                                        
#define pin_HREF_FALL_BIE                    (* (reg8 *) pin_HREF_FALL__BIE)
/* Bit-mask for Aliased Register Access */
#define pin_HREF_FALL_BIT_MASK               (* (reg8 *) pin_HREF_FALL__BIT_MASK)
/* Bypass Enable */
#define pin_HREF_FALL_BYP                    (* (reg8 *) pin_HREF_FALL__BYP)
/* Port wide control signals */                                                   
#define pin_HREF_FALL_CTL                    (* (reg8 *) pin_HREF_FALL__CTL)
/* Drive Modes */
#define pin_HREF_FALL_DM0                    (* (reg8 *) pin_HREF_FALL__DM0) 
#define pin_HREF_FALL_DM1                    (* (reg8 *) pin_HREF_FALL__DM1)
#define pin_HREF_FALL_DM2                    (* (reg8 *) pin_HREF_FALL__DM2) 
/* Input Buffer Disable Override */
#define pin_HREF_FALL_INP_DIS                (* (reg8 *) pin_HREF_FALL__INP_DIS)
/* LCD Common or Segment Drive */
#define pin_HREF_FALL_LCD_COM_SEG            (* (reg8 *) pin_HREF_FALL__LCD_COM_SEG)
/* Enable Segment LCD */
#define pin_HREF_FALL_LCD_EN                 (* (reg8 *) pin_HREF_FALL__LCD_EN)
/* Slew Rate Control */
#define pin_HREF_FALL_SLW                    (* (reg8 *) pin_HREF_FALL__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define pin_HREF_FALL_PRTDSI__CAPS_SEL       (* (reg8 *) pin_HREF_FALL__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define pin_HREF_FALL_PRTDSI__DBL_SYNC_IN    (* (reg8 *) pin_HREF_FALL__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define pin_HREF_FALL_PRTDSI__OE_SEL0        (* (reg8 *) pin_HREF_FALL__PRTDSI__OE_SEL0) 
#define pin_HREF_FALL_PRTDSI__OE_SEL1        (* (reg8 *) pin_HREF_FALL__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define pin_HREF_FALL_PRTDSI__OUT_SEL0       (* (reg8 *) pin_HREF_FALL__PRTDSI__OUT_SEL0) 
#define pin_HREF_FALL_PRTDSI__OUT_SEL1       (* (reg8 *) pin_HREF_FALL__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define pin_HREF_FALL_PRTDSI__SYNC_OUT       (* (reg8 *) pin_HREF_FALL__PRTDSI__SYNC_OUT) 


#if defined(pin_HREF_FALL__INTSTAT)  /* Interrupt Registers */

    #define pin_HREF_FALL_INTSTAT                (* (reg8 *) pin_HREF_FALL__INTSTAT)
    #define pin_HREF_FALL_SNAP                   (* (reg8 *) pin_HREF_FALL__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_pin_HREF_FALL_H */


/* [] END OF FILE */
