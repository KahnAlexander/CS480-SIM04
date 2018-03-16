// PROGRAMMER INFORMATION ////////////////////////////////////////////
/**

Secret Number: 764819

*/
// Header File Information /////////////////////////////////////
/**
* @file configParser.h
*
* @brief Header file for configParser code
*
* @details Specifies functions, constants, and other information
* related to the configParser code
*/
// Program Description/Support /////////////////////////////////////
/*
This program parses a given configuration file and stores data into
a Config type struct.
*/
// Precompiler Directives //////////////////////////////////////////
//
#ifndef CONFIG_PARSER_H
#define CONFIG_PARSER_H
//
// Header Files ///////////////////////////////////////////////////
//
#include <stdio.h>
#include <stdlib.h>
//
// Global Constant Definitions ////////////////////////////////////
//
extern const char NONE[];
extern const char FCFS_N[];
extern const char SJF_N[];
extern const char SRTF_P[];
extern const char FCFS_P[];
extern const char RR_P[];

extern const char MONITOR[];
extern const char LOG_TO_FILE[];
extern const char BOTH[];
//
// Data Structure Definitions (structs, enums, etc.)////////////////
//
typedef struct Config
{
    int version;
    char metadataFilePath[ 50 ];
    char scheduleCode[ 50 ];
    int quantumTime;
    int memorySize;
    int pCycleTime;
    int ioCycleTime;
    char logTo[ 50 ];
    char logFilePath[ 50 ];
} Config;
//
// Free Function Prototypes ///////////////////////////////////////
//

int parseConfig( FILE *config, Config *configData );

//==========================================================================

int validateLine( FILE *file, Config *configData, char *fileData,
                    const char *formatStr, int valueFlag );

//==========================================================================

int validateData( int flag, char data[], long validData );

//==========================================================================

int storeData( char titleStr[], int validData, Config *configData );

//==========================================================================

int storeString( char title[], char data[], Config *configData );

//==========================================================================

int validateScheduleCode( char* scheduleCode, Config *configData );

//==========================================================================

int validateLogTo( char* logTo, Config *configData );

//==========================================================================
// Terminating Precompiler Directives ///////////////////////////////
//
#endif // CONFIG_PARSER_H
//
