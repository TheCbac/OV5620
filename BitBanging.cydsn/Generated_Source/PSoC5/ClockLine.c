/*******************************************************************************
* File Name: ClockLine.c  
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
#include "ClockLine.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 ClockLine__PORT == 15 && ((ClockLine__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: ClockLine_Write
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
void ClockLine_Write(uint8 value) 
{
    uint8 staticBits = (ClockLine_DR & (uint8)(~ClockLine_MASK));
    ClockLine_DR = staticBits | ((uint8)(value << ClockLine_SHIFT) & ClockLine_MASK);
}


/*******************************************************************************
* Function Name: ClockLine_SetDriveMode
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
void ClockLine_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(ClockLine_0, mode);
}


/*******************************************************************************
* Function Name: ClockLine_Read
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
*  Macro ClockLine_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 ClockLine_Read(void) 
{
    return (ClockLine_PS & ClockLine_MASK) >> ClockLine_SHIFT;
}


/*******************************************************************************
* Function Name: ClockLine_ReadDataReg
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
uint8 ClockLine_ReadDataReg(void) 
{
    return (ClockLine_DR & ClockLine_MASK) >> ClockLine_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(ClockLine_INTSTAT) 

    /*******************************************************************************
    * Function Name: ClockLine_ClearInterrupt
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
    uint8 ClockLine_ClearInterrupt(void) 
    {
        return (ClockLine_INTSTAT & ClockLine_MASK) >> ClockLine_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
