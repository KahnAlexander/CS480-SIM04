// PROGRAMMER INFORMATION ////////////////////////////////////////////
/**

Secret Number: 764819

*/
// Code Implementation File Information /////////////////////////////
/**
* @file metadataParser.c
*
* @brief Implementation file for metadataParser code
*
* @details Implements all functions of the metadataParser utilities
*/

// Program Description/Support /////////////////////////////////////
/*
This program reads metadata from a file and validates and stores that
information into a linked list struct. This program borrows error
codes from configParser.h.
*/
// Header Files ///////////////////////////////////////////////////
//
#include "metadataParser.h"
#include "configParser.h"
#include "metadataList.h"
#include "utilities.h"
//
// Global Constant Definitions ////////////////////////////////////
//
const char META_START_STR[] = "Start Program Meta-Data Code:";
const char META_END_STR[] = "End Program Meta-Data Code.";

const char OPEN_PAREN = '(';
const char CLOSE_PAREN = ')';
const char SEMICOLON = ';';
const char PERIOD = '.';

const char ACCESS_OP[] = "access";
const char ALLOC_OP[] = "allocate";
const char END_OP[] = "end";
const char HD_OP[] = "hard drive";
const char KEYBOARD_OP[] = "keyboard";
const char PRINTER_OP[] = "printer";
const char MONITOR_OP[] = "monitor";
const char RUN_OP[] = "run";
const char START_OP[] = "start";
//
// Free Function Prototypes ///////////////////////////////////////
//
/**
* @brief Function validates each line in the metadata file and validates and
*   stores the opCodes in the file if they are formatted correctly.
*
* @details Function calls getFirstLine() to validate first line of file,
*   returns error codes for proper or improper file format, then loops over
*   each following line of file until a line is incorrectly formatted or it
*   reaches the end of the file. Function then frees the inLine pointer.
*
* @par Algorithm
*   Function gets a validates the first file line with getFirstLine(),
*   then loops and calls getData() until it reaches the end of the file,
*   or the file is found to be invalid. Whether the file is valid or not,
*   the inLine pointer is freed and proper error code is returned.
*
* @param[in] metaFile
* A valid and open file handle to the metadata file
*
* @param[in] list
* An initialized metadataList
*
* @return no error code if file is valid, or invalid metadata file if the file
*   is not formatted correctly.
*/
int parseMetadata( FILE *metaFile, MetadataList *list )
{
  char *inLine = malloc( STD_META_STR );

  if( getFirstLine( inLine, metaFile ) == MISMATCH_STR )
  {
    return INVALID_METADATA_FILE;
  }

  int result = 0;
  while( result == NO_ERROR_MSG )
  {
    result = getData( inLine, metaFile, list );
  }
  if( result == INVALID_METADATA_FILE )
  {
    free( inLine );
    return INVALID_METADATA_FILE;
  }

  free( inLine );
  return NO_ERROR_MSG;
}

//==========================================================================
/**
* @brief Function checks the first line of the file for correct formatting
*
* @details Function gets first line from metadata file, compares to format
*   string, and returns no error if matches, returns mismatch string if not
*
* @par Algorithm
*   Function takes a char pointer to store the file line in, and a file handle
*   to the open metadata file, trims the whitespace from the first line of the
*   file, then compares it to the format string. If matches, return no error,
*   if not match, return mismatch string.
*
* @param[in] fileLine
* A char pointer to store the first file line in
*
* @param[in] metaFile
* An open file handle for the metadata file
*
* @return no error found code if first line matches format, returns
*   mismatch string if doesn't match format
*/
int getFirstLine( char *fileLine, FILE *metaFile )
{
  fgets( fileLine, STD_META_STR, metaFile );
  fileLine = trimWhiteSpace( fileLine );

  if( stringCompare( fileLine, META_START_STR ) == NO_ERROR_MSG )
  {
      return NO_ERROR_MSG;
  }

  return MISMATCH_STR;
}

