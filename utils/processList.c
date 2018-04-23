// PROGRAMMER INFORMATION ////////////////////////////////////////////
/**

Secret Number: 764819

*/
// Code Implementation File Information /////////////////////////////
/**
* @file processList.c
*
* @brief Implementation file for processList code
*
* @details Implements all functions of the processList utilities and nodes
*/

// Program Description/Support /////////////////////////////////////
/*
This program is adapted from a previous linked list I created.
This program holds a linked list struct and a node struct to hold
operating system processes.
*/
// Precompiler Directives //////////////////////////////////////////
//
///// NONE
//
// Header Files ///////////////////////////////////////////////////
//
#include "configParser.h"
#include "processList.h"
#include "metadataList.h"
#include "utilities.h"
//
// Global Constant Definitions ////////////////////////////////////
//
const int STD_STR = 200;
//
// Free Function Prototypes ///////////////////////////////////////
//

//==========================================================================
/**
* @brief Function creates and returns a pointer to a linked list
*
* @details Function allocates space for a linked list, sets equal to a
*   pointer, and returns that pointer.
*
* @par Algorithm
*   Function allocates space for a linked list, sets a pointer to that
*   space, and returns the pointer. Sets initial fields first and count
*   to NULL and zero.
*
* @param[out] list
* pointer to a linked list in memory
*
* @return returns a pointer to the processList in memory
*/
ProcessList *procListCreate()
{
    ProcessList *list = malloc( sizeof( ProcessList ));

    list->first = NULL;
    list->count = 0;

    return list;
}

//==========================================================================
/**
* @brief Function creates a node and returns a pointer to it
*
* @details Function allocates space for a node in memory and creates
*   a pointer to it, initializes the node fields to the given paramters,
*   then returns the pointer to the node.
*
* @par Algorithm
*   Function takes in field parameters for a ProcessControlBlock, allocates
*   space for and creates a pointer to the node, sets the fields to the values
*   of the parameters and returns the pointer to the node.
*
* @param[in] process
* A MetadataNode pointing to the beginning of the process.
*
* @param[out] node
* A pointer to the new ProcessControlBlock in memory
*
* @return a pointer to the node
*/
ProcessControlBlock *createPCB( MetadataNode *process, int pid )
{
    ProcessControlBlock *node = malloc( sizeof( ProcessControlBlock ));

    node->state = NEW;
    node->pid = pid;
    node->processTime = 0;
    node->processHead = process;
    node->next = NULL;
	node->nextInQueue = NULL;

    return node;
}

//==========================================================================
/**
* @brief Function appends a node to the end of a list
*
* @details Function finds ending node in list and appends given node
*
* @par Algorithm
*   Function takes a node and a list, finds the ending node in the list,
*   and links that last node to the given node, making the given node the
*   new last node in the list. If the list is empty, it makes the given
*   node the head of the list.
*
* @param[in] list
* A ProcessList pointer
*
* @param[in] node
* A ProcessControlBlock pointer
*/
void listAddPCB( ProcessList *list, ProcessControlBlock *node )
{
    if( list->first == NULL && list->count == 0 )
    {
        list->first = node;
        list->count++;
        return;
    }

    ProcessControlBlock *currNode = list->first;

    while( currNode->next != NULL )
    {
        currNode = currNode->next;
    }

    currNode->next = node;
    list->count++;

    return;
}

//==========================================================================
/**
* @brief Function frees every node in the given list
*
* @details Function creates a pointer to the next node of current, frees the
*   current node and loops back until all nodes have been freed. Then sets
*   list values to NULL head and zero count.
*
* @par Algorithm
*   Function creates a pointer to the next node of head, frees head, then
*   sets head to next, sets next to next of head, and loops until all
*   nodes in list are freed.
*
* @param[in] list
* A ProcessList pointer
*/
static void freePCBs( ProcessList *list )
{
    ProcessControlBlock *next = list->first->next;

    while( next != NULL )
    {
        free( list->first );
        list->first = next;
        next = next->next;
    }

    free( list->first );

    list->first = NULL;
    list->count = 0;
}

//==========================================================================
/**
* @brief Function frees all nodes in a linked list and frees list
*
* @details Function calls free_nodes() on a linked list and then frees
*   the list pointer as well, effectively freeing all structs within the list
*
* @par Algorithm
*   Function calls free_nodes() and then frees list, then sets list pointer
*   to null and return pointer.
*
* @param[in] list
* A ProcessList pointer
*
* @return a freed and nulled ProcessList pointer
*/
ProcessList *procListDestroy( ProcessList *list )
{
    freePCBs( list );
    free( list );

    list = NULL;
    return list;
}

//==========================================================================
/**
* @brief Function returns number of nodes in the list
*
* @details Function accesses count value in list and returns it
*
* @par Algorithm
*   Function accesses count field in list and returns it
*
* @param[in] list
* A ProcessList pointer
*
* @param[out] count
* Count of nodes in ProcessList
*
* @return count of nodes in list
*/
int procListCount( ProcessList *list )
{
    return list->count;
}

