// PROGRAMMER INFORMATION ////////////////////////////////////////////
/**

Secret Number: 764819

*/
// Code Implementation File Information /////////////////////////////
/**
* @file mmuList.c
*
* @brief Implementation file for mmuList code
*
* @details Implements all functions of the mmuList utilities and nodes
*/
// Program Description/Support /////////////////////////////////////
/*
This program stores memory allocations for the simulator, which are
then accessed later by the process operations.
*/
// Header Files ///////////////////////////////////////////////////
//
#include "mmuList.h"
#include "configParser.h"
//
// Global Constant Definitions ////////////////////////////////////
//
///// NONE
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
* @post returned pointer now points to a linked list in memory
*
* @par Algorithm
*   Function allocates space for a linked list, sets a pointer to that
*   space, and returns the pointer. Sets initial fields first and count
*   to NULL and zero.
*
* @param[out] list
* pointer to a linked list in memory
*
* @return returns a pointer to the MMUList in memory
*/
MMUList *MMUListCreate( int totalMem ) {
    MMUList *list = malloc( sizeof( MMUList ));

    list->first = NULL;
    list->count = 0;
    list->totalMemory = totalMem;
    list->availableMemory = totalMem;

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
*   Function takes in field parameters for an MMUNode, allocates space
*   for and creates a pointer to the node, sets the fields to the values of
*   the parameters and returns the pointer to the node.
*
* @param[in] sid
* an integer representing an allocation ID
*
* @param[in] base
* an integer representing a starting memory base
*
* @param[in] offset
* an integer representing an offset to allocate from the base
*
* @param[out] node
* A pointer to the MMUNode in memory
*
* @return a pointer to the node
*/
MMUNode *createMMUNode( int pid, int sid, int base, int offset,
                        Config *configData, MMUList *mmu )
{
    if( base >= 0 && ( base + offset ) <= mmu->totalMemory )
    {
        MMUNode *currNode = MMUListFirst( mmu );
        while( currNode != NULL )
        {
            if( currNode->sid == sid )
            {
                return NULL;
            }

            else if(
            ( base >= currNode->base &&
                  base < ( currNode->base + currNode->offset ) ) ||
            ( ( base + offset ) > currNode->base &&
                ( base + offset ) <= ( currNode->base + currNode->offset ) ) ||
            ( currNode->base >= base &&
                currNode->base < ( base + offset ) ) ||
            ( ( currNode->base + currNode->offset ) > base &&
                ( currNode->base + currNode->offset ) <= ( base + offset ) ) )
            {
                return NULL;
            }
            currNode = currNode->next;
        }

        MMUNode *node = malloc( sizeof( MMUNode ));
        node->next = NULL;
        node->pid = pid;
        node->sid = sid;
        node->base = base;
        node->offset = offset;

        return node;
    }
    else
    {
        return NULL;
    }
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
* A MMUList pointer
*
* @param[in] node
* A MMUNode pointer
*/
void addMMUNode( MMUList *list, MMUNode *node )
{
    if( list->first == NULL && list->count == 0 )
    {
        list->first = node;
        list->count++;
        return;
    }

    MMUNode *currNode = list->first;

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
* A MMUList pointer
*/
static void freeMMUNodes( MMUList *list )
{
    if( list->count == 0 && list->first == NULL )
    {
        return;
    }

    MMUNode *next = list->first->next;

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
* @details Function calls freeMMUNodes() on a linked list and then frees
*   the list pointer as well, effectively freeing all structs within the list
*
* @par Algorithm
*   Function calls freeMMUNodes() and then frees list, then sets list pointer
*   to null and return pointer.
*
* @param[in] list
* A MMUList pointer
*
* @return a freed and nulled MMUList pointer
*/
MMUList *MMUListDestroy( MMUList *list )
{
    freeMMUNodes( list );
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
* A MMUList pointer
*
* @param[out] count
* Count of nodes in MMUList
*
* @return count of nodes in list
*/
int MMUListCount( MMUList *list )
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
* A MMUList pointer
*
* @param[out] first
* A pointer to the first node in list
*
* @return a pointer to the head node in list
*/
MMUNode *MMUListFirst( MMUList *list )
{
    return list->first;
}

//==========================================================================
// Terminating Precompiler Directives ///////////////////////////////
//
///// NONE
//
