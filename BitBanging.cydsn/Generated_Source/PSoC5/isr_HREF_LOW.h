/*******************************************************************************
* File Name: isr_HREF_LOW.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_isr_HREF_LOW_H)
#define CY_ISR_isr_HREF_LOW_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void isr_HREF_LOW_Start(void);
void isr_HREF_LOW_StartEx(cyisraddress address);
void isr_HREF_LOW_Stop(void);

CY_ISR_PROTO(isr_HREF_LOW_Interrupt);

void isr_HREF_LOW_SetVector(cyisraddress address);
cyisraddress isr_HREF_LOW_GetVector(void);

void isr_HREF_LOW_SetPriority(uint8 priority);
uint8 isr_HREF_LOW_GetPriority(void);

void isr_HREF_LOW_Enable(void);
uint8 isr_HREF_LOW_GetState(void);
void isr_HREF_LOW_Disable(void);

void isr_HREF_LOW_SetPending(void);
void isr_HREF_LOW_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the isr_HREF_LOW ISR. */
#define isr_HREF_LOW_INTC_VECTOR            ((reg32 *) isr_HREF_LOW__INTC_VECT)

/* Address of the isr_HREF_LOW ISR priority. */
#define isr_HREF_LOW_INTC_PRIOR             ((reg8 *) isr_HREF_LOW__INTC_PRIOR_REG)

/* Priority of the isr_HREF_LOW interrupt. */
#define isr_HREF_LOW_INTC_PRIOR_NUMBER      isr_HREF_LOW__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable isr_HREF_LOW interrupt. */
#define isr_HREF_LOW_INTC_SET_EN            ((reg32 *) isr_HREF_LOW__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the isr_HREF_LOW interrupt. */
#define isr_HREF_LOW_INTC_CLR_EN            ((reg32 *) isr_HREF_LOW__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the isr_HREF_LOW interrupt state to pending. */
#define isr_HREF_LOW_INTC_SET_PD            ((reg32 *) isr_HREF_LOW__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the isr_HREF_LOW interrupt. */
#define isr_HREF_LOW_INTC_CLR_PD            ((reg32 *) isr_HREF_LOW__INTC_CLR_PD_REG)


#endif /* CY_ISR_isr_HREF_LOW_H */


/* [] END OF FILE */
