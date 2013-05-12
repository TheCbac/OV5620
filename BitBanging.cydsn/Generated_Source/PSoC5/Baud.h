/*******************************************************************************
* File Name: Baud.h
* Version 2.0
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_Baud_H)
#define CY_CLOCK_Baud_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component cy_clock_v2_0 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void Baud_Start(void) ;
void Baud_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void Baud_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void Baud_StandbyPower(uint8 state) ;
void Baud_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 Baud_GetDividerRegister(void) ;
void Baud_SetModeRegister(uint8 modeBitMask) ;
void Baud_ClearModeRegister(uint8 modeBitMask) ;
uint8 Baud_GetModeRegister(void) ;
void Baud_SetSourceRegister(uint8 clkSource) ;
uint8 Baud_GetSourceRegister(void) ;
#if defined(Baud__CFG3)
void Baud_SetPhaseRegister(uint8 clkPhase) ;
uint8 Baud_GetPhaseRegister(void) ;
#endif /* defined(Baud__CFG3) */

#define Baud_Enable()                       Baud_Start()
#define Baud_Disable()                      Baud_Stop()
#define Baud_SetDivider(clkDivider)         Baud_SetDividerRegister(clkDivider, 1)
#define Baud_SetDividerValue(clkDivider)    Baud_SetDividerRegister((clkDivider) - 1, 1)
#define Baud_SetMode(clkMode)               Baud_SetModeRegister(clkMode)
#define Baud_SetSource(clkSource)           Baud_SetSourceRegister(clkSource)
#if defined(Baud__CFG3)
#define Baud_SetPhase(clkPhase)             Baud_SetPhaseRegister(clkPhase)
#define Baud_SetPhaseValue(clkPhase)        Baud_SetPhaseRegister((clkPhase) + 1)
#endif /* defined(Baud__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define Baud_CLKEN              (* (reg8 *) Baud__PM_ACT_CFG)
#define Baud_CLKEN_PTR          ((reg8 *) Baud__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define Baud_CLKSTBY            (* (reg8 *) Baud__PM_STBY_CFG)
#define Baud_CLKSTBY_PTR        ((reg8 *) Baud__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define Baud_DIV_LSB            (* (reg8 *) Baud__CFG0)
#define Baud_DIV_LSB_PTR        ((reg8 *) Baud__CFG0)
#define Baud_DIV_PTR            ((reg16 *) Baud__CFG0)

/* Clock MSB divider configuration register. */
#define Baud_DIV_MSB            (* (reg8 *) Baud__CFG1)
#define Baud_DIV_MSB_PTR        ((reg8 *) Baud__CFG1)

/* Mode and source configuration register */
#define Baud_MOD_SRC            (* (reg8 *) Baud__CFG2)
#define Baud_MOD_SRC_PTR        ((reg8 *) Baud__CFG2)

#if defined(Baud__CFG3)
/* Analog clock phase configuration register */
#define Baud_PHASE              (* (reg8 *) Baud__CFG3)
#define Baud_PHASE_PTR          ((reg8 *) Baud__CFG3)
#endif /* defined(Baud__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define Baud_CLKEN_MASK         Baud__PM_ACT_MSK
#define Baud_CLKSTBY_MASK       Baud__PM_STBY_MSK

/* CFG2 field masks */
#define Baud_SRC_SEL_MSK        Baud__CFG2_SRC_SEL_MASK
#define Baud_MODE_MASK          (~(Baud_SRC_SEL_MSK))

#if defined(Baud__CFG3)
/* CFG3 phase mask */
#define Baud_PHASE_MASK         Baud__CFG3_PHASE_DLY_MASK
#endif /* defined(Baud__CFG3) */

#endif /* CY_CLOCK_Baud_H */


/* [] END OF FILE */
