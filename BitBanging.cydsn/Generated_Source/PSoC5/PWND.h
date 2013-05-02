/*******************************************************************************
* File Name: PWND.h  
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

#if !defined(CY_PINS_PWND_H) /* Pins PWND_H */
#define CY_PINS_PWND_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PWND_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_80 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 PWND__PORT == 15 && ((PWND__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    PWND_Write(uint8 value) ;
void    PWND_SetDriveMode(uint8 mode) ;
uint8   PWND_ReadDataReg(void) ;
uint8   PWND_Read(void) ;
uint8   PWND_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PWND_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define PWND_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define PWND_DM_RES_UP          PIN_DM_RES_UP
#define PWND_DM_RES_DWN         PIN_DM_RES_DWN
#define PWND_DM_OD_LO           PIN_DM_OD_LO
#define PWND_DM_OD_HI           PIN_DM_OD_HI
#define PWND_DM_STRONG          PIN_DM_STRONG
#define PWND_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define PWND_MASK               PWND__MASK
#define PWND_SHIFT              PWND__SHIFT
#define PWND_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PWND_PS                     (* (reg8 *) PWND__PS)
/* Data Register */
#define PWND_DR                     (* (reg8 *) PWND__DR)
/* Port Number */
#define PWND_PRT_NUM                (* (reg8 *) PWND__PRT) 
/* Connect to Analog Globals */                                                  
#define PWND_AG                     (* (reg8 *) PWND__AG)                       
/* Analog MUX bux enable */
#define PWND_AMUX                   (* (reg8 *) PWND__AMUX) 
/* Bidirectional Enable */                                                        
#define PWND_BIE                    (* (reg8 *) PWND__BIE)
/* Bit-mask for Aliased Register Access */
#define PWND_BIT_MASK               (* (reg8 *) PWND__BIT_MASK)
/* Bypass Enable */
#define PWND_BYP                    (* (reg8 *) PWND__BYP)
/* Port wide control signals */                                                   
#define PWND_CTL                    (* (reg8 *) PWND__CTL)
/* Drive Modes */
#define PWND_DM0                    (* (reg8 *) PWND__DM0) 
#define PWND_DM1                    (* (reg8 *) PWND__DM1)
#define PWND_DM2                    (* (reg8 *) PWND__DM2) 
/* Input Buffer Disable Override */
#define PWND_INP_DIS                (* (reg8 *) PWND__INP_DIS)
/* LCD Common or Segment Drive */
#define PWND_LCD_COM_SEG            (* (reg8 *) PWND__LCD_COM_SEG)
/* Enable Segment LCD */
#define PWND_LCD_EN                 (* (reg8 *) PWND__LCD_EN)
/* Slew Rate Control */
#define PWND_SLW                    (* (reg8 *) PWND__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PWND_PRTDSI__CAPS_SEL       (* (reg8 *) PWND__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PWND_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PWND__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PWND_PRTDSI__OE_SEL0        (* (reg8 *) PWND__PRTDSI__OE_SEL0) 
#define PWND_PRTDSI__OE_SEL1        (* (reg8 *) PWND__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PWND_PRTDSI__OUT_SEL0       (* (reg8 *) PWND__PRTDSI__OUT_SEL0) 
#define PWND_PRTDSI__OUT_SEL1       (* (reg8 *) PWND__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PWND_PRTDSI__SYNC_OUT       (* (reg8 *) PWND__PRTDSI__SYNC_OUT) 


#if defined(PWND__INTSTAT)  /* Interrupt Registers */

    #define PWND_INTSTAT                (* (reg8 *) PWND__INTSTAT)
    #define PWND_SNAP                   (* (reg8 *) PWND__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_PWND_H */


/* [] END OF FILE */
