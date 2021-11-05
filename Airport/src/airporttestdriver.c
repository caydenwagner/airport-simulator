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
	Airport sTheAirport;
	FILE *fPtr;

	airportLoadErrorMessages ();
	fPtr = fopen(argv[1], "r");

	if (fPtr == NULL)
	{
		printf("Error! File not found\n\n");
		EXIT_FAILURE;
	}

	airportCreate(&sTheAirport);

	airportTerminate(&sTheAirport);

	printf("\n\nSuccess");
	return 0;
}
