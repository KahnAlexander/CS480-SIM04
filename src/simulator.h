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

void logListToFile( Config *configData, LogList *logList );

//==========================================================================

void runThread( int threadTime );

//==========================================================================

ProcessControlBlock *findShortestJob( ProcessList *procList );

//==========================================================================

void processOpCodes( MetadataNode *currOp, Config *configData,
                    LogList *logList, ProcessControlBlock *currBlock,
                    char *logStr, MMUList *mmu );

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

// Terminating Precompiler Directives ///////////////////////////////
//
#endif // SIM_H
//
