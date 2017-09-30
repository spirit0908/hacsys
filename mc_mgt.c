
#include "hard.h"
#include "mc_mgt.h"
#include "ADC.h"
#include "interrupt.h"
#include "Can.h"
#include "Task.h"
#include "IO.h"
#include "Light.h"
#include "FIFO.h"

void MC_Init(void)
{
    
}

void MC_Driver_Init(void)
{
    // IO Init
    IO_Init();
	ADC_Init();
    
    // Interrupts init
    IT_Init();
    Peripheral_IT_Init();
    
    // Communication buses init
    Can_Init();
    //CAN_Init_HwFilters();
    
    //USART_Init();
}

void MC_Config_Init(void)
{
    // Init Task manager module
    TaskManager_Init(); 

    // Init Fifo
    FIFO_Init(FIFO_table);

    // Initialize Light module
    Light_Init();
    Light_Init_cfg();
    
}

void MC_Pre_Run(void)
{
    // Communication buses 
    CAN_Start();
    
    // activate ISR
    SEI();
}

void MC_Run(void)
{
    TaskManager();
}

void MC_Sleep(void)
{
    //goToSleepMode();
}
