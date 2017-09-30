
#include "hard.h"

#include "def.h"
#include "Task.h"
#include "hard.h"
#include "FIFO.h"
#include "interrupt.h"
#include "Task_cfg.h"


//void InterruptHandlerHigh(void);
//void InterruptHandlerLow(void);

unsigned int CanRxMsg_addr;
unsigned char CanRxMsg_lengh;
unsigned char CanRxMsg_data[8];

/*#pragma code InterruptVectorHigh = 0x08 // High ISR

void InterruptVectorHigh(void) {
#asm
    goto InterruptHandlerHigh //jump to interrupt routine
#endasm
}

#pragma code InterruptVectorLow = 0x18 // Low ISR

void InterruptVectorLow(void) {
#asm
    goto InterruptHandlerLow //jump to interrupt routine
#endasm
}*/

//#pragma interrupt InterruptHandlerHigh
//void InterruptHandlerHigh(void)
void interrupt high_priority High_ISR(void) // High interrupt handler
{
    INTCONbits.GIE = 0;
    INTCONbits.PEIE = 0;

    // --- Timer IT ---

    if (INTCONbits.TMR0IF) // TMR0IF 
    {
        TMR0H = 0xB1; //0xFF; //0xF4 ;
        TMR0L = 0xDF; //0x37; //0x24 ;

        Task_Manager_IT();

        INTCONbits.TMR0IF = 0; //clear interrupt flag
    }

    if (PIR1bits.TMR1IF) // TMR1IF 
    {
        TMR1H = 0xB1;
        TMR1L = 0xDF;
    
        PIR1bits.TMR1IF = 0;
    }

    if (PIR1bits.TMR2IF) // TMR2IF 
    {
        PIR1bits.TMR2IF = 0;
    }

    // --- INT/RB port IT ---
    if (INTCONbits.INT0IF) // signal 100Hz
    {
        INTCONbits.INT0IF = 0;
    }


    // --- CAN IT ---

    if (PIR3bits.RXB0IF) // RX0 interrupt
    {
        Can_Receive(CAN_CTRL_0, &CanRxMsg_addr, &CanRxMsg_lengh, CanRxMsg_data);
        CAN_FIFO_add( &CAN_RX_FIFO, CanRxMsg_addr, CanRxMsg_lengh, CanRxMsg_data );
        
        TaskAdd_unique(Task_CanMsgProcess_ID);
        
        PIR3bits.RXB0IF = 0;
    }
    
    if (PIR3bits.RXB1IF) // RX0 interrupt
    {
        Can_Receive(CAN_CTRL_1, &CanRxMsg_addr, &CanRxMsg_lengh, CanRxMsg_data);
        CAN_FIFO_add( &CAN_RX_FIFO, CanRxMsg_addr, CanRxMsg_lengh, CanRxMsg_data );
        
        TaskAdd_unique(Task_CanMsgProcess_ID);
        
        PIR3bits.RXB1IF = 0;
    }
    
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
}

//#pragma interrupt InterruptHandlerLow

