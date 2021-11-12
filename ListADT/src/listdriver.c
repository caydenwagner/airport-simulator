/**************************************************************************
 File name:  partBdriverbig.c
 Author:     Computer Science, Pacific University
 Date:
 Class:
 Assignment:
 Purpose:
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


void insertAndValidManyTypes(ListPtr psTheList)
{
	// int
	int maxInt = INT_MAX;

	// char
	char maxChar = CHAR_MAX;

	// double
	double maxDouble = DBL_MAX;

	// float
	float maxFloat = FLT_MAX;

	// bool
	bool bTrue = true;

	// short
	short maxShort = SHRT_MAX;

	// long long
	long long maxLongLong = LLONG_MAX;

	lstInsertAfter(psTheList, &maxInt, sizeof(int));
	lstInsertAfter(psTheList, &maxChar, sizeof(char));
	lstInsertAfter(psTheList, &maxDouble, sizeof(double));
	lstInsertAfter(psTheList, &maxFloat, sizeof(float));
	lstInsertAfter(psTheList, &bTrue, sizeof(bool));
	lstInsertAfter(psTheList, &maxShort, sizeof(short));
	lstInsertAfter(psTheList, &maxLongLong, sizeof(long long));

	lstFirst(psTheList);

	maxInt = 0;
	lstPeek(psTheList, &maxInt, sizeof(int));
	assert(INT_MAX == maxInt, "Max int correct", "Max int incorrect");
	lstNext(psTheList);

	maxChar = 0;
	lstPeek(psTheList, &maxChar, sizeof(char));
	assert(CHAR_MAX == maxChar, "Max char correct", "Max char incorrect");
	lstNext(psTheList);

	maxDouble = 0.0;
	lstPeek(psTheList, &maxDouble, sizeof(double));
	assert(DBL_MAX == maxDouble, "Max double correct", "Max double incorrect");
	lstNext(psTheList);

	maxFloat = 0.0;
	lstPeek(psTheList, &maxFloat, sizeof(float));
	assert(FLT_MAX == maxFloat, "Max float correct", "Max float incorrect");
	lstNext(psTheList);

	bTrue = false;
	lstPeek(psTheList, &bTrue, sizeof(bool));
	assert(true == bTrue, "Max TRUE correct", "Max TRUE incorrect");
	lstNext(psTheList);

	maxShort = 0;
	lstPeek(psTheList, &maxShort, sizeof(short));
	assert(SHRT_MAX == maxShort, "Max short correct", "Max short incorrect");
	lstNext(psTheList);

	maxLongLong = 0;
	lstPeek(psTheList, &maxLongLong, sizeof(long long));
	assert(LLONG_MAX == maxLongLong, "Max long long correct", "Max long long incorrect");
	lstNext(psTheList);
}

void makeBigList(ListPtr psList, int max)
{
	int i;

	// insert max nodes
	for (i = 0; i < max; ++i)
	{
		lstInsertAfter (psList, &i, sizeof (int));
	}

	assert( max == lstSize (psList), "The list size is max",
			"The list size is not max");

	assert( !lstIsEmpty (psList), "The list is NOT empty",
			"The list is empty");

	// For debugging purposes only
	// printIntList (sTheList);

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
	List sTheSecondList;
	const int BIG_LIST_SIZE = 1000000;
	int i, intValue, secondIntValue;
	int numValues;
	char charValue;
	char *szLetters="ABCDEFGHIJ";
	char letter, storedLetter;

	puts ("Driver Start");

	lstLoadErrorMessages();

	lstCreate (&sTheList);
	success ("List Created");


	// insert the ints 0 to 9
	numValues = 10;
	for (i = 0; i < numValues; ++i)
	{
		lstInsertAfter (&sTheList, &i, sizeof (int));
	}


	// insert a character between each int
	lstFirst(&sTheList);
	for (i = 0; i < numValues; ++i)
	{
		lstInsertAfter (&sTheList, &(szLetters[i]) , sizeof (char));
		lstNext(&sTheList);
	}

	// validate the list
	lstFirst(&sTheList);
	for (i = 0; i < numValues; ++i)
	{
		lstPeek (&sTheList, &(intValue) , sizeof (int));
		lstPeekNext(&sTheList, &charValue , sizeof(char));

		lstNext(&sTheList);
		lstNext(&sTheList);

		if( intValue != i)
		{
			assert(intValue == i && charValue == szLetters[i], "Valid Data",
				"Invalid Data");
		}
	}

	lstTerminate(&sTheList);

	lstCreate(&sTheList);
	lstCreate(&sTheSecondList);

	makeBigList(&sTheList, BIG_LIST_SIZE);
	makeBigList(&sTheSecondList, BIG_LIST_SIZE);

	// walk through both lists and validate!

	lstFirst(&sTheList);
	lstFirst(&sTheSecondList);

	i = lstSize(&sTheList);

	while(lstHasCurrent(&sTheList))
	{

		lstPeek(&sTheList, &intValue, sizeof(int));
		lstPeek(&sTheSecondList, &secondIntValue, sizeof(int));

		if( intValue != secondIntValue )
		{
			assert(intValue == secondIntValue, "Big lists match", "Big lists do not match");
		}

		lstNext(&sTheList);
		lstNext(&sTheSecondList);

		--i;
	}

	lstTerminate (&sTheList);
	success ("List Terminated");

	lstTerminate (&sTheSecondList);
	success ("Second List Terminated");

	lstCreate (&sTheList);
	success ("List Created");

	insertAndValidManyTypes(&sTheList);

	lstTerminate (&sTheList);
	success ("List Terminated");

	lstCreate (&sTheList);
	success ("List Created");


	for (letter = 'A'; letter <= 'Z'; ++letter)
	{
		lstInsertBefore (&sTheList, &letter, sizeof (char));
		lstPeek(&sTheList, &storedLetter, sizeof(char));
		if(  letter != storedLetter)
		{
			assert( letter == storedLetter, "Valid letter data",
				"Invalid letter data");
		}
	}

	lstFirst(&sTheList);
	for (letter = 'Z'; letter >= 'A'; --letter)
	{
		lstDeleteCurrent(&sTheList, &storedLetter, sizeof(char));
		if(  letter != storedLetter)
		{
			assert( letter == storedLetter, "Valid letter data",
				"Invalid letter data");
		}
	}

	lstInsertAfter (&sTheList, &letter, sizeof (char));

	lstNext(&sTheList);

	// make sure all output gets to the screen
	fflush(stdout);

	lstUpdateCurrent (&sTheList, &intValue, sizeof (int));

	lstTerminate (&sTheList);
	success ("List Terminated");

	puts ("Driver End");
	return EXIT_SUCCESS;
}
