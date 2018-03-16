// PROGRAMMER INFORMATION ////////////////////////////////////////////
/**

Secret Number: 764819

*/
// Code Implementation File Information /////////////////////////////
/**
* @file logList.c
*
* @brief Implementation file for logList code
*
* @details Implements all functions of the logList utilities and nodes
*/
// Program Description/Support /////////////////////////////////////
/*
This program stores logging data for the simulator, which is used
to later be stored in a log file specified in the configuration data.
*/
// Header Files ///////////////////////////////////////////////////
//
#include "logList.h"
//
// Global Constant Definitions ////////////////////////////////////
//
const int STD_LOG_STR = 120;
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
* @return returns a pointer to the MetadataList in memory
*/
LogList *logListCreate() {
    LogList *list = malloc( sizeof( LogList ));

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
*   Function takes in field parameters for a metadataNode, allocates space
*   for and creates a pointer to the node, sets the fields to the values of
*   the parameters and returns the pointer to the node.
*
* @param[in] logStr
* a char representing a log string to be stored
*
* @param[out] node
* A pointer to the metadataNode in memory
*
* @return a pointer to the node
*/
LogNode *createLogNode( char *logStr )
{
    LogNode *node = malloc( sizeof( LogNode ));
    node->logStr = malloc( STD_LOG_STR );
    node->next = NULL;
    copyString( node->logStr, logStr );

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
* A metadataList pointer
*
* @param[in] node
* A metadataNode pointer
*/
void addLogNode( LogList *list, LogNode *node )
{
    if( list->first == NULL && list->count == 0 )
    {
        list->first = node;
        list->count++;
        return;
    }

    LogNode *currNode = list->first;

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
* A metadataList pointer
*/
static void freeLogNodes( LogList *list )
{
    if( list->count == 0 && list->first == NULL )
    {
        return;
    }

    LogNode *next = list->first->next;

    while( next != NULL )
    {
        free( list->first->logStr );
        free( list->first );
        list->first = next;
        next = next->next;
    }
    free( list->first->logStr );
    free( list->first );

    list->first = NULL;
    list->count = 0;
}

//==========================================================================
/**
* @brief Function frees all nodes in a linked list and frees list
*
* @details Function calls freeLogNodes() on a linked list and then frees
*   the list pointer as well, effectively freeing all structs within the list
*
* @par Algorithm
*   Function calls freeLogNodes() and then frees list, then sets list pointer
*   to null and return pointer.
*
* @param[in] list
* A metadataList pointer
*
* @return a freed and nulled logList pointer
*/
LogList *logListDestroy( LogList *list )
{
    freeLogNodes( list );
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
* A metadataList pointer
*
* @param[out] count
* Count of nodes in metadataList
*
* @return count of nodes in list
*/
int logListCount( LogList *list )
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
* A metadataList pointer
*
* @param[out] first
* A pointer to the first node in list
*
* @return a pointer to the head node in list
*/
LogNode *logListFirst( LogList *list )
{
    return list->first;
}

//==========================================================================
// Terminating Precompiler Directives ///////////////////////////////
//
///// NONE
//
