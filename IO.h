/* 
 * File:   IO.h
 * Author: spirit
 *
 * Created on June 5, 2017, 4:19 PM
 */

#ifndef IO_H
#define	IO_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct
{
    unsigned char physicalNum;  //
	unsigned char port;         // PortA, ..., PortE
	unsigned char portPin;      // 0...7
}T_output_mapping;

//extern T_FctGrp fct_group[];
extern T_output_mapping PinMapping[];



void IO_Init(void);
void IOsetState( T_output_mapping * num, unsigned char set );
unsigned char IOcheckState(unsigned char outputIndex );



#ifdef	__cplusplus
}
#endif

#endif	/* IO_H */

