// PROGRAMMER INFORMATION ////////////////////////////////////////////
/**

Secret Number: 764819

*/
// Code Implementation File Information /////////////////////////////
/**
* @file simulator.c
*
* @brief Implementation file for simulator code
*
* @details Implements all functions of the simulator utilities
*/

// Program Description/Support /////////////////////////////////////
/*
This program simulates running processes from a ProcessList structure,
using a timer and threads to run each operation code.
*/
// Header Files ///////////////////////////////////////////////////
//
#include <pthread.h>
#include <stdio.h>
#include "processList.h"
#include "metadataList.h"
#include "utilities.h"
#include "logList.h"
#include "simtimer.h"
#include "configParser.h"
#include "simulator.h"
#include "mmuList.h"
//
// Free Function Prototypes ///////////////////////////////////////
//
//======================================================================
/**
* @brief Function runs starting OS functions, then runs the configured
*   scheduling algorithm on the processes created.
*
* @details The function creates a list of process control blocks that
*   point to the provided metadata, store them in a list, then begin
*   OS functions, assigning a scheduling algorithm, and then run this
*   algorithm on the process list. After running, the sim logs output
*   to a file if configured.
*
* @param[in] mdList
*   A pointer to a metadataList struct storing the given metadata
*
* @param[in] configData
*   A pointer to a Config struct storing the given configuration data
*/
void runSimulator( MetadataList *mdList, Config *configData )
{
    ProcessList *procList = procListCreate();
    LogList *logList = logListCreate();
    MMUList *mmu = MMUListCreate( configData->memorySize );

    logAction( "System Start", configData, logList );
    runOSStart( mdList, procList, configData, logList );

    runScheduler( configData, procList, logList, mmu );

    if( stringCompare( configData->logTo, LOG_TO_FILE ) == 0 ||
        stringCompare( configData->logTo, BOTH )        == 0 )
    {
        logListToFile( configData, logList );
    }

    MMUListDestroy( mmu );
    logListDestroy( logList );
    procListDestroy( procList );
}

//======================================================================
/**
* @brief Function Begins system, creates PCB list, initializes PCBs to
*   NEW, and then sets PCBs to READY.
*
* @details This function logs actions to the monitor and log file if
*   desired, then creates a list of NEW PCBs, sets them to READY,
*   and logs all data concerning these functions.
*
* @param[in] mdList
*   A pointer to a metadataList struct storing the given metadata
*
* @param[in] procList
*   A pointer to a processList struct storing the created PCBs
*
* @param[in] configData
*   A pointer to a Config struct storing the given configuration data
*
* @param[in] logList
*   A pointer to a logList struct storing the created logs
*/
void runOSStart( MetadataList *mdList,
                    ProcessList *procList,
                    Config *configData,
                    LogList *logList )
{
    logAction( "OS: Begin PCB Creation", configData, logList );
    if( fillProcessList( procList, mdList, configData ) == UNKNOWN_ERR )
    {
        mdListDestroy( mdList );
        procListDestroy( procList );
        free( configData );
        printf( "===ERR: PROCESS LIST FAILED TO POPULATE===\n" );
        return;
    }
    logAction( "OS: All processes initialized in New state",
                configData, logList );

    setReady( procList );
    logAction( "OS: All processes now set in Ready state",
                configData, logList );
}

//======================================================================
/**
* @brief Function runs the configured scheduling algorithm
*
* @details This function runs the configured scheduling algorithm on the
*   list of PCBs.
*
* @param[in] procList
*   A pointer to a processList struct storing the created PCBs
*
* @param[in] configData
*   A pointer to a Config struct storing the given configuration data
*
* @param[in] logList
*   A pointer to a logList struct storing the created logs
*
* @param[in] mmu
*   A pointer to an MMUList struct storing allocs
*
*/
void runScheduler( Config *configData, ProcessList *procList, LogList *logList,
                    MMUList *mmu )
{
    if( stringCompare( configData->scheduleCode, FCFS_N ) == 0 )
    {
        runFCFS( configData, procList, logList, mmu );
    }
    else if( stringCompare( configData->scheduleCode, SJF_N ) == 0 )
    {
        runSJFN( configData, procList, logList, mmu );
    }
    else if( stringCompare( configData->scheduleCode, SRTF_P ) == 0 )
    {
        logAction( "OS: SRTF-P Strategy is not yet implemented",
                    configData, logList );
        logAction( "System End", configData, logList );
    }
    else if( stringCompare( configData->scheduleCode, FCFS_P ) == 0 )
    {
        logAction( "OS: FCFS-P Strategy is not yet implemented",
                    configData, logList );
        logAction( "System End", configData, logList );
    }
    else if( stringCompare( configData->scheduleCode, RR_P ) == 0 )
    {
        logAction( "OS: RR-P Strategy is not yet implemented",
                    configData, logList );
        logAction( "System End", configData, logList );
    }
}