//void InterruptHandlerLow(void)
void interrupt low_priority Low_ISR(void) // Low interrupt handler
{
    INTCONbits.GIE = 0;
    INTCONbits.PEIE = 0;

    // --- Timer IT ---

    /*if (INTCONbits.TMR0IF) // TMR0IF 
    {
        TMR0H = 0xB1; //0xFF;
        TMR0L = 0xDF; //0x37;

        INTCONbits.TMR0IF = 0; //clear interrupt flag
    }*/

    /*if (PIR1bits.TMR1IF) // TMR1IF 
    {
        TMR1H = 0xB1; //0xFF;
        TMR1L = 0xDF; //0x37;
        
        Task_Manager_IT();
        //Nop();
        PIR1bits.TMR1IF = 0;
    }*/

    if (PIR1bits.TMR2IF) // TMR2IF 
    {
        Nop();
    }

    /*if (PIR1bits.TMR3IF) // TMR3IF 
    {
        Nop();
    }*/

    // --- INT/RB change IT ---

    // --- CAN IT ---
    // *** CAN Invalid Received Message *** 
    if( PIR3bits.IRXIF )
    {
        PIR3bits.IRXIF=0;
    }
    
    // ***  CAN bus Activity Wake-up ***
    if( PIR3bits.WAKIF )
    {
        PIR3bits.WAKIF=0;
    }

    // *** CAN bus Error Interrupt ***
    if( PIR3bits.ERRIF )
    {
        PIR3bits.ERRIF=0;
    }    

    // *** CAN Transmit Buffer 2 ***
    if( PIR3bits.TXB2IF )
    {
        PIR3bits.TXB2IF=0;
    }
    
    // *** CAN Transmit Buffer 1 ***
    if( PIR3bits.TXB1IF )
    {
        PIR3bits.TXB1IF=0;
    }
    
    // *** CAN Transmit Buffer 0 ***
    if( PIR3bits.TXB0IF )
    {
        PIR3bits.TXB0IF=0;
    }
    
    // *** CAN Receive Buffer 1 ***
    if( PIR3bits.RXB1IF )
    {
        PIR3bits.RXB1IF=0;
    }
    
    // *** CAN Receive Buffer 0 ***
    if( PIR3bits.RXB0IF )
    {
        PIR3bits.RXB0IF=0;
    }
    
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
}

//#pragma code

void IT_Init(void) {
    INTCONbits.GIE = 0;  // Disables all interrupt
    INTCONbits.PEIE = 0; // Disable peripheral interrupts

    // *** Timer0 : ***
    // T = 1/(Fosc/4) * prediv * ( TMR0_max - TMR0_preload )

    INTCONbits.TMR0IE = 0;

    //T0CON = 0b11000001 ; //T0CON = 0b11000010 ;
    // dividor     : 1:2   = 000
    //				 1:4   = 001
    //				 1:256 = 111

    // - Timer : 100ms 
    // - prescal = 62500, TMR=62500=0xF424
    // - timer 16 bits
    T0CON = 0x00 |
            (0 << 7) | // TMR0ON - disable Timer0 for configuration
            (0 << 6) | // T08BIT - 0=16bits - 1=8bits
            (0 << 5) | // T0CS   - clock source : 1:T0CKI - 0:internal
            (0 << 4) | // T0SE   - 0:increment on low-to-high - 1:increment on high-to-low on TOCKI
            (1 << 3) | // PSA    - 1:no prescal - 0:prescal (see below)
            (0b000); // T0PS2:T0PS0 - prescal 000:1/2 - 111:1/256

    TMR0H = 0xFF; // TMR0 = 0xF424
    TMR0L = 0x37;

    T0CONbits.TMR0ON = ENABLE; //Disable Timer0 (TMR0ON)

    INTCON2bits.TMR0IP = 0; // TMR0 priority
    INTCONbits.TMR0IE = 1; // TMR0 IT enable state
    INTCONbits.TMR0IF = 0; // Reset TMR0 IT flag

    // *** Timer1 ***
    T1CON = 0x00 |
           (1 << 7) | //RD1 - 16bits Read/Write Mode (1:16bits / 0:8bits)
           (1 << 6) | //T1RUN - System clock status (1:Timer1 oscillator / 0:another source)
           (00 << 4)| //T1KPS1:T1CKPS0 - Timer1 prescaler
                      //00=1:1 / 01=1:2 / 10=1:4 / 11=1:8
           (0 << 3) | //T1OSCEN - Timer1 oscillator enabled
           (1 << 2) | //T1SYNC
           (0 << 1) | //TMR1CS - Timer1 Clock source (0=Fosc/4 - 1=ext pin)
           (0);       //TMR1ON
            
    //10ms interrupt
//    TMR1H = 0xB1;
//    TMR1L = 0xDF;
    
    //2ms interrupt
    TMR1H = 0xF0;
    TMR1L = 0x5F;
            
    T1CONbits.TMR1ON = ENABLE;
    IPR1bits.TMR1IP  = PRIORITY_LOW;
    PIE1bits.TMR1IE  = ENABLE;
    PIR1bits.TMR1IF  = 0;
    
    // *** Timer2 ***
    T2CONbits.TMR2ON = DISABLE;
    IPR1bits.TMR2IP  = PRIORITY_LOW;
    PIE1bits.TMR2IE  = DISABLE;
    PIR1bits.TMR2IF  = 0;
    
    // *** Timer3 ***
    T3CONbits.TMR3ON = DISABLE;
    IPR2bits.TMR3IP  = PRIORITY_LOW;
    PIE2bits.TMR3IE  = DISABLE;
    PIR2bits.TMR3IF  = 0;
    
    // *** INT0/RB0 : ***
    INTCON2bits.INTEDG0 = FALLING_EDGE; // edge select
    INTCONbits.INT0IF = 0; // Reset INT0 flag
    INTCONbits.INT0IE = DISABLE; // INT0 enable state

    // *** INT1/RB1 ***
    INTCON2bits.INTEDG1 = FALLING_EDGE; // edge select
    INTCON3bits.INT1IP = PRIORITY_LOW; // Priority
    INTCON3bits.INT1IF = 0; // Reset INT1 flag
    INTCON3bits.INT1IE = DISABLE; // INT1 enable state

    // *** INT2/RBx ***
    INTCON2bits.INTEDG2 = FALLING_EDGE; // edge select
    INTCON3bits.INT2IP = PRIORITY_LOW; // Priority
    INTCON3bits.INT2IF = 0; // Reset INT1 flag
    INTCON3bits.INT2IE = DISABLE; // INT1 enable state

    // *** Interrupt on RB change ***
    INTCONbits.RBIE = DISABLE; // RB change interrupt enable
    INTCONbits.RBIF = 0; // Reset the RB IT flag
    INTCON2bits.RBIP = PRIORITY_LOW; // Prority of RB change IT
    
    
    INTCONbits.GIE = 0; // Disables all interrupt
    INTCONbits.PEIE = 01; // Disable peripheral interrupts
}


