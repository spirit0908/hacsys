
/************************************************************************
* INCLUDES *
*************************************************************************/
#include <p18cxxx.h>
#include "Can.h"
#include "def.h"
#include "hard.h"

/************************************************************************
* GLOBAL VARIABLES *
*************************************************************************/

/************************************************************************
* FUNCTIONS *
*************************************************************************/

void Can_Init(void)
{
    // Enter CAN module into config mode
    CANCON = 0x80; // Set config Mode
    while ((CANSTAT & 0x80) != 0x80);

    // Enter CAN module into Mode 1
    //ECANCON = 0x40;
    ECANCON = 0x00;
    
    // Initialize CAN Timing
#if CLOCK_FREQ == CLOCK_FREQ_8MHz
 #if CAN_FREQ == CAN_FREQ_125kbps
    //125kbps @ 8MHz
    BRGCON1 = 0x01;
    BRGCON2 = 0xAC;
    BRGCON3 = 0x02;
 #elif CAN_FREQ == CAN_FREQ_250kbps
    //250kbps @ 8MHz
    BRGCON1 = 0x01;
    BRGCON2 = 0x90;
    BRGCON3 = 0x02;
 #elif CAN_FREQ == CAN_FREQ_500kbps
    //500kbps @ 8Mhz
    BRGCON1 = 0x00;
    BRGCON2 = 0x91;
    BRGCON3 = 0x01;
 #elif CAN_FREQ == CAN_FREQ_1000kbps
    #error Value is not possible for this CAN clock frequency.
 #else
  #error INVALID CAN RATE at 8MHz!
 #endif
#elif CLOCK_FREQ == CLOCK_FREQ_10MHz
 #if CAN_FREQ == CAN_FREQ_125kbps
    //125kbps @ 10Mhz 
    BRGCON1 = 0x01;
    BRGCON2 = 0xB6;
    BRGCON3 = 0x04;
 #elif CAN_FREQ == CAN_FREQ_250kbps
    //250kbps @ 10Mhz 
    BRGCON1 = 0x00;
    BRGCON2 = 0xBA;
    BRGCON3 = 0x07;
 #elif CAN_FREQ == CAN_FREQ_500kbps
    //500kbps @ 10Mhz
    BRGCON1 = 0x00;
    BRGCON2 = 0x92;
    BRGCON3 = 0x02;
 #elif CAN_FREQ == CAN_FREQ_1000kbps
    //1Mbps @ 10Mhz
    BRGCON1 = 0x00;
    BRGCON2 = 0x80;
    BRGCON3 = 0x01;
 #else
  #error INVALID CAN RATE at CLOCK FREQ 10MHz!
 #endif
#else
 #error No CLOCK FREQ configured or invalid frequence !
#endif

    // Mask acceptance: receive everything
    RXM0SIDL = 0x00;
    RXM0SIDH = 0x00;
    /*
        // Setup Programmable buffers
        //  B0 is a receive buffer AND B2,B3,B4,B5 are Transmit buffers
        BSEL0 = 0xF8;   //1111 10--
    
        // Initialize Receive Masks
        //  The first mask is used that accepts all SIDs and no EIDs
        RXM0EIDH = 0x00;    // 
        RXM0EIDL = 0x00;
        RXM0SIDH = 0xFF;    // Standard ID FILTER
        RXM0SIDL = 0xE0;
    
        //  The second mask is used that accepts all SIDs and EIDs
        RXM1EIDH = 0x00;    // 0's for EID and SID
        RXM1EIDL = 0x00;
        RXM1SIDH = 0xFF;
        RXM1SIDL = 0xE0;
    
        // Enable Filters
        //  Only using first three filters
        RXFCON0 = 0x07;     //Enable Filters 0,1,2
        RXFCON1 = 0x00;     //Disable all others
    
        // Assign Filters to Masks
        MSEL0 = 0xC0;     //Assign Filters 0-2 to Mask 0 //F  3 3 No mask
        MSEL1 = 0xFF;     //Assign Filters 4-7 to Mask     // No mask
        MSEL2 = 0xFF;     //Assign Filters 8-11 to Mask    // No mask
        MSEL3 = 0xFF;     //Assign Filters 12-15 to Mask   // No mask
    
        // Assign Filters to Buffers
    
        RXFBCON0 = 0x10;     //Assign Filter 0 to RXB0, and Filter 1 to RXB1
        RXFBCON1 = 0xF2;     //Assign Filter 2 to B0, Filter 2 no filter
    
        RXFBCON2 = 0xFF;     //Assign the rest of the buffers with no filter
        RXFBCON3 = 0xFF;
        RXFBCON4 = 0xFF;
        RXFBCON5 = 0xFF;
        RXFBCON6 = 0xFF;
        RXFBCON7 = 0xFF;
    
        // Initialize Receive Filters
        //  Filter 0 = 0x196
        //  Filter 1 = 0x19A
        //  Filter 2 = 0x19E
        RXF0EIDH = 0x00;
        RXF0EIDL = 0x00;
        RXF0SIDH = 0x32;
        RXF0SIDL = 0xC0;
        RXF1EIDH = 0x00;
        RXF1EIDL = 0x00;
        RXF1SIDH = 0x33;
        RXF1SIDL = 0x40;
        RXF2EIDH = 0x00;
        RXF2EIDL = 0x00;
        RXF2SIDH = 0x33;
        RXF2SIDL = 0xC0;
     */

    CIOCON = 0x20; // CANTX HiZ when recessive

    CANCON = 0x00;
    Nop();
    //while ((CANSTAT & 0xE0) != 0x00);

    // Set Receive Mode for buffers
    RXB0CON = 0x00;
    RXB1CON = 0x00;

    // Set interrupt :
    PIE3bits.IRXIE = DISABLE; // CAN Invalid Received Message Interrupt Enable bit
    PIE3bits.WAKIE = DISABLE; // CAN bus Activity Wake-up Interrupt Enable bit
    PIE3bits.ERRIE = DISABLE; // CAN bus Error Interrupt Enable bit
    PIE3bits.TXB2IE = DISABLE; // CAN Transmit Buffer 2 Interrupt Enable bit
    PIE3bits.TXB1IE = DISABLE; // CAN Transmit Buffer 1 Interrupt Enable bit(1)
    PIE3bits.TXB0IE = DISABLE; // CAN Transmit Buffer 0 Interrupt Enable bit(1)
    PIE3bits.RXB1IE = ENABLE; // CAN Receive Buffer 1 Interrupt Enable bit
    PIE3bits.RXB0IE = ENABLE; // CAN Receive Buffer 0 Interrupt Enable bit
}

