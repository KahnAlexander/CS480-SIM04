// PROGRAMMER INFORMATION ////////////////////////////////////////////
/**

Secret Number: 764819

*/
// Code Implementation File Information /////////////////////////////
/**
* @file configParser.c
*
* @brief Implementation file for configParser code
*
* @details Implements all functions of the configParser utilities.
*   This program opens a configuration file, validates the given
*   data in various ways to ensure it is within constraints,
*   and stores that data into a Config type struct.
*
* @note Requires configParser.h, metadataParser.h
*/
// Program Description/Support /////////////////////////////////////
/*
This program uses functions from metadataParser to process
data about the given files.
*/
// Header Files ///////////////////////////////////////////////////
//
#include "configParser.h"
#include "metadataParser.h"
#include "utilities.h"
//
// Global Constant Definitions ////////////////////////////////////
//
const char CONFIG_START_LN[] = "Start Simulator Configuration File";
const char VERSION_STR[] = "Version/Phase: ";
const char META_FILE_STR[] = "File Path: ";
const char CPU_SCHD_STR[] = "CPU Scheduling Code: ";
const char QUANTUM_TIME_STR[] = "Quantum Time (cycles): ";
const char MEMORY_STR[] = "Memory Available (KB): ";
const char PROCESSOR_STR[] = "Processor Cycle Time (msec): ";
const char IO_STR[] = "I/O Cycle Time (msec): ";
const char LOG_TO_STR[] = "Log To: ";
const char LOG_PATH_STR[] = "Log File Path: ";
const char CONFIG_END_LN[] = "End Simulator Configuration File.";

// Configuration Schedule Codes
const char NONE[] = "NONE";
const char FCFS_N[] = "FCFS-N";
const char SJF_N[] = "SJF-N";
const char SRTF_P[] = "SRTF-P";
const char FCFS_P[] = "FCFS-P";
const char RR_P[] = "RR-P";

//Configuration LogTo Option
const char MONITOR[] = "Monitor";
const char LOG_TO_FILE[] = "File";
const char BOTH[] = "Both";

const int STD_CONFIG_STR = 50;
//
// Free Function Prototypes ///////////////////////////////////////
//
//==========================================================================
/**
* @brief Function parses and stores data from a configuration file into a
*   Config type struct
*
* @details Function takes a file handle to the Config file, begins parsing
*   each line, validating format, and stores data into Config type struct.
*   If any validation comes back as fail, free the line pointer, returns
*   proper error code for invalid config file.
*
* @par Algorithm
* Function allocates memory for line taken from config file, calls
*   validateLine() to check each line of config file, and validate.
*   If successful, continue until whole file is validated. Free the
*   the char pointer for each line, and return no error code. If
*   validation fails, free the char pointer and return invalid
*   configuration file code.
*
* @param[in] config
* points to the open file handle for the configuration file
*
* @param[in] configData
* points to the struct in memory to hold configuration data
*
* @param[out] file
* a file handle to the given file from command line
*
* @return Error codes for invalid configuration file, or no error code
*/
int parseConfig( FILE *config, Config *configData )
{
    char *inLine = malloc( STD_CONFIG_STR );

    if( validateLine( config, configData, inLine, CONFIG_START_LN, 0 ) ==
            MISMATCH_STR )
    {
        free( inLine );
        return INVALID_CONFIG_FILE;
    }

    if( validateLine( config, configData, inLine, VERSION_STR, 1 ) ==
            MISMATCH_STR )
    {
        free( inLine );
        return INVALID_CONFIG_FILE;
    }

    if( validateLine( config, configData, inLine, META_FILE_STR, 2 ) ==
            MISMATCH_STR )
    {
        free( inLine );
        return INVALID_CONFIG_FILE;
    }

    if( validateLine( config, configData, inLine, CPU_SCHD_STR, 2 ) ==
            MISMATCH_STR )
    {
        free( inLine );
        return INVALID_CONFIG_FILE;
    }

    if( validateLine( config, configData, inLine, QUANTUM_TIME_STR, 1 ) ==
            MISMATCH_STR )
    {
        free( inLine );
        return INVALID_CONFIG_FILE;
    }

    if( validateLine( config, configData, inLine, MEMORY_STR, 1 ) ==
            MISMATCH_STR )
    {
        free( inLine );
        return INVALID_CONFIG_FILE;
    }

    if( validateLine( config, configData, inLine, PROCESSOR_STR, 1 ) ==
            MISMATCH_STR )
    {
        free( inLine );
        return INVALID_CONFIG_FILE;
    }

    if( validateLine( config, configData, inLine, IO_STR, 1 ) ==
            MISMATCH_STR )
    {
        free( inLine );
        return INVALID_CONFIG_FILE;
    }

    if( validateLine( config, configData, inLine, LOG_TO_STR, 2 ) ==
            MISMATCH_STR )
    {
        free( inLine );
        return INVALID_CONFIG_FILE;
    }

    if( validateLine( config, configData, inLine, LOG_PATH_STR, 2 ) ==
            MISMATCH_STR )
    {
        free( inLine );
        return INVALID_CONFIG_FILE;
    }

    if( validateLine( config, configData, inLine, CONFIG_END_LN, 0 ) ==
            MISMATCH_STR )
    {
        free( inLine );
        return INVALID_CONFIG_FILE;
    }

    free( inLine );

    return NO_ERROR_MSG;
}

