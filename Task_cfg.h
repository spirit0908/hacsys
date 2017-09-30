/* 
 * File:   Task_cfg.h
 * Author: spirit
 *
 * Created on September 30, 2017, 3:20 PM
 */

#ifndef TASK_CFG_H
#define	TASK_CFG_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "Task.h"
    
#define TASK_SCHEDULE_MAX 20 //to be moved to Task_cfg.h
#define TASK_MANAGER_IT_CYCLE 2 /*ms*/


    
extern T_TASK Task_List[];


typedef enum
{
    TASK_20ms_ID=0u,
    TASK_50ms_ID,
    TASK_100ms_ID,
    TASK_1s_ID,
    Task_CanMsgProcess_ID,
  
    // Keep next value at the end of enum
    TASK_TOTAL_NUM
}T_TASK_ID;

unsigned char Task_20ms(void);
unsigned char Task_50ms(void);
unsigned char Task_100ms(void);
unsigned char Task_1s(void);
unsigned char Task_CanMsgProcess(void);


#ifdef	__cplusplus
}
#endif

#endif	/* TASK_CFG_H */

