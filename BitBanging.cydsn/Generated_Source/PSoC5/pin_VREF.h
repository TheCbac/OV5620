/*******************************************************************************
* File Name: pin_VREF.h  
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

#if !defined(CY_PINS_pin_VREF_H) /* Pins pin_VREF_H */
#define CY_PINS_pin_VREF_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "pin_VREF_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_80 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 pin_VREF__PORT == 15 && ((pin_VREF__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    pin_VREF_Write(uint8 value) ;
void    pin_VREF_SetDriveMode(uint8 mode) ;
uint8   pin_VREF_ReadDataReg(void) ;
uint8   pin_VREF_Read(void) ;
uint8   pin_VREF_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define pin_VREF_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define pin_VREF_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define pin_VREF_DM_RES_UP          PIN_DM_RES_UP
#define pin_VREF_DM_RES_DWN         PIN_DM_RES_DWN
#define pin_VREF_DM_OD_LO           PIN_DM_OD_LO
#define pin_VREF_DM_OD_HI           PIN_DM_OD_HI
#define pin_VREF_DM_STRONG          PIN_DM_STRONG
#define pin_VREF_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define pin_VREF_MASK               pin_VREF__MASK
#define pin_VREF_SHIFT              pin_VREF__SHIFT
#define pin_VREF_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define pin_VREF_PS                     (* (reg8 *) pin_VREF__PS)
/* Data Register */
#define pin_VREF_DR                     (* (reg8 *) pin_VREF__DR)
/* Port Number */
#define pin_VREF_PRT_NUM                (* (reg8 *) pin_VREF__PRT) 
/* Connect to Analog Globals */                                                  
#define pin_VREF_AG                     (* (reg8 *) pin_VREF__AG)                       
/* Analog MUX bux enable */
#define pin_VREF_AMUX                   (* (reg8 *) pin_VREF__AMUX) 
/* Bidirectional Enable */                                                        
#define pin_VREF_BIE                    (* (reg8 *) pin_VREF__BIE)
/* Bit-mask for Aliased Register Access */
#define pin_VREF_BIT_MASK               (* (reg8 *) pin_VREF__BIT_MASK)
/* Bypass Enable */
#define pin_VREF_BYP                    (* (reg8 *) pin_VREF__BYP)
/* Port wide control signals */                                                   
#define pin_VREF_CTL                    (* (reg8 *) pin_VREF__CTL)
/* Drive Modes */
#define pin_VREF_DM0                    (* (reg8 *) pin_VREF__DM0) 
#define pin_VREF_DM1                    (* (reg8 *) pin_VREF__DM1)
#define pin_VREF_DM2                    (* (reg8 *) pin_VREF__DM2) 
/* Input Buffer Disable Override */
#define pin_VREF_INP_DIS                (* (reg8 *) pin_VREF__INP_DIS)
/* LCD Common or Segment Drive */
#define pin_VREF_LCD_COM_SEG            (* (reg8 *) pin_VREF__LCD_COM_SEG)
/* Enable Segment LCD */
#define pin_VREF_LCD_EN                 (* (reg8 *) pin_VREF__LCD_EN)
/* Slew Rate Control */
#define pin_VREF_SLW                    (* (reg8 *) pin_VREF__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define pin_VREF_PRTDSI__CAPS_SEL       (* (reg8 *) pin_VREF__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define pin_VREF_PRTDSI__DBL_SYNC_IN    (* (reg8 *) pin_VREF__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define pin_VREF_PRTDSI__OE_SEL0        (* (reg8 *) pin_VREF__PRTDSI__OE_SEL0) 
#define pin_VREF_PRTDSI__OE_SEL1        (* (reg8 *) pin_VREF__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define pin_VREF_PRTDSI__OUT_SEL0       (* (reg8 *) pin_VREF__PRTDSI__OUT_SEL0) 
#define pin_VREF_PRTDSI__OUT_SEL1       (* (reg8 *) pin_VREF__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define pin_VREF_PRTDSI__SYNC_OUT       (* (reg8 *) pin_VREF__PRTDSI__SYNC_OUT) 


#if defined(pin_VREF__INTSTAT)  /* Interrupt Registers */

    #define pin_VREF_INTSTAT                (* (reg8 *) pin_VREF__INTSTAT)
    #define pin_VREF_SNAP                   (* (reg8 *) pin_VREF__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_pin_VREF_H */


/* [] END OF FILE */
