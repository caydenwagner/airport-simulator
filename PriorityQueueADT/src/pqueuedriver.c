/****************************************************************************
 File name:  	pqdriver2.c
 Author:     	chadd williams
 Date:       	Oct 17, 2019
 Class:			 	CS 300
 Assignment:	Priority Queue
 Purpose:			Extended PQ functionality
 ****************************************************************************/

#include "../include/pqueue.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/*
 * In VirtualBox on a MacBookPro i7
 *
 * With Valgrind this takes:  2 m 10 seconds
 *  time valgrind -v --leak-check=yes --track-origins=yes --leak-check=full
 *     --show-leak-kinds=all bin/pqdriver2
 *
 * Without Valgrind this takes: 1.7 seconds
 *  time bin/pqdriver2
 */

/****************************************************************************
 Function: 	 	success

 Description: print a success message

 Parameters:	szStr - the message to print

 Returned:	 	none
 ****************************************************************************/
static void success (char * szStr)
{
	printf ("SUCCESS: %s\n", szStr);
}

/****************************************************************************
 Function: 	 	failure

 Description: print a failure message

 Parameters:	szStr - the message to print

 Returned:	 	none
 ****************************************************************************/
static void failure (char * szStr)
{
	printf ("FAILURE: %s\n", szStr);
}

/****************************************************************************
 Function: 	 	assert

 Description: if the expression is true, assert success; otherwise, assert
 	 	 	 	 	 	 	failure

 Parameters:	szStr - the message to print

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
 Function: 	 	main

 Description: test all the functionality of the list

 Parameters:	none
 Returned:	 	none
 ****************************************************************************/
int main ()
{
	PriorityQueue sThePQ;
	int dataValue, priorityValue;
	int i, j, throwaway;
	const int SCALE_FAST = 2;

	bool bIsCorrect;
	const int PRIORITY_MAX = 100;
	const int VALUE_MAX = 100;

	const int DATA_VALUE = 100;

	puts ("Program Start\n");

	pqueueLoadErrorMessages();

	puts ("SUCCESS TESTS:\n");

	pqueueCreate (&sThePQ);
	success ("PQ Create");

	priorityValue = VALUE_MAX * PRIORITY_MAX ;

	for (i = 1; i <= VALUE_MAX; ++i)
	{
		for (j = PRIORITY_MAX ; j >= 1; --j)
		{
			priorityValue = j;
			dataValue = i;
			pqueueEnqueue (&sThePQ, &dataValue, sizeof (int), priorityValue);
			priorityValue --;
		}
	}
	assert (VALUE_MAX * PRIORITY_MAX == pqueueSize (&sThePQ),
			"pqueueSize is VALUE_MAX * PRIORITY_MAX",
			"pqueueSize is not VALUE_MAX * PRIORITY_MAX");


	pqueuePeek(&sThePQ, &dataValue, sizeof (int), &priorityValue);

	assert( 1== dataValue && 1 == priorityValue,
			"Peek found (1,1)", "Peek did not find (1,1)");

	bIsCorrect = true;

	for (i = 1; i <= VALUE_MAX; ++i)
	{
		for (j = 1; j <= PRIORITY_MAX; ++j)
		{
			pqueueDequeue (&sThePQ, &dataValue, sizeof (int), &priorityValue);
			if (dataValue != j || priorityValue != i)
			{
				bIsCorrect = false;
			}
		}
	}

	assert (bIsCorrect, "Dequeue VALUE_MAX * PRIORITY_MAX Is Correct",
			"Dequeue VALUE_MAX * PRIORITY_MAX Is NOT Correct");

	priorityValue = VALUE_MAX * PRIORITY_MAX ;

	for (i = 1; i <= VALUE_MAX; ++i)
	{
		for (j = PRIORITY_MAX ; j >= 1; --j)
		{
			priorityValue = j;
			dataValue = i;
			pqueueEnqueue (&sThePQ, &dataValue, sizeof (int), priorityValue--);
		}
	}

	dataValue = DATA_VALUE;

	for (i = 0; i < 1000; ++i)
	{
		if (i < 250)
		{
			pqueueDequeue (&sThePQ, &throwaway, sizeof (int), &priorityValue);
		}
		else
		{
			++dataValue;
			pqueueEnqueue (&sThePQ, &dataValue, sizeof (int), 1000 - dataValue);
		}
	}

	assert (pqueueSize (&sThePQ) == 10500, "pqueueSize is 10500",
																		   "pqueueSize is not 10500");

	pqueueDequeue (&sThePQ, &dataValue, sizeof (int), &priorityValue);
	assert (3 == priorityValue && 51 == dataValue, "Front is (51, 3)",
																		           "Front is not (51, 3)");

	dataValue = DATA_VALUE;
	pqueueEnqueue (&sThePQ, &dataValue, sizeof (int), PRIORITY_MAX * VALUE_MAX);

	while (pqueueSize (&sThePQ) > 1)
	{
		pqueueDequeue (&sThePQ, &dataValue, sizeof (int), &priorityValue);
	}


	pqueuePeek(&sThePQ, &dataValue, sizeof (int), &priorityValue);

	assert (PRIORITY_MAX * VALUE_MAX == priorityValue && DATA_VALUE == dataValue,
			"Peek is (100, PRIORITY_MAX * VALUE_MAX)",
			"Peek is not (100, PRIORITY_MAX * VALUE_MAX)");


	pqueueChangePriority(&sThePQ, PRIORITY_MAX);

	pqueueDequeue (&sThePQ, &dataValue, sizeof (int), &priorityValue);

	assert (PRIORITY_MAX * VALUE_MAX + PRIORITY_MAX == priorityValue
			&& DATA_VALUE == dataValue,
			"Changed Priority is (100, PRIORITY_MAX * VALUE_MAX + PRIORITY_MAX)",
			"Changed Priority is not (100, PRIORITY_MAX * VALUE_MAX + PRIORITY_MAX)");

	assert (pqueueSize (&sThePQ) == 0, "pqueueSize is 0",
																		   "pqueueSize is not 0");

	pqueueTerminate (&sThePQ);
	success ("PQ Terminate");

	pqueueCreate(&sThePQ);

	for (i = 1; i <= VALUE_MAX / SCALE_FAST; ++i)
	{
		for (j = PRIORITY_MAX /SCALE_FAST ; j >= 1; --j)
		{
			priorityValue = j;
			dataValue = i;
			pqueueEnqueue (&sThePQ, &dataValue, sizeof (int), priorityValue);
		}
	}

	pqueueChangePriority(&sThePQ, 1);

	bIsCorrect = true;

	for (i = 1; i <= VALUE_MAX / SCALE_FAST; ++i)
	{
		for (j = 1; j <= PRIORITY_MAX / SCALE_FAST; ++j)
		{
			pqueueDequeue (&sThePQ, &dataValue, sizeof (int), &priorityValue);
			if (dataValue != j || priorityValue - 1 != i)
			{
				bIsCorrect = false;
			}
		}
	}

	assert (bIsCorrect, "Huge change priority is correct",
			"Huge change priority is NOT Correct");

	pqueueTerminate (&sThePQ);
	success ("PQ Terminate");


	puts("Program End");
}
