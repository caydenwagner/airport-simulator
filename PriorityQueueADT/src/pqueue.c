/**************************************************************************
 File name:		 pqueue.c
 Author:			 Cayden Wagner
 Date:				 10/11/21
 Class:			 	 CS300
 Assignment:	 pqueue ADT
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../include/pqueue.h"

char gszPQErrors[NUMBER_OF_LIST_ERRORS][MAX_ERROR_LIST_CHARS];
/**************************************************************************
 Function: 	 		pqLoadErrorMessages

 Description: 	Initializes the string of error messages. LOAD_ERRORS is a
 	 	 	 					macro defined in the header file.

 Parameters:		None

 Returned:	 		None
 *************************************************************************/
void pqueueLoadErrorMessages ()
{
	LOAD_PQ_ERRORS
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
			gszPQErrors [errorCode]);
  exit (EXIT_FAILURE);
}
/**************************************************************************
 Function:			pqueueCreate

 Description:		Initializes pointers in the list to NULL and number of
 	 	 	 					elements to 0

 Parameters:		psQueue - a pointer to the queue

 Returned:			None
 *************************************************************************/
void pqueueCreate (PriorityQueuePtr psQueue)
{
	if (NULL == psQueue)
	{
		processError("pqueueCreate", ERROR_NO_PQ_CREATE);
	}
	lstCreate(&(psQueue->sTheList));
}
/**************************************************************************
 Function:			pqueueSize

 Description:		Returns the number of elements in the queue

 Parameters:		psQueue - a pointer to the queue

 Returned:			The number of elements in the queue
 *************************************************************************/
int pqueueSize (const PriorityQueuePtr psQueue)
{
	if (NULL == psQueue)
	{
		processError("pqueueSize", ERROR_INVALID_PQ);
	}
	return psQueue->sTheList.numElements;
}
/**************************************************************************
 Function:			pqueueIsEmpty

 Description:		Determines if the queue contains any elements or not

 Parameters:		psQueue - a pointer to the queue

 Returned:			True if the list contains 0 elements, else false
 *************************************************************************/
bool pqueueIsEmpty (const PriorityQueuePtr psQueue)
{
	if (NULL == psQueue)
	{
		processError("pqueueIsEmpty", ERROR_INVALID_PQ);
	}
	return (0 == psQueue->sTheList.numElements);
}
