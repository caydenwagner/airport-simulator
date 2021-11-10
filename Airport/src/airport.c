/**************************************************************************
 File name:		 airport.c
 Author:			 Cayden Wagner
 Date:				 10/28/21
 Class:			 	 CS300
 Assignment:	 Airport
 *************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../include/airport.h"

const char EMPTY_RUNWAY = '-';
const char EMERGENCY_RUNWAY = 'E';
const char LANDING_RUNWAY = 'L';
const char TAKEOFF_RUNWAY = 'T';
const int MAX_RUNWAYS = 3;

char gszAirportErrors[NUMBER_OF_AIRPORT_ERRORS][MAX_ERROR_AIRPORT_CHARS];
/**************************************************************************
 Function: 	 		processError

 Description:   Process the error code passed to this routine

 Parameters:		pszFunctionName - function causing the error
 	 	 	 					errorCode 	    - identifies the list error

 Returned:	 		None
 *************************************************************************/
void processError (const char *pszFunctionName, int errorCode)
{
	printf ("Function: %s %s \n ", pszFunctionName,
			gszAirportErrors [errorCode]);
  exit (EXIT_FAILURE);
}
/**************************************************************************
 Function:			airportLoadErrorMessages

 Description: 	Initializes the string of error messages.
 	 	 	 	 	 	 	 	LOAD_AIRPORT_ERRORS is a macro defined in the header file.


 Parameters:		None

 Returned:	 		None
 *************************************************************************/
void airportLoadErrorMessages ()
{
	pqueueLoadErrorMessages ();
	queueLoadErrorMessages ();
	LOAD_AIRPORT_ERRORS
}
/**************************************************************************
 Function:			airportCreate

 Description:		creates the airport by initializing the runway queue and
 	 	 	 	 	 	 	 	the in flight priority queue

 Parameters:		psTheAirport - the address of the airport
 	 	 	 	 	 	 	 	psStats			 - a pointer to the AirportStats struct that stores
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 key data about the airport

 Returned:	 		None
 *************************************************************************/
void airportCreate (AirportPtr psTheAirport, AirportStatsPtr psStats)
{
	if (NULL == psTheAirport)
	{
		processError("airportCreate", ERROR_NO_AIRPORT_CREATE);
	}
	if (NULL == psStats)
	{
		processError("airportCreate", ERROR_NULL_PTR_AIRPORT_STATS);
	}
	queueCreate(&(psTheAirport->sRunwayQueue));
	pqueueCreate(&(psTheAirport->sInFlightPQueue));
	psTheAirport->timer = 1;
	for (int i = 0; i < MAX_RUNWAYS; i++)
	{
		psTheAirport->aRunwayStatus[i] = EMPTY_RUNWAY;
		psTheAirport->crashCount = 0;
	}
	psStats->totalLandingWait = 0;
	psStats->totalTakeoffWait = 0;
	psStats->totalNumLanding = 0;
	psStats->totalNumTakeoff = 0;
	psStats->totalTimeRemaining = 0;
	psStats->numCrashes = 0;
	psStats->numPlanesWithNoFuel = 0;
}
/**************************************************************************
 Function:			airportTerminate

 Description:		terminates the airport by terminating the runway queue and
 	 	 	 	 	 	 	 	the in flight priority queue

 Parameters:		psTheAirport - the address of the airport

 Returned:	 		None
 *************************************************************************/
void airportTerminate (AirportPtr psTheAirport)
{
	if (NULL == psTheAirport)
	{
		processError("airportTerminate", ERROR_NO_AIRPORT_TERMINATE);
	}
	queueTerminate(&(psTheAirport->sRunwayQueue));
	pqueueTerminate(&(psTheAirport->sInFlightPQueue));
}
/**************************************************************************
 Function:			airportReadLine

 Description:		reads a line from a file and updates the the runway queue and
 	 	 	 	 	 	 	 	the in flight priority queue using the data read

 Parameters:		psTheAirport - the address of the airport
 	 	 	 	 	 	 	 	fPtr 				 - a pointer to the read file
 	 	 	 	 	 	 	 	psStats			 - a pointer to the AirportStats struct that stores
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 key data about the airport

 Returned:	 		None
 *************************************************************************/
