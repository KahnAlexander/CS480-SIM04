// PROGRAMMER INFORMATION ////////////////////////////////////////////
/**

Secret Number: 764819

*/
// Code Implementation File Information /////////////////////////////
/**
* @file
*
* @brief
*
* @details
*/
// Program Description/Support /////////////////////////////////////
/*

*/
// Header Files ///////////////////////////////////////////////////
//
#include "readyQueue.h"
//
// Global Constant Definitions ////////////////////////////////////
//
///// NONE
//
// Free Function Prototypes ///////////////////////////////////////
//
//==========================================================================
/**
* @brief
*
* @details
*
* @par Algorithm
*
*
* @param[in]
*
*
* @return
*/
void enqueuePCB( ReadyQueue *queue, ProcessControlBlock *pcb )
{
    if( queue->first == NULL && queue->count == 0 )
    {
        queue->first = pcb;
        queue->count++;
        return;
    }

    ProcessControlBlock *currBlock = queue->first;
    while( currBlock->next != NULL )
    {
        currBlock = currBlock->next;
    }

    currBlock->next = pcb;
    queue->count++;
    return;
}

//==========================================================================
/**
* @brief
*
* @details
*
* @par Algorithm
*
*
* @param[out]
*
*
* @return
*/
ProcessControlBlock *dequeuePCB( ReadyQueue *queue )
{
    ProcessControlBlock *returnBlock = queue->first;
    queue->first = queue->first->next;
    queue->count--;

    return returnBlock;
}

//==========================================================================
/**
* @brief
*
* @details
*
* @par Algorithm
*
*
* @param[out]
*
*
* @return
*/
ReadyQueue *createReadyQueue()
{
    ReadyQueue *returnQueue = malloc( sizeof( ReadyQueue ) );
    returnQueue->first = NULL;
    returnQueue->count = 0;

    return returnQueue;
}

//==========================================================================
// Terminating Precompiler Directives ///////////////////////////////
//
///// NONE
//
