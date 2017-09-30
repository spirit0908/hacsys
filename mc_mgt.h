/* 
 * File:   mc_mgt.h
 *
 * Created on 18 mars 2017, 19:24
 */

#ifndef MC_MGT_H
#define	MC_MGT_H

#ifdef	__cplusplus
extern "C" {
#endif

    
typedef enum 
{
    MC_INIT=0,
    MC_DRIVER_INIT,   
    MC_CONFIG_INIT,
    MC_PRE_RUN,
    MC_RUN,
    MC_SLEEP
}T_MC_STATE;



void MC_Init(void);
void MC_Driver_Init(void);
void MC_Config_Init(void);
void MC_Pre_Run(void);
void MC_Run(void);
void MC_Sleep(void);


#ifdef	__cplusplus
}
#endif

#endif	/* MC_MGT_H */

