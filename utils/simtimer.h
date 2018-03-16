// PROGRAMMER INFORMATION ////////////////////////////////////////////
/**

Secret Number: 764819

*/
// Program Information ////////////////////////////////////////////////////////
/**
 * @file simtimer.h
 *
 * @brief Header file for micro-second precision timer. This is code slightly
 *  altered from Michael Leverington's simtimer code, made to work with sim02.
 *
 * @details Specifies all member methods of the SimpleTimer
 */

// Precompiler directives /////////////////////////////////////////////////////

#ifndef SIMTIMER_H
#define SIMTIMER_H

// Header files ///////////////////////////////////////////////////////////////

#include <sys/time.h>
#include <string.h>
#include <math.h>

// Global Constants  //////////////////////////////////////////////////////////

enum TIMER_CTRL_CODES { ZERO_TIMER, LAP_TIMER, STOP_TIMER };
enum Bool { False, True };

extern const char RADIX_POINT;
extern const char SPACE;

// Function Prototyp  /////////////////////////////////////////////////////////

void *runTimer( void *msTime );
double accessTimer( int controlCode, char *timeStr );
double processTime( double startSec, double endSec,
                           double startUSec, double endUSec, char *timeStr );
void timeToString( int secTime, int uSecTime, char *timeStr );

#endif // ifndef SIMTIMER_H
