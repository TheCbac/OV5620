/*******************************************************************************
* File Name: Clock.c  
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
#include "Clock.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 Clock__PORT == 15 && ((Clock__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: Clock_Write
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
void Clock_Write(uint8 value) 
{
    uint8 staticBits = (Clock_DR & (uint8)(~Clock_MASK));
    Clock_DR = staticBits | ((uint8)(value << Clock_SHIFT) & Clock_MASK);
}


/*******************************************************************************
* Function Name: Clock_SetDriveMode
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
void Clock_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Clock_0, mode);
}


/*******************************************************************************
* Function Name: Clock_Read
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
*  Macro Clock_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Clock_Read(void) 
{
    return (Clock_PS & Clock_MASK) >> Clock_SHIFT;
}


/*******************************************************************************
* Function Name: Clock_ReadDataReg
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
uint8 Clock_ReadDataReg(void) 
{
    return (Clock_DR & Clock_MASK) >> Clock_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Clock_INTSTAT) 

    /*******************************************************************************
    * Function Name: Clock_ClearInterrupt
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
    uint8 Clock_ClearInterrupt(void) 
    {
        return (Clock_INTSTAT & Clock_MASK) >> Clock_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
