/**************************************************************************
 File name:			airport.h
 Author:        CS, Pacific University
 Date:				  November 8 ,2021
 Class:         CS300
 Assignment:    Airport Simulation
 Purpose:				To define the constants, data structures, and
                function prototypes for implementing an Airport
 *************************************************************************/

#ifndef AIRPORT_H_
#define AIRPORT_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../QueueADT/include/queue.h"
#include "../../ListADT/include/list.h"

//*************************************************************************
// Constants
//*************************************************************************
#define MAX_ERROR_AIRPORT_CHARS 64
#define NUM_RUNWAYS 3
#define MAX_PLANES 3

enum {NO_AIRPORT_ERROR = 0,
			ERROR_NO_AIRPORT_CREATE,
			ERROR_NULL_PTR_AIRPORT,
			ERROR_NULL_FILE_PTR,
			ERROR_NULL_PTR_AIRPORT_STATS,
			ERROR_INVALID_AIRPORT,
			ERROR_EMPTY_RUNWAY,
			ERROR_EMPTY_IN_FLIGHT_PQ,
			ERROR_NO_AIRPORT_TERMINATE,
			ERROR_EMPTY_AIRPORT}; // If this error name changes, change stmt below
#define NUMBER_OF_AIRPORT_ERRORS ERROR_EMPTY_AIRPORT - NO_AIRPORT_ERROR + 1

//*************************************************************************
// Error Messages
//*************************************************************************
#define LOAD_AIRPORT_ERRORS strcpy(gszAirportErrors[NO_AIRPORT_ERROR] \
		, "No Error.");\
strcpy(gszAirportErrors[ERROR_NO_AIRPORT_CREATE] \
		, "Error: No AIRPORT Create.");\
strcpy(gszAirportErrors[ERROR_NULL_PTR_AIRPORT] \
		, "Error: Null Pointer.");\
strcpy(gszAirportErrors[ERROR_NULL_PTR_AIRPORT_STATS] \
		, "Error: Null Airport Stats.");\
strcpy(gszAirportErrors[ERROR_NULL_FILE_PTR] \
		, "Error: Null File Pinter.");\
strcpy(gszAirportErrors[ERROR_NO_AIRPORT_TERMINATE] \
		, "Error: No AIRPORT Terminate.");\
strcpy(gszAirportErrors[ERROR_EMPTY_RUNWAY] \
		, "Error: Runway is Empty.");\
strcpy(gszAirportErrors[ERROR_EMPTY_IN_FLIGHT_PQ] \
		, "Error: In Flight Priority Queue is Empty.");\
strcpy(gszAirportErrors[ERROR_INVALID_AIRPORT] \
		, "Error: Invalid AIRPORT.");\
strcpy(gszAirportErrors[ERROR_EMPTY_AIRPORT] \
		, "Error: Empty AIRPORT.");

//*************************************************************************
// User-defined types
//*************************************************************************

typedef struct Airplane
{
	int fuel;
	int entryTimer;
} Airplane;
typedef Airplane* AirplanePtr;


typedef struct Airport *AirportPtr;
typedef struct Airport
{
	Queue sRunwayQueue;
	PriorityQueue sInFlightPQueue;
	char aRunwayStatus[NUM_RUNWAYS];
	int timer;
	int crashCount;
} Airport;

typedef struct AirportStats *AirportStatsPtr;
typedef struct AirportStats
{
	int currentNumTakeoff;
	int currentNumLanding;
	int totalNumTakeoff;
	int totalNumLanding;
	int aFuelRemaining[MAX_PLANES];
	int totalLandingWait;
	int totalTakeoffWait;
	int totalTimeRemaining;
	int numPlanesWithNoFuel;
	int numCrashes;

} AirportStats;

//*************************************************************************
//										Allocation and Deallocation
//*************************************************************************

extern void airportCreate (AirportPtr, AirportStatsPtr);

extern void airportTerminate (AirportPtr);

extern void airportLoadErrorMessages ();

//*************************************************************************
//									Inserting and retrieving values
//*************************************************************************

extern void enqueueRunway (AirportPtr);

extern void enqueueInFlightPQ (AirportPtr, int);

extern void dequeueRunway (AirportPtr);

extern void dequeueInFlightPQ (AirportPtr, int*);

extern Airplane peekInFlightPQ (AirportPtr, int*, int*);

extern Airplane peekRunway(AirportPtr, int*);

void airportPrintRow (AirportPtr, AirportStatsPtr);

//*************************************************************************
//									Checking number of elements in priority queue
//*************************************************************************

extern int airportRunwaySize (AirportPtr);

extern int airportInFlightSize (AirportPtr);

extern bool emptyAirportRunway (AirportPtr);

extern bool emptyAirportInFlightPQ (AirportPtr);

//*************************************************************************
//									Setting values in Airport for next turn
//*************************************************************************

extern void setNextTurn (AirportPtr, AirportStatsPtr);

extern void updateAirport (AirportPtr, AirportStatsPtr);

extern void decrementFuel (AirportPtr);

extern void airportReadLine (AirportPtr, FILE*, AirportStatsPtr);

extern void airportIncrementTimer (AirportPtr);

#endif /* AIRPORT_H_ */
