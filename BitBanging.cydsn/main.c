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
int vsync =0;
uint8 picture[10][10];
uint8 Row =0;
uint8 Column =0;

//##################################### SCCB FUNCTIONS ####################################

// This Function pulses the Clock line
void pump()
{
    CyDelayUs(3);
    ClockLine_Write(1);
    CyDelayUs(5);
    ClockLine_Write(0);
    CyDelayUs(3);
}


// This is the end sequence for sccb
void endSeq()
{
    ClockLine_Write(1);  //End Sequence
    CyDelayUs(3);
    DataLine_Write(1);
    
    CyDelayUs(50);
}

// THis is the Start sequnce for sccb
void startSeq()
{
    DataLine_Write(0); // Start Transmission
    CyDelayUs(3);
    ClockLine_Write(0);
    CyDelayUs(5);
}


void SccbWritePhase1(uint8 id, uint8 addr)
{
    int i;
    
    // Phase 1 Write
     startSeq();
    
    for( i=sizeof(id)*CHAR_BIT-1; i>=0;--i) // write the device id
    {
        int bit = (id>>i) & 1;
        DataLine_Write(bit);
        pump();
    }
    
    DataLine_Write(0); // Don't Care bit
    pump();
    // Phase 2 Write
    for( i=sizeof(addr)*CHAR_BIT-1; i>=0;--i) // write the register
    {
        int bit = (addr>>i) & 1;
        DataLine_Write(bit);
        pump();
    }    
    
    DataLine_Write(0); // Don't Care bit
    pump();

    }
    


void SccbWrite(uint8 id, uint8 addr, uint8 byte)
{
    SccbWritePhase1(id, addr);
    int i;
    for( i=sizeof(byte)*CHAR_BIT-1; i>=0;--i) // write the register
    {
        int bit = (byte>>i) & 1;
        DataLine_Write(bit);
        pump();
    }    
    
    DataLine_Write(0); // Don't Care bit
    pump();
    endSeq();
    
}

void SccbRead(uint8 id, uint8 addr )
{
    int i;
    SccbWritePhase1(id, addr);
    endSeq();
    startSeq();
    
    //Phase 1 Read
    id++; // for read
    for( i=sizeof(id)*CHAR_BIT-1; i>=0;--i) // write the device id+1 for read
    {
        int bit = (id>>i) & 1;
        DataLine_Write(bit);
        pump();
    }
    
    //Phase 2 read
    // read data 
    pump(); //don't care bit
    
    
    for( i=7; i>=0;--i) // write the device id
    {
       
       /*if(i==8){DataLine_Read();} // ignore first bit
       
       else{LCD_Char_1_PrintNumber(DataLine_Read());}*/
       
        LCD_Char_1_PrintNumber(DataLine_Read());
        CyDelayUs(15);
        pump();
    }
    
    DataLine_Write(1);
    pump();
    DataLine_Write(0);
    CyDelayUs(4);   
 
    endSeq();
    
}
void CameraConfig()
{
    //SccbWrite(0x60,0x12,0x80); // initiates soft reset
    SccbWrite(0x60,0x12,0x10); // Binning 08 is 1/8 binning
    SccbWrite(0x60,0x11,0x7f); // Output clock divider
    SccbWrite(0x60,0x32,0xc0); //pixel clock divider 1/4
    SccbWrite(0x60,0x15,0x20); // PCLK output only when HREF high
    SccbWrite(0x60,0x80,0x11); //Color bar enable (Test pattern?)
    //SccbWrite(0x60,0x1b,0x05); //pixel shift
    SccbWrite(0x60,0x09,0x04); //Slave Mode
    //SccbRead(0x60,0x12);

}

//###################### END SCCB FUNCTIONS ######################

uint8 buffer[350],length;
uint8 pixel;
uint16 row, column=0;
//uint8 imageData0[350][350];
uint8 pos;
uint8 imageNumber;
uint8 state;
uint8 status=0;
uint16 countpc;

