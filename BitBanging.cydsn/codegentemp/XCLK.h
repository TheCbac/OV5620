/*******************************************************************************
* File Name: XCLK.h  
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

#if !defined(CY_PINS_XCLK_H) /* Pins XCLK_H */
#define CY_PINS_XCLK_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "XCLK_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_80 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 XCLK__PORT == 15 && ((XCLK__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    XCLK_Write(uint8 value) ;
void    XCLK_SetDriveMode(uint8 mode) ;
uint8   XCLK_ReadDataReg(void) ;
uint8   XCLK_Read(void) ;
uint8   XCLK_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define XCLK_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define XCLK_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define XCLK_DM_RES_UP          PIN_DM_RES_UP
#define XCLK_DM_RES_DWN         PIN_DM_RES_DWN
#define XCLK_DM_OD_LO           PIN_DM_OD_LO
#define XCLK_DM_OD_HI           PIN_DM_OD_HI
#define XCLK_DM_STRONG          PIN_DM_STRONG
#define XCLK_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define XCLK_MASK               XCLK__MASK
#define XCLK_SHIFT              XCLK__SHIFT
#define XCLK_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define XCLK_PS                     (* (reg8 *) XCLK__PS)
/* Data Register */
#define XCLK_DR                     (* (reg8 *) XCLK__DR)
/* Port Number */
#define XCLK_PRT_NUM                (* (reg8 *) XCLK__PRT) 
/* Connect to Analog Globals */                                                  
#define XCLK_AG                     (* (reg8 *) XCLK__AG)                       
/* Analog MUX bux enable */
#define XCLK_AMUX                   (* (reg8 *) XCLK__AMUX) 
/* Bidirectional Enable */                                                        
#define XCLK_BIE                    (* (reg8 *) XCLK__BIE)
/* Bit-mask for Aliased Register Access */
#define XCLK_BIT_MASK               (* (reg8 *) XCLK__BIT_MASK)
/* Bypass Enable */
#define XCLK_BYP                    (* (reg8 *) XCLK__BYP)
/* Port wide control signals */                                                   
#define XCLK_CTL                    (* (reg8 *) XCLK__CTL)
/* Drive Modes */
#define XCLK_DM0                    (* (reg8 *) XCLK__DM0) 
#define XCLK_DM1                    (* (reg8 *) XCLK__DM1)
#define XCLK_DM2                    (* (reg8 *) XCLK__DM2) 
/* Input Buffer Disable Override */
#define XCLK_INP_DIS                (* (reg8 *) XCLK__INP_DIS)
/* LCD Common or Segment Drive */
#define XCLK_LCD_COM_SEG            (* (reg8 *) XCLK__LCD_COM_SEG)
/* Enable Segment LCD */
#define XCLK_LCD_EN                 (* (reg8 *) XCLK__LCD_EN)
/* Slew Rate Control */
#define XCLK_SLW                    (* (reg8 *) XCLK__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define XCLK_PRTDSI__CAPS_SEL       (* (reg8 *) XCLK__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define XCLK_PRTDSI__DBL_SYNC_IN    (* (reg8 *) XCLK__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define XCLK_PRTDSI__OE_SEL0        (* (reg8 *) XCLK__PRTDSI__OE_SEL0) 
#define XCLK_PRTDSI__OE_SEL1        (* (reg8 *) XCLK__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define XCLK_PRTDSI__OUT_SEL0       (* (reg8 *) XCLK__PRTDSI__OUT_SEL0) 
#define XCLK_PRTDSI__OUT_SEL1       (* (reg8 *) XCLK__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define XCLK_PRTDSI__SYNC_OUT       (* (reg8 *) XCLK__PRTDSI__SYNC_OUT) 


#if defined(XCLK__INTSTAT)  /* Interrupt Registers */

    #define XCLK_INTSTAT                (* (reg8 *) XCLK__INTSTAT)
    #define XCLK_SNAP                   (* (reg8 *) XCLK__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_XCLK_H */


/* [] END OF FILE */
