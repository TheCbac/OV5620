/*******************************************************************************
* File Name: EXPST.h  
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

#if !defined(CY_PINS_EXPST_H) /* Pins EXPST_H */
#define CY_PINS_EXPST_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "EXPST_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_80 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 EXPST__PORT == 15 && ((EXPST__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    EXPST_Write(uint8 value) ;
void    EXPST_SetDriveMode(uint8 mode) ;
uint8   EXPST_ReadDataReg(void) ;
uint8   EXPST_Read(void) ;
uint8   EXPST_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define EXPST_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define EXPST_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define EXPST_DM_RES_UP          PIN_DM_RES_UP
#define EXPST_DM_RES_DWN         PIN_DM_RES_DWN
#define EXPST_DM_OD_LO           PIN_DM_OD_LO
#define EXPST_DM_OD_HI           PIN_DM_OD_HI
#define EXPST_DM_STRONG          PIN_DM_STRONG
#define EXPST_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define EXPST_MASK               EXPST__MASK
#define EXPST_SHIFT              EXPST__SHIFT
#define EXPST_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define EXPST_PS                     (* (reg8 *) EXPST__PS)
/* Data Register */
#define EXPST_DR                     (* (reg8 *) EXPST__DR)
/* Port Number */
#define EXPST_PRT_NUM                (* (reg8 *) EXPST__PRT) 
/* Connect to Analog Globals */                                                  
#define EXPST_AG                     (* (reg8 *) EXPST__AG)                       
/* Analog MUX bux enable */
#define EXPST_AMUX                   (* (reg8 *) EXPST__AMUX) 
/* Bidirectional Enable */                                                        
#define EXPST_BIE                    (* (reg8 *) EXPST__BIE)
/* Bit-mask for Aliased Register Access */
#define EXPST_BIT_MASK               (* (reg8 *) EXPST__BIT_MASK)
/* Bypass Enable */
#define EXPST_BYP                    (* (reg8 *) EXPST__BYP)
/* Port wide control signals */                                                   
#define EXPST_CTL                    (* (reg8 *) EXPST__CTL)
/* Drive Modes */
#define EXPST_DM0                    (* (reg8 *) EXPST__DM0) 
#define EXPST_DM1                    (* (reg8 *) EXPST__DM1)
#define EXPST_DM2                    (* (reg8 *) EXPST__DM2) 
/* Input Buffer Disable Override */
#define EXPST_INP_DIS                (* (reg8 *) EXPST__INP_DIS)
/* LCD Common or Segment Drive */
#define EXPST_LCD_COM_SEG            (* (reg8 *) EXPST__LCD_COM_SEG)
/* Enable Segment LCD */
#define EXPST_LCD_EN                 (* (reg8 *) EXPST__LCD_EN)
/* Slew Rate Control */
#define EXPST_SLW                    (* (reg8 *) EXPST__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define EXPST_PRTDSI__CAPS_SEL       (* (reg8 *) EXPST__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define EXPST_PRTDSI__DBL_SYNC_IN    (* (reg8 *) EXPST__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define EXPST_PRTDSI__OE_SEL0        (* (reg8 *) EXPST__PRTDSI__OE_SEL0) 
#define EXPST_PRTDSI__OE_SEL1        (* (reg8 *) EXPST__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define EXPST_PRTDSI__OUT_SEL0       (* (reg8 *) EXPST__PRTDSI__OUT_SEL0) 
#define EXPST_PRTDSI__OUT_SEL1       (* (reg8 *) EXPST__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define EXPST_PRTDSI__SYNC_OUT       (* (reg8 *) EXPST__PRTDSI__SYNC_OUT) 


#if defined(EXPST__INTSTAT)  /* Interrupt Registers */

    #define EXPST_INTSTAT                (* (reg8 *) EXPST__INTSTAT)
    #define EXPST_SNAP                   (* (reg8 *) EXPST__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_EXPST_H */


/* [] END OF FILE */
