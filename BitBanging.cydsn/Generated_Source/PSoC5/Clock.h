/*******************************************************************************
* File Name: Clock.h  
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

#if !defined(CY_PINS_Clock_H) /* Pins Clock_H */
#define CY_PINS_Clock_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Clock_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_80 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Clock__PORT == 15 && ((Clock__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Clock_Write(uint8 value) ;
void    Clock_SetDriveMode(uint8 mode) ;
uint8   Clock_ReadDataReg(void) ;
uint8   Clock_Read(void) ;
uint8   Clock_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Clock_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Clock_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Clock_DM_RES_UP          PIN_DM_RES_UP
#define Clock_DM_RES_DWN         PIN_DM_RES_DWN
#define Clock_DM_OD_LO           PIN_DM_OD_LO
#define Clock_DM_OD_HI           PIN_DM_OD_HI
#define Clock_DM_STRONG          PIN_DM_STRONG
#define Clock_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Clock_MASK               Clock__MASK
#define Clock_SHIFT              Clock__SHIFT
#define Clock_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Clock_PS                     (* (reg8 *) Clock__PS)
/* Data Register */
#define Clock_DR                     (* (reg8 *) Clock__DR)
/* Port Number */
#define Clock_PRT_NUM                (* (reg8 *) Clock__PRT) 
/* Connect to Analog Globals */                                                  
#define Clock_AG                     (* (reg8 *) Clock__AG)                       
/* Analog MUX bux enable */
#define Clock_AMUX                   (* (reg8 *) Clock__AMUX) 
/* Bidirectional Enable */                                                        
#define Clock_BIE                    (* (reg8 *) Clock__BIE)
/* Bit-mask for Aliased Register Access */
#define Clock_BIT_MASK               (* (reg8 *) Clock__BIT_MASK)
/* Bypass Enable */
#define Clock_BYP                    (* (reg8 *) Clock__BYP)
/* Port wide control signals */                                                   
#define Clock_CTL                    (* (reg8 *) Clock__CTL)
/* Drive Modes */
#define Clock_DM0                    (* (reg8 *) Clock__DM0) 
#define Clock_DM1                    (* (reg8 *) Clock__DM1)
#define Clock_DM2                    (* (reg8 *) Clock__DM2) 
/* Input Buffer Disable Override */
#define Clock_INP_DIS                (* (reg8 *) Clock__INP_DIS)
/* LCD Common or Segment Drive */
#define Clock_LCD_COM_SEG            (* (reg8 *) Clock__LCD_COM_SEG)
/* Enable Segment LCD */
#define Clock_LCD_EN                 (* (reg8 *) Clock__LCD_EN)
/* Slew Rate Control */
#define Clock_SLW                    (* (reg8 *) Clock__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Clock_PRTDSI__CAPS_SEL       (* (reg8 *) Clock__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Clock_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Clock__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Clock_PRTDSI__OE_SEL0        (* (reg8 *) Clock__PRTDSI__OE_SEL0) 
#define Clock_PRTDSI__OE_SEL1        (* (reg8 *) Clock__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Clock_PRTDSI__OUT_SEL0       (* (reg8 *) Clock__PRTDSI__OUT_SEL0) 
#define Clock_PRTDSI__OUT_SEL1       (* (reg8 *) Clock__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Clock_PRTDSI__SYNC_OUT       (* (reg8 *) Clock__PRTDSI__SYNC_OUT) 


#if defined(Clock__INTSTAT)  /* Interrupt Registers */

    #define Clock_INTSTAT                (* (reg8 *) Clock__INTSTAT)
    #define Clock_SNAP                   (* (reg8 *) Clock__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Clock_H */


/* [] END OF FILE */