void Peripheral_IT_Init(void)
{
    // *** CAN Interrupts ***
    
    // *** CAN Receive Buffer 0 ***
    PIE3bits.RXB0IE = ENABLE;
    IPR3bits.RXB0IP = PRIORITY_HIGH;
    PIR3bits.RXB0IF = 0;
    
    // *** CAN Receive Buffer 1 ***
    PIE3bits.RXB1IE = ENABLE;
    IPR3bits.RXB1IP = PRIORITY_HIGH;
    PIR3bits.RXB1IF = 0;
    
    // *** CAN Transmit Buffer 0 ***
    PIE3bits.TXB0IE = ENABLE;
    IPR3bits.TXB0IP = PRIORITY_LOW;
    PIR3bits.TXB0IF = 0;
    
    // *** CAN Transmit Buffer 1 ***
    PIE3bits.TXB1IE = DISABLE;
    IPR3bits.TXB1IP = PRIORITY_LOW;
    PIR3bits.TXB1IF = 0;
    
    // *** CAN Transmit Buffer 2 ***
    PIE3bits.TXB2IE = DISABLE;
    IPR3bits.TXB2IP = PRIORITY_LOW;
    PIR3bits.TXB2IF = 0;    
    
    // *** CAN Invalid Received Message *** 
    PIE3bits.IRXIE = DISABLE;
    IPR3bits.IRXIP = PRIORITY_LOW;
    PIR3bits.IRXIF = 0;
    
    // ***  6 : CAN bus Activity Wake-up ***
    PIE3bits.WAKIE = DISABLE;
    IPR3bits.WAKIP = PRIORITY_LOW;
    PIR3bits.WAKIF = 0;
    
    // *** CAN bus Error Interrupt ***
    PIE3bits.ERRIE = DISABLE;
    IPR3bits.ERRIP = PRIORITY_LOW;
    PIR3bits.ERRIF = 0;
}

void SEI(void) // Set Interrupt
{
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
}

void CLI(void) // Cleat Interrupt
{
    INTCONbits.GIE = 0;
    INTCONbits.PEIE = 0;
}


