/* 
 * File:   ADC.h
 * Author: Spirit
 *
 * Created on 18 mars 2017, 19:46
 */

#ifndef ADC_H
#define	ADC_H

#ifdef	__cplusplus
extern "C" {
#endif

void ADC_Init(void);
unsigned int Read_Analog_channel(unsigned char channel);

#ifdef	__cplusplus
}
#endif

#endif	/* ADC_H */

