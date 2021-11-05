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
void airportReadLine (AirportPtr psTheAirport, FILE *fPtr)
{
	const int MAX_NUM_PLANES = 3;
	int numTakeoffPlanes, numLandingPlanes;
	int aFuel[MAX_NUM_PLANES];

	fscanf(fPtr,"%d", &numTakeoffPlanes);
	fscanf(fPtr,"%d", &numLandingPlanes);

	for (int i = 0; i < numTakeoffPlanes; i++)
	{
		enqueueRunway(psTheAirport);
	}

	for (int i = 0; i < numLandingPlanes; i++)
	{
		fscanf(fPtr,"%d", &aFuel[i]);
		enqueueInFlightPQ(psTheAirport, aFuel[i]);
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
		processError("enqueueRunway", ERROR_NO_AIRPORT_TERMINATE);
	}

	Airplane sAirplane;
	queueEnqueue(&(psTheAirport->sRunwayQueue), &sAirplane, sizeof(Airplane));
}
/**************************************************************************
 Function:			enqueueInFlightPQ

 Description:		enqueues the in flight priority queue

 Parameters:		psTheAiport - the address of the airport
 	 	 	 	 	 	 	 	fuel 				- the fuel of the queued airplane, used as the
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	priority in the in f;light priority queue

 Returned:	 		None
 *************************************************************************/
void enqueueInFlightPQ (AirportPtr psTheAirport, int fuel)
{
	if (NULL == psTheAirport)
	{
		processError("enqueueRunway", ERROR_NO_AIRPORT_TERMINATE);
	}

	Airplane sAirplane;
	pqueueEnqueue(&(psTheAirport->sInFlightPQueue), &sAirplane, sizeof(Airplane),
								fuel);
}

