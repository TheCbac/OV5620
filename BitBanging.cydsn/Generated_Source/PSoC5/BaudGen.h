/*******************************************************************************
* File Name: BaudGen.h
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

#if !defined(CY_CLOCK_BaudGen_H)
#define CY_CLOCK_BaudGen_H

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

void BaudGen_Start(void) ;
void BaudGen_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void BaudGen_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void BaudGen_StandbyPower(uint8 state) ;
void BaudGen_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 BaudGen_GetDividerRegister(void) ;
void BaudGen_SetModeRegister(uint8 modeBitMask) ;
void BaudGen_ClearModeRegister(uint8 modeBitMask) ;
uint8 BaudGen_GetModeRegister(void) ;
void BaudGen_SetSourceRegister(uint8 clkSource) ;
uint8 BaudGen_GetSourceRegister(void) ;
#if defined(BaudGen__CFG3)
void BaudGen_SetPhaseRegister(uint8 clkPhase) ;
uint8 BaudGen_GetPhaseRegister(void) ;
#endif /* defined(BaudGen__CFG3) */

#define BaudGen_Enable()                       BaudGen_Start()
#define BaudGen_Disable()                      BaudGen_Stop()
#define BaudGen_SetDivider(clkDivider)         BaudGen_SetDividerRegister(clkDivider, 1)
#define BaudGen_SetDividerValue(clkDivider)    BaudGen_SetDividerRegister((clkDivider) - 1, 1)
#define BaudGen_SetMode(clkMode)               BaudGen_SetModeRegister(clkMode)
#define BaudGen_SetSource(clkSource)           BaudGen_SetSourceRegister(clkSource)
#if defined(BaudGen__CFG3)
#define BaudGen_SetPhase(clkPhase)             BaudGen_SetPhaseRegister(clkPhase)
#define BaudGen_SetPhaseValue(clkPhase)        BaudGen_SetPhaseRegister((clkPhase) + 1)
#endif /* defined(BaudGen__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define BaudGen_CLKEN              (* (reg8 *) BaudGen__PM_ACT_CFG)
#define BaudGen_CLKEN_PTR          ((reg8 *) BaudGen__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define BaudGen_CLKSTBY            (* (reg8 *) BaudGen__PM_STBY_CFG)
#define BaudGen_CLKSTBY_PTR        ((reg8 *) BaudGen__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define BaudGen_DIV_LSB            (* (reg8 *) BaudGen__CFG0)
#define BaudGen_DIV_LSB_PTR        ((reg8 *) BaudGen__CFG0)
#define BaudGen_DIV_PTR            ((reg16 *) BaudGen__CFG0)

/* Clock MSB divider configuration register. */
#define BaudGen_DIV_MSB            (* (reg8 *) BaudGen__CFG1)
#define BaudGen_DIV_MSB_PTR        ((reg8 *) BaudGen__CFG1)

/* Mode and source configuration register */
#define BaudGen_MOD_SRC            (* (reg8 *) BaudGen__CFG2)
#define BaudGen_MOD_SRC_PTR        ((reg8 *) BaudGen__CFG2)

#if defined(BaudGen__CFG3)
/* Analog clock phase configuration register */
#define BaudGen_PHASE              (* (reg8 *) BaudGen__CFG3)
#define BaudGen_PHASE_PTR          ((reg8 *) BaudGen__CFG3)
#endif /* defined(BaudGen__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define BaudGen_CLKEN_MASK         BaudGen__PM_ACT_MSK
#define BaudGen_CLKSTBY_MASK       BaudGen__PM_STBY_MSK

/* CFG2 field masks */
#define BaudGen_SRC_SEL_MSK        BaudGen__CFG2_SRC_SEL_MASK
#define BaudGen_MODE_MASK          (~(BaudGen_SRC_SEL_MSK))

#if defined(BaudGen__CFG3)
/* CFG3 phase mask */
#define BaudGen_PHASE_MASK         BaudGen__CFG3_PHASE_DLY_MASK
#endif /* defined(BaudGen__CFG3) */

#endif /* CY_CLOCK_BaudGen_H */


/* [] END OF FILE */
