/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <device.h>

uint8 buffer[320], length;
uint8 count;


void init()
{
    // LCD Init
    LCD_Start();
    LCD_DisplayOn();
    //LCD_PrintNumber(1);
    
    
    ADC_Start();
    

}

void main()
{

   
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    CyGlobalIntEnable;  /* Uncomment this line to enable global interrupts. */
    init();
    // Start usb operation with 3V
    
    
    //Wait for device to enumerate
    USB_Start(0u,USB_3V_OPERATION);
    while(!USB_bGetConfiguration());
    
    //Enumeration i done, enable out endpoint for recieve data from host
    USB_EnableOutEP(2);
    
    ADC_StartConvert();
    
    
      while(1)
    {
        //wait for data
        while(USB_bGetEPState(2) !=USB_OUT_BUFFER_FULL);
        
        //read received bytes count
        length = USB_wGetEPCount(2);
        //turn on LED
        LED_Write(~LED_Read());
        
        //unload the out buffer
        USB_ReadOutEP(2, &buffer[0], length);
        
       // check for in buffer is empty
       while(USB_bGetEPState(1) != USB_IN_BUFFER_EMPTY);
       // Turn off LED
       
       
       // load the in buffer
       USB_LoadInEP(1, &buffer[0], length);
       while(USB_bGetEPState(1) != USB_IN_BUFFER_EMPTY);
        USB_LoadInEP(1, &buffer[1], length);
    
    
    }
    for(;;)
    {
    
        
   
        
    }
    
    
    
    
    
    /*
    while(!USB_bGetConfiguration());
    
    //Enumeration i done, enable out endpoint for recieve data from host
    USB_EnableOutEP(2);
    
    
    while(1)
    {
        //wait for data
        while(USB_bGetEPState(2) !=USB_OUT_BUFFER_FULL);
        
        //read received bytes count
        length = USB_wGetEPCount(2);
        //turn on LED
        LED_Write(~LED_Read());
        
        //unload the out buffer
        USB_ReadOutEP(2, &buffer[0], length);
        
       // check for in buffer is empty
       while(USB_bGetEPState(1) != USB_IN_BUFFER_EMPTY);
       // Turn off LED
       
       
       // load the in buffer
       USB_LoadInEP(1, &buffer[0], length);
    
    
    }*/
    
    
    /*
        if( ADC_IsEndConversion(ADC_WAIT_FOR_RESULT))
       {
            //LCD_ClearDisplay();
            //LCD_PrintNumber(ADC_GetResult16());
            //CyDelay(250);
            
            Pin_1_Write(~Pin_1_Read());
            
            //buffer[count]=ADC_GetResult8();
            buffer[count]=count;
            ++count;
            USB_LoadInEP(1,&buffer[0],1);
            
            if (count==64)
            {
                // load the in buffer
                //USB_LoadInEP(1, &buffer[0], 64);
                count=0;
            }
            
        }
        */
}

/* [] END OF FILE */
