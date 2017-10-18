
#include "hard.h"

#include "Task.h"
#include "def.h"
#include "FIFO.h"
#include "Order_mgt.h"
#include "Light.h"
#include "Task.h"
#include "Task_cfg.h"

//*********************
// Task configuration
//*********************

T_TASK Task_List[] =
{
    { Task_20ms    , STOPPED, 0, SYNC_TASK, 20   /*ms*/, 0 },
    { Task_50ms    , STOPPED, 0, SYNC_TASK, 50   /*ms*/, 0 },
    { Task_100ms   , STOPPED, 0, SYNC_TASK, 100  /*ms*/, 10},
    { Task_1s      , STOPPED, 0, SYNC_TASK, 1000 /*ms*/, 0 },
    { Task_CanMsgProcess, STOPPED, 0, ASYNC_TASK, 0/*ms*/,0}
};
#define TASK_TOTAL_NUM (sizeof(Task_List)/sizeof(T_TASK))

extern unsigned char dim_idx;

//*********************************
// Synchronous tasks implementation
//*********************************

unsigned char Task_20ms(void)
{
    return 0;
}

unsigned char Task_50ms(void)
{
    CanSendMessage();
    
    return 0;
}

unsigned char cpt_test=0;
unsigned char Task_100ms(void)
{
    LightOrderProcess();
    
    cpt_test++;
    if( cpt_test >= 10 )
    {
        cpt_test=0;
        // every 1sec
        LED9 = !LED9;
    }
    
    return 0;
}

unsigned char Task_1s(void)
{
    LightSendStatus();
    
    return 0;
}

//**********************************
// Asynchronous tasks implementation
//**********************************
unsigned char Task_CanMsgProcess(void)
{
    unsigned int CanId;
    unsigned char msgLen, msgData[8];
    unsigned char i, NbMsgReceived;
    
    NbMsgReceived = CAN_RX_FIFO.NumElem;
    
    for(i=0; i<NbMsgReceived; i++)
    {
        // Reception of CAN messages
        if( CAN_FIFO_read(&CAN_RX_FIFO, &CanId, &msgLen, msgData) != 0)
        {
            OrderProcess(CanId, msgLen, msgData);
        }
    }
    
    return 0;
}

