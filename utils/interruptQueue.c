// PROGRAMMER INFORMATION ////////////////////////////////////////////
/**

Secret Number: 764819

*/
// Code Implementation File Information /////////////////////////////
/**
* @file logList.c
*
* @brief Implementation file for logList code
*
* @details Implements all functions of the logList utilities and nodes
*/
// Program Description/Support /////////////////////////////////////
/*
This program stores logging data for the simulator, which is used
to later be stored in a log file specified in the configuration data.
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
void enqueue( InterruptQueue *queue, Interrupt *interrupt )
{
    if( queue->first == NULL && queue->count == 0 )
    {
        queue->first = interrupt;
        count++;
        return;
    }

    Interrupt *currInt = queue->first;
    while( currInt->next != NULL )
    {
        currInt = currInt->next;
    }

    currInt->next = interrupt;
    count++;
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
Interrupt *dequeue( InterruptQueue *queue )
{
    Interrupt *returnInt = queue->first;
    queue->first = queue->first->next;
    count--;

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
// Terminating Precompiler Directives ///////////////////////////////
//
///// NONE
//
