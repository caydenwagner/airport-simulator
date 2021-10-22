/**************************************************************************
 File name:	 pqueuedriver.c
 Author:		 Cayden Wagner
 Date:			 10/19/21
 Class:			 CS300
 Assignment: pqueueADT
 Purpose:		 To create a priority queue ADT backed by a linked list
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
 Function:			main

 Description:		test all the functionality of the priority queue

 Parameters:		none

 Returned:			none
 ****************************************************************************/
int main ()
{
	const int TEST_NUMBER = 10;
	PriorityQueue sTheQueue;
	int data = 0;
	int pBuf;
	int pPriBuf;

	pqueueLoadErrorMessages();
	lstLoadErrorMessages();

	pqueueCreate(&sTheQueue);

//	Purposefully Triggering every failure in each function
//	pqueueCreate(NULL);
//	pqueueSize(NULL);
//	pqueueIsEmpty(NULL);
//	pqueueEnqueue(NULL, &data, sizeof(int), 0);
//	pqueueEnqueue(&sTheQueue, NULL, sizeof(int), 0);
//	pqueueDequeue(NULL, &data, sizeof(int), 0);
//	pqueueDequeue(&sTheQueue, NULL, sizeof(int), 0);
//	pqueuePeek(NULL, &data, sizeof(int), 0);
//	pqueuePeek(&sTheQueue, NULL, sizeof(int), 0);
//	pqueueChangePriority(NULL, TEST_NUMBER);

	pqueueTerminate(&sTheQueue);
	pqueueCreate(&sTheQueue);

	assert(0 == pqueueSize(&sTheQueue), "The queue is has 0 elements",
																			"The queue contains elements");

	assert(pqueueIsEmpty(&sTheQueue), "The queue is empty",
																	"The queue is not empty");

	for (int i = 0; i < TEST_NUMBER; i++)
	{
		pqueueEnqueue(&sTheQueue, &data, sizeof(int), i);
		data++;
	}

	assert(TEST_NUMBER == pqueueSize(&sTheQueue), "The queue is the right size",
																							"The list is not the right size");

	for (int i = TEST_NUMBER; i > 0; i--)
	{
		pqueueEnqueue(&sTheQueue, &data, sizeof(int), i);
		data++;
	}

	assert(TEST_NUMBER * 2 == pqueueSize(&sTheQueue),
														"The queue is the right size",
														"The list is not the right size");

	for (int i = 0; i < TEST_NUMBER; i++)
	{
		pqueuePeek(&sTheQueue, &pBuf, sizeof(int), &pPriBuf);
		printf("%d. Data: %d , Priority: %d\n", i, pBuf, pPriBuf);
		printf("Queue Size: %d\n\n", pqueueSize(&sTheQueue));
		pqueueDequeue(&sTheQueue, &pBuf, sizeof(int), &pPriBuf);
	}

	pqueueChangePriority(&sTheQueue, TEST_NUMBER);

	for (int i = 0; i < TEST_NUMBER; i++)
	{
		pqueuePeek(&sTheQueue, &pBuf, sizeof(int), &pPriBuf);
		printf("%d. Data: %d , Priority: %d\n", i, pBuf, pPriBuf);
		printf("Queue Size: %d\n\n", pqueueSize(&sTheQueue));
		pqueueDequeue(&sTheQueue, &pBuf, sizeof(int), &pPriBuf);
	}

	assert(0 == pqueueSize(&sTheQueue), "The queue is has 0 elements",
																				"The queue contains elements");

	assert(pqueueIsEmpty(&sTheQueue), "The queue is empty",
																		"The queue is not empty");

	printf("Success");
	pqueueTerminate(&sTheQueue);

	return 0;
}