//==========================================================================
/**
* @brief Function takes next line from a metadata file, either compares it
*   to the file ending string, or processes the opCode within the line.
*
* @details Function gets a line from metafile, checks it for last line of
*   file, and if not, gets the opCodes from that line.
*
* @par Algorithm
*   Function gets next line from file, trims whitespace from line,
*   checks if it is ending line of file, if so, it returns end of file code,
*   if not, it passes the fileLine to getNextOpCode() for validating and
*   storing into list.
*
* @param[in] fileLine
* A char pointer to hold the next line of the file
*
* @param[in] metaFile
* A file handle pointing to the open metadata file
*
* @param[in] list
* A metadataList
*
* @return end of file code if last line was read in, no error message if
*   opCodes were processed successfully, or invalid metadata file code if
*   end line did not match or codes were not successfully stored.
*/
int getData( char *fileLine, FILE *metaFile, MetadataList *list )
{
  if( fgets( fileLine, STD_META_STR, metaFile ) == NULL )
  {
      return INVALID_METADATA_FILE;
  }

  fileLine = trimWhiteSpace( fileLine );

  if( fileLine[0] == 'E' )
  {
      if( stringCompare( fileLine, META_END_STR ) == NO_ERROR_MSG )
      {
          return END_OF_FILE;
      }
      return INVALID_METADATA_FILE;
  }

  if( getNextOpCode( fileLine, list ) == INVALID_OP_CODE )
  {
      return INVALID_METADATA_FILE;
  }

  return NO_ERROR_MSG;
}

//==========================================================================
/**
* @brief Function takes in a list and opCode values, stores these values in
*   a metadataNode and appends this node to the linked list
*
* @details Function takes in a command, operation, and value, creates a node
*   and stores these parameters in the node. Then the node is appended to the
*   linked list.
*
* @par Algorithm
*   Function takes a command, operation, and value, calls function to create
*   a node with these parameters, then appends that node to the end of the
*   given linked list.
*
* @param[in] command
* A char validated as a command letter
*
* @param[in] operatiom
* A char pointer validated as an opCode operation
*
* @param[in]  value
* An integer validated as a cycle time
*
* @param[in] list
* A metadata linked list
*/
void storeOpCode( char command, char *operation,
                  int value, MetadataList *list )
{
  addMdNode( list, createMdNode( command, operation, value ));
}

//==========================================================================
/**
* @brief Function takes in a file line, and a list,
*
* @details Function takes in a file line, and scans the line, looking for one
*   opCode at a time, by scanning one command letter, an open paren,
*   an operation string, a close paren, an integer, and a period or semicolon.
*   If these are all found, the data is validated and stored in a node in
*   list, and it continues to the end of the line.
*
* @par Algorithm
*   Function creates indices for scanning, and values to hold validated fields
*   of the opCodes. Loops over line until it finds the null terminator.
*   For each loop (one opCode), it clears the operation and valueStr buffers,
*   if the current char is a space (space between each opCode), it skips,
*   then it stores the next letter into command, and calls validateCommand().
*   It then checks for an open paren (, then iterates over chars to store
*   the operation, which is then validated. It checks for a close paren ).
*   Now it reads in number characters into valueStr, converts value to an int,
*   and checks for a period or semicolon, where if one is found, it stores the
*   opCode into list, and returns the proper error code.
*
* @param[in] dataToScan
* A char pointer to the line of the file containing opCodes
*
* @param[in] list
* An initialized metadataList
*
* @return no error if formatting is valid, invalid op code if formatting is
*   not, or end of file if last opcode is found.
*/
int getNextOpCode( char *dataToScan, MetadataList *list )
{
  int dataIndex = 0;
  int operationIndex = 0;
  int valueStrIndex = 0;

  char command;
  int value = 0;
  char valueStr[STD_META_STR];

  while( dataToScan[dataIndex] != NUL )
  {
    char operation[STD_META_STR];
    clearBuffer( operation );
    clearBuffer( valueStr );

    if( dataToScan[dataIndex] == SPACE )
    {
      dataIndex++;
    }

    command = dataToScan[dataIndex++];
    if( validateCommand( command ) == MISMATCH_STR )
    {
      return INVALID_OP_CODE;
    }

    if( dataToScan[dataIndex++] != OPEN_PAREN )
    {
      return INVALID_OP_CODE;
    }

    operationIndex = 0;
    while(( dataToScan[dataIndex] >= 'a' && dataToScan[dataIndex] <= 'z' ) ||
          ( dataToScan[dataIndex] == SPACE ))
    {
      operation[operationIndex++] = dataToScan[dataIndex++];
    }
    if( validateOperation( operation, command ) == MISMATCH_STR)
    {
      return INVALID_OP_CODE;
    }

    if( dataToScan[dataIndex++] != CLOSE_PAREN )
    {
      return INVALID_OP_CODE;
    }

    valueStrIndex = 0;
    while( dataToScan[dataIndex] >= '0' && dataToScan[dataIndex] <= '9' )
    {
      valueStr[valueStrIndex++] = dataToScan[dataIndex++];
    }
    if( command == 'M' && stringLength( valueStr ) != 8 )
    {
        return INVALID_OP_CODE;
    }
    value = stringToInt( valueStr );

    if( dataToScan[dataIndex] == PERIOD )
    {
      if( dataToScan[dataIndex + 1] == NUL )
      {
        storeOpCode( command, operation, value, list );
        return END_OF_FILE;
      }
      return INVALID_OP_CODE;
    }

    if( dataToScan[dataIndex++] != SEMICOLON )
    {
      return INVALID_OP_CODE;
    }
    storeOpCode( command, operation, value, list );
  }

  return NO_ERROR_MSG;
}

