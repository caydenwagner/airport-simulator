/**************************************************************************
 File name:
 Author:		 Cayden Wagner
 Date:			 10/28/21
 Class:			 CS300
 Assignment:
 Purpose:
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
char *ROW1[] = {"Planes Added", "Runways", "Queue", "Lengths"};
char *ROW2[] = {"Time", "Takeoff  Landing (Fuel Remaining)", "1   2   3  Crash",
								"Takeoff", "Landing"};


void printHeader ();
void printChar(char, int);
void printDivider ();
void printCol (int, char[], int);
void printRow1 ();
void printRow2 ();
/****************************************************************************
 Function:

 Description:

 Returned:
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

	fPtr = fopen(argv[1], "r");

	if (fPtr == NULL)
	{
		printf("Error! File not found\n\n");
		EXIT_FAILURE;
	}

	printHeader();
	airportCreate(&sTheAirport);

	while (!feof(fPtr))
	{
		airportReadLine(&sTheAirport, fPtr, &sStats);

		airportPrintRow(&sTheAirport, &sStats);

		airportIncrementTimer(&sTheAirport);
	}

	fclose(fPtr);
	airportTerminate(&sTheAirport);

	return 0;
}
/****************************************************************************
 Function:

 Description:

 Returned:
 ****************************************************************************/
void printCol (int leftBuf, char header[], int rightBuf)
{
	printf("%*s", leftBuf, header);

	printChar(BUFFER, rightBuf);
}
/****************************************************************************
 Function:

 Description:

 Returned:
 ****************************************************************************/
void printHeader ()
{
	printRow1 ();
	printRow2 ();
	printDivider ();
}
/****************************************************************************
 Function:

 Description:

 Returned:
 ****************************************************************************/
void printChar(char character, int num)
{
	for (int i = 0; i < num; i++)
	{
		printf("%c", character);
	}
}
/****************************************************************************
 Function:

 Description:

 Returned:
 ****************************************************************************/
void printDivider ()
{
	const int THREE_SPACES = 3;

	printChar(DIVIDER, strlen(ROW2[0]));
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
 Function:

 Description:

 Returned:
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
	printCol(COL_2_WIDTH, ROW1[0], COL_2_BUFFER);
	printf("|");
	printCol(COL_3_WIDTH, ROW1[1], COL_3_BUFFER);
	printf("|");
	printCol(COL_4_WIDTH, ROW1[2], COL_4_BUFFER);
	printCol(COL_5_WIDTH, ROW1[3], COL_5_BUFFER);
	printf("\n");
}
/****************************************************************************
 Function:

 Description:

 Returned:
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


	printCol(COL_1_WIDTH, ROW2[0], COL_1_BUFFER);
	printf("|");
	printCol(COL_2_WIDTH, ROW2[1], COL_2_BUFFER);
	printf("|");
	printCol(COL_3_WIDTH, ROW2[2], COL_3_BUFFER);
	printf("|");
	printCol(COL_4_WIDTH, ROW2[3], COL_4_BUFFER);
	printCol(COL_4_WIDTH, ROW2[4], 0);

	printf("\n");
}