void airportReadLine (AirportPtr psTheAirport, FILE *fPtr,
											AirportStatsPtr psStats)
{
	if (NULL == psTheAirport)
	{
		processError("airportReadLine", ERROR_NULL_PTR_AIRPORT);
	}
	if (NULL == fPtr)
	{
		processError("airportReadLine", ERROR_NULL_FILE_PTR);
	}
	if (NULL == psStats)
	{
		processError("airportReadLine", ERROR_NULL_PTR_AIRPORT_STATS);
	}
	const int MAX_NUM_PLANES = 3;
	const int EMPTY = -1;
	int numTakeoffPlanes = 0, numLandingPlanes = 0;
	int aFuel[MAX_NUM_PLANES];

	for (int i = 0; i < MAX_NUM_PLANES; i++)
	{
		psStats->aFuelRemaining[i] = EMPTY;
	}

	fscanf(fPtr,"%d", &numTakeoffPlanes);
	fscanf(fPtr,"%d", &numLandingPlanes);

	psStats->currentNumLanding = numLandingPlanes;
	psStats->currentNumTakeoff = numTakeoffPlanes;

	for (int i = 0; i < numTakeoffPlanes; i++)
	{
		enqueueRunway(psTheAirport);
	}

	for (int i = 0; i < MAX_NUM_PLANES; i++)
	{
		fscanf(fPtr,"%d", &aFuel[i]);
	}

	for (int i = 0; i < numLandingPlanes; i++)
	{
		enqueueInFlightPQ(psTheAirport, aFuel[i]);
	}

	for (int i = 0; i < numLandingPlanes; i++)
	{
		psStats->aFuelRemaining[i] = aFuel[i];
	}
}
/**************************************************************************
 Function:			enqueueRunway

 Description:		enqueues an airplane into the runway queue

 Parameters:		psTheAirport - the address of the airport

 Returned:	 		None
 *************************************************************************/
void enqueueRunway(AirportPtr psTheAirport)
{
	if (NULL == psTheAirport)
	{
		processError("enqueueRunway", ERROR_INVALID_AIRPORT);
	}

	Airplane sAirplane;
	sAirplane.entryTimer = psTheAirport->timer;
	queueEnqueue(&(psTheAirport->sRunwayQueue), &sAirplane, sizeof(Airplane));
}
/**************************************************************************
 Function:			enqueueInFlightPQ

 Description:		enqueues the in flight priority queue

 Parameters:		psTheAirport - the address of the airport
 	 	 	 	 	 	 	 	fuel 				 - the fuel of the queued airplane, used as the
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 priority in the in flight priority queue

 Returned:	 		None
 *************************************************************************/
void enqueueInFlightPQ (AirportPtr psTheAirport, int fuel)
{
	if (NULL == psTheAirport)
	{
		processError("enqueueRunway", ERROR_INVALID_AIRPORT);
	}

	Airplane sAirplane;
	sAirplane.entryTimer = psTheAirport->timer;
	sAirplane.fuel = fuel;
	pqueueEnqueue(&(psTheAirport->sInFlightPQueue), &sAirplane, sizeof(Airplane),
								sAirplane.fuel);
}
/**************************************************************************
 Function:			airportRunwaySize

 Description:		returns the size of the airport runway queue

 Parameters:		psTheAirport - the address of the airport

 Returned:	 		an integer value that is the number of elements in the
 	 	 	 	 	 	 	 	runway queue
 *************************************************************************/
int airportRunwaySize (AirportPtr psTheAirport)
{
	if (NULL == psTheAirport)
	{
		processError("airportRunwaySize", ERROR_INVALID_AIRPORT);
	}
	return queueSize(&(psTheAirport->sRunwayQueue));
}
/**************************************************************************
 Function:			airportInFlightSize

 Description:		returns the size of the airport in flight priority queue

 Parameters:		psTheAirport - the address of the airport

 Returned:	 		an integer value that is the number of elements in the
 	 	 	 	 	 	 	 	in flight priority queue
 *************************************************************************/
int airportInFlightSize (AirportPtr psTheAirport)
{
	if (NULL == psTheAirport)
	{
		processError("airportInFlightSize", ERROR_INVALID_AIRPORT);
	}
	return pqueueSize(&(psTheAirport->sInFlightPQueue));
}
/**************************************************************************
 Function:			peekInFlightPQ

 Description:		checks the priority of the first element in the in flight
  							priority queue

 Parameters:		psTheAirport - the address of the airport
 	 	 	 	 	 	 	 	pFuel				 - space to store the fuel of the top plane in the
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 priority queue
 	 	 	 	 	 	 	 	pTimer			 - space to store the integer timer of the top plane
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 in the priority queue

 Returned:	 		a pointer to the highest priority airplane
 *************************************************************************/
