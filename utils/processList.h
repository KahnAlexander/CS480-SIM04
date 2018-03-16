// PROGRAMMER INFORMATION ////////////////////////////////////////////
/**

Secret Number: 764819

*/
// Header File Information /////////////////////////////////////
/**
* @file processList.h
*
* @brief Header file for processList code
*
* @details Specifies functions, constants, and other information
* related to the processList code
*/

// Precompiler Directives //////////////////////////////////////////
//
#ifndef PROCESS_LIST_H
#define PROCESS_LIST_H
//
// Header Files ///////////////////////////////////////////////////
//
#include "configParser.h"
#include "metadataList.h"
//
// Data Structure Definitions (structs, enums, etc.)////////////////
//
typedef enum PROC_STATE
{
    NEW, READY, RUN, BLOCKED, EXIT
} PROC_STATE;

typedef struct ProcessControlBlock
{
    PROC_STATE state;
    int pid;
    int processTime;
    MetadataNode *processHead;
    struct ProcessControlBlock *next;
} ProcessControlBlock;

typedef struct ProcessList
{
	int count;
	ProcessControlBlock *first;
} ProcessList;
//
// Free Function Prototypes ///////////////////////////////////////
//
/*
  Just initializes the List structure (the node pointers are NULL and
  the count = 0.
*/
ProcessList *procListCreate();

/*
  Just initializes a PCB structure (the node pointers are NULL and
  the pointer to the data is set to each field.
*/
ProcessControlBlock *createPCB( MetadataNode *process, int pid );

/*
  Finds end of list and adds link to given node
*/
void listAddPCB( ProcessList *list, ProcessControlBlock *node );

/*
  Frees any nodes in the list and then frees the list structure.
*/
ProcessList *procListDestroy( ProcessList *list );

/*
  Returns the count in the list structure.
*/
int procListCount( ProcessList *list );

/*
  Returns the first node in the list.
*/
ProcessControlBlock *procListFirst( ProcessList *list );

/*
  Creates a PCB for each process represented in the metadataList, then stores
  the PCB into the process list. Calls calculateProcessTime at end
*/
int fillProcessList( ProcessList *list,
                    MetadataList *mdList,
                    Config *configData );

/*
  Calculates total time to execute each PCB and stores this value within struct
*/
int calculateProcessTime( ProcessList *list, Config *configData );

/*
  Sets all PCBs in list to the READY state
*/
void setReady( ProcessList *list );

// Terminating Precompiler Directives ///////////////////////////////
//
#endif // PROCESS_LIST_H
//
