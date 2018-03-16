// PROGRAMMER INFORMATION ////////////////////////////////////////////
/**

Secret Number: 764819

*/
// Header File Information /////////////////////////////////////
/**
* @file metadataParser.h
*
* @brief Program takes in file name from a Config struct, opens and reads data
* from file, validates fields, and stores data in a linked list to be printed.
*
* @details Specifies functions, constants, and other information
* related to the parser code
*/
// Program Description/Support /////////////////////////////////////
/*
This file uses functions from metadataList.c and configParser.c.
*/
// Precompiler Directives //////////////////////////////////////////
//
#ifndef METADATA_PARSER_H
#define METADATA_PARSER_H
//
// Header Files ///////////////////////////////////////////////////
//
#include "metadataList.h"
#include "configParser.h"
//
// Free Function Prototypes ///////////////////////////////////////
//=========================================================================

int parseMetadata( FILE *metaFile, MetadataList *list );

//=========================================================================

int getFirstLine( char *fileLine, FILE *metaFile );

//=========================================================================

int getData( char *fileLine, FILE *metaFile, MetadataList *list );

//=========================================================================

int getNextOpCode( char *dataToScan, MetadataList *list );

//=========================================================================

void storeOpCode( char command, char *operation, int value, MetadataList *list );

//=========================================================================

int validateCommand( char command );

//=========================================================================

int validateOperation( char *operation, char command );

//=========================================================================
// Terminating Precompiler Directives ///////////////////////////////
//
#endif // METADATA_PARSER_H
//
