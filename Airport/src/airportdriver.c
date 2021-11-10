/**************************************************************************
 File name:	 airportDriver.c
 Author:		 Cayden Wagner
 Date:			 10/28/21
 Class:			 CS300
 Assignment: Airport
 Purpose:		 Design a program that can service airplanes that need to launch
  					 and takeoff using priorityQueueADT and queueADT
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../include/airport.h"
#include <limits.h>
#include <float.h>

const char BUFFER = ' ';
const char DIVIDER = '-';
char *paRow1[] = {"Planes Added", "Runways", "Queue", "Lengths"};
char *paRow2[] = {"Time", "Takeoff  Landing (Fuel Remaining)", "1   2   3  Crash",
								"Takeoff", "Landing"};


void printHeader ();
void printChar(char, int);
void printDivider ();
void printCol (int, char[], int);
void printRow1 ();
void printRow2 ();
void calculateStats (AirportStatsPtr);
/****************************************************************************
 Function:		main

 Description:	Drives the Airplane simulator

 Parameters:  argc - the count of command line args
 	 	 	 	 	 	 	argv - the command line args

 Returned:    Exit status
 ****************************************************************************/
int main (int argc, char **argv)
{
	Airport sTheAirport;
	AirportStats sStats;
	FILE *fPtr;

	airportLoadErrorMessages ();
	if (!(argc > 0))
	{
		printf("Error, expected data file in command line\n\n");
		return EXIT_FAILURE;
	}
	else {
		fPtr = fopen(argv[1], "r");

		if (NULL == fPtr)
		{
			printf("Error! File not found\n\n");
			return EXIT_FAILURE;
		}
	}

	airportCreate(&sTheAirport, &sStats);
	printHeader();

	do
	{
		if (!feof(fPtr))
		{
			airportReadLine(&sTheAirport, fPtr, &sStats);
		}
		decrementFuel(&sTheAirport);
		updateAirport(&sTheAirport, &sStats);
		airportPrintRow(&sTheAirport, &sStats);
		airportIncrementTimer(&sTheAirport);
		setNextTurn(&sTheAirport, &sStats);
	}	while ((!(emptyAirportRunway(&sTheAirport)) ||
			 (!(emptyAirportInFlightPQ(&sTheAirport)))) || (!feof(fPtr)));

	fclose(fPtr);

	calculateStats (&sStats);
	airportTerminate(&sTheAirport);

	return 0;
}
/****************************************************************************
 Function:			printCol

 Description:		prints a header surrounded by specified buffer space

 Parameters:		leftPadding - the amount of padding on the left of the header
 	 	 	 	 	 	 	 	header 			- the header of the column
 	 	 	 	 	 	 	 	rightPadding - the amount of padding on the right of the header

 Returned:			none
 ****************************************************************************/
void printCol (int leftPadding, char header[], int rightPadding)
{
	printf("%*s", leftPadding, header);

	printChar(BUFFER, rightPadding);
}
/****************************************************************************
 Function:		printHeader

 Description:	calls printRow functions and printDivider functions to print the
  						header in the correct format

 Parameters:  None

 Returned:		None
 ****************************************************************************/
void printHeader ()
{
	printRow1 ();
	printRow2 ();
	printDivider ();
}
/****************************************************************************
 Function:		printChar

 Description: prints a specified char a certain number of times

 Parameters:	character - the char that is printed
 	 	 	 	 	 	 	num 			- how many times the char is printed

 Returned:		none
 ****************************************************************************/
void printChar(char character, int num)
{
	for (int i = 0; i < num; i++)
	{
		printf("%c", character);
	}
}
/****************************************************************************
 Function:		printDivider

 Description:	prints a divided of char '-' in the correct format

 Parameters:  None

 Returned:		None
 ****************************************************************************/
