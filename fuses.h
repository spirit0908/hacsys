/**********************************************************************
* Project : HACSYS interrupteur4S
*
* FileName:        fuses.h
* Processor:       PIC18F2680
* Linker:          MPLINK 4.37+
* Compiler:        C18 3.36+
*
* REVISION HISTORY:
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Date          Comments on this revision
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* 20/10/2013    First release of source file
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Code Tested on: 
*
* DESCRIPTION:
*
*********************************************************************/


//
#pragma config OSC = HS         // oscillator in High Speed mode

#pragma config PWRT = OFF       // power-up timer
#pragma config BOREN = BOHW     // Brown-out Reset

#pragma config WDT = OFF        // Watchdog disabled
#pragma config WDTPS = 256      // 1:256 postscalar for watchdog timer

#pragma config LVP = OFF        // Signle-supply ICSP
#pragma config DEBUG = OFF      // Debug mode
#pragma config STVREN = ON      // Stack full/underflow reset


