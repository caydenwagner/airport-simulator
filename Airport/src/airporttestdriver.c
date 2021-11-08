/**************************************************************************
 File name:	 airporttestdriver.c
 Author:		 Cayden Wagner
 Date:			 10/27/21
 Class:			 CS300
 Assignment: airport
 Purpose:
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
	int pBuf;
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

	airportCreate(&sTheAirport);

	printf("Line 1:\n");
	airportReadLine(&sTheAirport, fPtr, &sStats);
	assert(FIRST_READ_SIZE == airportRunwaySize(&sTheAirport),
				 "Success, size is 3", "Failure");
	assert(FIRST_READ_SIZE == airportInFlightSize(&sTheAirport),
				 "Success, size is 3", "Failure");
	peekInFlightPQ(&sTheAirport, &pBuf);
	printf("The highest priority plane is: %d\n\n", pBuf);

	printf("Line 2:\n");
	airportReadLine(&sTheAirport, fPtr, &sStats);
	assert(SECOND_READ_SIZE == airportRunwaySize(&sTheAirport),
				 "Success, size is 6", "Failure");
	assert(SECOND_READ_SIZE == airportInFlightSize(&sTheAirport),
				 "Success, size is 6", "Failure");
	peekInFlightPQ(&sTheAirport, &pBuf);
	printf("The highest priority plane is: %d\n\n", pBuf);

	printf("Line 3:\n");
	airportReadLine(&sTheAirport, fPtr, &sStats);
	assert(THIRD_READ_SIZE == airportRunwaySize(&sTheAirport),
				 "Success, size is 6", "Failure");
	assert(THIRD_READ_SIZE == airportInFlightSize(&sTheAirport),
				 "Success, size is 6", "Failure");
	peekInFlightPQ(&sTheAirport, &pBuf);
	printf("The highest priority plane is: %d\n\n", pBuf);

	pBuf = 0;
	dequeueInFlightPQ(&sTheAirport, &pBuf);
	printf("Dequeue, The priority was: %d\n\n", pBuf);
	peekInFlightPQ(&sTheAirport, &pBuf);
	printf("The highest priority plane is: %d\n\n", pBuf);
	assert(THIRD_READ_SIZE  - 1 == airportInFlightSize(&sTheAirport),
				 "Success, size is 5", "Failure");

	airportTerminate(&sTheAirport);

	fclose(fPtr);

	printf("\nSuccess\n\n");
	return 0;
}
