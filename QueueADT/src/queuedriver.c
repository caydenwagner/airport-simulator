/**************************************************************************
 File name:	 queuedriver.c
 Author:		 Cayden Wagner
 Date:			 10/11/21
 Class:			 CS300
 Assignment: pqueueADT
 Purpose:
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../include/queue.h"
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
 Function:
 Description:
 Parameters:
 Returned:
 ****************************************************************************/
int main ()
{
	int num = 5, num2 = 10;
	int buf;
	Queue sTheQueue;

	queueCreate(&sTheQueue);

	assert(queueIsEmpty(&sTheQueue), "List is empty", "List is not empty");
	queueEnqueue(&sTheQueue, &num, sizeof(int));
	assert(queueSize(&sTheQueue) == 1, "Size is 1", "Size is not 1");

	queueEnqueue(&sTheQueue, &num2, sizeof(int));

	queuePeek(&sTheQueue, &buf, sizeof(int));
	assert(buf == num, "Data matches", "Data does not match");

	queueDequeue(&sTheQueue, &buf, sizeof(int));
	assert(buf == num, "Data matches", "Data does not match");

	queueDequeue(&sTheQueue, &buf, sizeof(int));
	assert(buf == num2, "Data matches", "Data does not match");

	queueTerminate(&sTheQueue);
	puts("Success!");

	return 0;
}
