/*******************************************************************************
* File Name: DataLine.h  
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

#if !defined(CY_PINS_DataLine_H) /* Pins DataLine_H */
#define CY_PINS_DataLine_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "DataLine_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_80 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 DataLine__PORT == 15 && ((DataLine__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    DataLine_Write(uint8 value) ;
void    DataLine_SetDriveMode(uint8 mode) ;
uint8   DataLine_ReadDataReg(void) ;
uint8   DataLine_Read(void) ;
uint8   DataLine_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define DataLine_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define DataLine_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define DataLine_DM_RES_UP          PIN_DM_RES_UP
#define DataLine_DM_RES_DWN         PIN_DM_RES_DWN
#define DataLine_DM_OD_LO           PIN_DM_OD_LO
#define DataLine_DM_OD_HI           PIN_DM_OD_HI
#define DataLine_DM_STRONG          PIN_DM_STRONG
#define DataLine_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define DataLine_MASK               DataLine__MASK
#define DataLine_SHIFT              DataLine__SHIFT
#define DataLine_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define DataLine_PS                     (* (reg8 *) DataLine__PS)
/* Data Register */
#define DataLine_DR                     (* (reg8 *) DataLine__DR)
/* Port Number */
#define DataLine_PRT_NUM                (* (reg8 *) DataLine__PRT) 
/* Connect to Analog Globals */                                                  
#define DataLine_AG                     (* (reg8 *) DataLine__AG)                       
/* Analog MUX bux enable */
#define DataLine_AMUX                   (* (reg8 *) DataLine__AMUX) 
/* Bidirectional Enable */                                                        
#define DataLine_BIE                    (* (reg8 *) DataLine__BIE)
/* Bit-mask for Aliased Register Access */
#define DataLine_BIT_MASK               (* (reg8 *) DataLine__BIT_MASK)
/* Bypass Enable */
#define DataLine_BYP                    (* (reg8 *) DataLine__BYP)
/* Port wide control signals */                                                   
#define DataLine_CTL                    (* (reg8 *) DataLine__CTL)
/* Drive Modes */
#define DataLine_DM0                    (* (reg8 *) DataLine__DM0) 
#define DataLine_DM1                    (* (reg8 *) DataLine__DM1)
#define DataLine_DM2                    (* (reg8 *) DataLine__DM2) 
/* Input Buffer Disable Override */
#define DataLine_INP_DIS                (* (reg8 *) DataLine__INP_DIS)
/* LCD Common or Segment Drive */
#define DataLine_LCD_COM_SEG            (* (reg8 *) DataLine__LCD_COM_SEG)
/* Enable Segment LCD */
#define DataLine_LCD_EN                 (* (reg8 *) DataLine__LCD_EN)
/* Slew Rate Control */
#define DataLine_SLW                    (* (reg8 *) DataLine__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define DataLine_PRTDSI__CAPS_SEL       (* (reg8 *) DataLine__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define DataLine_PRTDSI__DBL_SYNC_IN    (* (reg8 *) DataLine__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define DataLine_PRTDSI__OE_SEL0        (* (reg8 *) DataLine__PRTDSI__OE_SEL0) 
#define DataLine_PRTDSI__OE_SEL1        (* (reg8 *) DataLine__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define DataLine_PRTDSI__OUT_SEL0       (* (reg8 *) DataLine__PRTDSI__OUT_SEL0) 
#define DataLine_PRTDSI__OUT_SEL1       (* (reg8 *) DataLine__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define DataLine_PRTDSI__SYNC_OUT       (* (reg8 *) DataLine__PRTDSI__SYNC_OUT) 


#if defined(DataLine__INTSTAT)  /* Interrupt Registers */

    #define DataLine_INTSTAT                (* (reg8 *) DataLine__INTSTAT)
    #define DataLine_SNAP                   (* (reg8 *) DataLine__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_DataLine_H */


/* [] END OF FILE */
