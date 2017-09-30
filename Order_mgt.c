
#include "hard.h"
#include "Order_mgt.h"
#include "def.h"
#include "Light.h"
#include "FIFO.h"

T_FctGrp fct_group[] =
{
    /* ElemId, type , Addr, FctId, pRxIndication */
    { 0u, TYPE_LIGHT, 0x123, 0u, LightOrderTmt }, // FCT_GROUP 0 - SORTIE 0 - 
    { 1u, TYPE_LIGHT, 0x123, 1u, LightOrderTmt }, // SORTIE 1
    { 2u, TYPE_LIGHT, 0x123, 2u, LightOrderTmt }, // SORTIE 2
    { 3u, TYPE_LIGHT, 0x123, 3u, LightOrderTmt }, // SORTIE 3
    { 4u, TYPE_LIGHT, 0x123, 4u, LightOrderTmt }, // SORTIE 4
    { 5u, TYPE_LIGHT, 0x123, 5u, LightOrderTmt }, // SORTIE 5
    { 6u, TYPE_LIGHT, 0x123, 6u, LightOrderTmt }, // SORTIE 6
    { 7u, TYPE_LIGHT, 0x123, 7u, LightOrderTmt }  // SORTIE 7
};
#define fct_group_size ( sizeof(fct_group)/sizeof(T_FctGrp) ) //(sizeof(fct_group) / sizeof(T_FctGrp))

T_FctGrp fct_group2[] =
{
    /* ElemId   , type      , pRxIndication */
    { Light_ID_0, TYPE_LIGHT, LightOrderTmt },
    { Light_ID_1, TYPE_LIGHT, LightOrderTmt },
    { Light_ID_2, TYPE_LIGHT, LightOrderTmt },
    { Light_ID_3, TYPE_LIGHT, LightOrderTmt },
    { Light_ID_4, TYPE_LIGHT, LightOrderTmt },
    { Light_ID_5, TYPE_LIGHT, LightOrderTmt },
    { Light_ID_6, TYPE_LIGHT, LightOrderTmt },
    { Light_ID_7, TYPE_LIGHT, LightOrderTmt }
};

void OrderProcess(unsigned int CanId, unsigned char msgLenm, unsigned char msgData[8])
{
    unsigned char deviceModule;
    unsigned char LightId, Order, param;
    unsigned char i;
    unsigned int temp;
    deviceModule = (msgData[0] & 0xF0u);
    
    if( CanId == OWN_CAN_ID)
    {
        //Loop on all functionnal groups
        for(i=0; i<fct_group_size; i++)
        {
            
        }
        
        switch(deviceModule)
        {
            case ORDER_BROADCAST:
                // this message is a broadcast

                // check if we are concerned by the can id
            break;

            case ORDER_LIGHT:
                Order   = msgData[0];
                LightId = msgData[1];
                param   = msgData[2];

                LightOrderTmt(LightId, Order, param);
            break;

            case ORDER_HEATING:
                //HeatingOrderTmt();
            break;

            case ORDER_SHUTTER:
                //ShutterOrderTmt();
            break;
        }

    }
    else if( CanId == CAN_ID_BROADCAST )
    {
    }
    else
    {
    }
    
}



void updateIndicStatus(unsigned char Idx)
{
}



void CanSendMessage(void)
{
    unsigned char NbMsgToSend;
    unsigned char CanId, msgLen;
    unsigned char *msgData;
    unsigned char retVal, i;
    
    // Send CAN messages    
    NbMsgToSend = CAN_TX_FIFO.NumElem;
    
    for(i=0; i<NbMsgToSend; i++)
    {
        if( CAN_FIFO_read(&CAN_TX_FIFO, &CanId, &msgLen, msgData) != 0)
        {
            if( Can_Transmit_data(CanId, msgLen, msgData) == ret_OK)
            {
                //return TRUE;
                retVal = ret_OK;
            }
            else
            {
                // no free slot, insert the msg back
                CAN_FIFO_add(&CAN_TX_FIFO, CanId, msgLen, msgData);
                retVal = ret_NOK;
            }
        }
    }
}


