// PROGRAMMER INFORMATION ////////////////////////////////////////////
/**

Secret Number: 764819

*/
// Header File Information /////////////////////////////////////
/**
* @file logList.h
*
* @brief Header file for logList code
*
* @details Specifies functions, constants, and other information
* related to the logList code
*/
// Precompiler Directives //////////////////////////////////////////
//
#ifndef LOG_LIST_H
#define LOG_LIST_H
//
// Header Files ///////////////////////////////////////////////////
//
#include "utilities.h"
//
// Global Constant Definitions ////////////////////////////////////
//
extern const int STD_LOG_STR;
//
// Data Structure Definitions (structs, enums, etc.)////////////////
//
typedef struct LogNode
{
    struct LogNode *next;
    char *logStr;
} LogNode;

typedef struct LogList
{
	int count;
	LogNode *first;
} LogList;
//
// Free Function Prototypes ///////////////////////////////////////
//
//==========================================================================
/*
  Just initializes the List structure (the node pointers are NULL and
  the count = 0.
*/
LogList *logListCreate();

/*
  Just initializes a Node structure (the node pointers are NULL and
  the pointer to the data is set to each field.
*/
LogNode *createLogNode( char *logStr );

/*
  Finds end of list and adds link to given node
*/
void addLogNode( LogList *list, LogNode *node );

/*
  Frees any nodes in the list and then frees the list structure.
*/
LogList *logListDestroy( LogList *list );

/*
  Returns the count in the list structure.
*/
int logListCount( LogList *list );

/*
  Returns the first node in the list.
*/
LogNode *logListFirst( LogList *list );

// Terminating Precompiler Directives ///////////////////////////////
//
#endif // LOG_LIST_H
//