//==========================================================================
/**
* @brief Function reads line from configuration file, validates line and
*   stores data into Config struct.
*
* @details Function takes a file handle, gets the next line in file, stores
*   line into fileData, validates fileData against formatStr and valueFlag,
*   then stores data into configData struct.
*
* @par Algorithm
* Function gets the next line in the config file, stores in fileData,
*   trims the whitespace from the line, begins validating based on
*   given valueFlag. If no data, compares fileData to formatStr,
*   returns proper error code. If integer or string data, splits fileData
*   into titleStr and dataStr, compares titleStr to formatStr, then if
*   integer data, data to integer and store data into Config struct. If
*   string data, store string into Config struct.
*
* @param[in] file
* points to the open file handle for the configuration file
*
* @param[in] configData
* points to the struct in memory to hold configuration data
*
* @param[in] fileData
* points to the string in memory to hold the configuration file line
*   returned from fgets()
*
* @param[in] formatStr
* the constant string representing the next expected line in the
*   configuration file
*
* @param[in] valueFlag
* integer representing the type of expected data in that line of
*   configuration data. Will be 0 for no data expected, 1 for
*   integer data, and 2 for string data.
*
* @return Error code representing correct execution and no error, a found
*   string not matching to file format, or unknown error if correct
*   conditions not met to complete.
*/
int validateLine( FILE *file, Config *configData, char *fileData,
                  const char *formatStr, int valueFlag )
{
    int result;

    fgets( fileData, STD_CONFIG_STR, file );
    fileData = trimWhiteSpace( fileData );

    if( valueFlag == 0 )
    {
        result = stringCompare( fileData, formatStr );

        if( result == NO_ERROR_MSG )
        {
            return NO_ERROR_MSG;
        }
        else if( result == MISMATCH_STR )
        {
            return MISMATCH_STR;
        }
    }

    char titleStr[STD_CONFIG_STR];
    char data[STD_CONFIG_STR];

    splitString( fileData, titleStr, data, stringLength( formatStr ));
    result = stringCompare( titleStr, formatStr );

    if( result == MISMATCH_STR )
    {
        return MISMATCH_STR;
    }

    else if( valueFlag == 1 )
    {
        int validNumber = 0;

        if( result == 0 )
        {
            validNumber = stringToInt( data );
            if( storeData( titleStr, validNumber, configData ) == INVALID_DATA )
            {
                return MISMATCH_STR;
            }

            return NO_ERROR_MSG;
        }
    }

    else if( valueFlag == 2 )
    {
        if( result == NO_ERROR_MSG )
        {
            if( storeString( titleStr, data, configData ) ==
                    MISMATCH_STR )
            {
                return MISMATCH_STR;
            }

            return NO_ERROR_MSG;
        }
    }
    return UNKNOWN_ERR;
}

//==========================================================================
/**
* @brief Function stores data into Config struct
*
* @details Function finds proper location to store data to in Config struct
*   and stores data
*
* @par Algorithm
* Function compares titleStr to each expected format string for integer
*   data from configuration file, finds matching one, stores data in
*   proper location in Config struct
*
* @param[in] titleStr
* array holding title string corresponding with given data
*
* @param[in] validData
* validated integer data corresponding to title string from configuration file
*
* @param[in] configData
* points to the Config type struct in memory that holds all configuration
*   data.
*
* @return returns no error found code if successful, unknown error code
*   if fail
*/
int storeData( char titleStr[], int validData, Config *configData )
{
    if( stringCompare( titleStr, VERSION_STR ) == NO_ERROR_MSG )
    {
        if( 0 <= validData && validData <= 10 )
        {
            configData->version = validData;
        }
        else
        {
            return INVALID_DATA;
        }
    }
    else if( stringCompare( titleStr, QUANTUM_TIME_STR ) == NO_ERROR_MSG )
    {
        if( 0 <= validData && validData <= 100 )
        {
            configData->quantumTime = validData;
        }
        else
        {
            return INVALID_DATA;
        }
    }
    else if( stringCompare( titleStr, MEMORY_STR ) == NO_ERROR_MSG )
    {
        if( 0 <= validData && validData <= 1048576 )
        {
            configData->memorySize = validData;
        }
        else
        {
            return INVALID_DATA;
        }
    }
    else if( stringCompare( titleStr, PROCESSOR_STR ) == NO_ERROR_MSG )
    {
        if( 1 <= validData && validData <= 1000 )
        {
            configData->pCycleTime = validData;
        }
        else
        {
            return INVALID_DATA;
        }
    }
    else if( stringCompare( titleStr, IO_STR ) == NO_ERROR_MSG )
    {
        if( 1 <= validData && validData <= 10000 )
        {
            configData->ioCycleTime = validData;
        }
        else
        {
            return INVALID_DATA;
        }
    }
    else
    {
        return UNKNOWN_ERR;
    }

    return NO_ERROR_MSG;
}

//==========================================================================
/**
* @brief Function stores data into Config struct
*
* @details Function finds proper location to store data to in Config struct
*   and stores data
*
* @par Algorithm
* Function compares titleStr to each expected format string for string
*   data from configuration file, finds matching one, stores data in
*   proper location in Config struct
*
* @param[in] titleStr
* array holding title string corresponding with given data
*
* @param[in] data
* data corresponding to title string from configuration file
*
* @param[in] configData
* points to the Config type struct in memory that holds all configuration
*   data.
*
* @return returns no error found code if successful, unknown error code
*   if fail
*/
int storeString( char title[], char data[], Config *configData )
{
    if( stringCompare( title, META_FILE_STR ) == NO_ERROR_MSG )
    {
        copyString( configData->metadataFilePath, data );
    }
    else if( stringCompare( title, CPU_SCHD_STR ) == NO_ERROR_MSG )
    {
        return validateScheduleCode( data, configData );
    }
    else if( stringCompare( title, LOG_TO_STR ) == NO_ERROR_MSG )
    {
        return validateLogTo( data, configData );
    }
    else if( stringCompare( title, LOG_PATH_STR ) == NO_ERROR_MSG )
    {
        copyString( configData->logFilePath, data );
    }
    else
    {
        return UNKNOWN_ERR;
    }

    return NO_ERROR_MSG;
}

//==========================================================================
/**
* @brief Function validates value of scheduleCode from configuration file
*
* @details Function checks scheduleCode value against list of acceptable
*   values, if one is found, no error returned, if value not valid,
*   returns mismatch string
*
* @param[in] scheduleCode
* A char pointer to the configuration file's given code
*
* @param[in] configData
* A Config struct pointer that will store the validated schedule code
*
* @return an integer error code of no error message if validation passes,
*   or mismatch string if schedule code is not valid
*/
int validateScheduleCode( char* scheduleCode, Config *configData )
{
    if( stringCompare( scheduleCode, NONE ) == NO_ERROR_MSG )
    {
        copyString( configData->scheduleCode, "FCFS-N" );
    }
    else if( stringCompare( scheduleCode, FCFS_N ) == NO_ERROR_MSG ||
            stringCompare( scheduleCode, SJF_N ) == NO_ERROR_MSG ||
            stringCompare( scheduleCode, SRTF_P ) == NO_ERROR_MSG ||
            stringCompare( scheduleCode, FCFS_P ) == NO_ERROR_MSG ||
            stringCompare( scheduleCode, RR_P ) == NO_ERROR_MSG )
    {
        copyString( configData->scheduleCode, scheduleCode );
    }
    else
    {
        return MISMATCH_STR;
    }
    return NO_ERROR_MSG;
}

//==========================================================================
/**
* @brief Function validates value of logTo from configuration file
*
* @details Function checks logTo value against list of acceptable
*   values, if one is found, no error returned, if value not valid,
*   returns mismatch string
*
* @param[in] logTo
* A char pointer to the configuration file's given code
*
* @param[in] configData
* A Config struct pointer that will store the validated log code
*
* @return an integer error code of no error message if validation passes,
*   or mismatch string if log code is not valid
*/
int validateLogTo( char* logTo, Config *configData )
{
    if( stringCompare( logTo, MONITOR ) == NO_ERROR_MSG ||
        stringCompare( logTo, LOG_TO_FILE ) == NO_ERROR_MSG ||
        stringCompare( logTo, BOTH ) == NO_ERROR_MSG )
    {
        copyString( configData->logTo, logTo );
    }
    else
    {
        return MISMATCH_STR;
    }
    return NO_ERROR_MSG;
}

//==========================================================================
// Terminating Precompiler Directives ///////////////////////////////
//
///// NONE
//