void sendData()
{
        Pin_5_Write(1);
        LED_Write(0);
        while(USB_bGetEPState(1) != USB_IN_BUFFER_EMPTY); 
        USB_LoadInEP(1, &buffer[0], 64);
        
            //LCD_Char_1_PrintNumber(USB_bGetEPState(1));
        while(USB_bGetEPState(1) != USB_IN_BUFFER_EMPTY);
        USB_LoadInEP(1, &buffer[64], 64);
           // LCD_Char_1_PrintNumber(USB_bGetEPState(1));
        while(USB_bGetEPState(1) != USB_IN_BUFFER_EMPTY);
        USB_LoadInEP(1, &buffer[128], 64);
           // LCD_Char_1_PrintNumber(USB_bGetEPState(1));
        while(USB_bGetEPState(1) != USB_IN_BUFFER_EMPTY);
        USB_LoadInEP(1, &buffer[192], 64);
           // LCD_Char_1_PrintNumber(USB_bGetEPState(1));
        while(USB_bGetEPState(1) != USB_IN_BUFFER_EMPTY);
        USB_LoadInEP(1, &buffer[256], 64);
           // LCD_Char_1_PrintNumber(USB_bGetEPState(1));
        LED_Write(1);
        Pin_5_Write(0);
        /*
        
        while(USB_bGetEPState(1) != USB_IN_BUFFER_EMPTY);
        USB_LoadInEP(1, &buffer[64], 64);
        while(USB_bGetEPState(1) != USB_IN_BUFFER_EMPTY);
        USB_LoadInEP(1, &buffer[128], 64);
        while(USB_bGetEPState(1) != USB_IN_BUFFER_EMPTY);
        USB_LoadInEP(1, &buffer[192], 64);
        while(USB_bGetEPState(1) != USB_IN_BUFFER_EMPTY);
        USB_LoadInEP(1, &buffer[256], 64);
       //Pin_5_Write(0);
       */
}



CY_ISR(PCLK_Interrupt)
{

   buffer[column]=DataBus_Read();
   ++column;

}


CY_ISR(VREF_Interrupt)
{ 
    Pin_5_Write(~Pin_5_Read());
    sendData();
    //isr_HREF_Enable(); // Start the HREF interrupts
    //isr_HREF_FALL_Enable();
    //isr_PCLK_Enable();
}

/*
CY_ISR(VREF_FALL_Interrupt)
{ 
    //LED_Write(0);
    row=0;
    isr_PCLK_Enable();  
}*/


CY_ISR(HREF_Interrupt)
{

    //isr_PCLK_Enable();
    column=0;

}

uint8 pixelarray[5];


CY_ISR(HREF_FALL_Interrupt)
{
    isr_PCLK_Disable();
    isr_HREF_Disable();
    isr_HREF_FALL_Disable();
    isr_VREF_Disable();
    sendData();
    
}
uint8 testarray[320];
uint8 counter=0;
uint8 testi;
uint16 size=255;

CY_ISR(RX_Interrupt)

{
    LED_Write(1); // Turn on an LED

   isr_VREF_Enable(); // Start the Image
    
}



void main()
{
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
   // uint8 test;
    LCD_Char_1_Start();
    LCD_Char_1_DisplayOn();

    
   // UART_Start();  
    PWND_Write(0);
    RST_B_Write(1);
    FREX_Write(0);
    EXPST_Write(0);

    isr_rx_StartEx(RX_Interrupt);        //UART Read Interrupt
    isr_PCLK_StartEx(PCLK_Interrupt);    //Pixel Clock interrupt
    isr_VREF_StartEx(VREF_Interrupt);    // Rising vertical sync 
    //isr_VREF_FALL_StartEx(VREF_FALL_Interrupt); //Falling vertical sync
    isr_HREF_StartEx(HREF_Interrupt); //Rising Horizontal sync
    isr_HREF_FALL_StartEx(HREF_FALL_Interrupt); // Falling Horizontal sync
    
    
    isr_VREF_SetPriority(0); //highest priority
    //isr_VREF_FALL_SetPriority(0);
    isr_HREF_SetPriority(1);
    //isr_HREF_LOW_SetPriority(1);
    isr_PCLK_SetPriority(2);
    
    isr_PCLK_Disable();
    isr_VREF_Disable();
    //isr_VREF_FALL_Disable();
    isr_HREF_Disable();
    isr_HREF_FALL_Disable();
    
    CameraConfig();
    
    //global enable    
    CyGlobalIntEnable; 
    /*
    FREX_Write(1);
    CyDelayUs(50);
    EXPST_Write(1);
    CyDelayUs(50);
    EXPST_Write(0);
    CyDelayUs(50);
    FREX_Write(0);
    */
    
    //Start the USB and wait for it to connect
    USB_Start(0u, USB_3V_OPERATION);
    while(!USB_bGetConfiguration());
    
    //Enable the EndPoint as output
    USB_EnableOutEP(2);
    
    
    //Read from the computer 
    while(USB_bGetEPState(2) !=USB_OUT_BUFFER_FULL);
    length = USB_wGetEPCount(2);
    USB_ReadOutEP(2, &buffer[0], length);
    
    //Start the transmission capture
    LED_Write(1);
    
    isr_VREF_ClearPending();
   // isr_VREF_Enable();
    sendData();
    
      
    
    for(;;)
    {
        /* Place your application code here. */
        
        /*
         if (pos >=255)
        {
            // CyGlobalIntDisable;
            isr_PCLK_Disable();
            isr_HREF_Disable();
            isr_VREF_Disable();       
             sendData();
        //LED_Write(1);
        }*/
    }
    
}


/*
    while(1)
    {
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
/* [] END OF FILE */