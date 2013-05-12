/*******************************************************************************
* File Name: HREF.h  
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

#if !defined(CY_PINS_HREF_H) /* Pins HREF_H */
#define CY_PINS_HREF_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "HREF_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_80 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 HREF__PORT == 15 && ((HREF__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    HREF_Write(uint8 value) ;
void    HREF_SetDriveMode(uint8 mode) ;
uint8   HREF_ReadDataReg(void) ;
uint8   HREF_Read(void) ;
uint8   HREF_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define HREF_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define HREF_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define HREF_DM_RES_UP          PIN_DM_RES_UP
#define HREF_DM_RES_DWN         PIN_DM_RES_DWN
#define HREF_DM_OD_LO           PIN_DM_OD_LO
#define HREF_DM_OD_HI           PIN_DM_OD_HI
#define HREF_DM_STRONG          PIN_DM_STRONG
#define HREF_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define HREF_MASK               HREF__MASK
#define HREF_SHIFT              HREF__SHIFT
#define HREF_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define HREF_PS                     (* (reg8 *) HREF__PS)
/* Data Register */
#define HREF_DR                     (* (reg8 *) HREF__DR)
/* Port Number */
#define HREF_PRT_NUM                (* (reg8 *) HREF__PRT) 
/* Connect to Analog Globals */                                                  
#define HREF_AG                     (* (reg8 *) HREF__AG)                       
/* Analog MUX bux enable */
#define HREF_AMUX                   (* (reg8 *) HREF__AMUX) 
/* Bidirectional Enable */                                                        
#define HREF_BIE                    (* (reg8 *) HREF__BIE)
/* Bit-mask for Aliased Register Access */
#define HREF_BIT_MASK               (* (reg8 *) HREF__BIT_MASK)
/* Bypass Enable */
#define HREF_BYP                    (* (reg8 *) HREF__BYP)
/* Port wide control signals */                                                   
#define HREF_CTL                    (* (reg8 *) HREF__CTL)
/* Drive Modes */
#define HREF_DM0                    (* (reg8 *) HREF__DM0) 
#define HREF_DM1                    (* (reg8 *) HREF__DM1)
#define HREF_DM2                    (* (reg8 *) HREF__DM2) 
/* Input Buffer Disable Override */
#define HREF_INP_DIS                (* (reg8 *) HREF__INP_DIS)
/* LCD Common or Segment Drive */
#define HREF_LCD_COM_SEG            (* (reg8 *) HREF__LCD_COM_SEG)
/* Enable Segment LCD */
#define HREF_LCD_EN                 (* (reg8 *) HREF__LCD_EN)
/* Slew Rate Control */
#define HREF_SLW                    (* (reg8 *) HREF__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define HREF_PRTDSI__CAPS_SEL       (* (reg8 *) HREF__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define HREF_PRTDSI__DBL_SYNC_IN    (* (reg8 *) HREF__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define HREF_PRTDSI__OE_SEL0        (* (reg8 *) HREF__PRTDSI__OE_SEL0) 
#define HREF_PRTDSI__OE_SEL1        (* (reg8 *) HREF__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define HREF_PRTDSI__OUT_SEL0       (* (reg8 *) HREF__PRTDSI__OUT_SEL0) 
#define HREF_PRTDSI__OUT_SEL1       (* (reg8 *) HREF__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define HREF_PRTDSI__SYNC_OUT       (* (reg8 *) HREF__PRTDSI__SYNC_OUT) 


#if defined(HREF__INTSTAT)  /* Interrupt Registers */

    #define HREF_INTSTAT                (* (reg8 *) HREF__INTSTAT)
    #define HREF_SNAP                   (* (reg8 *) HREF__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_HREF_H */


/* [] END OF FILE */