Airplane peekInFlightPQ (AirportPtr psTheAirport, int* pFuel, int* pTimer)
{
	if (NULL == psTheAirport)
	{
		processError("peekInFlightPQ", ERROR_INVALID_AIRPORT);
	}
	if (NULL == pFuel)
	{
		processError("peekInFlightPQ", ERROR_NULL_PTR_AIRPORT);
	}
	if (NULL == pTimer)
	{
		processError("peekInFlightPQ", ERROR_NULL_PTR_AIRPORT);
	}
	if (emptyAirportInFlightPQ(psTheAirport))
	{
		processError("peekInFlightPQ", ERROR_EMPTY_IN_FLIGHT_PQ);
	}
	Airplane sAirplane;
	pqueuePeek(&(psTheAirport->sInFlightPQueue), &sAirplane, sizeof(Airplane),
						 pFuel);
	*pTimer = sAirplane.entryTimer;

	return sAirplane;
}
/**************************************************************************
 Function:			peekRunway

 Description:		checks the airplane at the front of the runway queue

 Parameters:		psTheAirport - the address of the airport
 	 	 	 	 	 	 	  pTimer 			 - Space to store the timer integer of the dequeued
 	 	 	 	 	 	 	   	 	 	 	 	 	   plane

 Returned:	 		the airplane at the front of the queue
 *************************************************************************/
Airplane peekRunway (AirportPtr psTheAirport, int* pTimer)
{
	if (NULL == psTheAirport)
	{
		processError("peekRunway", ERROR_INVALID_AIRPORT);
	}
	if (NULL == pTimer)
	{
		processError("peekRunway", ERROR_NULL_PTR_AIRPORT);
	}
	if (emptyAirportRunway(psTheAirport))
	{
		processError("peekRunway", ERROR_EMPTY_RUNWAY);
	}
	Airplane sAirplane;
	queuePeek(&(psTheAirport->sRunwayQueue), &sAirplane, sizeof(Airplane));
	*pTimer = sAirplane.entryTimer;

	return sAirplane;
}
/**************************************************************************
 Function:			emptyAirportRunway

 Description:		checks if the runway is empty or not

 Parameters:		psTheAirport - the address of the airport

 Returned:	 		true if the runway queue contains 0 elements, else false
 *************************************************************************/
bool emptyAirportRunway (AirportPtr psTheAirport)
{
	if (NULL == psTheAirport)
	{
		processError("emptyAirportRunway", ERROR_INVALID_AIRPORT);
	}

	return queueIsEmpty(&(psTheAirport->sRunwayQueue));
}
/**************************************************************************
 Function:			emptyAirportInFlightPQ

 Description:		checks if the in flight priority queue is empty or not

 Parameters:		psTheAirport - the address of the airport

 Returned:	 		true if the priority queue contains 0 elements, else false
 *************************************************************************/
bool emptyAirportInFlightPQ (AirportPtr psTheAirport)
{
	if (NULL == psTheAirport)
	{
		processError("emptyAirportInFlightPQ", ERROR_INVALID_AIRPORT);
	}

	return pqueueIsEmpty(&(psTheAirport->sInFlightPQueue));
}
/**************************************************************************
 Function:			dequeueRunway

 Description:		dequeues the first element in the runway queue

 Parameters:		psTheAirport - the address of the airport

 Returned:	 		None
 *************************************************************************/
void dequeueRunway (AirportPtr psTheAirport)
{
	if (NULL == psTheAirport)
	{
		processError("dequeueRunway", ERROR_INVALID_AIRPORT);
	}
	if (emptyAirportRunway(psTheAirport))
	{
		processError("dequeueRunway", ERROR_EMPTY_RUNWAY);
	}
	Airplane sAirplane;
	queueDequeue(&(psTheAirport->sRunwayQueue), &sAirplane, sizeof(Airplane));
}
/**************************************************************************
 Function:			dequeueInFlightPQ

 Description:		dequeues the highest priority element in the in flight
 	 	 	 	 	 	 	 	priority queue

 Parameters:		psTheAirport - the address of the airport
 	 	 	 	 	 	 	 	pBuf 				 - Buffer space to store the priority of the
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	dequeued plane

 Returned:	 		None
 *************************************************************************/
