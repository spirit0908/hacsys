/************************************************************************
* Project : HACSYS                                                      *
*           IO_16                                                       *
*                                                                       *
* FileName:      main.c                                                 *
* Processor:     PIC18F4680                                             *
* Linker:        MPLINK 4.48                                            *
* Compiler:      XC8 v1.44                                              *
* Assembler: 	 MPASM v5.75                                            *
*                                                                       *
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*
* DESCRIPTION:                                                          *
*************************************************************************/


/************************************************************************
* INCLUDES *
*************************************************************************/
#include "hard.h"
#include "Can.h"
#include "def.h"
#include "fuses.h"
#include "interrupt.h"
#include "mc_mgt.h"
#include "Task.h"
#include "ADC.h"
#include "hard.h"
#include "FIFO.h"

/************************************************************************
* DEFINES *
************************************************************************/


/************************************************************************
* FUNCTION PROTOTYPES *
************************************************************************/


/************************************************************************
* GLOBAL VARIABLES *
************************************************************************/


/************************************************************************
* MAIN FUNCTION *
************************************************************************/
void main(void)
{
    // Local variables:
    // ----------------
    unsigned char mc_run_step;
	
    T_MC_STATE uc_state;
    uc_state = MC_INIT;
    
    // Deactivate interrupts
    CLI();
    
    // MC state machine:
    do
    {
        switch( uc_state )
        {
            case MC_INIT:
                uc_state = MC_DRIVER_INIT;
                break;

            case MC_DRIVER_INIT:
                MC_Driver_Init();
                uc_state = MC_CONFIG_INIT;
                break;
                
            case MC_CONFIG_INIT:
                MC_Config_Init();
                uc_state = MC_PRE_RUN;
                break;
                
            case MC_PRE_RUN:
                MC_Pre_Run();
                uc_state = MC_RUN;
                break;
                
            case MC_RUN:
                MC_Run();
                break;

            case MC_SLEEP:
                MC_Sleep();
                break;
                
            default:
                uc_state = MC_DRIVER_INIT;
                break;
            
        }
    }while(1);
}

