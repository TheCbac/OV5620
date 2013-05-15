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
    // No reset pins
    PWND_Write(0);
    RST_B_Write(1);

   
    //SccbRead(0x42, 0x1d); // Manufacturer number
    SccbWrite(0x42,0x15,0x20); // No PCLK during HREF low
    SccbWrite(0x42,0x11,0x8f); // clock output
    SccbWrite(0x42,0x12,0x25); // Output is CIF, BAYER RAW is 21
    SccbWrite(0x42,0x13,0x87); // Auto Gain Control, Auto White Balance, Auto Exposure
    SccbWrite(0x42,0x2b,0x08); //8 dummy pixels 
    SccbWrite(0x42,0x1e,0x31); //enable vertical flip and mirror 
    
    /*
    SccbWrite(0x60,0x12,0x80); // initiates soft reset
    CyDelay(20);
    SccbWrite(0x60,0x12,0x00); // Binning 08 is 1/8 binning
    SccbWrite(0x60,0x11,0x7f); // Output clock divider
    SccbWrite(0x60,0x32,0xc0); //pixel clock divider 1/4
    SccbWrite(0x60,0x15,0x20); // PCLK output only when HREF high
    SccbWrite(0x60,0x80,0x11); //Color bar enable (Test pattern?)
    //SccbWrite(0x60,0x0c,0x0d); //  enable custom output
    //SccbWrite(0x60,0x61,0x1e); // 240
   // SccbWrite(0x60,0x60,0x19); // 240
    //SccbWrite(0x60,0x1b,0x05); //pixel shift
    //SccbWrite(0x60,0x09,0x04); //Slave Mode
    //SccbRead(0x60,0x12);
    */
  
}

void CameraConfigFull()
{
    SccbWrite(0x42,0x15,0x20); // No PCLK during HREF low
    SccbWrite(0x42,0x11,0x8f); // clock output scalling factor
    SccbWrite(0x42,0x12,0x05); // Output is full, 05 is processed bayer, 01 is raw
    SccbWrite(0x42,0x13,0x87); // Auto Gain Control, Auto White Balance, Auto Exposure
    //SccbWrite(0x42,0x2b,0x08); //8 dummy pixels 
    SccbWrite(0x42,0x1e,0x31); //enable vertical flip and mirror
}


//###################### END SCCB FUNCTIONS ######################

void DMA_Config();

uint8 buffer[640] = {0};
uint8 length;
uint8 pixel;
uint16 row, column=0;
uint16 count=0;
uint8 camState=1; //0 is CIF(356x292), 1 is VGA(640x480)
uint8 buffIn;
uint16 hrows=292;
uint16 vrows=356;

//uint8 imageData0[350][350];



/* DMA Configuration for DMA */
#define DMA_BYTES_PER_BURST 1
#define DMA_REQUEST_PER_BURST 1
#define DMA_SRC_BASE (CYDEV_PERIPH_BASE)
#define DMA_DST_BASE (CYDEV_SRAM_BASE)


// global variable for the DMA channel
uint8 DMA_Chan;
uint8 DMA_TD[1];
 


// sendData()

void sendData()
{
        // if VGA 640x480
        if (camState==1)
        { 
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
         while(USB_bGetEPState(1) != USB_IN_BUFFER_EMPTY);
        USB_LoadInEP(1, &buffer[320], 64);
                 while(USB_bGetEPState(1) != USB_IN_BUFFER_EMPTY);
        USB_LoadInEP(1, &buffer[384], 64);
                 while(USB_bGetEPState(1) != USB_IN_BUFFER_EMPTY);
        USB_LoadInEP(1, &buffer[448], 64);
                 while(USB_bGetEPState(1) != USB_IN_BUFFER_EMPTY);
        USB_LoadInEP(1, &buffer[512], 64);
                 while(USB_bGetEPState(1) != USB_IN_BUFFER_EMPTY);
        USB_LoadInEP(1, &buffer[576], 64);
              
        }
        
        else{  
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
         while(USB_bGetEPState(1) != USB_IN_BUFFER_EMPTY);
        USB_LoadInEP(1, &buffer[320], 64);
        }

       
} 

// isr_PCLK
/*
CY_ISR(PCLK_Interrupt)
{

   buffer[column]=DataBus_Read();
   ++column;

}
*/

CY_ISR(VREF_Interrupt)
{ 
    // Clear any pending requests on the TD
    CyDmaClearPendingDrq(DMA_Chan);
    
    // Enable the channel
    CyDmaChEnable(DMA_Chan, 1);   
}

