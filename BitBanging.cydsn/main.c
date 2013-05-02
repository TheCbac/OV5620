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

void main()
{
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    LCD_Char_1_Start();
    LCD_Char_1_DisplayOn();
    PWND_Write(0);
    RST_B_Write(1);
    FREX_Write(0);
    EXPST_Write(0);
    
    SccbWrite(0x60,0x00,0x0a);
    SccbRead(0x60,0x00);


       
    
    
    
    
    /* CyGlobalIntEnable; */ /* Uncomment this line to enable global interrupts. */
    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */