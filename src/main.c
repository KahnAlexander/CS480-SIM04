// PROGRAMMER INFORMATION ////////////////////////////////////////////
/**

Secret Number: 764819

*/
// Program Information ////////////////////////////////////////////////
/**
* @file main.c
*
* @brief Driver program to exercise the configParser and
*       metadataParser classes
*
* @details Allows for testing all configParser and
* metadataParser methods in an interactive and controlled
* operation of the simulator
*/

// Program Description/Support /////////////////////////////////////
/*
This program takes a command line argument for the name of the
configuration file to be parsed by the program. This data is
validated and stored in a struct, then opens a metadata file
name that is stored in that struct, parses that file, validates,
and stores that information into a linked list. Then both the
struct and linked list are printed to the screen.
*/
// Header Files ///////////////////////////////////////////////////
//
#include "configParser.h"
#include "metadataParser.h"
#include "metadataList.h"
#include "processList.h"
#include "utilities.h"
#include "simulator.h"
//
// Free Function Prototypes ///////////////////////////////////////
//
void printConfig( Config *config );
void printMetadata( MetadataList *list );
//
// Main Function Implementation ///////////////////////////////////
//
int main ( int argc, char *argv[] )
{
    if ( argc != 2 )
    {
        printf( "===ERR: %s REQUIRES CONFIGURATION FILE ARGUMENT===\n",
                argv[0] );
        return 0;
    }

    else
    {
        FILE *configFile = openFile( argv[1] );

        if( configFile == 0 || configFile == NULL )
        {
            free( configFile );
            printf( "===ERR: CONFIGURATION FILE NOT FOUND===\n" );
            return 0;
        }

        Config *configData = malloc( sizeof( Config ));
        if( parseConfig( configFile, configData ) == -5 )
        {
            printf( "===ERR: INVALID CONFIGURATION FILE===\n" );
            free( configFile );
            free( configData );
            return 0;
        }
        closeFile( configFile );

        FILE *metaFile = openFile( configData->metadataFilePath );

        if( metaFile == 0 || metaFile == NULL )
        {
            free( metaFile );
            printf( "===ERR: METADATA FILE NOT FOUND===\n" );
            return 0;
        }

        MetadataList *mdList = mdListCreate();

        if( parseMetadata( metaFile, mdList ) == INVALID_METADATA_FILE )
        {
            printf( "===ERR: INVALID METADATA FILE===\n" );
            free( metaFile );
            free( configData );
            return 0;
        }
        closeFile( metaFile );

		setvbuf(stdout, NULL, _IONBF, 0); // turn off buffering for stdout
        runSimulator( mdList, configData );

        mdListDestroy( mdList );
        free( configData );

        return 0;
    }
}

//==========================================================================
/**
* @brief Function prints fields from a Config struct
*
* @details Function takes a Config struct, accesses each of its' fields
*   and prints the information with a label to the screen
*
* @par Algorithm
*   Functiont takes in a Config struct, sequentially accesses each field,
*   prints a label and the data for each field in the struct.
*
* @param[in] config
* A config struct holding validated data about operating system configuration
*/
void printConfig( Config *config )
{
    printf( "Config File Dump\n" );
    printf( "====================\n" );
    printf( "Version            : %d\n", config->version );
    printf( "Program file name  : %s\n", config->metadataFilePath );
    printf( "CPU schedule code  : %s\n", config->scheduleCode );
    printf( "Quantum time       : %d\n", config->quantumTime );
    printf( "Memory size        : %d\n", config->memorySize );
    printf( "Process cycle time : %d\n", config->pCycleTime );
    printf( "I/O Cycle Time     : %d\n", config->ioCycleTime );
    printf( "Log to code        : %s\n", config->logTo );
    printf( "Log file name      : %s\n", config->logFilePath );
    printf( "====================\n\n" );
}

//==========================================================================
/**
* @brief Function prints a linked list containing metadata for operating
*   system operations and cycle times.
*
* @details Function takes a linked list and accesses each node, and prints
*   its' contents to the screen.
*
* @par Algorithm
*   Function takes in a linked list and accesses first node, prints its'
*   fields, then continues to the next node and repeats. When the end of
*   the list is reached, the function returns.
*
* @param[in] list
* A linked list containing information in its' nodes about operating
*   system metadata
*/
void printMetadata( MetadataList *list )
{
  printf("Meta-Data File Dump\n");
  printf("===================\n");

  MetadataNode *currentNode = list->first;

  while( currentNode != NULL )
  {
    printf("The data item component letter is: %c\n", currentNode->command );
    printf("The data item operation string is: %s\n", currentNode->operation );
    printf("The data item cycle time is      : %d\n\n", currentNode->value );

    currentNode = currentNode->next;
  }

  return;
}

//==========================================================================
// Terminating Precompiler Directives ///////////////////////////////
//
///// NONE
//
