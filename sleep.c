
#include <p18cxxx.h>
#include "def.h"
#include "Can.h"
#include "interrupt.h"


void wakeUp( void );

void goToSleepMode(void)
{
	// Set CAN bus in sleep_mode
	
	// Reset ADC
	
	// Activate watchdog
	WDTCONbits.SWDTEN = 1;
	
	// Enter Deep Sleep Mode
	OSCCONbits.IDLEN = 0;	// Deep sleep mode
	Sleep();				
	
	// ********
	// At wakeup, µC continue to execute code after Sleep() instruction
	// Reset watchdor :
	WDTCONbits.SWDTEN = 0;
	
    // Init CAN
    ECAN_Init();
}
