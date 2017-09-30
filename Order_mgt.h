/* 
 * File:   Order_mgt.h
 * Author: spirit
 *
 * Created on June 8, 2017, 10:26 PM
 */

#ifndef ORDER_MGT_H
#define	ORDER_MGT_H

#ifdef	__cplusplus
extern "C" {
#endif

    
typedef struct{
    unsigned char ElemId;
    unsigned char type;
    unsigned int  Addr;
    unsigned char FctId;
    unsigned char (*pRxIndication)();
}T_FctGrp;


void OrderProcess(unsigned int CanId, unsigned char msgLenm, unsigned char msgData[8]);
void updateIndicStatus(unsigned char Idx);
void CanSendMessage(void);


#ifdef	__cplusplus
}
#endif

#endif	/* ORDER_MGT_H */

