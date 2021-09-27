/**************************************************************************
 File name:  	 list.c
 Author:     	 Computer Science, Pacific University
 Date:			 9.21.16
 Class:			 CS300
 Assignment:
 Purpose:
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../include/list.h"

char gszListErrors[NUMBER_OF_LIST_ERRORS][MAX_ERROR_LIST_CHARS];


/**************************************************************************
 Function: 	 	lstLoadErrorMessages

 Description: 	Initializes the string of error messages. LOAD_ERRORS is a
 	 	 	 	macro defined in the header file.

 Parameters:	None

 Returned:	 	None
 *************************************************************************/
void lstLoadErrorMessages ()
{
	LOAD_LIST_ERRORS
}


/**************************************************************************
 Function: 	 	processError

 Description:   Process the error code passed to this routine

 Parameters:	pszFunctionName - function causing the error
 	 	 	 	errorCode 	    - identifies the list error

 Returned:	 	None
 *************************************************************************/

static void processError (const char *pszFunctionName, int errorCode)
{
	printf ("Function: %s %s \n ", pszFunctionName,
			 gszListErrors [errorCode]);
	exit (EXIT_FAILURE);
}

/**************************************************************************
 Function: 	 	lstCreate

 Description:	Initializes pointers in the list to NULL and number of
 	 	 	 	elements to 0

 Parameters:	psList - List pointer that is initialized to default
 	 	 	 	 	 	 values

 Returned:		None
 *************************************************************************/

void lstCreate (ListPtr psList)
{
	if ( NULL == psList )
	{
		processError("lstCreate", ERROR_NO_LIST_CREATE);
	}

	psList->numElements = 0;
	psList->psFirst = NULL;
	psList->psCurrent = NULL;
	psList->psLast = NULL;
}

/**************************************************************************
 Function: 	 	lstInsertAfter

 Description:

 Parameters:

 Returned:		None
 *************************************************************************/

void lstInsertAfter (ListPtr psList, const void *pBuffer, int size)
{
	if ( NULL == psList )
	{
		processError("lstInsertAfter", ERROR_INVALID_LIST);
	}

	ListElementPtr psTemp;

	psTemp = (ListElementPtr) malloc(sizeof(ListElement));
	psTemp->pData = malloc(size);
	memcpy(psTemp->pData, pBuffer, size);
	psTemp->psNext = NULL;

	if (psList->psCurrent == NULL)
	{
		psList->psFirst = psTemp;
		psList->psLast = psTemp;
		psList->psCurrent = psTemp;
	}
	else if (psList->psCurrent->psNext == NULL)
	{
		psList->psCurrent->psNext = psTemp;
		psList->psCurrent = psTemp;
		psList->psLast = psTemp;
	}
	else
	{
		psTemp->psNext = psList->psCurrent->psNext;
		psList->psCurrent->psNext = psTemp;
		psList->psCurrent = psTemp;
	}
	psList->numElements++;
}

/**************************************************************************
 Function: 	 	lstPeek

 Description:

 Parameters:

 Returned:		None
 *************************************************************************/
void *lstPeek (const ListPtr psList, void *pBuffer, int size){
	if ( psList == NULL )
	{
		processError("lstPeek", ERROR_NULL_PTR);
	}
	if ( psList->numElements == 0)
	{
		processError("lstPeek", ERROR_EMPTY_LIST);
	}
	if (psList->psCurrent == NULL)
	{
		processError("lstPeek", ERROR_NO_CURRENT);
	}
}
