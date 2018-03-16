// PROGRAMMER INFORMATION ////////////////////////////////////////////
/**

Secret Number: 764819

*/
// Header File Information /////////////////////////////////////
/**
* @file mmuList.h
*
* @brief Header file for mmuList code
*
* @details Specifies functions, constants, and other information
* related to the mmuList code
*/
// Precompiler Directives //////////////////////////////////////////
//
#ifndef MMU_LIST_H
#define MMU_LIST_H
//
// Header Files ///////////////////////////////////////////////////
//
#include "configParser.h"
//
// Global Constant Definitions ////////////////////////////////////
//
///// NONE
//
// Data Structure Definitions (structs, enums, etc.)////////////////
//
typedef struct MMUNode
{
    struct MMUNode *next;
    int pid;
    int sid;
    int base;
    int offset;
} MMUNode;

typedef struct MMUList
{
    MMUNode *first;
	int count;
    int totalMemory;
    int availableMemory;
} MMUList;
//
// Free Function Prototypes ///////////////////////////////////////
//
//==========================================================================
/*
  Just initializes the List structure (the node pointers are NULL and
  the count = 0.
*/
MMUList *MMUListCreate( int totalMem );

/*
  Just initializes a Node structure (the node pointers are NULL and
  the pointer to the data is set to each field.
*/
MMUNode *createMMUNode( int pid, int sid, int base, int offset,
                        Config *configData, MMUList *mmu );

/*
  Finds end of list and adds link to given node
*/
void addMMUNode( MMUList *list, MMUNode *node );

/*
  Frees any nodes in the list and then frees the list structure.
*/
MMUList *MMUListDestroy( MMUList *list );

/*
  Returns the count in the list structure.
*/
int MMUListCount( MMUList *list );

/*
  Returns the first node in the list.
*/
MMUNode *MMUListFirst( MMUList *list );

// Terminating Precompiler Directives ///////////////////////////////
//
#endif // MMU_LIST_H
//
