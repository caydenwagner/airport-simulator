/**************************************************************************
 File name:
 Author:		 Cayden Wagner
 Date:			 10/28/21
 Class:			 CS300
 Assignment:
 Purpose:
 *************************************************************************/

void printHeader ();

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../include/airport.h"
#include <limits.h>
#include <float.h>
/****************************************************************************
 Function:

 Description:

 Returned:
 ****************************************************************************/
int main ()
{
	printHeader();

	return EXIT_SUCCESS;
}
/****************************************************************************
 Function:

 Description:

 Returned:
 ****************************************************************************/
void printHeader ()
{
	char *row1[] = {"Planes Added", "Runways", "Queue", "Lengths"};
	char *row2[] = {"Time", "Takeoff", "Landing (Fuel Remaining)", "1", "2", "3",
								"Crash", "Takeoff", "Landing"};

	for (int i = 1; i < 81; i++)
	{
		printf("%d", i % 10);
	}
	printf("\n");
	printf("%*c %*s %*c %*s %*c %*s %*s\n", 6, '|', 22, row1[0], 12, '|', 12,
				 row1[1], 6, '|', 7, row1[2], -9, row1[3]);
	printf("%s | %s %*s | %*s %*s %*s %*s | %s %*s", row2[0], row2[1], 25,
				 row2[2], 2, row2[3], 3, row2[4], 3, row2[5], 6, row2[6], row2[7], -9,
				 row2[8]);
}
