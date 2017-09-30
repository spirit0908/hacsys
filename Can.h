#ifndef _CAN_H
#define _CAN_H


/* *** Defines *** */ 
#define TRUE    1u
#define FALSE   0u

#define CAN_CTRL_0  0u
#define CAN_CTRL_1  1u

// CAN bus Frequency
#define CAN_FREQ_125kbps    1
#define CAN_FREQ_250kbps    2
#define CAN_FREQ_500kbps    3
#define CAN_FREQ_1000kbps   4

// Clock Frequency
#define CLOCK_FREQ_8MHz	    1
#define CLOCK_FREQ_10MHz    2


/* Function Prototypes  */

void Can_Init(void);
void CanTrcvEnable(void);
void CanTrcvDisable(void);
void CAN_Start(void);
void CAN_Stop(void);

unsigned char Can_Receive(unsigned char ctrl, unsigned int *addr, unsigned char *lengh, unsigned char *data);
unsigned char Can_Transmit_data(unsigned char addr, unsigned char length, unsigned char *data);

#endif
