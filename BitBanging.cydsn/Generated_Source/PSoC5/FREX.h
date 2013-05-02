/*******************************************************************************
* File Name: FREX.h  
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

#if !defined(CY_PINS_FREX_H) /* Pins FREX_H */
#define CY_PINS_FREX_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "FREX_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_80 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 FREX__PORT == 15 && ((FREX__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    FREX_Write(uint8 value) ;
void    FREX_SetDriveMode(uint8 mode) ;
uint8   FREX_ReadDataReg(void) ;
uint8   FREX_Read(void) ;
uint8   FREX_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define FREX_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define FREX_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define FREX_DM_RES_UP          PIN_DM_RES_UP
#define FREX_DM_RES_DWN         PIN_DM_RES_DWN
#define FREX_DM_OD_LO           PIN_DM_OD_LO
#define FREX_DM_OD_HI           PIN_DM_OD_HI
#define FREX_DM_STRONG          PIN_DM_STRONG
#define FREX_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define FREX_MASK               FREX__MASK
#define FREX_SHIFT              FREX__SHIFT
#define FREX_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define FREX_PS                     (* (reg8 *) FREX__PS)
/* Data Register */
#define FREX_DR                     (* (reg8 *) FREX__DR)
/* Port Number */
#define FREX_PRT_NUM                (* (reg8 *) FREX__PRT) 
/* Connect to Analog Globals */                                                  
#define FREX_AG                     (* (reg8 *) FREX__AG)                       
/* Analog MUX bux enable */
#define FREX_AMUX                   (* (reg8 *) FREX__AMUX) 
/* Bidirectional Enable */                                                        
#define FREX_BIE                    (* (reg8 *) FREX__BIE)
/* Bit-mask for Aliased Register Access */
#define FREX_BIT_MASK               (* (reg8 *) FREX__BIT_MASK)
/* Bypass Enable */
#define FREX_BYP                    (* (reg8 *) FREX__BYP)
/* Port wide control signals */                                                   
#define FREX_CTL                    (* (reg8 *) FREX__CTL)
/* Drive Modes */
#define FREX_DM0                    (* (reg8 *) FREX__DM0) 
#define FREX_DM1                    (* (reg8 *) FREX__DM1)
#define FREX_DM2                    (* (reg8 *) FREX__DM2) 
/* Input Buffer Disable Override */
#define FREX_INP_DIS                (* (reg8 *) FREX__INP_DIS)
/* LCD Common or Segment Drive */
#define FREX_LCD_COM_SEG            (* (reg8 *) FREX__LCD_COM_SEG)
/* Enable Segment LCD */
#define FREX_LCD_EN                 (* (reg8 *) FREX__LCD_EN)
/* Slew Rate Control */
#define FREX_SLW                    (* (reg8 *) FREX__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define FREX_PRTDSI__CAPS_SEL       (* (reg8 *) FREX__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define FREX_PRTDSI__DBL_SYNC_IN    (* (reg8 *) FREX__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define FREX_PRTDSI__OE_SEL0        (* (reg8 *) FREX__PRTDSI__OE_SEL0) 
#define FREX_PRTDSI__OE_SEL1        (* (reg8 *) FREX__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define FREX_PRTDSI__OUT_SEL0       (* (reg8 *) FREX__PRTDSI__OUT_SEL0) 
#define FREX_PRTDSI__OUT_SEL1       (* (reg8 *) FREX__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define FREX_PRTDSI__SYNC_OUT       (* (reg8 *) FREX__PRTDSI__SYNC_OUT) 


#if defined(FREX__INTSTAT)  /* Interrupt Registers */

    #define FREX_INTSTAT                (* (reg8 *) FREX__INTSTAT)
    #define FREX_SNAP                   (* (reg8 *) FREX__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_FREX_H */


/* [] END OF FILE */