//==========================================================================
/**
* @brief Function returns first node in the list
*
* @details Function accesses list's head pointer and returns pointer to
*   that node
*
* @par Algorithm
*   Function accesses list's head pointer and returns the pointer to the
*   first node in the list.
*
* @param[in] list
* A ProcessList pointer
*
* @param[out] first
* A pointer to the first node in list
*
* @return a pointer to the head node in list
*/
ProcessControlBlock *procListFirst( ProcessList *list )
{
    return list->first;
}

//==========================================================================
/**
* @brief Function creates a Process List and fills it with process control
*   blocks
*
* @details Function iterates through the metadataList, and creates a
*   process control block struct for each application-start opCode.
*
* @par Algorithm
*   Function creates a process control block for every application-start
*   opCode in the metadata list and adds it to the process list.
*
* @param[in] list
* A ProcessList pointer
*/
int fillProcessList( ProcessList *list,
                    MetadataList *mdList,
                    Config *configData )
{
    MetadataNode *currOp = mdListFirst( mdList );
    if( currOp->command != 'S' ||
        stringCompare( currOp->operation, "start" ) != NO_ERROR_MSG )
    {
        return INVALID_OP_CODE;
    }

    currOp = currOp->next;
    int nextPid = 0;

    while( currOp->command != 'S' )
    {
        if( currOp->command == 'A' &&
            stringCompare( currOp->operation, "start" ) == NO_ERROR_MSG )
        {
            listAddPCB( list, createPCB( currOp, nextPid ) );
            nextPid++;
        }

        currOp = currOp->next;
    }

    if( currOp->command == 'S' &&
        stringCompare( currOp->operation, "end" ) == 0 )
    {
        calculateProcessTime( list, configData );
        return NO_ERROR_MSG;
    }
    else
    {
        return UNKNOWN_ERR;
    }
}

//==========================================================================
/**
* @brief Function calculates the total time for each Process Control Block
*
* @details Function iterates through a process list, then iterates through
*   opCode for each PCB, and grabs the cycle times from each opCode,
*   calculates the time for each opCode and totals these times for the PCB
*
* @par Algorithm
*   Function iterates through a process list, then iterates through
*   opCode for each PCB, and grabs the cycle times from each opCode,
*   calculates the time for each opCode and totals these times for the PCB
*
* @param[in] list
* A ProcessList pointer
*/
int calculateProcessTime( ProcessList *list, Config *configData )
{
    ProcessControlBlock *currBlock = procListFirst( list );
    MetadataNode *currOp;

    while( currBlock != NULL )
    {
        currOp = currBlock->processHead;

        while( stringCompare( currOp->operation, "end" ) != 0 )
        {
            if( currOp->command == 'A' &&
                stringCompare( currOp->operation, "start" ) == 0 )
            {
                currOp = currOp->next;
                continue; //is A(start)0 for PCB
            }
            else if( currOp->command == 'P' )
            {
                currBlock->processTime +=
                    configData->pCycleTime * currOp->value;
            }
            else if( currOp->command == 'I' || currOp->command == 'O' )
            {
                currBlock->processTime +=
                    configData->ioCycleTime * currOp->value;
            }

            // M command adds no time, A(end) caught by inner while loop
            currOp = currOp->next;
        }
        currBlock = currBlock->next;
    }

    return NO_ERROR_MSG;
}

//==========================================================================
/**
* @brief Function sets all PCBs to READY state
*
* @details Function takes a process list pointer, iterates through each PCB,
*   and changes state to READY state for whole list.
*
* @param[in] list
*   A pointer to a ProcessList containing PCBs
*/
void setReady( ProcessList *list )
{
    ProcessControlBlock *currBlock = procListFirst( list );

    while( currBlock != NULL )
    {
        if( currBlock->state == NEW )
        {
            currBlock->state = READY;
        }
        currBlock = currBlock->next;
    }
}

//==========================================================================
/**
* @brief
*
* @details
*
* @param[in]
*/
ProcessControlBlock *removeFirst( ProcessList *procList )
{
	ProcessControlBlock *returnBlock = procList->first;
	procList->first = procList->first->next;
	procList->count--;

	returnBlock->next = NULL;
	return returnBlock;
}

//==========================================================================
/**
* @brief
*
* @details
*
* @param[in]
*/
void removeBlocked( ProcessList *procList, int pid )
{
	ProcessControlBlock *currBlock = procList->first;

	if( currBlock->pid == pid )
	{
		procList->first = procList->first->next;
		currBlock->next = NULL;
		return;
	}

	while( currBlock->next != NULL )
	{
		if( currBlock->next->pid == pid )
		{
			ProcessControlBlock *temp = currBlock->next;
			currBlock->next = currBlock->next->next;
			temp->next = NULL;
			return;
		}
		currBlock = currBlock->next;
	}

	return;
}

//==========================================================================
// Terminating Precompiler Directives ///////////////////////////////
//
///// NONE
//
