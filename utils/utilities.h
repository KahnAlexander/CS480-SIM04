// PROGRAMMER INFORMATION ////////////////////////////////////////////
/**

Secret Number: 764819

*/
// Header File Information /////////////////////////////////////
/**
* @file utilities.h
*
* @brief Header file for utilities code
*
* @details Specifies functions, constants, and other information
* to be extracted as utilities
*/

// Program Description/Support /////////////////////////////////////
/*
This program implements all utility functions
*/
// Precompiler Directives //////////////////////////////////////////
//
#ifndef UTIL_H
#define UTIL_H
//
// Header Files ///////////////////////////////////////////////////
//
#include <stdio.h>
#include <stdlib.h>
//
// Global Constant Definitions ////////////////////////////////////
//
extern const char NUL;
extern const char SPACE;
extern const int STD_META_STR;
extern const int STD_STR;
//
// Data Structure Definitions (structs, enums, etc.)////////////////
//
enum ERR_CODES
{
    INVALID_DATA = -10, INVALID_OP_CODE = -9, IS_SPACE = -8,
    END_OF_FILE = -7, INVALID_METADATA_FILE = -6, INVALID_CONFIG_FILE = -5,
    FILE_NOT_FOUND_ERR = -4, OPEN_FILE_FAIL = -2, MISMATCH_STR = -3,
    UNKNOWN_ERR = -1, NO_ERROR_MSG = 0
};
//
// Free Function Prototypes ///////////////////////////////////////
//

FILE *openFile( char *fileName );

//==========================================================================

FILE *writeToFile( char *fileName );

//==========================================================================

int closeFile( FILE *file );

//==========================================================================

char *trimWhiteSpace( char *data );

//==========================================================================

int stringCompare( char *dataStr, const char *formatStr );

//==========================================================================

void splitString( char *fileData, char titleStr[], char dataStr[], int upToData );

//==========================================================================

void copyString( char to[], char from[] );

//==========================================================================

int stringLength( const char *string );

//==========================================================================

int stringToInt(char stringNumber[]);

//=========================================================================

void clearBuffer( char buffer[] );

//=========================================================================

int isASpace( char checkMe );

//=========================================================================
// Terminating Precompiler Directives ///////////////////////////////
//
#endif // UTIL_H
//
