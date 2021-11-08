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

const char EMPTY_RUNWAY = 'E';
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

 Parameters:		psTheAiport - the address of the airport

 Returned:	 		None
 *************************************************************************/
void airportCreate (AirportPtr psTheAirport)
{
	if (NULL == psTheAirport)
	{
		processError("airportCreate", ERROR_NO_AIRPORT_CREATE);
	}
	queueCreate(&(psTheAirport->sRunwayQueue));
	pqueueCreate(&(psTheAirport->sInFlightPQueue));
	psTheAirport->timer = 1;
	for (int i = 0; i < MAX_RUNWAYS; i++)
	{
		psTheAirport->aRunwayStatus[i] = EMPTY_RUNWAY;
		psTheAirport->crashCount = 0;
	}
}
/**************************************************************************
 Function:			airportTerminate

 Description:		terminates the airport by terminating the runway queue and
 	 	 	 	 	 	 	 	the in flight priority queue

 Parameters:		psTheAiport - the address of the airport

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

 Parameters:		psTheAiport - the address of the airport
 	 	 	 	 	 	 	 	fPtr 				- a pointer to the read file

 Returned:	 		None
 *************************************************************************/
void airportReadLine (AirportPtr psTheAirport, FILE *fPtr,
											AirportStatsPtr sStats)
{
	const int MAX_NUM_PLANES = 3;
	const int EMPTY = -1;
	int numTakeoffPlanes = 0, numLandingPlanes = 0;
	int aFuel[MAX_NUM_PLANES];

	for (int i = 0; i < MAX_NUM_PLANES; i++)
	{
		sStats->aFuelRemaining[i] = EMPTY;
	}

	fscanf(fPtr,"%d", &numTakeoffPlanes);
	fscanf(fPtr,"%d", &numLandingPlanes);

	sStats->Landing = numLandingPlanes;
	sStats->Takeoff = numTakeoffPlanes;

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
		sStats->aFuelRemaining[i] = aFuel[i];
	}
}
/**************************************************************************
 Function:			enqueueRunway

 Description:		enqueues an airplane into the runway queue

 Parameters:		psTheAiport - the address of the airport

 Returned:	 		None
 *************************************************************************/
void enqueueRunway(AirportPtr psTheAirport)
{
	if (NULL == psTheAirport)
	{
		processError("enqueueRunway", ERROR_INVALID_AIRPORT);
	}

	Airplane sAirplane;
	queueEnqueue(&(psTheAirport->sRunwayQueue), &sAirplane, sizeof(Airplane));
}
/**************************************************************************
 Function:			enqueueInFlightPQ

 Description:		enqueues the in flight priority queue

 Parameters:		psTheAiport - the address of the airport
 	 	 	 	 	 	 	 	fuel 				- the fuel of the queued airplane, used as the
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
	sAirplane.fuel = fuel;
	pqueueEnqueue(&(psTheAirport->sInFlightPQueue), &sAirplane, sizeof(Airplane),
								sAirplane.fuel);
}
/**************************************************************************
 Function:			airportRunwaySize

 Description:		returns the size of the airport runway queue

 Parameters:		psTheAiport - the address of the airport

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

 Parameters:		psTheAiport - the address of the airport

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

 Parameters:		psTheAiport - the address of the airport

 Returned:	 		the priority of the first element in the in flight priority
  							queue
 *************************************************************************/
int peekInFlightPQ (AirportPtr psTheAirport, int* pBuf)
{
	if (NULL == psTheAirport)
	{
		processError("peekInFlightPQ", ERROR_INVALID_AIRPORT);
	}
	if (NULL == pBuf)
	{
		processError("peekInFlightPQ", ERROR_NULL_PTR_AIRPLANE);
	}
	if (emptyAirportInFlightPQ(psTheAirport))
	{
		processError("peekInFlightPQ", ERROR_EMPTY_IN_FLIGHT_PQ);
	}
	Airplane sAirplane;
	pqueuePeek(&(psTheAirport->sInFlightPQueue), &sAirplane, sizeof(Airplane),
						 pBuf);

	return *pBuf;
}
/**************************************************************************
 Function:			emptyAirportRunway

 Description:		checks if the runway is empty or not

 Parameters:		psTheAiport - the address of the airport

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

 Parameters:		psTheAiport - the address of the airport

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

 Parameters:		psTheAiport - the address of the airport

 Returned:	 		None
 *************************************************************************/
void dequeueRunway (AirportPtr psTheAirport)
{
	if (NULL == psTheAirport)
	{
		processError("dequeueRunway", ERROR_INVALID_AIRPORT);
	}
	if (emptyAirportInFlightPQ(psTheAirport))
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

 Parameters:		psTheAiport - the address of the airport

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
	Airplane sAirplane;

	pqueueDequeue(&(psTheAirport->sInFlightPQueue), &sAirplane, sizeof(Airplane),
								pBuf);
}
/**************************************************************************
 Function:

 Description:

 Parameters:		psTheAiport - the address of the airport

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
 Function:

 Description:

 Parameters:		psTheAiport - the address of the airport

 Returned:	 		None
 *************************************************************************/
void airportPrintRow (AirportPtr psTheAirport, AirportStatsPtr sStats)
{
	if (NULL == psTheAirport)
	{
		processError("AirportPrintTimer", ERROR_INVALID_AIRPORT);
	}
	const int EMPTY = -1;
	const char EMPTY_CHAR = '-';
	const int COL_1_SPACES = 4;
	const int COL_2_SPACES = 7;
	const int COL_3_SPACES = 9;
	const int COL_4_SPACES = 5;

	fprintf(stdout, "%*d", COL_1_SPACES, psTheAirport->timer);
	printf(" | ");
	printf("%*d", COL_2_SPACES, sStats->Takeoff);
	printf("%*d", COL_3_SPACES, sStats->Landing);
	printf(" |");

	for (int i = 0; i < MAX_PLANES; i++)
	{
		if (EMPTY == sStats->aFuelRemaining[i])
		{
			printf("%*c", COL_4_SPACES, EMPTY_CHAR);
		}
		else
		{
			printf("%*d", COL_4_SPACES, sStats->aFuelRemaining[i]);
		}
	}

	printf(" | ");

	printf("\n");


}
