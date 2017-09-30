
/************************************************************************
* INCLUDES *
*************************************************************************/
#include "hard.h"
#include "ADC.h"
#include "def.h"


/************************************************************************
* FUNCTIONS *
*************************************************************************/
void ADC_Init(void)
{
    ADCON0 = 0x00;     // Disable ADC Module
    
    ADCON1 = (0<<5)|   // bit 5: Voltage Reference Configuration bit (VREF- source) - 1 = VREF- (AN2) - 0 = AVSS
             (0<<4)|   // bit 4 VCFG0: Voltage Reference Configuration bit (VREF+ source) - 1 = VREF+ (AN3) - 0 = AVDD
             (0b1110); // bit3-0: PCFG3:PCFG0: A/D Port Configuration Control bits
                       // 0b 1110 : AN0 is ANALOG, all other inputs are DIGITAL
    
    ADCON2 = (0<<7)  |   // bit 7 ADFM: A/D Result Format Select bit - 1 = Right justified - 0 = Left justified
                         // bit 6 Unimplemented: Read as ?0?
            (0b000<<3) | //bit 5-3 ACQT2:ACQT0: A/D Acquisition Time Select bits
                         // 111 = 20 TAD | 110 = 16 TAD | 101 = 12 TAD | 100 = 8 TAD
                         // 011 = 6 TAD  | 010 = 4 TAD  | 001 = 2 TAD  | 000 = 0 TAD(1)
            (0b100);     //bit 2-0 ADCS2:ADCS0: A/D Conversion Clock Select bits
                         // 111 = FRC (clock derived from A/D RC oscillator)(1)
                         // 110 = FOSC/64 | 101 = FOSC/16 | 100 = FOSC/4
                         // 011 = FRC (clock derived from A/D RC oscillator)(1)
                         // 010 = FOSC/32 | 001 = FOSC/8 | 000 = FOSC/2
}



unsigned int Read_Analog_channel(unsigned char channel)
{
    unsigned int result=ret_NOK;
    
    // First select channel to convert:
    ADCON0 = (unsigned char)( (channel<2) & 0x7C );
    
    // Start convertion:
    ADCON0 |= 0x01; // Enable converter module
    
    // Wait for convertion:
    while((ADCON0 & 0x02)); // Wait until convertion is in progress
    result = (unsigned int)(ADRESH<<8);
    result |= ADRESL;
        
    return result;
}

