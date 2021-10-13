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
