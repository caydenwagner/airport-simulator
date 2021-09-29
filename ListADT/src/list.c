/**************************************************************************
 File name:  	 list.c
 Author:     	 Computer Science, Pacific University
 Date:			 	 9.21.16
 Class:			 	 CS300
 Assignment:	 ListADT
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../include/list.h"

char gszListErrors[NUMBER_OF_LIST_ERRORS][MAX_ERROR_LIST_CHARS];


/**************************************************************************
 Function: 	 		lstLoadErrorMessages

 Description: 	Initializes the string of error messages. LOAD_ERRORS is a
 	 	 	 					macro defined in the header file.

 Parameters:		None

 Returned:	 		None
 *************************************************************************/

void lstLoadErrorMessages ()
{
	LOAD_LIST_ERRORS
}

/**************************************************************************
 Function: 	 		processError

 Description:   Process the error code passed to this routine

 Parameters:		pszFunctionName - function causing the error
 	 	 	 					errorCode 	    - identifies the list error

 Returned:	 		None
 *************************************************************************/

static void processError (const char *pszFunctionName, int errorCode)
{
	printf ("Function: %s %s \n ", pszFunctionName,
			gszListErrors [errorCode]);
  exit (EXIT_FAILURE);
}

/**************************************************************************
 Function: 	 		lstCreate

 Description:		Initializes pointers in the list to NULL and number of
 	 	 	 					elements to 0

 Parameters:		psList - a pointer to the list

 Returned:			None
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
 Function: 	 		lstInsertAfter

 Description:		Insert the new element as the successor of the current
 	 	 	 	 	 	 	 	element pointed to by psCurrent

 Parameters:		psList  -  a pointer to the list
 	 	 	 	 	 	 	 	pBuffer -	 a pointer to data that is inserted as the
 	 	 	 	 	 	 	 						 successor of psCurrent
 	 	 	 	 	 	 	 	size    -	 the size of the data pointed to by pBuffer

 Returned:			None
 *************************************************************************/

void lstInsertAfter (ListPtr psList, const void *pBuffer, int size)
{
	if ( NULL == psList )
	{
		processError("lstInsertAfter", ERROR_INVALID_LIST);
	}

	if ( NULL == pBuffer )
	{
		processError("lstInsertAfter", ERROR_NULL_PTR);
	}
	if (NULL == psList->psCurrent && psList->numElements != 0 )
	{
		processError("lstInsertAfter", ERROR_NO_CURRENT);
	}

	ListElementPtr psTemp = (ListElementPtr) malloc(sizeof(ListElement));
	void* temp = malloc(sizeof(temp));

	psTemp->pData = malloc(size);
	psTemp->psNext = NULL;
	memcpy(temp, pBuffer, sizeof(size));

	psTemp->pData = temp;

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
 Function: 	 		lstPeek

 Description:		Accesses the value of the element pointed to by psCurrent

 Parameters:		psList  -  a pointer to the list
 	 	 	 	 	 	 	 	pBuffer -	 a pointer to buffer space which stores the value
 	 	 	 	 	 	 	 	 	 	 	 	 	 of the element pointed to by psCurrent
 	 	 	 	 	 	 	 	size    -	 the size of the data pointed to by psCurrent

 Returned:			None
 *************************************************************************/

void *lstPeek (const ListPtr psList, void *pBuffer, int size)
{
	if ( psList == NULL )
	{
		processError("lstPeek", ERROR_INVALID_LIST);
	}
	if ( pBuffer == NULL )
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

	memcpy(pBuffer, psList->psCurrent->pData, size);

	return pBuffer;
}

/**************************************************************************
 Function: 	 		lstTerminate

 Description:		Terminates all elements of the list and points the psFirst,
  							psLast, and psCurrent to NULL

 Parameters:		psList - a pointer to the list

 Returned:			None
 *************************************************************************/

void lstTerminate (ListPtr psList)
{
	if (NULL == psList )
	{
		processError("lstTerminate", ERROR_NO_LIST_TERMINATE);
	}

	ListElementPtr psTemp = psList->psFirst;
	ListElementPtr psNext = NULL;

	psList->psCurrent = psList->psFirst;

	while(psTemp != NULL)
	{
		psNext = psList->psCurrent->psNext;
		psList->psCurrent = psList->psCurrent->psNext;

		free(psTemp->pData);
		free(psTemp);

		psTemp = psNext;
	}

	psList->numElements = 0;
	psList->psFirst = NULL;
	psList->psCurrent = NULL;
	psList->psLast = NULL;
}

/**************************************************************************
 Function: 	 		lstSize

 Description:		Accesses the number of elements in the list

 Parameters:		psList - a pointer to the list

 Returned:			The amount of elements in the list
 *************************************************************************/

int lstSize (const ListPtr psList)
{
	if (NULL == psList)
	{
		processError("lstSize", ERROR_INVALID_LIST);
	}

	return psList->numElements;
}

/**************************************************************************
 Function: 	 		lstIsEmpty

 Description:		Determines if the list is empty or not

 Parameters:		psList - a pointer to the list

 Returned:			True if the list is empty, else false
 *************************************************************************/

bool lstIsEmpty (const ListPtr psList)
{
	if ( NULL == psList)
	{
		processError("lstSize", ERROR_INVALID_LIST);
	}

	return (psList->numElements == 0);
}

/**************************************************************************
 Function: 	 		lstFirst

 Description:		Sets psCurrent to the first element in the list

 Parameters:		psList - a pointer to the list

 Returned:			None
 *************************************************************************/

void lstFirst (ListPtr psList)
{
	if ( NULL == psList)
	{
		processError("lstFirst", ERROR_INVALID_LIST);
	}
	if ( psList->numElements == 0 )
	{
		processError("lstFirst", ERROR_EMPTY_LIST);
	}

	psList->psCurrent = psList->psFirst;
}

/**************************************************************************
 Function: 	 		lstNext

 Description:		Sets psCurrent to the next element in the list

 Parameters:		psList - a pointer to the list

 Returned:			None
 *************************************************************************/

void lstNext (ListPtr psList)
{
	if ( NULL == psList)
	{
		processError("lstNext", ERROR_INVALID_LIST);
	}
	if ( psList->numElements == 0 )
	{
		processError("lstNext", ERROR_EMPTY_LIST);
	}
	if ( psList->psCurrent == NULL )
	{
		processError("lstNext", ERROR_NO_CURRENT);
	}

	psList->psCurrent = psList->psCurrent->psNext;
}
