
/************************************************************************
* INCLUDES *
*************************************************************************/
#include "FIFO.h"
#include "def.h"

/************************************************************************
* DEFINES *
************************************************************************/


/************************************************************************
* GLOBAL VARIABLES *
************************************************************************/

/************************************************************************
* FUNCTIONS *
************************************************************************/

/************************************************************************
 * Function: FIFO_Init                                                  *
 * input: FIFO_table, pPointer to a table that contains all FIFO        *
 * output: none                                                         *
 * return: none                                                         *
 * description: This function initialize all FIFO defined in the table  *
 ************************************************************************/
void FIFO_Init(FIFO_TAB_T *pFifoTab)
{
    // Loop on all FIFO created:
    while(pFifoTab->pFIFO != 0) // #TBD: Whille loop to be tested
    {
        // Initialize Fifo
        (pFifoTab->pFIFO)->msgBuff 		= pFifoTab->pFIFO_Buff; //  FIFO1.msgBuff = FIFO1_Buff;
        (pFifoTab->pFIFO)->size 		= pFifoTab->size;
        (pFifoTab->pFIFO)->WriteIdx 	= 0;
        (pFifoTab->pFIFO)->ReadIdx 		= 0;
        (pFifoTab->pFIFO)->NumElem 		= 0;
        (pFifoTab->pFIFO)->NumMaxElem 	= 0;
        (pFifoTab->pFIFO)->overrun      = 0;
        
        pFifoTab++;
    }
}

/************************************************************************
 * Function: CAN_FIFO_add                                               *
 * input: FIFO: FIFO name message will be added                         *
 *        CAN_Id: Can ID                                                *
 *        msg_len:                                                      *
 *        msg_data                                                      *
 * output: none                                                         *
 * return: none                                                         *
 * description: Add a CAN message in FIFO                               *
 ************************************************************************/
unsigned char CAN_FIFO_add ( T_CAN_FIFO *pFIFO, unsigned int CAN_Id, unsigned char msg_len, unsigned char *msg_data )
{
    unsigned char i, status;
	unsigned char * pWriteIdx;
	T_CAN_MESSAGE * pMsgBuff;

	pWriteIdx = &(pFIFO->WriteIdx);
	
	pMsgBuff = &(pFIFO->msgBuff[*pWriteIdx]);
	
	status=ret_OK;
    
    if( pFIFO->NumElem < pFIFO->size )
	{
        // Store CAN_ID and msg_len
		pMsgBuff->addr = CAN_Id;
		pMsgBuff->length = msg_len;
        
        // Store data
        for( i=0; i<msg_len; i++)
			pMsgBuff->data[i] = msg_data[i];
		
        pFIFO->NumElem++;   // Increment the number of elements
        (*pWriteIdx)++;     // Increment FIFO write index to next position
        
        // Manage overflow:
		if( (*pWriteIdx) >= pFIFO->size )
			*pWriteIdx = 0;

        //Used for debug purpose
        if( pFIFO->NumElem > pFIFO->NumMaxElem)
        {
            pFIFO->NumMaxElem = pFIFO->NumElem; // Record how many elements were used in maximum since startup
        }
	}
	else
	{
		// FIFO overrun
        if( pFIFO->overrun < 0xFF)
        {
            pFIFO->overrun++;
		}
        status = ret_NOK;
	}
    return status;
}

/************************************************************************
 * Function: CAN_FIFO_aread                                             *
 * input: FIFO: FIFO name to read                                       *
 * output:CAN_Id: pointer to store Can ID                               *
 *        msg_len: pointer to store msg length                          *
 *        msg_data: pointer to store data                               *
 * return: OK if element is read, NOK if FIFO is empty                  *
 * description: Add a CAN message in FIFO                               *
 ************************************************************************/
unsigned char CAN_FIFO_read(T_CAN_FIFO *pFIFO, unsigned int *CAN_Id, unsigned char *msg_len, unsigned char *msg_data )
{
	unsigned char i;
	
	if( pFIFO->NumElem > 0 )
	{
        // Get CAN_Id and message length
		*CAN_Id = pFIFO->msgBuff[pFIFO->ReadIdx].addr ;
		*msg_len = pFIFO->msgBuff[pFIFO->ReadIdx].length;
        
        // Get on data
		for( i=0; i<*msg_len; i++ )
			msg_data[i] = pFIFO->msgBuff[pFIFO->ReadIdx].data[i];
		
        // Remove read element
		pFIFO->NumElem --;
        
        // Increment Read index and manage overrun
		pFIFO->ReadIdx ++;
		if( pFIFO->ReadIdx >= pFIFO->size )
			pFIFO->ReadIdx = 0;
		
		return ret_OK;
	}
	else
    {
        // No element in this buffer
		return ret_NOK;
	}
}


/*
char USART_FIFO_add ( T_USART_FIFO FIFO, unsigned int CAN_Id, unsigned char msg_len, unsigned char *msg_data )
{
    unsigned char i, status;
	status=OK;
    
    if( FIFO.NumElem < FIFO.size ) // IS there enough space for one more elem?
	{
        // Record CAN_ID and msg_len
		FIFO.msgBuff[FIFO.WriteIdx].addr = CAN_Id;
		FIFO.msgBuff[FIFO.WriteIdx].length = msg_len;
        
        // Record data
        for( i=0; i<msg_len; i++)
			FIFO.msgBuff[FIFO.WriteIdx].data[i] = msg_data[i];
		
        FIFO.NumElem++;  // Increment the number of elements
        FIFO.WriteIdx++; // Increment FIFO write index to next position
        // Manage overflow:

		if( FIFO.WriteIdx >= FIFO.size )
			FIFO.WriteIdx = 0;

//#ifdef FIFO_DEBUG
        if( FIFO.NumElem > FIFO.NumMaxElem)
        {
            FIFO.NumMaxElem = FIFO.NumElem; // Record how many elements were used in maximum since startup
        }
//#endif
	}
	else
	{
		// FIFO overrun
		//Set a flag for FIFO overrun #TBD
		status = NOK;
	}
}
unsigned char CAN_FIFO_read(T_CAN_FIFO FIFO, unsigned int *CAN_Id, unsigned char *msg_len, unsigned char *msg_data )
{
	int i;
	
	if( FIFO.NumElem > 0 ) // Check if at least one element is in the FIFO
	{
        // Get CAN_Id and message length
		*CAN_Id = FIFO.msgBuff[FIFO.ReadIdx].addr ;
		*msg_len = FIFO.msgBuff[FIFO.ReadIdx].length;
        
        // Loop on data
		for( i=0; i<*msg_len; i++ )
			msg_data[i] = FIFO.msgBuff[FIFO.ReadIdx].data[i];
		
		// To be tested instead of for loop above: 
		// *data = FIFO.msgBuff[FIFO.ReadIdx].data[0];

        // Remove one element as we just read it
		FIFO.NumElem --;
        
        // Increment Read index and manage overrun
		FIFO.ReadIdx ++;
		if( FIFO.ReadIdx >= FIFO.size )
			FIFO.ReadIdx = 0;
		
		return OK;
	}
	else
    {
        // No element in this buffer
		return NOK;
	}
}
*/