//======================================================================
/**
* @brief Function logs the given logStr to the configured destination
*
* @details The function logs a string to the configured location (file or
*   monitor), accesses the timer for when the log is happening and prepends
*   the time to the log string.
*
* @param[in] logStr
*   A char pointer to the string desired to be logged
*
* @param[in] configData
*   A pointer to a Config struct storing the given configuration data
*
* @param[in] logList
*   A pointer to a logList struct storing the created logs
*/
void logAction( char *logStr, Config *configData, LogList *logList )
{
    char *currTime = malloc( 10 );
    char *properLogStr = malloc( STD_LOG_STR );

    if( stringCompare( logStr, "System Start" ) == 0 )
    {
        accessTimer( ZERO_TIMER, currTime );
    }
    else if( stringCompare( logStr, "System End" ) == 0 )
    {
        accessTimer( STOP_TIMER, currTime );
    }
    else
    {
        accessTimer( LAP_TIMER, currTime );
    }

    snprintf( properLogStr, STD_LOG_STR, "Time: %s, %s\n",
              currTime, logStr );
    addLogNode( logList, createLogNode( properLogStr ) );

    if( stringCompare( configData->logTo, MONITOR ) == 0 ||
        stringCompare( configData->logTo, BOTH )    == 0 )
    {
        printf( "Time: %s, %s\n", currTime, logStr );
    }
    free( properLogStr );
    free( currTime );
    return;
}

//======================================================================
/**
* @brief Function runs FirstComeFirstServed scheduling on the given
*   list of process control blocks.
*
* @details The function chooses a PCB from the list, sets it to RUNNING,
*   then begins processes each opCode within. For each opCode, it logs
*   the operation, then if it is I/O or processing, it creates a thread
*   to run for the given time, and logs the start and end. When the PCB
*   is done, it sets the process to EXIT and moves to the next one.
*
* @param[in] procList
*   A pointer to a processList struct storing the created PCBs
*
* @param[in] configData
*   A pointer to a Config struct storing the given configuration data
*
* @param[in] logList
*   A pointer to a logList struct storing the created logs
*
* @param[in] mmu
*   A pointer to an MMUList struct storing allocs
*
*/
void runFCFS( Config *configData, ProcessList *procList, LogList *logList,
                MMUList *mmu )
{
    ProcessControlBlock *currBlock = procListFirst( procList );
    char logStr[ STD_LOG_STR ];

    while( currBlock != NULL )
    {
        snprintf( logStr, STD_LOG_STR,
                  "OS: FCFS-N Strategy selects Process %d with time: %d mSec",
                  currBlock->pid, currBlock->processTime );
        logAction( logStr, configData, logList );

        currBlock->state = RUN;
        snprintf( logStr, STD_LOG_STR,
                  "OS: Process %d set in Running state", currBlock->pid );
        logAction( logStr, configData, logList );

        processOpCodes( currBlock->processHead, configData, logList, currBlock,
                        logStr, mmu );

        endProcess( mmu, currBlock );
        snprintf( logStr, STD_LOG_STR,
                  "OS: Process %d set in Exit state", currBlock->pid );
        logAction( logStr, configData, logList );
        currBlock = currBlock->next;
    }

    logAction( "System End", configData, logList );

    return;
}

//======================================================================
/**
* @brief Function runs ShortestJobFirst scheduling on the given
*   list of process control blocks.
*
* @details The function organizes the process list by SJF, and begins running.
*
* @param[in] procList
*   A pointer to a processList struct storing the created PCBs
*
* @param[in] configData
*   A pointer to a Config struct storing the given configuration data
*
* @param[in] logList
*   A pointer to a logList struct storing the created logs
*
* @param[in] mmu
*   A pointer to an MMUList struct storing allocs
*
*/
void runSJFN( Config *configData, ProcessList *procList, LogList *logList,
                MMUList *mmu )
{
    ProcessControlBlock *currBlock = findShortestJob( procList );
    char logStr[ STD_LOG_STR ];

    while( currBlock != NULL )
    {
        snprintf( logStr, STD_LOG_STR,
                  "OS: SJF-N Strategy selects Process %d with time: %d mSec",
                  currBlock->pid, currBlock->processTime );
        logAction( logStr, configData, logList );

        currBlock->state = RUN;
        snprintf( logStr, STD_LOG_STR,
                  "OS: Process %d set in Running state", currBlock->pid );
        logAction( logStr, configData, logList );

        processOpCodes( currBlock->processHead, configData, logList, currBlock,
                        logStr, mmu );

        endProcess( mmu, currBlock );
        snprintf( logStr, STD_LOG_STR,
                  "OS: Process %d set in Exit state", currBlock->pid );
        logAction( logStr, configData, logList );

        currBlock = findShortestJob( procList );
    }

    logAction( "System End", configData, logList );

    return;
}

