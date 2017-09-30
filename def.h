/****************************************
* def.h
****************************************/

#include "Can.h"

#define PIC18F2680 0
#define PIC18F4680 1


//
#define FALSE			0u
#define TRUE			1u

#define ret_OK          1u
#define ret_NOK         0u



// other
#define DISABLE 		0u
#define ENABLE			1u
	
#define FALLING_EDGE	0u
#define RISING_EDGE		1u

#define PRIORITY_LOW	0u
#define PRIORITY_HIGH	1u

// Serial order
#define SERIAL_IDLE					0u
#define SERIAL_DEVICE_CONNECTED 	1u
#define SERIAL_WAIT_ORDER			2u


// Output type
#define TYPE_LIGHT                  1u
#define TYPE_HEATING                2u
#define TYPE_SHUTTER                3u

// Order types
#define ORDER_BROADCAST 0x00
#define ORDER_LIGHT     0x10
#define ORDER_HEATING   0x20
#define ORDER_SHUTTER   0x30

// pushType
#define SHORTPUSH		0u
#define LONGPUSH		1u

// FREQ/Rate Settings
#define CAN_FREQ			CAN_FREQ_500kbps
//#define CLOCK_FREQ			CLOCK_FREQ_10MHz


#define STEP_INPUT_READ					0u
#define STEP_RUN						1u
#define STEP_EMISSION_CAN				2u
#define STEP_RECEPTION_CAN				3u
#define STEP_CHECK_COND_TO_SLEEP		4u
#define STEP_GO_TO_SLEEP				5u
#define STEP_CHECK_CONTINUE_TO_SLEEP 	6u
	

#define PORT_A      0u
#define PORT_B      1u
#define PORT_C      2u
#define PORT_D      3u
#define PORT_E      4u
#define PORT_F      5u

#define PIN0        0u
#define PIN1        1u
#define PIN2        2u
#define PIN3        3u
#define PIN4        4u
#define PIN5        5u
#define PIN6        6u
#define PIN7        7u



#define MAX_LIGHT_NUM       4u


