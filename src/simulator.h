// PROGRAMMER INFORMATION ////////////////////////////////////////////
/**

Secret Number: 764819

*/
// Header File Information /////////////////////////////////////
/**
* @file simulator.h
*
* @brief Header file for simulator code
*
* @details Specifies functions, constants, and other information
* related to the simulator code
*/

// Precompiler Directives //////////////////////////////////////////
//
#ifndef SIM_H
#define SIM_H
//
// Header Files ///////////////////////////////////////////////////
//
#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include "processList.h"
#include "metadataList.h"
#include "utilities.h"
#include "logList.h"
#include "configParser.h"
#include "mmuList.h"
#include "interruptQueue.h"
#include "readyQueue.h"
#include "simtimer.h"

//
// Data Structure Definitions (structs, enums, etc.)////////////////
//
typedef struct ThreadContainer
{
	InterruptQueue *intQueue;
	ProcessControlBlock *currBlock;
	int waitTime;
} ThreadContainer;
//
// Free Function Prototypes ///////////////////////////////////////
//
//==========================================================================

void runSimulator( MetadataList *mdList, Config *configData );

//==========================================================================

void runScheduler( Config *configData, ProcessList *procList, LogList *logList,
                    MMUList *mmu );

//==========================================================================

void logAction( char *logStr, Config *configData, LogList *logList );

//==========================================================================

void runOSStart( MetadataList *mdList, ProcessList *procList,
                    Config *configData, LogList *logList );

//==========================================================================

void runFCFS( Config *configData, ProcessList *procList, LogList *logList,
                MMUList *mmu );

//==========================================================================

void runSJFN( Config *configData, ProcessList *procList, LogList *logList,
                MMUList *mmu );

//==========================================================================

void runSRTF( Config *configData, ProcessList *procList, LogList *logList,
                MMUList *mmu );

//==========================================================================

void runFCFSP( Config *configData, ProcessList *procList, LogList *logList,
                MMUList *mmu );

//==========================================================================

void runRRP( Config *configData, ProcessList *procList, LogList *logList,
                MMUList *mmu );

//==========================================================================

void logListToFile( Config *configData, LogList *logList );

//==========================================================================

void runNonpreemptiveThread( int threadTime );

//==========================================================================

void runPreemptiveThread( ThreadContainer *container );

//==========================================================================

void *runConcurrentThread( void *container );

//==========================================================================

ProcessControlBlock *findShortestJob( ProcessList *procList );

//==========================================================================

void processOpCodesNonpreemptive( MetadataNode *currOp, Config *configData,
                    LogList *logList, ProcessControlBlock *currBlock,
                    char *logStr, MMUList *mmu );

//==========================================================================

void processOpCodesPreemptive( Config *configData, LogList *logList,
				ProcessControlBlock *currBlock, char *logStr, MMUList *mmu,
			 	InterruptQueue *intQueue, ProcessList *procList,
				ReadyQueue *ready, ProcessList *blocked );

//==========================================================================

int allocateMem( int value, MMUList *mmu, ProcessControlBlock *currBlock,
                Config *configData, LogList *logList );

//==========================================================================

int accessMem( int value, MMUList *mmu, ProcessControlBlock *currBlock,
                Config *configData, LogList *logList );

//==========================================================================

void endProcess( MMUList *mmu, ProcessControlBlock *currBlock );

//==========================================================================

MMUNode *removeAlloc( MMUList *mmu, MMUNode *alloc );

//==========================================================================

int listEmpty( ProcessList *procList );

//==========================================================================

int queueEmpty( ReadyQueue *ready );

//==========================================================================

ProcessControlBlock *getNextReady( ProcessList *procList );

//==========================================================================

void checkForInterrupts( ProcessControlBlock *pcb, InterruptQueue *intQueue,
 						char *logStr, Config *configData, LogList *logList,
					 	ReadyQueue *ready, ProcessList *procList );

//==========================================================================

ThreadContainer *buildThreadContainer( Config *configData, LogList *logList,
								InterruptQueue *intQueue,
								ProcessControlBlock *currBlock, int waitTime );

//==========================================================================

void printPCBStatus( ReadyQueue *ready );

void printPCBList( ProcessList *procList );

// Terminating Precompiler Directives ///////////////////////////////
//
#endif // SIM_H
//
