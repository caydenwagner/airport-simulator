/**************************************************************************
 File name:  pqMemTest.c
 Author:     chadd
 Date:			 Oct 15, 2019
 Class:			 CS300
 Assignment: Priority Queue
 Purpose:    Memory Stress test for PQ
 *************************************************************************/

/*
 * In VirtualBox on a MacBookPro i7
 *
 * With Valgrind this takes:  2 m 50 seconds
 *  time valgrind -v --leak-check=yes --track-origins=yes --leak-check=full
 *     --show-leak-kinds=all bin/pqMemTest
 *
 * Without Valgrind this takes: 1.6 seconds
 *  time bin/pqMemTest
 */

#include "../include/pqueue.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ARRAY_SIZE 100
// a struct larger than a pointer
typedef struct BigStruct
{
		int aBigArray[ARRAY_SIZE];
		int number;
		char letter;
		double decimal;
} BigStruct;

typedef enum InsertOrder { FAST, SLOW} InsertOrder;

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
 Function: 	 	insertInts

 Description: Insert size ints into the PQ.  The int and priority match

 Parameters:	psPQ - the priority queue
 	 	 	 	 	 	  size - the number of ints to insert
							order - the order to insert the priorities
 Returned:	 	none
 ****************************************************************************/
static void insertInts(PriorityQueuePtr psPQ, int size,	InsertOrder order)
{
	int i;
	int start, end, step;

	if( FAST == order)
	{
		start = size;
		step = -1;
		end = 0;
	}
	else
	{
		start = 1;
		step = 1;
		end = size + 1;

	}

	for(i = start; i != end; i += step)
	{
		pqueueEnqueue(psPQ, &i, sizeof(int), i);
	}
}

/****************************************************************************
 Function: 	  removeInts

 Description: Remove size ints from the PQ.  Assert if the removed int
 	 	 	 	 	 	 	 and priority don't match

 Parameters:	psPQ - the priority queue
 	 	 	 	 	 	  size - the number of ints to remove

 Returned:	 	none
 ****************************************************************************/
static bool removeInts(PriorityQueuePtr psPQ, int size)
{
	int i, data, priority;
	bool bRetVal = true;

	for(i = 1; i <= size; ++i)
	{
		pqueueDequeue(psPQ, &data, sizeof(int), &priority);

		if( data != priority)
		{
			assert(data == priority, "", "removeInts failed");
			bRetVal = false;
		}
	}
	return bRetVal;
}

/****************************************************************************
 Function: 	 	main

 Description: Stress test the dynamic memory allocation

 Parameters:	none

 Returned:	 	none
 ****************************************************************************/
int main ()
{
	const int BIG_TEST = 1000000;
	PriorityQueue sThePQ;
	BigStruct sBigData;
	int priorityValue;
	int i, j;

	puts ("Program Start\n");

	pqueueLoadErrorMessages();

	pqueueCreate (&sThePQ);
	success ("PQ Create");

	for(i=0; i < 52; ++i)
	{
		sBigData.number = i;
		sBigData.decimal = (i + (i/52.0));
		sBigData.letter = i;

		for(j = 0; j < ARRAY_SIZE; ++j)
		{
			sBigData.aBigArray[j] = i*ARRAY_SIZE+1;
		}

		pqueueEnqueue(&sThePQ, &sBigData, sizeof(BigStruct), i);
	}

	for(i=0; i < 50; ++i)
	{
		pqueueDequeue(&sThePQ, &sBigData, sizeof(BigStruct), &priorityValue);

		// be careful comparing floating point numbers!
		// rounding may cause false negatives.
		// if decimal is a float rather than a double, errors are
		// reported
		if(!(i == priorityValue && sBigData.number == i && sBigData.letter == i
				&& i+(i/52.0) == sBigData.decimal))
		{
			assert(i == priorityValue && sBigData.number == i &&
					sBigData.letter == i && i+(i/52.0) == sBigData.decimal,
					"", "BigStruct failed");
		}
		for(j=0;j<ARRAY_SIZE;++j)
		{
			if (i*ARRAY_SIZE +1 !=  sBigData.aBigArray [j])
			{
				assert(i*ARRAY_SIZE +1 ==  sBigData.aBigArray[j],"","Bad value in sBigData");
			}
		}
	}

	pqueueTerminate (&sThePQ);
	success ("PQ Terminate");

	pqueueCreate (&sThePQ);
	success ("PQ Create");

	insertInts(&sThePQ, BIG_TEST, FAST);

	pqueueTerminate (&sThePQ);
	success ("PQ Terminate");

	pqueueCreate (&sThePQ);
	success ("PQ Create");

	insertInts(&sThePQ, BIG_TEST, FAST);

	if(removeInts(&sThePQ, BIG_TEST ) )
	{
		success("removeInts(&sThePQ, BIG_TEST ) OK");
	}

	pqueueTerminate (&sThePQ);
	success ("PQ Terminate");

	pqueueCreate (&sThePQ);
	success ("PQ Create");

	insertInts(&sThePQ, BIG_TEST, FAST);

	if(removeInts(&sThePQ, BIG_TEST / 2 ) )
	{
		success("removeInts(&sThePQ, BIG_TEST / 2 ) OK");
	}

	insertInts(&sThePQ, BIG_TEST / 2, FAST);

	if(removeInts(&sThePQ, BIG_TEST / 2 ) )
	{
		success("removeInts(&sThePQ, BIG_TEST / 2 ) OK");
	}

	if(removeInts(&sThePQ, BIG_TEST / 2 ) )
	{
		success("removeInts(&sThePQ, BIG_TEST / 2 ) OK");
	}

	insertInts(&sThePQ, BIG_TEST / 100, SLOW);

	if(removeInts(&sThePQ, BIG_TEST / 100 ) )
	{
		success("removeInts(&sThePQ, BIG_TEST / 100 ) OK");
	}

	pqueueTerminate (&sThePQ);
	success ("PQ Terminate");

	puts ("\nProgram End");

	return EXIT_SUCCESS;
}


