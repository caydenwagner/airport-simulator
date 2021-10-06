/**************************************************************************
 File name:  listdriver.c
 Author:     Computer Science, Pacific University
 Date:		 October 6 2021
 Class:		 CS300
 Assignment: ListADT part 2
 Purpose:	 Create a fully function linked list abstract data type
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../include/list.h"
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
/**************************************************************************
 Function: 	 	printList

 Description: Prints a list of integers for debugging purposes.

 Parameters:	sTheList - the list of integers to be printed

 Returned:	 	none
 *************************************************************************/

static void printCharList (List sTheList)
{
	char i, theIntData;

	if (!lstIsEmpty (&sTheList))
	{
		printf ("         ");
		lstFirst (&sTheList);
		for (i = 0; i < lstSize (&sTheList); ++i)
		{
			lstPeek(&sTheList,  &theIntData, sizeof (char));
			lstNext (&sTheList);
			printf ("%c ", theIntData);
		}
		printf ("\n");
	}
}

/**************************************************************************
 Function: 	 	main

 Description: test all the functionality of the list

 Parameters:	none

 Returned:	 	none
 *************************************************************************/

int main ()
{
	List sTheList;
	char letter, storedLetter;
	char letterA = 'A', letterB = 'B', letterC = 'C';

	puts ("Driver Start");

	lstLoadErrorMessages();

	lstCreate (&sTheList);
	success ("List Created");

//	Purposefully triggering errors in each function

//	lstHasCurrent(NULL);

//	lstInsertBefore(NULL, &letterA, sizeof(char));
//	lstInsertBefore(&sTheList, NULL, sizeof(char));
//	lstInsertBefore(&sTheList, &letterA, sizeof(char));
//	assert(lstHasCurrent(&sTheList), "The List Has a Current Node"
//								   , "The List Has No Current Node");
//	lstNext(&sTheList);
//	assert(!lstHasCurrent(&sTheList), "The List Has No Current Node"
//								   , "The List Has a Current Node");
//	lstInsertBefore(&sTheList, &letterA, sizeof(char));

//	lstDeleteCurrent(NULL, &letterA, sizeof(char));
//	lstDeleteCurrent(&sTheList, NULL, sizeof(char));
//	lstDeleteCurrent(&sTheList, &letterA, sizeof(char));
//	lstInsertBefore(&sTheList, &letterA, sizeof(char));
//	lstNext(&sTheList);
//	lstDeleteCurrent(&sTheList, &letterA, sizeof(char));

//	lstUpdateCurrent(NULL, &letterA, sizeof(char));
//	lstUpdateCurrent(&sTheList, NULL, sizeof(char));
//	lstUpdateCurrent(&sTheList, &letterA, sizeof(char));
//	lstInsertBefore(&sTheList, &letterA, sizeof(char));
//	lstNext(&sTheList);
//	lstUpdateCurrent(&sTheList, &letterA, sizeof(char));

//	lstLast(NULL);
//	lstLast(&sTheList);

//	lstPeekNext(NULL, &letterA, sizeof(char));
//	lstPeekNext(&sTheList, NULL, sizeof(char));
//	lstPeekNext(&sTheList, &letterA, sizeof(char));
//	lstInsertBefore(&sTheList, &letterA, sizeof(char));
//	lstNext(&sTheList);
//	lstPeekNext(&sTheList, &letterA, sizeof(char));

//	lstInsertBefore(&sTheList, &letterA, sizeof(char));
//	lstLast(&sTheList);
//	lstPeekNext(&sTheList, &letterA, sizeof(char));

//	lstLast(NULL);
//	lstLast(&sTheList);

	for (letter = 'A'; letter <= 'Z'; ++letter)
	{
		lstInsertBefore (&sTheList, &letter, sizeof (char));
		lstPeek(&sTheList, &storedLetter, sizeof(char));
		if(letter != storedLetter)
		{
			assert( letter == storedLetter, "Valid letter data",
				"Invalid letter data");
		}
	}

	printCharList (sTheList);

	lstTerminate(&sTheList);

	for (letter = 'Z'; letter >= 'A'; --letter)
	{
		lstInsertBefore (&sTheList, &letter, sizeof (char));
		lstPeek(&sTheList, &storedLetter, sizeof(char));
		if(letter != storedLetter)
		{
			assert( letter == storedLetter, "Valid letter data",
				"Invalid letter data");
		}
	}

	printCharList (sTheList);

	lstFirst(&sTheList);
	lstDeleteCurrent(&sTheList, &letter, sizeof(char));
	lstDeleteCurrent(&sTheList, &letter, sizeof(char));
	lstDeleteCurrent(&sTheList, &letter, sizeof(char));

	lstLast(&sTheList);
	lstDeleteCurrent(&sTheList, &letter, sizeof(char));

	printCharList (sTheList);

	lstFirst(&sTheList);
	lstUpdateCurrent(&sTheList, &letterA, sizeof(char));
	lstNext(&sTheList);

	lstUpdateCurrent(&sTheList, &letterB, sizeof(char));
	lstNext(&sTheList);

	lstUpdateCurrent(&sTheList, &letterC, sizeof(char));
	lstNext(&sTheList);

	printCharList (sTheList);

	lstTerminate(&sTheList);

	puts ("Driver End");
	return EXIT_SUCCESS;
}
