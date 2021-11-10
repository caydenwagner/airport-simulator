/**************************************************************************
 File name:	 airporttestdriver.c
 Author:		 Cayden Wagner
 Date:			 10/27/21
 Class:			 CS300
 Assignment: airport
 Purpose:		 To test airport functions and print several success messages to
 	 	 	 	 	 	 easily spot errors
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../include/airport.h"
#include <limits.h>
#include <float.h>
/**************************************************************************
 Function: 	 	success

 Description: print a success message

 Parameters:	szStr - the message to print

 Returned:	 	none
 *************************************************************************/
static void success (char * szStr)
{
	printf ("SUCCESS: %s\n", szStr);
}
/**************************************************************************
 Function: 	 	failure

 Description: print a failure message

 Parameters:	szStr - the message to print

 Returned:	 	none
 *************************************************************************/
static void failure (char * szStr)
{
	printf ("FAILURE: %s\n", szStr);
	exit (EXIT_FAILURE);
}
/****************************************************************************
 Function: 	 	assert

 Description: if the expression is true, assert success; otherwise, assert
 	 	 	 	 	 	 	failure

 Parameters:	bExpression - The validity of the expression passed in, either
  													true or false
  						pTrue				- The message that is printed if the statement is
  													true
  						pFalse			- The message that is printed if the statement is
  													false
 Returned:	 	none
 ****************************************************************************/
static void assert (bool bExpression, char *pTrue, char *pFalse)
{
	if (bExpression)
	{
		success (pTrue);
	}
	else
	{
		failure (pFalse);
	}
}
/****************************************************************************
 Function:			main

 Description:		tests functionality of the queue

 Returned:			EXIT SUCCESS
 ****************************************************************************/
