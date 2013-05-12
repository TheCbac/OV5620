/*******************************************************************************
* File Name: PCLK.h  
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

#if !defined(CY_PINS_PCLK_H) /* Pins PCLK_H */
#define CY_PINS_PCLK_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PCLK_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_80 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 PCLK__PORT == 15 && ((PCLK__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    PCLK_Write(uint8 value) ;
void    PCLK_SetDriveMode(uint8 mode) ;
uint8   PCLK_ReadDataReg(void) ;
uint8   PCLK_Read(void) ;
uint8   PCLK_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PCLK_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define PCLK_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define PCLK_DM_RES_UP          PIN_DM_RES_UP
#define PCLK_DM_RES_DWN         PIN_DM_RES_DWN
#define PCLK_DM_OD_LO           PIN_DM_OD_LO
#define PCLK_DM_OD_HI           PIN_DM_OD_HI
#define PCLK_DM_STRONG          PIN_DM_STRONG
#define PCLK_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define PCLK_MASK               PCLK__MASK
#define PCLK_SHIFT              PCLK__SHIFT
#define PCLK_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PCLK_PS                     (* (reg8 *) PCLK__PS)
/* Data Register */
#define PCLK_DR                     (* (reg8 *) PCLK__DR)
/* Port Number */
#define PCLK_PRT_NUM                (* (reg8 *) PCLK__PRT) 
/* Connect to Analog Globals */                                                  
#define PCLK_AG                     (* (reg8 *) PCLK__AG)                       
/* Analog MUX bux enable */
#define PCLK_AMUX                   (* (reg8 *) PCLK__AMUX) 
/* Bidirectional Enable */                                                        
#define PCLK_BIE                    (* (reg8 *) PCLK__BIE)
/* Bit-mask for Aliased Register Access */
#define PCLK_BIT_MASK               (* (reg8 *) PCLK__BIT_MASK)
/* Bypass Enable */
#define PCLK_BYP                    (* (reg8 *) PCLK__BYP)
/* Port wide control signals */                                                   
#define PCLK_CTL                    (* (reg8 *) PCLK__CTL)
/* Drive Modes */
#define PCLK_DM0                    (* (reg8 *) PCLK__DM0) 
#define PCLK_DM1                    (* (reg8 *) PCLK__DM1)
#define PCLK_DM2                    (* (reg8 *) PCLK__DM2) 
/* Input Buffer Disable Override */
#define PCLK_INP_DIS                (* (reg8 *) PCLK__INP_DIS)
/* LCD Common or Segment Drive */
#define PCLK_LCD_COM_SEG            (* (reg8 *) PCLK__LCD_COM_SEG)
/* Enable Segment LCD */
#define PCLK_LCD_EN                 (* (reg8 *) PCLK__LCD_EN)
/* Slew Rate Control */
#define PCLK_SLW                    (* (reg8 *) PCLK__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PCLK_PRTDSI__CAPS_SEL       (* (reg8 *) PCLK__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PCLK_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PCLK__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PCLK_PRTDSI__OE_SEL0        (* (reg8 *) PCLK__PRTDSI__OE_SEL0) 
#define PCLK_PRTDSI__OE_SEL1        (* (reg8 *) PCLK__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PCLK_PRTDSI__OUT_SEL0       (* (reg8 *) PCLK__PRTDSI__OUT_SEL0) 
#define PCLK_PRTDSI__OUT_SEL1       (* (reg8 *) PCLK__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PCLK_PRTDSI__SYNC_OUT       (* (reg8 *) PCLK__PRTDSI__SYNC_OUT) 


#if defined(PCLK__INTSTAT)  /* Interrupt Registers */

    #define PCLK_INTSTAT                (* (reg8 *) PCLK__INTSTAT)
    #define PCLK_SNAP                   (* (reg8 *) PCLK__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_PCLK_H */


/* [] END OF FILE */
