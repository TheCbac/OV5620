/*******************************************************************************
* File Name: FREX.c  
* Version 1.80
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "FREX.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 FREX__PORT == 15 && ((FREX__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: FREX_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None
*  
*******************************************************************************/
void FREX_Write(uint8 value) 
{
    uint8 staticBits = (FREX_DR & (uint8)(~FREX_MASK));
    FREX_DR = staticBits | ((uint8)(value << FREX_SHIFT) & FREX_MASK);
}


/*******************************************************************************
* Function Name: FREX_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to this drive mode.
*
* Return: 
*  None
*
*******************************************************************************/
void FREX_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(FREX_0, mode);
}


/*******************************************************************************
* Function Name: FREX_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro FREX_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 FREX_Read(void) 
{
    return (FREX_PS & FREX_MASK) >> FREX_SHIFT;
}


/*******************************************************************************
* Function Name: FREX_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 FREX_ReadDataReg(void) 
{
    return (FREX_DR & FREX_MASK) >> FREX_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(FREX_INTSTAT) 

    /*******************************************************************************
    * Function Name: FREX_ClearInterrupt
    ********************************************************************************
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 FREX_ClearInterrupt(void) 
    {
        return (FREX_INTSTAT & FREX_MASK) >> FREX_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
