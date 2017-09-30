
#include "hard.h"
#include "Task.h"
#include "IO.h"
#include "def.h"
#include "Light.h"


void IO_Init(void)
{
    //Reset all outputs
    LATA = 0x00;
    LATB = 0x00;
    LATC = 0x00;
    LATD = 0x00;
    LATE = 0x00;
    
    //Configure IO
    // 0 Output - 1 Input
    TRISA = 0b11000000;  //(osc   | osc   | LED4 | LED3 | LED2    | LED1   | Vlum | Vbp)
    TRISB = 0b11111001;  //(PGD   | PGC   | -    | -    | CANRX   | CAN_TX |CAN_EN| - )
    TRISC = 0b11111111;  //(Rx_TTL| Tx_TTL| -    | I2C_SDA | I2C_SCL | -   | -   | -)
    TRISD = 0b11111011;  //(Rx_TTL| Tx_TTL| -    | I2C_SDA | I2C_SCL | -   | -   | -)
    TRISE = 0b11111011;  //(Rx_TTL| Tx_TTL| -    | I2C_SDA | I2C_SCL | -   | -   | -)
    
    //By default, set all IO as digital (erased by ADC module if used) 
    ADCON1 = 0b00001111;
}


T_output_mapping PinMapping[16] =
{
/*	physicalNum;
	unsigned char port;         // PortA, ..., PortE
	unsigned char portPin;
*/
    
	{ 2u, PORT_A, PIN0},	// RA0
	{ 3u, PORT_A, PIN1},	// output 1
	{ 4u, PORT_A, PIN2},	// output 2
	{ 5u, PORT_A, PIN3},	// output 3
	{ 6u, PORT_A, PIN4},	// output 4
	{ 7u, PORT_A, PIN5},	// output 5
	{ 8u, PORT_E, PIN0},  // output 6
	{ 9u, PORT_E, PIN1},  // output 7
	{ 10u, PORT_E, PIN2}, // output 8
 	{ 15u, PORT_C, PIN0}, // output 9
 	{ 16u, PORT_C, PIN1}, // output 10
	{ 17u, PORT_C, PIN2}, // output 11
	{ 18u, PORT_C, PIN3}, // output 12
 	{ 19u, PORT_D, PIN0}, // output 13
	{ 20u, PORT_D, PIN1}, // output 14
	{ 21u, PORT_D, PIN2}  // output 15
    
};


void IOsetState( T_output_mapping * num, unsigned char set )
{
	switch( num->port )
	{
		case PORT_A :
			if( set )
				LATA |= (unsigned char)( 1 << num->portPin);
			else
				LATA &= (unsigned char)( ~(1<<num->portPin) );
		break;
		
		case PORT_B:
			if( set )
				LATB |= (unsigned char)(1<<num->portPin);
			else
				LATB &= (unsigned char)(~(1<<num->portPin));
		break;
	
		case PORT_C:
			if( set )
				LATC |= (unsigned char)(1<<num->portPin);
			else
				LATC &= (unsigned char)(~(1<<num->portPin));
		break;
		
		case PORT_D:
			if( set )
				LATD |= (unsigned char)(1<<num->portPin);
			else
				LATD &= (unsigned char)(~(1<<num->portPin));
		break;
		
		case PORT_E:
			if( set )
				LATE |= (1<<num->portPin);
			else
				LATE &= (unsigned char)(~(1<<num->portPin));
		break;
        
        default:
        break;
	}
}

unsigned char IOcheckState(unsigned char outputIndex )
{
    unsigned char port, pin, functIdx, retval=0;

    port = PinMapping[functIdx].port;
    pin = PinMapping[functIdx].portPin;
    
    // Then check pin state
    switch( port )
    {
        case PORT_A:
            retval = ( PORTA & (1u<<pin) );
        break;
        case PORT_B:
            retval = ( LATB & (1u<<pin) );
        break;
        case PORT_C:
            retval = ( LATC & (1u<<pin) );
        break;
        case PORT_D:
            retval = ( LATD & (1u<<pin) );
        break;
        case PORT_E:
            retval = ( LATE & (1u<<pin) );
        break;
        
        default:
        break;
    }
    
    return retval;
}

