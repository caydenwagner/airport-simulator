/**************************************************************************
 File name:
 Author:        CS, Pacific University
 Date:
 Class:         CS300
 Assignment:    Airport Simulation
 Purpose:
 *************************************************************************/


#ifndef AIRPORT_H_
#define AIRPORT_H_

#include <stdbool.h>
#include "../../PriorityQueueADT/include/pqueue.h"
#include "../../QueueADT/include/queue.h"

//*************************************************************************
// Constants
//*************************************************************************
#define MAX_ERROR_AIRPORT_CHARS 64

enum {NO_AIRPORT_ERROR = 0,
			ERROR_NO_AIRPORT_CREATE,
			ERROR_INVALID_AIRPORT,
			ERROR_EMPTY_AIRPORT}; // If this error name changes, change stmt below
#define NUMBER_OF_AIRPORT_ERRORS ERROR_EMPTY_AIRPORT - NO_AIRPORT_ERROR + 1

//*************************************************************************
// Error Messages
//*************************************************************************
#define LOAD_AIRPORT_ERRORS strcpy(gszAirportErrors[NO_AIRPORT_ERROR], "No Error.");\
strcpy(gszAirportErrors[ERROR_NO_AIRPORT_CREATE], "Error: No AIRPORT Create.");\
strcpy(gszAirportErrors[ERROR_INVALID_AIRPORT], "Error: Invalid AIRPORT.");\
strcpy(gszAirportErrors[ERROR_EMPTY_AIRPORT], "Error: Empty AIRPORT.");

//*************************************************************************
// User-defined types
//*************************************************************************

typedef struct Airplane
{
	int fuel;
} Airplane;
typedef Airplane* AirplanePtr;


typedef struct Airport *AirportPtr;
typedef struct Airport
{
	Queue sRunwayQueue;
	PriorityQueue sInFlightPQueue;
	char aRunwayStatus[3];
	int timer;
} Airport;

extern void airportCreate (AirportPtr);

extern void airportLoadErrorMessages ();

#endif /* AIRPORT_H_ */