int main (int argc, char **argv)
{
	const int FIRST_READ_SIZE = 3;
	const int SECOND_READ_SIZE = 6;
	const int THIRD_READ_SIZE = 6;
	const int HIGHEST_PRIORITY_PLANE = 0;
	int buf, timer;
	Airport sTheAirport;
	AirportStats sStats;
	FILE *fPtr;

	airportLoadErrorMessages ();
	if (!(argc > 0))
	{
		printf("Error, expected data file in command line\n\n");
		return EXIT_FAILURE;
	}
	fPtr = fopen(argv[1], "r");

	if (fPtr == NULL)
	{
		printf("Error! File not found\n\n");
		EXIT_FAILURE;
	}

	airportCreate(&sTheAirport, &sStats);

//  airportCreate (NULL, &sStats);
//  airportCreate (&sTheAirport, NULL);

//	airportTerminate (NULL);

//	enqueueRunway (NULL);

//	enqueueInFlightPQ (NULL, buf);

//	dequeueRunway (NULL);
//	dequeueRunway (&sTheAirport);

//	dequeueInFlightPQ (NULL, &buf);
//	dequeueInFlightPQ (&sTheAirport, &buf);
//	airportReadLine(&sTheAirport, fPtr, &sStats);
//	dequeueInFlightPQ (&sTheAirport, NULL);

//	peekInFlightPQ (NULL, &buf, &timer);
//	peekInFlightPQ (&sTheAirport, NULL, &timer);
//	peekInFlightPQ (&sTheAirport, &buf, NULL);
//	peekInFlightPQ (&sTheAirport, &buf, &timer);

//	peekRunway(NULL, &timer);
//	peekRunway(&sTheAirport, NULL);
//	peekRunway(&sTheAirport, &timer);

//  airportPrintRow (NULL, NULL);
//	airportPrintRow (&sTheAirport, NULL);

//	airportRunwaySize (NULL);

//	airportInFlightSize (NULL);

//	emptyAirportRunway (NULL);

//	emptyAirportInFlightPQ (NULL);

//	setNextTurn (NULL, &sStats);
//	setNextTurn (&sTheAirport, NULL);

//  updateAirport (NULL, &sStats);
//	updateAirport (&sTheAirport, NULL);

//	decrementFuel (NULL);

//	airportReadLine (NULL, fPtr, &sStats);
//	airportReadLine (&sTheAirport, NULL, &sStats);
//	airportReadLine (&sTheAirport, fPtr, NULL);

//	airportIncrementTimer (AirportPtr);

	printf("Read Line 1:\n");
	airportReadLine(&sTheAirport, fPtr, &sStats);
	assert(FIRST_READ_SIZE == airportRunwaySize(&sTheAirport),
				 "runway size is 3", "Failure");
	assert(FIRST_READ_SIZE == airportInFlightSize(&sTheAirport),
				 "inFlight size is 3", "Failure");
	peekInFlightPQ(&sTheAirport, &buf, &timer);
	printf("The highest priority plane is: %d\n\n", buf);
	printf("Fuel is decremented\n");
	decrementFuel(&sTheAirport);
	peekInFlightPQ(&sTheAirport, &buf, &timer);
	assert(HIGHEST_PRIORITY_PLANE == buf,
				 "Highest Priority Plane is now 0\n", "Failure\n\n");

	printf("Fuel is decremented\n");
	decrementFuel(&sTheAirport);
	peekInFlightPQ(&sTheAirport, &buf, &timer);
	assert(HIGHEST_PRIORITY_PLANE - 1 == buf,
					"Highest Priority Plane is now -1\n", "Failure\n\n");

	printf("Read Line 2:\n");
	airportReadLine(&sTheAirport, fPtr, &sStats);
	assert(SECOND_READ_SIZE == airportRunwaySize(&sTheAirport),
				 "runway size is 6", "Failure");
	assert(SECOND_READ_SIZE == airportInFlightSize(&sTheAirport),
				 "inFlight size is 6", "Failure");
	peekInFlightPQ(&sTheAirport, &buf, &timer);
	printf("The highest priority plane is: %d\n\n", buf);

	printf("Read Line 3:\n");
	airportReadLine(&sTheAirport, fPtr, &sStats);
	assert(THIRD_READ_SIZE == airportRunwaySize(&sTheAirport),
					 "runway size is 6", "Failure");
		assert(THIRD_READ_SIZE == airportInFlightSize(&sTheAirport),
					 "inFlight size is 6", "Failure");
	peekInFlightPQ(&sTheAirport, &buf, &timer);
	printf("\nThe highest priority plane is: %d\n", buf);

	buf = 0;
	dequeueInFlightPQ(&sTheAirport, &buf);
	printf("Dequeue inFlight, The priority was: %d\n", buf);
	peekInFlightPQ(&sTheAirport, &buf, &timer);
	printf("The highest priority plane is: %d\n", buf);
	assert(THIRD_READ_SIZE  - 1 == airportInFlightSize(&sTheAirport),
				 "size of inFlight is 5\n", "Failure");


	peekInFlightPQ(&sTheAirport, &buf, &timer);
	printf("The highest priority plane is: %d\n", buf);
	dequeueInFlightPQ(&sTheAirport, &buf);
	printf("Dequeue inFlight, The priority was: %d\n", buf);
	peekInFlightPQ(&sTheAirport, &buf, &timer);
	printf("The highest priority plane is: %d\n", buf);
	assert(THIRD_READ_SIZE  - 2 == airportInFlightSize(&sTheAirport),
				 "size of inFlight is 4", "Failure");

	buf = airportRunwaySize(&sTheAirport);
	dequeueRunway(&sTheAirport);
	printf("\nDequeue runway, The size was: %d\n", buf);
	assert(buf - 1 == airportRunwaySize(&sTheAirport),
				"The new size is correct", "failure");
	buf = airportRunwaySize(&sTheAirport);
	printf("The new size is: %d\n", buf);

	buf = airportRunwaySize(&sTheAirport);
	dequeueRunway(&sTheAirport);
	printf("\nDequeue runway, The size was: %d\n", buf);
	assert(buf - 1 == airportRunwaySize(&sTheAirport),
				"The new size is correct", "failure");
	buf = airportRunwaySize(&sTheAirport);
	printf("The new size is: %d\n\n", buf);

	airportTerminate(&sTheAirport);

	fclose(fPtr);

	printf("\nSuccess\n\n");
	return 0;
}
