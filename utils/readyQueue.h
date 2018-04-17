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
///// NONE
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

void enqueue( ReadyQueue *queue, ProcessControlBlock *pcb );

//==========================================================================

ProcessControlBlock *dequeue( ReadyQueue *queue );

//==========================================================================

ProcessControlBlock *createReadyQueue();

// Terminating Precompiler Directives ///////////////////////////////
//
#endif // READY_QUEUE_H
//
