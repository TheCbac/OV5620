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

//###################### END SCCB FUNCTIONS ######################





CY_ISR(PCLK_Interrupt)
{
    /*  Place your Interrupt code here. */
    /* `#START isr_PCLK_Interrupt` */
    

    if(Column <10)
    {
        picture[Row][Column] = DataBus_Read();
        ++Column;
    }
 
    /*
    if(vsync <=1)
    {
        LCD_Char_1_PrintNumber(DataBus_Read());
        //LCD_Char_1_PrintString(" ");
        UART_WriteTxData(DataBus_Read());
    }
    else{;}
    */
    /* `#END` */
}

CY_ISR(VREF_Interrupt)
{ 
    /*  Place your Interrupt code here. */
    /* `#START isr_PCLK_Interrupt` */
    //LED_Write(~LED_Read());
    ++vsync;
    
    /* `#END` */
}

CY_ISR(HREF_Interrupt)
{
    /*  Place your Interrupt code here. */
    /* `#START isr_PCLK_Interrupt` */
    isr_PCLK_Enable();
    /* `#END` */
}

CY_ISR(HREF_LOW_Interrupt)
{
    isr_PCLK_Disable();
    if(Row<10)
    {
        ++Row;
    }
}


uint8 testarray[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
CY_ISR(RX_Interrupt)
{
    LED_Write(1);
    isr_PCLK_Disable();
    UART_PutArray(testarray, 10);
    
}


void main()
{
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
   // uint8 test;
    LCD_Char_1_Start();
    LCD_Char_1_DisplayOn();
    
    /*

    */
    
    isr_rx_StartEx(RX_Interrupt);
   
    UART_Start();
    
    PWND_Write(0);
    RST_B_Write(1);
    FREX_Write(0);
    EXPST_Write(0);
    
    
    //SccbWrite(0x60,0x12,0x80); // initiates soft reset
    SccbWrite(0x60,0x12,0x08); // Binning 08 is 1/8 binning
    SccbWrite(0x60,0x11,0x7f); // Output clock divider
    SccbWrite(0x60,0x32,0xc0); //pixel clock divider 1/4
    //SccbRead(0x60,0x12);


    // for Snap Shot 

       // LED_Write(1);
    isr_PCLK_StartEx(PCLK_Interrupt);
    isr_VREF_StartEx(VREF_Interrupt);
    isr_HREF_StartEx(HREF_Interrupt);
    isr_HREF_LOW_StartEx(HREF_LOW_Interrupt);
    
    isr_VREF_SetPriority(0); //highest priority
    isr_HREF_SetPriority(1);
    isr_HREF_LOW_SetPriority(1);
    isr_PCLK_SetPriority(2);
 
    
    FREX_Write(1);
    CyDelayUs(50);
    EXPST_Write(1);
    CyDelayUs(50);
    EXPST_Write(0);
    CyDelayUs(50);
    FREX_Write(0);
    
    
    
    CyGlobalIntEnable;  /* Uncomment this line to enable global interrupts. */
    
    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */