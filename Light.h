/* 
 * File:   Light.h
 *
 * Created on 11 f�vrier 2017, 11:42
 */

#ifndef LIGHT_H
#define	LIGHT_H

#ifdef	__cplusplus
extern "C" {
#endif

//#include "FIFO.h"

    
// Light orders
#define LIGHT_OFF                     0x10
#define LIGHT_ON                      0x11
#define LIGHT_REVERSE                 0x12
#define LIGHT_ON_SPECIFIED_BRIGHTNESS 0x13
#define LIGHT_ON_DEFAULT_BRIGHTNESS   0x14
#define LIGHT_ON_LAST_BRIGHTNESS      0x15
#define LIGHT_BRIGHTNESS_MORE         0x16
#define LIGHT_BRIGHTNESS_LESS         0x17
#define LIGHT_ON_TIMER                0x18
#define LIGHT_ON_TIMER_ADD_30S        0x19
#define LIGHT_INHIBIT_OUTPUT          0x0A
#define LIGHT_RELEASE_OUTPUT          0x0B


enum
{
    Light_ID_0 = 0,
    Light_ID_1,
    Light_ID_2,
    Light_ID_3,
    Light_ID_4,
    Light_ID_5,
    Light_ID_6,
    Light_ID_7,
    
    // Keep this position
    Light_ID_MAX
};
    

typedef struct
{
    unsigned char type;
    // type of output is:
    // - bit 7: 0: output is inactive / 1: output is active
    // - bit 6: 0: output is not dimmable / 1:output is dimmable
    // - bit 5: 0: timer can not be set / 1: timer can be set
    // - bit 4-0: NA
    unsigned char outPin;
    unsigned char curState;             // State/Brightness of current output: form 0 (OFF) to FF (MAX).
    unsigned char state;                // State/Brightness of current output: form 0 (OFF) to FF (MAX).
    unsigned char brightness_default;   // default brightness value
    unsigned char brightness_last;      // last brightness value recorded
    unsigned int  timer_default;        // default timer value
    unsigned int  timer_val;            // Current timer value
} T_LightState;
    

void Light_Init(void);
void Light_Init_cfg(void);
unsigned char LightOrderTmt( unsigned char LightId, unsigned char Order, unsigned char param );
void LightOrderProcess(void);
void LightSendStatus(void);
void LightSendOutputStatus(unsigned char i);



#ifdef	__cplusplus
}
#endif

#endif	/* LIGHT_H */