//==========================================================================
/**
* @brief Function takes a command letter and validates it against expected
*   command letters
*
* @details Function compares given command letter against expected ones to
*   validate it, return mismatch string if not valid command letter, returns
*   no error if it matches an expected letter.
*
* @par Algorithm
*   Function takes a command letter, compares it to expected ones, returns
*   no error if match found, returns mismatch string if error not found.
*
* @param[in] command
* A char corresponding to a command letter
*
* @return no error code if match found, mismatch string if not valid letter
*/
int validateCommand( char command )
{
  if( command == 'S' || command == 'A' || command == 'P' ||
      command == 'M' || command == 'I' || command == 'O' )
  {
    return NO_ERROR_MSG;
  }
  return MISMATCH_STR;
}

//==========================================================================
/**
* @brief Function compares the given operation against valid expected
*   operation strings
*
* @details Function compares given string against expected format for
*   operations, returns no error message if given operation is valid,
*   returns mismatch string if operation is not valid
*
* @par Algorithm
*   Function takes in char pointer looking at operation string,
*   compares that to expected operations and returns success if
*   it matches a format, returns mismatch if not found
*
* @param[in] operation
* A char pointer looking at a string in memory
*
* @return mismatch string error code if operation does not match any format,
*   no error found code if operation matches a format.
*/
int validateOperation( char *operation, char command )
{
    if( stringCompare( operation, ACCESS_OP ) == NO_ERROR_MSG ||
        stringCompare( operation, ALLOC_OP ) == NO_ERROR_MSG )
    {
        if( command == 'M'){
            return NO_ERROR_MSG;
        }
    }
    else if( stringCompare( operation, END_OP ) == NO_ERROR_MSG ||
            stringCompare( operation, START_OP ) == NO_ERROR_MSG )
    {
        if( command == 'S' || command == 'A' )
        {
            return NO_ERROR_MSG;
        }
    }
    else if( stringCompare( operation, MONITOR_OP ) == NO_ERROR_MSG ||
            stringCompare( operation, PRINTER_OP ) == NO_ERROR_MSG )
    {
        if( command == 'O' )
        {
            return NO_ERROR_MSG;
        }
    }
    else if( stringCompare( operation, KEYBOARD_OP ) == NO_ERROR_MSG )
    {
        if( command == 'I' )
        {
            return NO_ERROR_MSG;
        }
    }
    else if( stringCompare( operation, HD_OP ) == NO_ERROR_MSG )
    {
        if( command == 'I' || command == 'O')
        {
            return NO_ERROR_MSG;
        }
    }
    else if( stringCompare( operation, RUN_OP ) == NO_ERROR_MSG )
    {
        if( command == 'P' )
        {
            return NO_ERROR_MSG;
        }
    }

    return MISMATCH_STR;
}

//==============================================================================
// Terminating Precompiler Directives ///////////////////////////////
//
///// NONE
//
