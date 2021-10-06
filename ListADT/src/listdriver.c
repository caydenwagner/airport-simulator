/**************************************************************************
 File name:  dlistdriver.c
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

	lstInsertBefore(psTheList, &maxInt, sizeof(int));
	lstInsertBefore(psTheList, &maxChar, sizeof(char));
	lstInsertBefore(psTheList, &maxDouble, sizeof(double));
	lstInsertBefore(psTheList, &maxFloat, sizeof(float));
	lstInsertBefore(psTheList, &bTrue, sizeof(bool));
	lstInsertBefore(psTheList, &maxShort, sizeof(short));
	lstInsertBefore(psTheList, &maxLongLong, sizeof(long long));

	lstFirst(psTheList);

	maxLongLong = 0;
	lstPeek(psTheList, &maxLongLong, sizeof(long long));
	assert(LLONG_MAX == maxLongLong, "Max long long correct", "Max long long incorrect");
	lstNext(psTheList);

	maxShort = 0;
	lstPeek(psTheList, &maxShort, sizeof(short));
	assert(SHRT_MAX == maxShort, "Max short correct", "Max short incorrect");
	lstNext(psTheList);

	bTrue = false;
	lstPeek(psTheList, &bTrue, sizeof(bool));
	assert(true == bTrue, "Max TRUE correct", "Max TRUE incorrect");
	lstNext(psTheList);

	maxFloat = 0.0;
	lstPeek(psTheList, &maxFloat, sizeof(float));
	assert(FLT_MAX == maxFloat, "Max float correct", "Max float incorrect");
	lstNext(psTheList);

	maxDouble = 0.0;
	lstPeek(psTheList, &maxDouble, sizeof(double));
	assert(DBL_MAX == maxDouble, "Max double correct", "Max double incorrect");
	lstNext(psTheList);

	maxChar = 0;
	lstPeek(psTheList, &maxChar, sizeof(char));
	assert(CHAR_MAX == maxChar, "Max char correct", "Max char incorrect");
	lstNext(psTheList);


	maxInt = 0;
	lstPeek(psTheList, &maxInt, sizeof(int));
	assert(INT_MAX == maxInt, "Max int correct", "Max int incorrect");
	lstNext(psTheList);


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

	puts ("Driver Start");

	lstLoadErrorMessages();

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

	printCharList (sTheList);

	lstTerminate(&sTheList);

	puts ("Driver End");
	return EXIT_SUCCESS;
}
