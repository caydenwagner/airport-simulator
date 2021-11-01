/**************************************************************************
 File name:
 Author:			 Cayden Wagner
 Date:				 10/28/21
 Class:			 	 CS300
 Assignment:
 *************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../include/airport.h"
#include "../../PriorityQueueADT/src/pqueue.c"
#include "../../QueueADT/src/queue.c"

char gszAirportErrors[NUMBER_OF_AIRPORT_ERRORS][MAX_ERROR_AIRPORT_CHARS];
/**************************************************************************
 Function:

 Description: 	Initializes the string of error messages. LOAD_ERRORS is a
 	 	 	 					macro defined in the header file.

 Parameters:		None

 Returned:	 		None
 *************************************************************************/
void airportLoadErrorMessages ()
{
	LOAD_AIRPORT_ERRORS
}
/**************************************************************************
 Function:

 Description:
 Parameters:		None

 Returned:	 		None
 *************************************************************************/
void airportCreate (AirportPtr psTheAirport)
{
	queueCreate(&(psTheAirport->sRunwayQueue));
	pqueueCreate(&(psTheAirport->sInFlightPQueue));
}