//======================================================================
/**
* @brief Function logs a logList to a configured output file
*
* @details This function opens a logFile specified in configData, then
*   iterates through the logList, logging each string from the node to
*   the open file. Closes the file when reaching the end of the list.
*
* @param[in] configData
*   A pointer to a Config struct storing the given configuration data
*
* @param[in] logList
*   A pointer to a logList struct storing the created logs
*/
void logListToFile( Config *configData, LogList *logList )
{
    FILE *logFile = writeToFile( configData->logFilePath );
    LogNode *currNode = logListFirst( logList );

    while( currNode != NULL )
    {
        fputs( currNode->logStr, logFile );
        currNode = currNode->next;
    }

    closeFile( logFile );
}

//======================================================================
/**
* @brief Function creates a POSIX thread and runs it for the given time.
*
* @details The function casts the given time to a void pointer, creates
*   a thread, and has the thread run the timer for the given time.
*
* @param[in] threadTime
*   A integer representing the milliseconds to run the thread for.
*/
void runThread( int threadTime )
{
    int *runTime = &threadTime;
    pthread_t tid;

    pthread_create( &tid, NULL, runTimer, (void *)runTime );
    pthread_join( tid, NULL );

    return;
}

//======================================================================
/**
* @brief Function finds the ProcessControlBlock with the shortest
*   processing time
*
* @details Function iterates over process list, and finds the PCB
*   with the shortest processing time and returns a pointer to that
*   block. If all PCBs are in EXIT state, NULL returned.
*
* @param[in] procList
*   A pointer to a list holding process control blocks
*/
ProcessControlBlock *findShortestJob( ProcessList *procList )
{
    ProcessControlBlock *currBlock = procListFirst( procList );
    ProcessControlBlock *shortestJob = procListFirst( procList );

    while( shortestJob->state == EXIT )
    {
        shortestJob = shortestJob->next;
        if( shortestJob == NULL )
        {
            return NULL;
        }
    }

    while( currBlock != NULL )
    {
        if( currBlock->state != EXIT )
        {
            if( currBlock->processTime < shortestJob->processTime )
            {
                shortestJob = currBlock;
            }
        }
        currBlock = currBlock->next;
    }

    return shortestJob;
}

