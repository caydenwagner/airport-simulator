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
/**************************************************************************
 Function:

 Description:

 Parameters:		psQueue - a pointer to the queue

 Returned:
 *************************************************************************/
void pqueueEnqueue (PriorityQueuePtr psQueue, const void *pBuffer,
										int size, int priority)
{
	if (NULL == psQueue)
	{
		processError("pqueueEnqueue", ERROR_INVALID_PQ);
	}
	if (NULL == pBuffer)
	{
		processError("pqueueEnqueue", ERROR_NULL_PQ_PTR);
	}

	PriorityQueueElementPtr psTemp;
	PriorityQueueElement sTempCurrent;

	psTemp = malloc(sizeof(PriorityQueueElementPtr));
	psTemp->pData = malloc(sizeof(size));

	memcpy(&(psTemp->priority), &priority, sizeof(int));
	memcpy(psTemp->pData, pBuffer, sizeof(size));

	if (pqueueIsEmpty(psQueue))
	{
		lstInsertAfter(&(psQueue->sTheList), psTemp, sizeof(PriorityQueueElementPtr));
	}
	else
	{
		lstFirst(&(psQueue->sTheList));
		lstPeek(&(psQueue->sTheList), &sTempCurrent,
						sizeof(PriorityQueueElementPtr));

		while (priority < sTempCurrent.priority &&
					lstHasNext(&(psQueue->sTheList)))
		{
			lstNext(&(psQueue->sTheList));
			lstPeek(&(psQueue->sTheList), &sTempCurrent,
							sizeof(PriorityQueueElementPtr));
		}
		if (priority < sTempCurrent.priority)
		{
			lstInsertAfter(&(psQueue->sTheList), psTemp, sizeof(PriorityQueueElementPtr));
		}
		else
		{
			lstInsertBefore(&(psQueue->sTheList), psTemp, sizeof(PriorityQueueElementPtr));
		}
	}
}
/**************************************************************************
 Function:

 Description:

 Parameters:		psQueue - a pointer to the queue

 Returned:
 *************************************************************************/
void *pqueuePeek (PriorityQueuePtr psQueue, void *pBuffer, int size,
								 int *priority)
{
	if (NULL == psQueue)
	{
		processError("pqueuePeek", ERROR_INVALID_PQ);
	}
	if (NULL == pBuffer)
	{
		processError("pqueuePeek", ERROR_NULL_PQ_PTR);
	}
	if (lstIsEmpty(&psQueue->sTheList))
	{
		processError("pqueuePeek", ERROR_EMPTY_PQ);
	}

	PriorityQueueElement sTemp;

	lstPeek(&psQueue->sTheList, &sTemp, sizeof(PriorityQueueElementPtr));

	memcpy(pBuffer, sTemp.pData, size);
	memcpy(priority, &(sTemp.priority), sizeof(int));

	return pBuffer;
}