void CanTrcvEnable(void)
{
    // Set CAN tranceiver in HighSpeed mode
    CAN_EN = 0;
}

void CanTrcvDisable(void)
{
    // Set CAN tranceiver in Standby or SLEEP mode 
    CAN_EN = 1;
}

void CAN_Start(void)
{
    // Enable tranceiver
    CanTrcvEnable();

    //Enable interrupts
    PIE3bits.IRXIE = DISABLE; // CAN Invalid Received Message Interrupt Enable bit
    PIE3bits.WAKIE = DISABLE; // CAN bus Activity Wake-up Interrupt Enable bit
    PIE3bits.ERRIE = DISABLE; // CAN bus Error Interrupt Enable bit
    PIE3bits.TXB2IE = DISABLE; // CAN Transmit Buffer 2 Interrupt Enable bit
    PIE3bits.TXB1IE = DISABLE; // CAN Transmit Buffer 1 Interrupt Enable bit(1)
    PIE3bits.TXB0IE = DISABLE; // CAN Transmit Buffer 0 Interrupt Enable bit(1)
    PIE3bits.RXB1IE = ENABLE; // CAN Receive Buffer 1 Interrupt Enable bit
    PIE3bits.RXB0IE = ENABLE; // CAN Receive Buffer 0 Interrupt Enable bit
}

void CAN_Stop(void)
{
    // Disable interrupts:
    PIE3bits.IRXIE = DISABLE; // CAN Invalid Received Message Interrupt Enable bit
    PIE3bits.WAKIE = DISABLE; // CAN bus Activity Wake-up Interrupt Enable bit
    PIE3bits.ERRIE = DISABLE; // CAN bus Error Interrupt Enable bit
    PIE3bits.TXB2IE = DISABLE; // CAN Transmit Buffer 2 Interrupt Enable bit
    PIE3bits.TXB1IE = DISABLE; // CAN Transmit Buffer 1 Interrupt Enable bit(1)
    PIE3bits.TXB0IE = DISABLE; // CAN Transmit Buffer 0 Interrupt Enable bit(1)
    PIE3bits.RXB1IE = DISABLE; // CAN Receive Buffer 1 Interrupt Enable bit
    PIE3bits.RXB0IE = DISABLE; // CAN Receive Buffer 0 Interrupt Enable bit
    
    // Disable tranceiver
    CAN_EN = 1;
}

