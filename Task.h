/* 
 * File:   Task.h
 * Author: Spirit
 *
 * Created on 12 février 2017, 21:50
 */

#ifndef TASK_H
#define	TASK_H

#ifdef	__cplusplus
extern "C" {
#endif

    
#define SYNC_TASK  0
#define ASYNC_TASK 1
    
typedef enum
{
	STOPPED = 0,
	WAITING = 1,
	PENDING = 2,
	RUNNING = 3,
	ERROR = 4
}T_task_state;


typedef struct  	
{
    unsigned char (*pf)();  // pointer to task
    T_task_state  state ;   // Current state of the task
    unsigned int cpt ;      // Current function executed in the task
    unsigned char sync_type;// sync or async task
    unsigned long periodicity;  // Periodicity of the task (10ms, 20ms, 50ms...)
    unsigned int offset;    //offset
} T_TASK ;


typedef struct
{
	unsigned char * TList; 
	unsigned char pFirst;
	unsigned char pLast;
	unsigned char nbElem;
    unsigned char maxNumElem; //used for debug purposes
	unsigned char overrun;
}T_TASK_LIST;



void TaskManager_Init();
void TaskManager(void);
void TaskAdd(unsigned char TaskId);
void TaskAdd_unique(unsigned char TaskId);
unsigned char TaskGet(unsigned char *TaskId);
void Task_Manager_IT(void);



#ifdef	__cplusplus
}
#endif

#endif	/* TASK_H */

