// PROGRAMMER INFORMATION ////////////////////////////////////////////
/**

Secret Number: 764819

*/
// Code Implementation File Information /////////////////////////////
/**
* @file utilities.c
*
* @brief Implementation file for utility functions
*
* @details Implements all utility functions.
*/

// Program Description/Support /////////////////////////////////////
/*
This program implements utility functions to be used in other files
*/

// Header Files ///////////////////////////////////////////////////
//
#include "utilities.h"
//
// Global Constant Definitions ////////////////////////////////////
//
const char NUL = '\0';
const char SPACE = ' ';
const int STD_META_STR = 200;
//
// Free Function Prototypes ///////////////////////////////////////
//
//==========================================================================
/**
* @brief Function returns a file handle to the given filename
*   if it exists
*
* @details Function takes a char pointer to a given filename,
*   attempts to open the file with fopen(), and returns the file handle.
*
* @pre char *fileName should be initialized and point to a fileName
*   given as a command line argument
*
* @post FILE *file will be a valid file handle or will be 0 if the file
*   was not successfully opened.
*
* @par Algorithm
* file is created by calling fopen() and passing in the given filename,
*   and an r character symbolizing a file read is desired. The file handle
*   is returned after this call.
*
* @exception NONE
*
* @param[in] fileName
* points to the command line argument, expected to be a valid file name
*
* @param[out] file
* a file handle to the given file from command line
*
* @return A file handle to the given command line argument resembling
*   a valid file, or zero if not successfully found
*
* @note NONE
*/
FILE *openFile( char *fileName )
{
    FILE *file = fopen( fileName, "r" );

    return file;
}

//==========================================================================
/**
* @brief Function returns a new file handle to the given filename
*   after creating it
*
* @details Function takes a char pointer to a given filename,
*   attempts to create the file for writing, and returns the file handle.
*
* @par Algorithm
* file is created by calling fopen() and passing in the given filename,
*   and an r character symbolizing a file read is desired. The file handle
*   is returned after this call.
*
* @param[in] fileName
* points to the filename, expected to not exist yet, or able to overwrite
*
* @param[out] file
* a file handle to the given log filename
*
* @return A file handle to the given command line argument resembling
*   a valid file, or zero if not successfully found
*/
FILE *writeToFile( char *fileName )
{
    FILE *file = fopen( fileName, "w" );

    return file;
}

//==========================================================================
/**
* @brief Function copies contents of from into to
*
* @details Function iterates over each char in from, copies char into to,
*   continues until null character is found.
*
* @pre from should be initialized
*
* @pre to should be prepared to lose its' contents
*
* @post to now holds the same chars as from
*
* @par Algorithm
* Function copies chars in from[] into to[] until char equals the
*   null character.
*
* @param[in] to
* char array to store data in from
*
* @param[in] from
* char array holding data to be stored in to
*/
void copyString( char to[], char from[] )
{
    int index = 0;

    while(( to[index] = from[index] ) != NUL )
    {
        ++index;
    }
}

//==========================================================================
/**
* @brief Function stores data into Config struct
*
* @details Function finds proper location to store data to in Config struct
*   and stores data
*
* @pre titleStr matches one of format strings in configuration file
*
* @post configData should now hold data from line in file
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
char *trimWhiteSpace( char *data )
{
    size_t strSize;
    char *strEnd;

    strSize = ( size_t ) stringLength( data );
    if( !strSize )
    {
        return data;
    }

    strEnd = data + strSize - 1;
    while( strEnd >= data && isASpace( *strEnd ) )
    {
        strEnd--;
    }

    *( strEnd + 1 ) = NUL;

    while( *data && isASpace( *data ) )
    {
        data++;
    }

    return data;
}

//==========================================================================
/**
* @brief Function compares dataStr to formatStr and returns corresponding
*   error code
*
* @details Function iteratively compares each char in formatStr to dataStr.
*   If each comparison passes, it continues for the length of the formatStr.
*   If a comparison fails, it returns mismatch string code, if passes, no
*   error message.
*
* @pre formatStr is a valid format string from the configuration file
*
* @par Algorithm
*   Function iterates over each char in formatStr, compares each char to
*   corresponding char in dataStr, passes successfully if reaches end,
*   else returns mismatch string code.
*
* @param[in] dataStr
* array holding data to compare against corresponding format string
*
* @param[out] formatStr
* const char holding format string to compare data against
*
* @return no error code for success, mismatch string code for fail
*/
int stringCompare( char *dataStr, const char *formatStr )
{
    int index;
    for( index = 0; index < stringLength( formatStr ); index++ )
    {
        if( dataStr[index] == formatStr[index] )
        {
            continue;
        }
        else
        {
            return MISMATCH_STR;
        }
    }
    for( index = 0; index < stringLength( dataStr ); index++ )
    {
        if( dataStr[index] == formatStr[index] )
        {
            continue;
        }
        else
        {
            return MISMATCH_STR;
        }
    }

    return NO_ERROR_MSG;
}