//======================================================================
/**
* @brief Function processes opCodes, logs output for each one, iterates
*   to end of metadataList
*
* @details Function takes in opCode, processes command letter, logs output,
*   moves to next opCode, and continues until reaching the end of the PCB
*
* @param[in] currOp
*   A pointer to the head MetadataNode of a PCB
*
* @param[in] configData
*   A pointer to a Config struct storing the given configuration data
*
* @param[in] logList
*   A pointer to a logList struct storing the created logs
*
* @param[in] currBlock
*   A pointer to the ProcessControlBlock being processed
*
* @param[in] logStr
*   A char pointer to the string to be logged in file or monitor
*
* @param[in] mmu
*   A pointer to an MMUList struct storing allocs
*
*/
void processOpCodes( MetadataNode *currOp, Config *configData,
                    LogList *logList, ProcessControlBlock *currBlock,
                    char *logStr, MMUList *mmu )
{
    while( stringCompare( currOp->operation, "end" ) != 0 )
    {
        if( currOp->command == 'A' )
        {
            currOp = currOp->next;
            continue;
        }
        else if( currOp->command == 'P' )
        {
            snprintf( logStr, STD_LOG_STR,
                      "Process %d, run operation start", currBlock->pid );
            logAction( logStr, configData, logList );

            runThread( configData->pCycleTime * currOp->value );

            snprintf( logStr, STD_LOG_STR,
                      "Process %d, run operation end", currBlock->pid );
            logAction( logStr, configData, logList );
        }
        else if( currOp->command == 'I' )
        {
            snprintf( logStr, STD_LOG_STR,
                      "Process %d, %s input start",
                      currBlock->pid, currOp->operation );
            logAction( logStr, configData, logList );

            runThread( configData->ioCycleTime * currOp->value );

            snprintf( logStr, STD_LOG_STR,
                      "Process %d, %s input end",
                      currBlock->pid, currOp->operation );
            logAction( logStr, configData, logList );
        }
        else if( currOp->command == 'O' )
        {
            snprintf( logStr, STD_LOG_STR,
                      "Process %d, %s output start",
                      currBlock->pid, currOp->operation );
            logAction( logStr, configData, logList );

            runThread( configData->ioCycleTime * currOp->value );

            snprintf( logStr, STD_LOG_STR,
                      "Process %d, %s output end",
                      currBlock->pid, currOp->operation );
            logAction( logStr, configData, logList );
        }
        else if( currOp->command == 'M' )
        {
            if( stringCompare( currOp->operation, "allocate" ) == 0 )
            {
                if( allocateMem( currOp->value, mmu, currBlock, configData,
                            logList ) == -1 )
                {
                    snprintf( logStr, STD_LOG_STR,
                        "OS: Process %d, Segmentation Fault - Process ended",
                        currBlock->pid );
                    logAction( logStr, configData, logList );
                    break;
                }
            }
            else if( stringCompare( currOp->operation, "access" ) == 0 )
            {
                if( accessMem( currOp->value, mmu, currBlock, configData,
                            logList ) == -1 )
                {
                    snprintf( logStr, STD_LOG_STR,
                        "OS: Process %d, Segmentation Fault - Process ended",
                        currBlock->pid );
                    logAction( logStr, configData, logList );
                    break;
                }
            }
        }

        currOp = currOp->next;
    }
}

//======================================================================
/**
* @brief Function creates allocation with given values, stores in mmu
*
* @details Function extracts data from given opCode value, creates an MMU
*    node, if returned value from createMMUNode is NULL, log failure,
*    if a value is returned, add the node to mmu, log success
*
* @param[in] value
*   Integer representing MetadataNode operation value
*
* @param[in] mmu
*    A pointer to a memory list
*
* @param[in] currBlock
*    A pointer to a ProcessControlBlock
*
* @param[in] configData
*   A pointer to a Config struct storing the given configuration data
*
* @param[in] logList
*   A pointer to a logList struct storing the created logs
*
*/
int allocateMem( int value, MMUList *mmu, ProcessControlBlock *currBlock,
                Config *configData, LogList *logList )
{
    char valStr[20];
    char segStr[5];
    char baseStr[5];
    char offStr[5];
    char logStr[STD_LOG_STR];

    sprintf( valStr, "%d", value );

    if( stringLength( valStr ) != 8 )
    {
        return -1;
    }

    segStr[0] = valStr[0];
    segStr[1] = valStr[1];
    segStr[2] = '\0';

    baseStr[0] = valStr[2];
    baseStr[1] = valStr[3];
    baseStr[2] = valStr[4];
    baseStr[3] = '\0';

    offStr[0] = valStr[5];
    offStr[1] = valStr[6];
    offStr[2] = valStr[7];
    offStr[3] = '\0';

    int sid = stringToInt( segStr );
    int base = stringToInt( baseStr );
    int offset = stringToInt( offStr );

    snprintf( logStr, STD_LOG_STR,
              "Process %d, MMU Allocation: %d/%d/%d",
              currBlock->pid, sid, base, offset );
    logAction( logStr, configData, logList );

    MMUNode *node = createMMUNode( currBlock->pid, sid, base, offset,
                                    configData, mmu );
    if( node == NULL )
    {
        snprintf( logStr, STD_LOG_STR, "Process %d, MMU Allocation: Failed",
                  currBlock->pid );
        logAction( logStr, configData, logList );
        return -1;
    }

    addMMUNode( mmu, node );
    snprintf( logStr, STD_LOG_STR, "Process %d, MMU Allocation: Successful",
              currBlock->pid );
    logAction( logStr, configData, logList );

    return 0;
}

