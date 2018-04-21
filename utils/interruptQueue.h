// PROGRAMMER INFORMATION ////////////////////////////////////////////
/**

Secret Number: 764819

*/
// Header File Information /////////////////////////////////////
/**
* @file logList.h
*
* @brief Header file for logList code
*
* @details Specifies functions, constants, and other information
* related to the logList code
*/
// Precompiler Directives //////////////////////////////////////////
//
#ifndef INT_QUEUE_H
#define INT_QUEUE_H
//
// Header Files ///////////////////////////////////////////////////
//
#include <stdlib.h>
#include "processList.h"
//
// Global Constant Definitions ////////////////////////////////////
//
///// NONE
//
// Data Structure Definitions (structs, enums, etc.)////////////////
//
typedef struct Interrupt
{
    struct Interrupt *next;
    ProcessControlBlock *pcb;
} Interrupt;

typedef struct InterruptQueue
{
	int count;
	Interrupt *first;
} InterruptQueue;
//
// Free Function Prototypes ///////////////////////////////////////
//
//==========================================================================

void enqueueInt( InterruptQueue *queue, Interrupt *interrupt );

//==========================================================================

Interrupt *dequeueInt( InterruptQueue *queue );

//==========================================================================

Interrupt *createInterrupt( ProcessControlBlock *pcb );

//==========================================================================

InterruptQueue *createInterruptQueue();

// Terminating Precompiler Directives ///////////////////////////////
//
#endif // INT_QUEUE_H
//