//==========================================================================
/**
* @brief Function splits the fileData string into titleStr and dataStr at
*   the upToData index
*
* @details Function iterates over fileData to upToData index, each char
*   gets stored titleStr until upToData index is reached, then rest of
*   fileData is stored in dataStr.
*
* @par Algorithm Function iterates over fileData to upToData index, each char
*   gets stored titleStr until upToData index is reached, then rest of
*   fileData is stored in dataStr. End of titleStr and dataStr are ended with
*   null characters.
*
* @param[in] fileData
* char pointer pointing at data that will be split
*
* @param[in] titleStr
* char array to hold title portion of fileData
*
* @param[in] dataStr
* char array to hold data portion of fileData
*
* @param[in] upToData
* index at which to split fileData
*/
void splitString( char *fileData, char titleStr[],
                  char dataStr[], int upToData )
{
    int tIndex;
    int dIndex;

    for( tIndex = 0; tIndex < upToData; tIndex++ )
    {
        titleStr[tIndex] = fileData[tIndex];
    }
    titleStr[tIndex] = NUL;

    for( dIndex = 0; dIndex < ( stringLength( fileData ) - upToData );
         dIndex++, tIndex++ )
    {
        dataStr[dIndex] = fileData[tIndex];
    }
    dataStr[dIndex] = NUL;
}

//==========================================================================
/**
* @brief Function closes given file handle after verifying an open handle
*   exists.
*
* @details Function is given a file handle, verifies that it exists,
*   then closes the handle and returns. If successful, returns no error code.
*   If fail, return file not found error code.
*
* @pre file should be an existing open file handle
*
* @post file will be a closed file handle
*
* @par Algorithm
*   Function verifies file exists and is not null, if yes, closes file handle,
*   if no, returns file not found error code.
*
* @exception NONE
*
* @param[in] file
* An existing open file handle
*
* @return file not found error if file handle doesn't exist, no error if
*   successful
*/
int closeFile( FILE *file )
{
    if( file == 0 || file == NULL )
    {
        return FILE_NOT_FOUND_ERR;
    }
    else
    {
        fclose( file );
    }

    return NO_ERROR_MSG;
}

//==========================================================================
/**
* @brief Function returns integer equal to length of given string
*
* @details Function iterates over given string until finding null terminator,
*   increments count for each index of string. Returns index when done.
*
* @pre string should point to a valid string in memory to measure
*
* @par Algorithm
*   Function takes a char pointer, iterates over each char in string and
*   increments count until finding the null terminator, then returns
*   count.
*
* @param[in] string
* char pointer to iterate over
*
* @param[out] count
* length of given string
*
* @return integer representing length of given string
*/
int stringLength( const char *string )
{
    int count = 0;
    while( string[count] != NUL )
    {
        count++;
    }

    return count;
}

//==========================================================================
/**
* @brief Function returns 1 if char is a space, 0 if not
*
* @details Function takes a char to check, returns if it is a space or note
*   by comparing it to the ASCII value of space and below
*
* @par Algorithm
*   Function takes a char, checks if it is an ASCII value equal to or below
*   the ASCII value of a space character. If it is below or equal, return 1
*   to indicate it is a space, if not, return 0.
*
* @param[in] checkMe
* A char to check if it is a space character
*
* @return 1 if the char is any space character, 0 if not.
*/
int isASpace( char checkMe )
{
  if( checkMe <= SPACE )
  {
    return 1;
  }
  return 0;
}

//==========================================================================
/**
* @brief Function takes in a char array and converts the string into an integer
*
* @details Function takes in a char array, validaes that the array isn't
*   zero length, checks the sign of the number in the array, then checks each
*   char is a digit, and stores them into a base 10 integer. It concatenates
*   the sign of the number and returns the int.
*
* @par Algorithm
*   Function checks the length and sign of the number, then assuming each
*   char in the string is a digit, it converts them each to a base 10 integer
*   one at a time, and stores them in number. When done, it adds the sign of
*   the number and returns the number.
*
* @param[in] stringNumber
* A char array holding an integer to convert
*
* @param[out] number
* An integer converted from stringNumber
*
* @return an integer converted from stringNumber
*/
int stringToInt( char stringNumber[] )
{
  if( !stringNumber )
  {
    return -1;
  }

  char numberSign = stringNumber[0];
  int isPositive = 1;
  int number = 0;
  int trackIndex = 0;

  if( numberSign < '0' )
  {
    if ( numberSign == '-' )
    {
      isPositive = 0;
      trackIndex++;
    }
    else
    {
      return -1;
    }
  }

  int index = 0;
  while( stringNumber[index] != NUL )
  {
    index ++;
  }
  int stringLength = index;

  while( trackIndex < stringLength )
  {
    int digit = stringNumber[trackIndex++] - '0';
    if( digit < 0 || digit > 9 )
    {
      if( digit == ('.' - '0'))
      {
        return stringNumber[trackIndex - 2] - '0';
      }
      return -1;
    }
    number *= 10;
    number += digit;
  }

  if( isPositive )
  {
    return number;
  }
  else
  {
    return -number;
  }
}

//==============================================================================
/**
* @brief Function clears the given buffer with null terminators
*
* @details Function clears the given buffer by filling the buffer with null
*   terminators
*
* @par Algorithm
*   Function takes in a valid buffer, then iterates over it, placing a
*   null terminator at each index of the buffer
*
* @param[in] buffer
* A char array to be cleared
*
* @param[out] buffer
* A cleared char array to be used
*/
void clearBuffer( char buffer[] )
{
  int bufferIndex;

  for( bufferIndex = 0; bufferIndex < STD_META_STR; bufferIndex++ )
  {
    buffer[bufferIndex] = NUL;
  }
}