/*
CY_ISR(VREF_FALL_Interrupt)
{ 
    //LED_Write(0);
    row=0;
    isr_PCLK_Enable();  
}*/
/*
CY_ISR(HREF_Interrupt)
{

    //isr_PCLK_Enable();
    column=0;

}*/
/*
CY_ISR(HREF_FALL_Interrupt)
{
    isr_PCLK_Disable();
    isr_HREF_Disable();
    isr_HREF_FALL_Disable();
    isr_VREF_Disable();
    sendData();
    
}*/
/*
CY_ISR(RX_Interrupt)

{
    LED_Write(1); // Turn on an LED

   isr_VREF_Enable(); // Start the Image
    
}
*/

uint8 state=0;


// This isr fires when the buffer is full, and the line is ready to be read out
CY_ISR(DMA_Interrupt)
{
   // Intiate the USB send data command
    state=1;
    

}


void main()
{
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
   // uint8 test;
    LCD_Char_1_Start();
    LCD_Char_1_DisplayOn();

   
    // set the vector for the vertical sync isr
    isr_VREF_StartEx(VREF_Interrupt);
    // disable the isr 
    isr_VREF_Disable();
    // When the DMA has written 320 bytes to the buffer isr_DMA will trigger
    isr_DMA_StartEx(DMA_Interrupt);    
    // Configure DMA to transfer from Camera to internal buffer
    isr_DMA_Disable();
   
    // Doesn't start until VREF_Interrupt fires
    
   
    // config in full VGA (640x480)    
    if (camState==1){
    CameraConfigFull();
    hrows=480;
    vrows=640;
    }
    // config in CIF 356x292
    else{
    CameraConfig();
    hrows=292;
    vrows=356;
    }
    DMA_Config();
        
    
    //global interrupt enable    
    CyGlobalIntEnable; 
     
// ############### Wait for USB command (OR 8051)  ####################
    //Start the USB and wait for it to connect

    
    USB_Start(0u, USB_3V_OPERATION);
    while(!USB_bGetConfiguration());
    
    //Enable the EndPoint as output
    USB_EnableOutEP(2);
    
    
    //Read from the computer and wait for a byte to be sent
    while(USB_bGetEPState(2) !=USB_OUT_BUFFER_FULL);
    length = USB_wGetEPCount(2);
    USB_ReadOutEP(2, &buffIn, length);

  
    
 

    
    // Turn on the LED for testing purposes 
    LED_Write(1);
    
    // Clear any pending interrupts, so isr_Enable() doesn't fire immediately
    isr_VREF_ClearPending();
    isr_VREF_Enable();
    
    isr_DMA_ClearPending();
    isr_DMA_Enable();
    
    // Send out 320 bytes of data
    //sendData();
    
    
    for(;;)
    {
        if (state==1)
        {
            Pin_5_Write(1);
            
            sendData();
            Pin_5_Write(0);
            state=0;
            ++count; 
            
            if (count>=hrows)
            {
                    // Stop the DMA 
                    CyDmaChDisable(DMA_Chan);
                    
                    // Stop VREF from Reenabling it
                    isr_VREF_Disable();
                    isr_DMA_Disable();
                    
                    // reset the row count
                    count=0;
                    
                    //wait for new USB command 
                    while(USB_bGetEPState(2) !=USB_OUT_BUFFER_FULL);
                    length = USB_wGetEPCount(2);
                     USB_ReadOutEP(2, &buffIn, length);
                     
                      // restart imaging
                    isr_VREF_ClearPending();
                    isr_VREF_Enable();
    
                    isr_DMA_ClearPending();
                    isr_DMA_Enable();
                     
                    
                    
            }
            
        }
        
       
    }
    
}



// Set up the DMA from camera to USB
void DMA_Config()
{
    /* Variable declarations for DMA */
    /* Move these variable declarations to the top of the function */
    
    // Set up the DMA channel with 1 byte per burst, and 1 request per burst
    DMA_Chan = DMA_DmaInitialize(DMA_BYTES_PER_BURST, DMA_REQUEST_PER_BURST,HI16(DMA_SRC_BASE), HI16(DMA_DST_BASE));
    
    // Create the Transaction Descriptor (TD)
    DMA_TD[0] = CyDmaTdAllocate();
    
    // Configure the TD , len of transfer, next TD, and enable output
    CyDmaTdSetConfiguration(DMA_TD[0], vrows, DMA_INVALID_TD, TD_TERMIN_EN | DMA__TD_TERMOUT_EN | TD_INC_DST_ADR);
    
    // the source is from status register, the destination is the buffer
    CyDmaTdSetAddress(DMA_TD[0], LO16((uint32)Status_Reg_1_Status_PTR), LO16((uint32)buffer));
    
    // Set the initial TD to be executed when CyDmaChEnable() is called 
    CyDmaChSetInitialTd(DMA_Chan, DMA_TD[0]);
    
    // Don't enable the channel until isr_VREF has been called 
    //CyDmaChEnable(DMA_Chan, 1);


}



/* [] END OF FILE */