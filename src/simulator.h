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
#include "processList.h"
#include "metadataList.h"
#include "utilities.h"
#include "logList.h"
#include "configParser.h"
#include "mmuList.h"
#include "interruptQueue.h"
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

void runPreemptiveThread( int threadTime );

//==========================================================================

ProcessControlBlock *findShortestJob( ProcessList *procList );

//==========================================================================

void processOpCodesNonpreemptive( MetadataNode *currOp, Config *configData,
                    LogList *logList, ProcessControlBlock *currBlock,
                    char *logStr, MMUList *mmu );

//==========================================================================

void processOpCodesPreemptive( Config *configData, LogList *logList,
				ProcessControlBlock *currBlock, char *logStr, MMUList *mmu,
			 	InterruptQueue *intQueue );

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

ProcessControlBlock *getNextReady( ProcessList *procList );

//==========================================================================

void checkForInterrupts( ProcessControlBlock *pcb, InterruptQueue *intQueue,
 						char *logStr, Config *configData, LogList *logList );

// Terminating Precompiler Directives ///////////////////////////////
//
#endif // SIM_H
//
