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
#include "../../QueueADT/include/queue.h"
#include "../../ListADT/include/list.h"

//*************************************************************************
// Constants
//*************************************************************************
#define MAX_ERROR_AIRPORT_CHARS 64
#define NUM_RUNWAYS 3

enum {NO_AIRPORT_ERROR = 0,
			ERROR_NO_AIRPORT_CREATE,
			ERROR_NULL_PTR_AIRPLANE,
			ERROR_INVALID_AIRPORT,
			ERROR_EMPTY_RUNWAY,
			ERROR_EMPTY_IN_FLIGHT_PQ,
			ERROR_NO_AIRPORT_TERMINATE,
			ERROR_EMPTY_AIRPORT}; // If this error name changes, change stmt below
#define NUMBER_OF_AIRPORT_ERRORS ERROR_EMPTY_AIRPORT - NO_AIRPORT_ERROR + 1

//*************************************************************************
// Error Messages
//*************************************************************************
#define LOAD_AIRPORT_ERRORS strcpy(gszAirportErrors[NO_AIRPORT_ERROR], "No Error.");\
strcpy(gszAirportErrors[ERROR_NO_AIRPORT_CREATE], "Error: No AIRPORT Create.");\
strcpy(gszAirportErrors[ERROR_NULL_PTR_AIRPLANE], "Error: Null Pointer.");\
strcpy(gszAirportErrors[ERROR_NO_AIRPORT_TERMINATE], "Error: No AIRPORT Terminate.");\
strcpy(gszAirportErrors[ERROR_EMPTY_RUNWAY], "Error: Runway is Empty.");\
strcpy(gszAirportErrors[ERROR_EMPTY_IN_FLIGHT_PQ], "Error: In Flight Priority Queue is Empty.");\
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
	char aRunwayStatus[NUM_RUNWAYS];
	int timer;
} Airport;

//*************************************************************************
//										Allocation and Deallocation
//*************************************************************************

extern void airportCreate (AirportPtr);

extern void airportTerminate (AirportPtr);

extern void airportLoadErrorMessages ();

extern void airportReadLine (AirportPtr, FILE*);

extern int airportRunwaySize (AirportPtr);

extern int airportInFlightSize (AirportPtr);

extern bool emptyAirportRunway (AirportPtr);

extern bool emptyAirportInFlightPQ (AirportPtr);

//*************************************************************************
//									Inserting and retrieving values
//*************************************************************************

extern void enqueueRunway (AirportPtr);

extern void enqueueInFlightPQ (AirportPtr, int);

extern void dequeueRunway (AirportPtr);

extern void dequeueInFlightPQ (AirportPtr, int*);

extern int peekInFlightPQ (AirportPtr, int*);

#endif /* AIRPORT_H_ */