void printDivider ()
{
	const int THREE_SPACES = 3;

	printChar(DIVIDER, strlen(paRow2[0]));
	printf(" | ");
	printChar(DIVIDER, strlen("Takeoff"));
	printf("  ");
	printChar(DIVIDER, strlen("Landing (Fuel Remaining)"));
	printf(" | ");
	for ( int i = 0; i < THREE_SPACES; i ++)
	{
		printChar(DIVIDER, THREE_SPACES);
		printf(" ");
	}
	printChar(DIVIDER, strlen("Crash"));
	printf(" | ");
	printChar(DIVIDER, strlen("Takeoff"));
	printf("  ");
	printChar(DIVIDER, strlen("Landing"));

	printf("\n");
}
/****************************************************************************
 Function:		printRow1

 Description:	prints the first for in the correct format

 Parameters: 	Calls printCol functions to print a row in the correct format

 Returned:		None
 ****************************************************************************/
void printRow1 ()
{
	const int COL_1_WIDTH = 5;
	const int COL_2_WIDTH = 23;
	const int COL_2_BUFFER = 12;
	const int COL_3_WIDTH = 13;
	const int COL_3_BUFFER = 6;
	const int COL_4_WIDTH = 8;
	const int COL_4_BUFFER = 1;
	const int COL_5_WIDTH = 8;
	const int COL_5_BUFFER = 1;

	printCol(COL_1_WIDTH, "", 0);
	printf("|");
	printCol(COL_2_WIDTH, paRow1[0], COL_2_BUFFER);
	printf("|");
	printCol(COL_3_WIDTH, paRow1[1], COL_3_BUFFER);
	printf("|");
	printCol(COL_4_WIDTH, paRow1[2], COL_4_BUFFER);
	printCol(COL_5_WIDTH, paRow1[3], COL_5_BUFFER);
	printf("\n");
}
/****************************************************************************
 Function:		printRow2

 Description:	prints the first for in the correct format

 Parameters: 	Calls printCol functions to print a row in the correct format

 Returned:		None
 ****************************************************************************/
void printRow2 ()
{
	const int COL_1_WIDTH = 4;
	const int COL_1_BUFFER = 1;
	const int COL_2_WIDTH = 34;
	const int COL_2_BUFFER = 1;
	const int COL_3_WIDTH = 18;
	const int COL_3_BUFFER = 1;
	const int COL_4_WIDTH = 8;
	const int COL_4_BUFFER = 1;


	printCol(COL_1_WIDTH, paRow2[0], COL_1_BUFFER);
	printf("|");
	printCol(COL_2_WIDTH, paRow2[1], COL_2_BUFFER);
	printf("|");
	printCol(COL_3_WIDTH, paRow2[2], COL_3_BUFFER);
	printf("|");
	printCol(COL_4_WIDTH, paRow2[3], COL_4_BUFFER);
	printCol(COL_4_WIDTH, paRow2[4], 0);

	printf("\n");
}
/****************************************************************************
 Function:		calculateStats

 Description:	Runs calculations in the AirportStats and prints key information

 Parameters:	psStats - a pointer to a struct containing key stats about the
  											airport

 Returned:		None
 ****************************************************************************/
void calculateStats(AirportStatsPtr psStats)
{
	double avgLandingWait, avgTakeoffWait;
	double avgFuelRemaining;
	avgLandingWait = psStats->totalLandingWait /(double)psStats->totalNumLanding;
	avgTakeoffWait = psStats->totalTakeoffWait /(double)psStats->totalNumTakeoff;
	avgFuelRemaining = psStats->totalTimeRemaining
															 /(double)psStats->totalNumLanding;

	printf("\nAverage takeoff waiting time: %g\n", avgTakeoffWait);

	printf("Average landing waiting time: %g\n", avgLandingWait);

	printf("Average flying time remaining on landing: %g\n", avgFuelRemaining);

	printf("Number of planes landing with zero fuel: %d\n",
					psStats->numPlanesWithNoFuel);

	printf("Number of crashes: %d\n\n", psStats->numCrashes);
}
