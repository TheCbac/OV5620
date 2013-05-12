/*******************************************************************************
* File Name: DataBus.c  
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
#include "DataBus.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 DataBus__PORT == 15 && ((DataBus__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: DataBus_Write
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
void DataBus_Write(uint8 value) 
{
    uint8 staticBits = (DataBus_DR & (uint8)(~DataBus_MASK));
    DataBus_DR = staticBits | ((uint8)(value << DataBus_SHIFT) & DataBus_MASK);
}


/*******************************************************************************
* Function Name: DataBus_SetDriveMode
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
void DataBus_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(DataBus_0, mode);
	CyPins_SetPinDriveMode(DataBus_1, mode);
	CyPins_SetPinDriveMode(DataBus_2, mode);
	CyPins_SetPinDriveMode(DataBus_3, mode);
	CyPins_SetPinDriveMode(DataBus_4, mode);
	CyPins_SetPinDriveMode(DataBus_5, mode);
	CyPins_SetPinDriveMode(DataBus_6, mode);
	CyPins_SetPinDriveMode(DataBus_7, mode);
}


/*******************************************************************************
* Function Name: DataBus_Read
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
*  Macro DataBus_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 DataBus_Read(void) 
{
    return (DataBus_PS & DataBus_MASK) >> DataBus_SHIFT;
}


/*******************************************************************************
* Function Name: DataBus_ReadDataReg
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
uint8 DataBus_ReadDataReg(void) 
{
    return (DataBus_DR & DataBus_MASK) >> DataBus_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(DataBus_INTSTAT) 

    /*******************************************************************************
    * Function Name: DataBus_ClearInterrupt
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
    uint8 DataBus_ClearInterrupt(void) 
    {
        return (DataBus_INTSTAT & DataBus_MASK) >> DataBus_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
