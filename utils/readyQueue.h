// PROGRAMMER INFORMATION ////////////////////////////////////////////
/**

Secret Number: 764819

*/
// Header File Information /////////////////////////////////////
/**
* @file
*
* @brief
*
* @details
*/
// Precompiler Directives //////////////////////////////////////////
//
#ifndef READY_QUEUE_H
#define READY_QUEUE_H
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
typedef struct ReadyQueue
{
	int count;
	ProcessControlBlock *first;
} ReadyQueue;
//
// Free Function Prototypes ///////////////////////////////////////
//
//==========================================================================

void enqueuePCB( ReadyQueue *queue, ProcessControlBlock *pcb );

//==========================================================================

ProcessControlBlock *dequeuePCB( ReadyQueue *queue );

//==========================================================================

ReadyQueue *createReadyQueue();

// Terminating Precompiler Directives ///////////////////////////////
//
#endif // READY_QUEUE_H
//
