/*******************************************************************************
* File Name: HREF.c  
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
#include "HREF.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 HREF__PORT == 15 && ((HREF__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: HREF_Write
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
void HREF_Write(uint8 value) 
{
    uint8 staticBits = (HREF_DR & (uint8)(~HREF_MASK));
    HREF_DR = staticBits | ((uint8)(value << HREF_SHIFT) & HREF_MASK);
}


/*******************************************************************************
* Function Name: HREF_SetDriveMode
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
void HREF_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(HREF_0, mode);
}


/*******************************************************************************
* Function Name: HREF_Read
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
*  Macro HREF_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 HREF_Read(void) 
{
    return (HREF_PS & HREF_MASK) >> HREF_SHIFT;
}


/*******************************************************************************
* Function Name: HREF_ReadDataReg
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
uint8 HREF_ReadDataReg(void) 
{
    return (HREF_DR & HREF_MASK) >> HREF_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(HREF_INTSTAT) 

    /*******************************************************************************
    * Function Name: HREF_ClearInterrupt
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
    uint8 HREF_ClearInterrupt(void) 
    {
        return (HREF_INTSTAT & HREF_MASK) >> HREF_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