//======================================================================
/**
* @brief Function finds alloc with given SID and PID, and attempts to
*    access memory in that, returns result
*
* @details Function extracts values from access operation, iterates over
*    mmu list looking for alloc with same SID and PID. If found, attempts
*    access and returns log. If alloc not found, returns failure.
*
* @param[in] value
*   Integer representing MetadataNode operation value
*
* @param[in] mmu
*    A pointer to a memory list
*
* @param[in] currBlock
*    A pointer to a ProcessControlBlock
*
* @param[in] configData
*   A pointer to a Config struct storing the given configuration data
*
* @param[in] logList
*   A pointer to a logList struct storing the created logs
*
*/
int accessMem( int value, MMUList *mmu, ProcessControlBlock *currBlock,
                Config *configData, LogList *logList )
{
    char valStr[20];
    char segStr[5];
    char baseStr[5];
    char offStr[5];
    char logStr[STD_LOG_STR];

    sprintf( valStr, "%d", value );

    if( stringLength( valStr ) != 8 )
    {
        return -1;
    }

    segStr[0] = valStr[0];
    segStr[1] = valStr[1];
    segStr[2] = '\0';

    baseStr[0] = valStr[2];
    baseStr[1] = valStr[3];
    baseStr[2] = valStr[4];
    baseStr[3] = '\0';

    offStr[0] = valStr[5];
    offStr[1] = valStr[6];
    offStr[2] = valStr[7];
    offStr[3] = '\0';

    int sid = stringToInt( segStr );
    int base = stringToInt( baseStr );
    int offset = stringToInt( offStr );

    snprintf( logStr, STD_LOG_STR,
              "Process %d, MMU Access: %d/%d/%d",
              currBlock->pid, sid, base, offset );
    logAction( logStr, configData, logList );

    MMUNode *currNode = MMUListFirst( mmu );
    while( currNode != NULL )
    {
        if( currNode->sid != sid || currBlock->pid != currNode->pid )
        {
            currNode = currNode->next;
        }
        else if( currNode->sid == sid && currBlock->pid == currNode->pid )
        {
            if( base >= currNode->base &&
            ( base + offset ) <= ( currNode->base + currNode->offset ) )
            {
                snprintf( logStr, STD_LOG_STR,
                          "Process %d, MMU Access: Successful",
                          currBlock->pid );
                logAction( logStr, configData, logList );
                return 0;
            }
            else
            {
                snprintf( logStr, STD_LOG_STR,
                          "Process %d, MMU Access: Failed",
                          currBlock->pid );
                logAction( logStr, configData, logList );
                return -1;
            }
        }
    }

    snprintf( logStr, STD_LOG_STR,
              "Process %d, MMU Access: Failed",
              currBlock->pid );
    logAction( logStr, configData, logList );
    return -1;
}

//======================================================================
/**
* @brief Function sets process to EXIT, and deallocates all memory nodes
*    that contain PID same as the exiting process
*
* @details Function sets process to EXIT, then iterates through mmu list
*    looking for allocs that contain PID equal to the process PID, and
*    removes those alloc nodes from mmu list
*
* @param[in] mmu
*    A pointer to a memory list
*
* @param[in] currBlock
*    A pointer to a ProcessControlBlock
*
*/
void endProcess( MMUList *mmu, ProcessControlBlock *currBlock )
{
    currBlock->state = EXIT;

    MMUNode *alloc = MMUListFirst( mmu );

    while( alloc != NULL )
    {
        if( alloc->pid == currBlock->pid )
        {
            alloc = removeAlloc( mmu, alloc );
        }
        else
        {
            alloc = alloc->next;
        }
    }
}

//======================================================================
/**
* @brief Function deallocates memory reserved by a process, returns a pointer
*    to the next allocation
*
* @details Function searches the mmu list for a given allocation, removes
*    the alloc node with matching PID and SID, and returns pointer to the
*    next node in mmu list. Returns NULL if the allocation does not exist
*
* @param[in] mmu
*    A pointer to a memory list
*
* @param[in] alloc
*    A pointer to a memory list node
*
*/
MMUNode *removeAlloc( MMUList *mmu, MMUNode *alloc )
{
    MMUNode *currAlloc = MMUListFirst( mmu );

    if( currAlloc->pid == alloc->pid && currAlloc->sid == alloc->sid )
    {
        mmu->first = alloc->next;

        free( alloc );
        mmu->count--;
        return mmu->first;
    }

    while( currAlloc->next != NULL )
    {
        if( currAlloc->next->pid == alloc->pid &&
            currAlloc->next->sid == alloc->sid )
        {
            currAlloc->next = alloc->next;

            free( alloc );
            mmu->count--;
            return currAlloc->next;
        }
        currAlloc = currAlloc->next;
    }
    return NULL;
}

// Terminating Precompiler Directives ///////////////////////////////
//
// NONE
//
