// PROGRAMMER INFORMATION ////////////////////////////////////////////
/**

Secret Number: 764819

*/
// Header File Information /////////////////////////////////////
/**
* @file metadataList.h
*
* @brief Header file for metadataList code
*
* @details Specifies functions, constants, and other information
* related to the metadataList code
*/

// Precompiler Directives //////////////////////////////////////////
//
#ifndef METADATA_LIST_H
#define METADATA_LIST_H
//
// Header Files ///////////////////////////////////////////////////
//
#include "utilities.h"
//
// Data Structure Definitions (structs, enums, etc.)////////////////
//
typedef struct MetadataNode
{
    struct MetadataNode *next;
    char command;
    char *operation;
    int value;
} MetadataNode;

typedef struct MetadataList
{
	int count;
	MetadataNode *first;
} MetadataList;
//
// Free Function Prototypes ///////////////////////////////////////
//
/*
  Just initializes the List structure (the node pointers are NULL and
  the count = 0.
*/
MetadataList *mdListCreate();

/*
  Just initializes a Node structure (the node pointers are NULL and
  the pointer to the data is set to each field.
*/
MetadataNode *createMdNode( char command, char *operation, int value );

/*
  Finds end of list and adds link to given node
*/
void addMdNode( MetadataList *list, MetadataNode *node );

/*
  Frees any nodes in the list and then frees the list structure.
*/
MetadataList *mdListDestroy( MetadataList *list );

/*
  Returns the count in the list structure.
*/
int mdListCount( MetadataList *list );

/*
  Returns the first node in the list.
*/
MetadataNode *mdListFirst( MetadataList *list );

// Terminating Precompiler Directives ///////////////////////////////
//
#endif // METADATA_LIST_H
//
