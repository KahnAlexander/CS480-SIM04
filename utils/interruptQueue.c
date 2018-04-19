// PROGRAMMER INFORMATION ////////////////////////////////////////////
/**

Secret Number: 764819

*/
// Code Implementation File Information /////////////////////////////
/**
* @file interruptQueue.c
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
#include "interruptQueue.h"
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
void enqueueInt( InterruptQueue *queue, Interrupt *interrupt )
{
    if( queue->first == NULL && queue->count == 0 )
    {
        queue->first = interrupt;
        queue->count++;
        return;
    }

    Interrupt *currInt = queue->first;
    while( currInt->next != NULL )
    {
        currInt = currInt->next;
    }

    currInt->next = interrupt;
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
Interrupt *dequeueInt( InterruptQueue *queue )
{
    Interrupt *returnInt = queue->first;
    queue->first = queue->first->next;
    queue->count--;

    return returnInt;
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
Interrupt *createInterrupt( int pid )
{
    Interrupt *returnInt = malloc( sizeof( Interrupt ) );
    returnInt->pid = pid;
    returnInt->next = NULL;

    return returnInt;
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
InterruptQueue *createInterruptQueue()
{
    InterruptQueue *returnQueue = malloc( sizeof( InterruptQueue ) );
    returnQueue->first = NULL;
    returnQueue->count = 0;

    return returnQueue;
}


//==========================================================================
// Terminating Precompiler Directives ///////////////////////////////
//
///// NONE
//
