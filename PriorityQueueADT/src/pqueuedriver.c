/**************************************************************************
 File name:	 pqueuedriver.c
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
#include "../include/pqueue.h"
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
	PriorityQueue sTheQueue;
	int data = 0;
	int pBuf;
	int pPriBuf;

	pqueueLoadErrorMessages();

	pqueueCreate(&sTheQueue);

	assert(0 == pqueueSize(&sTheQueue), "The list is empty",
																		"The list is not empty");

	assert(pqueueIsEmpty(&sTheQueue), "The list is empty",
																	"The list is not empty");
	for (int i = 0; i < 10; i++)
	{
		pqueueEnqueue(&sTheQueue, &data, sizeof(int), i);
		data++;
	}
	for (int i = 10; i > -4; i--)
	{
		pqueueEnqueue(&sTheQueue, &data, sizeof(int), i);
		data++;
	}

	lstFirst(&sTheQueue.sTheList);
	for (int i = 0; i < pqueueSize(&sTheQueue); i++)
	{
		pqueuePeek(&sTheQueue, &pBuf, sizeof(int), &pPriBuf);
		lstNext(&sTheQueue.sTheList);
		printf("%d. Data: %d , Priority: %d\n\n", i, pBuf, pPriBuf);
	}

	pqueueDequeue(&sTheQueue, &pBuf, sizeof(int), &pPriBuf);

	lstFirst(&sTheQueue.sTheList);
	for (int i = 0; i < pqueueSize(&sTheQueue); i++)
	{
		pqueuePeek(&sTheQueue, &pBuf, sizeof(int), &pPriBuf);
		lstNext(&sTheQueue.sTheList);
		printf("%d. Data: %d , Priority: %d\n\n", i, pBuf, pPriBuf);
	}

	pqueueChangePriority(&sTheQueue, 10);

	lstFirst(&sTheQueue.sTheList);

	for (int i = 0; i < pqueueSize(&sTheQueue); i++)
	{
		pqueuePeek(&sTheQueue, &pBuf, sizeof(int), &pPriBuf);
		lstNext(&sTheQueue.sTheList);
		printf("%d. Data: %d , Priority: %d\n\n", i, pBuf, pPriBuf);
	}

	printf("Hello World! Yes");
	pqueueTerminate(&sTheQueue);

	return 0;
}
