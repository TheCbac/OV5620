/*******************************************************************************
* File Name: BaudClock.h  
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

#if !defined(CY_PINS_BaudClock_H) /* Pins BaudClock_H */
#define CY_PINS_BaudClock_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "BaudClock_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_80 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 BaudClock__PORT == 15 && ((BaudClock__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    BaudClock_Write(uint8 value) ;
void    BaudClock_SetDriveMode(uint8 mode) ;
uint8   BaudClock_ReadDataReg(void) ;
uint8   BaudClock_Read(void) ;
uint8   BaudClock_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define BaudClock_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define BaudClock_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define BaudClock_DM_RES_UP          PIN_DM_RES_UP
#define BaudClock_DM_RES_DWN         PIN_DM_RES_DWN
#define BaudClock_DM_OD_LO           PIN_DM_OD_LO
#define BaudClock_DM_OD_HI           PIN_DM_OD_HI
#define BaudClock_DM_STRONG          PIN_DM_STRONG
#define BaudClock_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define BaudClock_MASK               BaudClock__MASK
#define BaudClock_SHIFT              BaudClock__SHIFT
#define BaudClock_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define BaudClock_PS                     (* (reg8 *) BaudClock__PS)
/* Data Register */
#define BaudClock_DR                     (* (reg8 *) BaudClock__DR)
/* Port Number */
#define BaudClock_PRT_NUM                (* (reg8 *) BaudClock__PRT) 
/* Connect to Analog Globals */                                                  
#define BaudClock_AG                     (* (reg8 *) BaudClock__AG)                       
/* Analog MUX bux enable */
#define BaudClock_AMUX                   (* (reg8 *) BaudClock__AMUX) 
/* Bidirectional Enable */                                                        
#define BaudClock_BIE                    (* (reg8 *) BaudClock__BIE)
/* Bit-mask for Aliased Register Access */
#define BaudClock_BIT_MASK               (* (reg8 *) BaudClock__BIT_MASK)
/* Bypass Enable */
#define BaudClock_BYP                    (* (reg8 *) BaudClock__BYP)
/* Port wide control signals */                                                   
#define BaudClock_CTL                    (* (reg8 *) BaudClock__CTL)
/* Drive Modes */
#define BaudClock_DM0                    (* (reg8 *) BaudClock__DM0) 
#define BaudClock_DM1                    (* (reg8 *) BaudClock__DM1)
#define BaudClock_DM2                    (* (reg8 *) BaudClock__DM2) 
/* Input Buffer Disable Override */
#define BaudClock_INP_DIS                (* (reg8 *) BaudClock__INP_DIS)
/* LCD Common or Segment Drive */
#define BaudClock_LCD_COM_SEG            (* (reg8 *) BaudClock__LCD_COM_SEG)
/* Enable Segment LCD */
#define BaudClock_LCD_EN                 (* (reg8 *) BaudClock__LCD_EN)
/* Slew Rate Control */
#define BaudClock_SLW                    (* (reg8 *) BaudClock__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define BaudClock_PRTDSI__CAPS_SEL       (* (reg8 *) BaudClock__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define BaudClock_PRTDSI__DBL_SYNC_IN    (* (reg8 *) BaudClock__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define BaudClock_PRTDSI__OE_SEL0        (* (reg8 *) BaudClock__PRTDSI__OE_SEL0) 
#define BaudClock_PRTDSI__OE_SEL1        (* (reg8 *) BaudClock__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define BaudClock_PRTDSI__OUT_SEL0       (* (reg8 *) BaudClock__PRTDSI__OUT_SEL0) 
#define BaudClock_PRTDSI__OUT_SEL1       (* (reg8 *) BaudClock__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define BaudClock_PRTDSI__SYNC_OUT       (* (reg8 *) BaudClock__PRTDSI__SYNC_OUT) 


#if defined(BaudClock__INTSTAT)  /* Interrupt Registers */

    #define BaudClock_INTSTAT                (* (reg8 *) BaudClock__INTSTAT)
    #define BaudClock_SNAP                   (* (reg8 *) BaudClock__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_BaudClock_H */


/* [] END OF FILE */