void dequeueInFlightPQ (AirportPtr psTheAirport, int* pBuf)
{
	if (NULL == psTheAirport)
	{
		processError("dequeueInFlightPQ", ERROR_INVALID_AIRPORT);
	}
	if (emptyAirportInFlightPQ(psTheAirport))
	{
		processError("dequeueInFlightPQ", ERROR_EMPTY_IN_FLIGHT_PQ);
	}
	if (NULL == pBuf)
	{
		processError("dequeueInFlightPQ", ERROR_NULL_PTR_AIRPORT);
	}
	Airplane sAirplane;

	pqueueDequeue(&(psTheAirport->sInFlightPQueue), &sAirplane, sizeof(Airplane),
								pBuf);
}
/**************************************************************************
 Function:			airportIncrementTimer

 Description:		Increments the airport timer by 1

 Parameters:		psTheAirport - the address of the airport

 Returned:	 		None
 *************************************************************************/
void airportIncrementTimer (AirportPtr psTheAirport) {
	if (NULL == psTheAirport)
	{
		processError("AirportIncrementTimer", ERROR_INVALID_AIRPORT);
	}
	psTheAirport->timer++;
}
/**************************************************************************
 Function:			airportPrintRow

 Description:		Prints one turn of the Airport in the correct format

 Parameters:		psTheAirport - the address of the airport
 	 	 	 	 	 	 	 	psStats			 - a pointer to the AirportStats struct that stores
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 key data about the airport

 Returned:	 		None
 *************************************************************************/
void airportPrintRow (AirportPtr psTheAirport, AirportStatsPtr psStats)
{
	if (NULL == psTheAirport)
	{
		processError("AirportPrintRow", ERROR_INVALID_AIRPORT);
	}
	if (NULL == psStats)
	{
		processError("AirportPrintRow", ERROR_NULL_PTR_AIRPORT_STATS);
	}
	const int EMPTY = -1;
	const char EMPTY_CHAR = '-';
	const int COL_1_SPACES = 4;
	const int COL_2_SPACES = 7;
	const int COL_3_SPACES = 9;
	const int COL_4_SPACES = 5;
	const int COL_6_SPACES = 3;
	const int COL_7_SPACES = 6;
	const int COL_8_SPACES = 7;
	const int COL_9_SPACES = 9;

	fprintf(stdout, "%*d", COL_1_SPACES, psTheAirport->timer);
	printf(" | ");
	printf("%*d", COL_2_SPACES, psStats->currentNumTakeoff);
	printf("%*d", COL_3_SPACES, psStats->currentNumLanding);
	printf(" |");

	for (int i = 0; i < MAX_PLANES; i++)
	{
		if (EMPTY == psStats->aFuelRemaining[i])
		{
			printf("%*c", COL_4_SPACES, EMPTY_CHAR);
		}
		else
		{
			printf("%*d", COL_4_SPACES, psStats->aFuelRemaining[i]);
		}
	}

	printf(" |");

	for(int i = 0; i < MAX_PLANES; i++)
	{
		printf("%*c ", COL_6_SPACES, psTheAirport->aRunwayStatus[i]);
	}

	printf("%*d", COL_7_SPACES, psTheAirport->crashCount);

	printf(" | ");

	printf("%*d", COL_8_SPACES, airportRunwaySize(psTheAirport));
	printf("%*d", COL_9_SPACES, airportInFlightSize(psTheAirport));


	printf("\n");
}
/**************************************************************************
 Function:			updateAirport

 Description:		Services planes that are in the air or ready for takeoff. Lands
  							emergency planes with no fuel as the first priority, then moves
  							on to whichever queue is larger

 Parameters:		psTheAirport - the address of the airport
 	 	 	 	 	 	 	  psStats			 - a pointer to the AirportStats struct that stores
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 key data about the airport

 Returned:	 		None
 *************************************************************************/
