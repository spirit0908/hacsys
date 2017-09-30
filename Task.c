
#include "hard.h"

#include "Task.h"
#include "def.h"
#include "FIFO.h"
#include "Order_mgt.h"
#include "Light.h"
#include "Task_cfg.h"


unsigned char Tasks[TASK_SCHEDULE_MAX];
T_TASK_LIST TaskSchedule={Tasks, 0, 0, 0, 0, 0};


void TaskManager_Init()
{
    unsigned char i;
    
    TaskSchedule.nbElem=0;
    TaskSchedule.pFirst=0;
    TaskSchedule.pLast=0;
    TaskSchedule.overrun=0;
    TaskSchedule.maxNumElem=0;
    
    for(i=0; i<TASK_TOTAL_NUM; i++)
    {
        Task_List[i].cpt = (Task_List[i].periodicity - Task_List[i].offset);
    }
}

void TaskManager(void)
{
    unsigned char TaskId;
    
    if( TaskGet(&TaskId) != 0 )
    {
        (Task_List[TaskId].pf)();
    }
    else
    {
        // background task
        //go to sleep
    }
}


void TaskAdd(unsigned char TaskId )
{
    if( TaskSchedule.nbElem < TASK_SCHEDULE_MAX )
    {
        //Add a new task
        TaskSchedule.TList[TaskSchedule.pLast] = TaskId;
        TaskSchedule.nbElem++;

        if( (TaskSchedule.pLast+1)<TASK_SCHEDULE_MAX )
        {
            TaskSchedule.pLast++;
        }
        else
        {
            TaskSchedule.pLast=0;
        }
    }
    else
    {
        TaskSchedule.overrun++;
    }
    
    //Used for debug purposes
    if(TaskSchedule.nbElem > TASK_SCHEDULE_MAX)
    {
        TaskSchedule.maxNumElem = TaskSchedule.nbElem;
    }
}

void TaskAdd_unique(unsigned char TaskId)
{
    int i, j;
    
    j=TaskSchedule.pFirst;
    for(i=0;i<TaskSchedule.nbElem;i++)
    {
        if( TaskSchedule.TList[j] == TaskId )
        {
            // Task already added;
            return; //fast return
        }

        if( j<TaskSchedule.nbElem )
        {
            j++;
        }
        else
        {
            j=0;
        }
    }
    
    if( TaskSchedule.nbElem < TASK_SCHEDULE_MAX )
    {
        //Add a new task
        TaskSchedule.TList[TaskSchedule.pLast] = TaskId;
        TaskSchedule.nbElem++;
        
        if( (TaskSchedule.pLast+1)<TASK_SCHEDULE_MAX )
        {
            TaskSchedule.pLast++;
        }
        else
        {
            TaskSchedule.pLast=0;
        }
    }
    else
    {
        TaskSchedule.overrun++;
    }
    
    //Used for debug purposes
    if(TaskSchedule.nbElem > TASK_SCHEDULE_MAX)
    {
        TaskSchedule.maxNumElem = TaskSchedule.nbElem;
    }
}

unsigned char TaskGet(unsigned char *TaskId)
{
    unsigned char retval;
    
    if( TaskSchedule.nbElem > 0 )
    {
        //Get first task to execute
       *TaskId = TaskSchedule.TList[TaskSchedule.pFirst];
        
        TaskSchedule.nbElem--;
        
        if( (TaskSchedule.pFirst+1) < TASK_SCHEDULE_MAX)
        {
            TaskSchedule.pFirst++;
        }
        else
        {
            TaskSchedule.pFirst=0;
        }
        retval=1;
    }
    else
    {
        //No task
        retval=0;
    }
    
    return retval;
}

void Task_Manager_IT(void)
{
    // Function called every 10ms
    unsigned char i;
    
    for(i=0u; i<TASK_TOTAL_NUM; i++)
    {
        if( Task_List[i].sync_type == SYNC_TASK )
        {
            if( Task_List[i].cpt >= Task_List[i].periodicity )
            {
                TaskAdd(i);
                Task_List[i].cpt = 0;
            }
            else
            {
                Task_List[i].cpt += TASK_MANAGER_IT_CYCLE;
            }
        }
    }
}

