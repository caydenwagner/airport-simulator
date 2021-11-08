/**************************************************************************
 File name:		 pqueue.c
 Author:			 Cayden Wagner
 Date:				 10/19/21
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
void processError (const char *pszFunctionName, int errorCode)
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
	return lstSize(&(psQueue->sTheList));
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
	return (lstIsEmpty(&psQueue->sTheList));
}
/**************************************************************************
 Function:			pqueueEnqueue

 Description:		Inserts an element into the queue after every element with
  							lower priority and before every element with higher
  							priority

 Parameters:		psQueue  - a pointer to the queue
 	 	 	 	 	 	 	 	pBuffer  - a pointer to the data inserted
 	 	 	 	 	 	 	 	size     - the size, in bytes, of pBuffer
 	 	 	 	 	 	 	 	priority - the priority of the inserted element

 Returned:			None
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

	PriorityQueueElement sTemp, sTempCurrent;

	sTemp.pData = (void*) malloc(size);

	sTemp.priority = priority;
	memcpy(sTemp.pData, pBuffer, size);

	if (pqueueIsEmpty(psQueue))
	{
		lstInsertAfter(&(psQueue->sTheList), &sTemp, sizeof(PriorityQueueElement));
	}
	else
	{
		lstFirst(&(psQueue->sTheList));
		lstPeek(&(psQueue->sTheList), &sTempCurrent,
						sizeof(PriorityQueueElement));

		while (priority >= sTempCurrent.priority &&
					lstHasNext(&(psQueue->sTheList)))
		{
			lstNext(&(psQueue->sTheList));
			lstPeek(&(psQueue->sTheList), &sTempCurrent,
							sizeof(PriorityQueueElement));
		}
		if (priority >= sTempCurrent.priority)
		{
			lstInsertAfter(&(psQueue->sTheList), &sTemp, sizeof(PriorityQueueElement));
		}
		else
		{
			lstInsertBefore(&(psQueue->sTheList), &sTemp, sizeof(PriorityQueueElement));
		}
	}
}
/**************************************************************************
 Function:			pqueuePeek

 Description:		Returns the priority and value of the first element through
  							the argument list

 Parameters:		psQueue  - a pointer to the queue
 	 	 	 	 	 	 	 	pBuffer  - a buffer to store the data
 	 	 	 	 	 	 	 	size     - the size, in bytes, of pBuffer
 	 	 	 	 	 	 	 	priority - space to store the priority of the removed
 	 	 	 	 	 	 	 						 element

 Returned:			A pointer to the data of the first element
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

	lstFirst(&(psQueue->sTheList));
	lstPeek(&psQueue->sTheList, &sTemp, sizeof(PriorityQueueElement));

	memcpy(pBuffer, sTemp.pData, size);
	*priority = sTemp.priority;

	return pBuffer;
}
/**************************************************************************
 Function:			pqueueDequeue

 Description:		removes the highest priority element from the queue

 Parameters:		psQueue  - a pointer to the queue
 	 	 	 	 	 	 	 	pBuffer  - a buffer to store the data
 	 	 	 	 	 	 	 	size     - the size, in bytes, of pBuffer
 	 	 	 	 	 	 	 	priority - space to store the priority of the removed
 	 	 	 	 	 	 	 						 element

 Returned:			A pointer to the data of the removed element
 *************************************************************************/
void *pqueueDequeue (PriorityQueuePtr psQueue, void *pBuffer,
										 int size, int  *pPriority)
{
	if (NULL == psQueue)
	{
		processError("pqueueDequeue", ERROR_INVALID_PQ);
	}
	if (NULL == pBuffer)
	{
		processError("pqueueDequeue", ERROR_NULL_PQ_PTR);
	}
	if (pqueueIsEmpty(psQueue))
	{
		processError("pqueueDequeue", ERROR_EMPTY_PQ);
	}
	PriorityQueueElement sTemp;

	lstFirst(&(psQueue->sTheList));
	lstPeek(&psQueue->sTheList, &sTemp, sizeof(PriorityQueueElement));

	memcpy(pBuffer, sTemp.pData, size);
	*pPriority = sTemp.priority;

	free(sTemp.pData);

	lstDeleteCurrent(&psQueue->sTheList, &sTemp, sizeof(PriorityQueueElement));

	return pBuffer;
}
/**************************************************************************
 Function:			pqueueTerminate

 Description:		Terminates the priority queue

 Parameters:		psQueue - a pointer to the queue

 Returned:			None
 *************************************************************************/
void pqueueTerminate (PriorityQueuePtr psQueue)
{
	if (NULL == psQueue)
	{
		processError("pqueueTerminate", ERROR_NO_PQ_TERMINATE);
	}
	PriorityQueueElement sTemp;

	if (!(lstIsEmpty(&psQueue->sTheList)))
	{
		lstFirst(&psQueue->sTheList);

			for (int i = 0; i < pqueueSize(psQueue); i++)
			{
				lstPeek(&psQueue->sTheList, &sTemp, sizeof(PriorityQueueElement));
				free(sTemp.pData);
				lstNext(&psQueue->sTheList);
			}

			lstTerminate(&psQueue->sTheList);
	}
}
/**************************************************************************
 Function:			pqueueChangePriority

 Description:		Increases the priority of all elements by the amount in
 	 	 	 	 	 	 	 	change

 Parameters:		psQueue - a pointer to the queue
 	 	 	 	 	 	 	 	change  - an integer value that is added to the priority of
 	 	 	 	 	 	 	 	 	 	 	 	 	every list element

 Returned:			None
 *************************************************************************/
void pqueueChangePriority (PriorityQueuePtr psQueue,
												   int change)
{
	if (NULL == psQueue)
	{
		processError("pqueueDequeue", ERROR_INVALID_PQ);
	}
	PriorityQueueElement sTemp;

	lstFirst(&psQueue->sTheList);

	for (int i = 0; i < pqueueSize(psQueue); i++)
	{
		lstPeek(&psQueue->sTheList, &sTemp, sizeof(PriorityQueueElement));
		sTemp.priority = sTemp.priority + change;
		lstUpdateCurrent(&psQueue->sTheList, &sTemp, sizeof(PriorityQueueElement));
		lstNext(&psQueue->sTheList);
	}
}