/*********************************************************************
 *                Check the buffers, if it have message
 *********************************************************************/
unsigned char Can_Receive(unsigned char ctrl, unsigned int *addr, unsigned char *lengh, unsigned char *data)
{
    unsigned char *pData, i;
    unsigned char retVal;

    switch(ctrl)
    {
        case CAN_CTRL_0:
            if (RXB0CONbits.RXFUL) //CheckRXB0
            {
                if( RXB0SIDL & 0x08 ) // EXID bit
                {
                    //Extended frame
                    *addr = (unsigned int)( (RXB0EIDL) |            //bits 0:7
                                            (RXB0EIDH << 8) |       //bits 8:15
                                            ((RXB0SIDL & 0x03)<<16)|//bits 16:17
                                            (((RXB0SIDL >> 3)&0x1C)<<16) );//bits 18:20
                }
                else
                {
                    //Standard frame
                    *addr = (unsigned int)( (RXB0SIDL >> 5) | (RXB0SIDH << 3) );
                }
                *lengh = RXB0DLC;

                pData = (unsigned char*)&RXB0D0;
                for(i=0u; i<8u; i++)
                    data[i++] = *pData++;
                
                data[0] = RXB0D0;
                data[1] = RXB0D1;
                data[2] = RXB0D2;
                data[3] = RXB0D3;
                data[4] = RXB0D4;
                data[5] = RXB0D5;
                data[6] = RXB0D6;
                data[7] = RXB0D7;
                
                
                RXB0CONbits.RXFUL = 0;
                retVal = ret_OK;
            }
            else
            {
                retVal = ret_NOK;
            }
            break;
            
        case CAN_CTRL_1:
            if (RXB1CONbits.RXFUL) //CheckRXB1
            {
                if( RXB1SIDL & 0x08 ) // EXID bit
                {
                    //Extended frame
                    *addr = (unsigned int)( (RXB1EIDL) |            //bits 0:7
                                            (RXB1EIDH << 8) |       //bits 8:15
                                            ((RXB1SIDL & 0x03)<<16)|//bits 16:17
                                            (((RXB1SIDL >> 3)&0x1C)<<16) );//bits 18:20
                }
                else
                {
                    //Standard frame
                    *addr = (unsigned int)( (RXB1SIDL >> 5) | (RXB1SIDH << 3) );
                }
                *lengh = RXB1DLC;
                
                pData = (unsigned char*)&RXB1D0;
                for(i=0u; i<8u; i++)
                    data[i++] = *pData++;
                
                RXB1CONbits.RXFUL = 0;
                retVal = ret_OK;
            }
            else
            {
                retVal = ret_NOK;
            }
            break;
    }
    
    return retVal;
}

unsigned char Can_Transmit_data(unsigned char addr, unsigned char length, unsigned char *data)
{
    unsigned char *ptr_TXB0Data;
    unsigned char i;
    unsigned char retval;

    // If TXB0 buffer is free, use it
    if (TXB0CONbits.TXREQ == 0)
    {
        //TXB0EIDH = 0x00;
        //TXB0EIDL = 0x00;

        // Set Identifier (Standard ID < 1023)
        TXB0SIDH = (unsigned char)(addr >> 3);
        TXB0SIDL = (unsigned char)((addr << 5) & 0xE0);

        // Set data length
        TXB0DLC = length;

        // Set used Data bytes :
        ptr_TXB0Data = (unsigned char*) &TXB0D0;
        
        for (i = 0; i < length; i++)
            *ptr_TXB0Data++ = *data++;
        
        TXB0CONbits.TXREQ = 1; //Set transmit request
        retval = ret_OK;
    }
    else if (TXB1CONbits.TXREQ == 0) {
        retval = ret_NOK;
    }
    else {
        retval = ret_NOK;
    }
    
    return retval;
}

