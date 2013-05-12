/*******************************************************************************
* File Name: DataBus.h  
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

#if !defined(CY_PINS_DataBus_H) /* Pins DataBus_H */
#define CY_PINS_DataBus_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "DataBus_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_80 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 DataBus__PORT == 15 && ((DataBus__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    DataBus_Write(uint8 value) ;
void    DataBus_SetDriveMode(uint8 mode) ;
uint8   DataBus_ReadDataReg(void) ;
uint8   DataBus_Read(void) ;
uint8   DataBus_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define DataBus_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define DataBus_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define DataBus_DM_RES_UP          PIN_DM_RES_UP
#define DataBus_DM_RES_DWN         PIN_DM_RES_DWN
#define DataBus_DM_OD_LO           PIN_DM_OD_LO
#define DataBus_DM_OD_HI           PIN_DM_OD_HI
#define DataBus_DM_STRONG          PIN_DM_STRONG
#define DataBus_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define DataBus_MASK               DataBus__MASK
#define DataBus_SHIFT              DataBus__SHIFT
#define DataBus_WIDTH              8u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define DataBus_PS                     (* (reg8 *) DataBus__PS)
/* Data Register */
#define DataBus_DR                     (* (reg8 *) DataBus__DR)
/* Port Number */
#define DataBus_PRT_NUM                (* (reg8 *) DataBus__PRT) 
/* Connect to Analog Globals */                                                  
#define DataBus_AG                     (* (reg8 *) DataBus__AG)                       
/* Analog MUX bux enable */
#define DataBus_AMUX                   (* (reg8 *) DataBus__AMUX) 
/* Bidirectional Enable */                                                        
#define DataBus_BIE                    (* (reg8 *) DataBus__BIE)
/* Bit-mask for Aliased Register Access */
#define DataBus_BIT_MASK               (* (reg8 *) DataBus__BIT_MASK)
/* Bypass Enable */
#define DataBus_BYP                    (* (reg8 *) DataBus__BYP)
/* Port wide control signals */                                                   
#define DataBus_CTL                    (* (reg8 *) DataBus__CTL)
/* Drive Modes */
#define DataBus_DM0                    (* (reg8 *) DataBus__DM0) 
#define DataBus_DM1                    (* (reg8 *) DataBus__DM1)
#define DataBus_DM2                    (* (reg8 *) DataBus__DM2) 
/* Input Buffer Disable Override */
#define DataBus_INP_DIS                (* (reg8 *) DataBus__INP_DIS)
/* LCD Common or Segment Drive */
#define DataBus_LCD_COM_SEG            (* (reg8 *) DataBus__LCD_COM_SEG)
/* Enable Segment LCD */
#define DataBus_LCD_EN                 (* (reg8 *) DataBus__LCD_EN)
/* Slew Rate Control */
#define DataBus_SLW                    (* (reg8 *) DataBus__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define DataBus_PRTDSI__CAPS_SEL       (* (reg8 *) DataBus__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define DataBus_PRTDSI__DBL_SYNC_IN    (* (reg8 *) DataBus__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define DataBus_PRTDSI__OE_SEL0        (* (reg8 *) DataBus__PRTDSI__OE_SEL0) 
#define DataBus_PRTDSI__OE_SEL1        (* (reg8 *) DataBus__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define DataBus_PRTDSI__OUT_SEL0       (* (reg8 *) DataBus__PRTDSI__OUT_SEL0) 
#define DataBus_PRTDSI__OUT_SEL1       (* (reg8 *) DataBus__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define DataBus_PRTDSI__SYNC_OUT       (* (reg8 *) DataBus__PRTDSI__SYNC_OUT) 


#if defined(DataBus__INTSTAT)  /* Interrupt Registers */

    #define DataBus_INTSTAT                (* (reg8 *) DataBus__INTSTAT)
    #define DataBus_SNAP                   (* (reg8 *) DataBus__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_DataBus_H */


/* [] END OF FILE */