void updateAirport (AirportPtr psTheAirport, AirportStatsPtr psStats)
{
	if (NULL == psTheAirport)
	{
		processError("updateAirport", ERROR_INVALID_AIRPORT);
	}
	if (NULL == psStats)
	{
		processError("updateAirport", ERROR_NULL_PTR_AIRPORT_STATS);
	}

	bool bEmergency = true, bEmpty = false;
	int runwaysTaken = 0;
	int fuel, entryTimer;
	Airplane sTemp;

	while(bEmergency && MAX_PLANES > runwaysTaken &&
			 (!(emptyAirportInFlightPQ(psTheAirport))))
	{
		sTemp = peekInFlightPQ(psTheAirport, &fuel, &entryTimer);
		if (fuel < 0)
		{
			psTheAirport->crashCount++;
			psStats->numCrashes++;
			dequeueInFlightPQ(psTheAirport, &fuel);
			psStats->totalLandingWait += psTheAirport->timer - sTemp.entryTimer + 1;
			psStats->totalTimeRemaining += fuel;
		}
		else if (0 == fuel)
		{
			dequeueInFlightPQ(psTheAirport, &fuel);
			psTheAirport->aRunwayStatus[runwaysTaken] = EMERGENCY_RUNWAY;
			runwaysTaken++;
			psStats->numPlanesWithNoFuel++;
			psStats->totalLandingWait += psTheAirport->timer - sTemp.entryTimer + 1;
			psStats->totalTimeRemaining += fuel;
		}
		else
		{
			bEmergency = false;
		}
	}

	while (MAX_PLANES > runwaysTaken && !bEmpty)
	{
		if (airportRunwaySize(psTheAirport) > airportInFlightSize(psTheAirport) &&
				(!(emptyAirportRunway(psTheAirport))))
		{
			sTemp = peekRunway(psTheAirport, &entryTimer);
			dequeueRunway(psTheAirport);
			psTheAirport->aRunwayStatus[runwaysTaken] = TAKEOFF_RUNWAY;
			runwaysTaken++;
			psStats->totalTakeoffWait += psTheAirport->timer - sTemp.entryTimer + 1;
		}
		else if ((!(emptyAirportInFlightPQ(psTheAirport))))
		{
			sTemp = peekInFlightPQ(psTheAirport, &fuel, &entryTimer);
			dequeueInFlightPQ(psTheAirport, &fuel);
			psTheAirport->aRunwayStatus[runwaysTaken] = LANDING_RUNWAY;
			runwaysTaken++;
			psStats->totalLandingWait += psTheAirport->timer - sTemp.entryTimer + 1;
			psStats->totalTimeRemaining += fuel;
		}
		else
		{
			bEmpty = true;
		}
	}
}
/**************************************************************************
 Function:			decrementFuel

 Description:		Decreases the fuel of all planes in the air by 1

 Parameters:		psTheAirport - the address of the airport

 Returned:	 		None
 *************************************************************************/
void decrementFuel (AirportPtr psTheAirport)
{
	if (NULL == psTheAirport)
	{
		processError("decrementFuel", ERROR_INVALID_AIRPORT);
	}
	const int PRIORITY_CHANGE = -1;

	if (!(emptyAirportInFlightPQ(psTheAirport)))
	{
		pqueueChangePriority(&(psTheAirport->sInFlightPQueue), PRIORITY_CHANGE);
	}
}
/**************************************************************************
 Function:			setNextTurn

 Description:		Sets key values back to initialized state

 Parameters:		psTheAirport - the address of the airport
 	 	 	 	 	 	 	 	psStats			- a pointer to the AirportStats struct that stores
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	key data about the airport

 Returned:	 		None
 *************************************************************************/
void setNextTurn (AirportPtr psTheAirport, AirportStatsPtr psStats)
{
	if (NULL == psTheAirport)
	{
		processError("setNextTurn", ERROR_INVALID_AIRPORT);
	}
	if (NULL == psStats)
	{
		processError("setNextTurn", ERROR_NULL_PTR_AIRPORT_STATS);
	}

	psTheAirport->crashCount = 0;
	psStats->totalNumTakeoff += psStats->currentNumTakeoff;
	psStats->totalNumLanding += psStats->currentNumLanding;
	psStats->currentNumTakeoff = 0;
	psStats->currentNumLanding = 0;

	for (int i = 0; i < MAX_PLANES; i++)
	{
		psTheAirport->aRunwayStatus[i] = EMPTY_RUNWAY;
	}
}
