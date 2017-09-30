// Define of hardware design

#include "p18f4680.h"
#include "def.h"
#include "Can.h"


#define MCU PIC18F4680


#define OUTPUT_MAX_NB	0

// 
#define SORTIE0			LATAbits.LATA0
#define SORTIE1			LATAbits.LATA1
#define SORTIE2			LATAbits.LATA2
#define SORTIE3			LATAbits.LATA3

/*#define SORTIE4			LATAbits.LATA4
#define SORTIE5			LATAbits.LATA5
#define SORTIE6			LATEbits.LATE0
#define SORTIE7			LATEbits.LATE1

#define SORTIE8			LATEbits.LATE2
#define SORTIE9			LATCbits.LATC0
#define SORTIE10		LATCbits.LATC1
#define SORTIE11        LATCbits.LATC2
#define SORTIE12		LATCbits.LATC3
#define SORTIE13		LATDbits.LATD0
#define SORTIE14		LATDbits.LATD1
#define SORTIE15		LATDbits.LATD2
*/


#define LED1	LATAbits.LATA2
#define LED2	LATAbits.LATA3
#define LED3	LATAbits.LATA4
#define LED4	LATAbits.LATA5

//#define LED7    LATDbits.LATD2
#define LED9    LATEbits.LATE2

#define CAN_EN          LATBbits.LATB1

//#define CAN_FREQ        CAN_FREQ_250kbps
#define CLOCK_FREQ      CLOCK_FREQ_8MHz

//#define OWN_NODE_ID     0x75		/*between 0x01 and 0xFF, means up to 255 nodes)*/


#define OWN_CAN_ID          0x0075
#define CAN_ID_BROADCAST    0x0000