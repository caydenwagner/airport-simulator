/**************************************************************************
 File name:		 queue.c
 Author:			 Cayden Wagner
 Date:				 10/19/21
 Class:			 	 CS300
 Assignment:	 pqueue ADT
 *************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../include/queue.h"

char gszQErrors[NUMBER_OF_LIST_ERRORS][MAX_ERROR_LIST_CHARS];
/**************************************************************************
 Function: 	 		pqLoadErrorMessages

 Description: 	Initializes the string of error messages. LOAD_ERRORS is a
 	 	 	 					macro defined in the header file.

 Parameters:		None

 Returned:	 		None
 *************************************************************************/
void queueLoadErrorMessages ()
{
	LOAD_Q_ERRORS
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
			gszQErrors [errorCode]);
  exit (EXIT_FAILURE);
}
/**************************************************************************
 Function:			queueCreate

 Description:		Initializes the queue

 Parameters:		psQueue - a pointer to the queue

 Returned:			None
 *************************************************************************/
void queueCreate (QueuePtr psQueue)
{
	if (NULL == psQueue)
	{
		processError("queueCreate", ERROR_NO_Q_CREATE);
	}
	pqueueCreate(&psQueue->sTheQueue);
}
/**************************************************************************
 Function:			queueSize

 Description:		Returns the number of elements in the queue

 Parameters:		psQueue - a pointer to the queue

 Returned:			The number of elements in the queue
 *************************************************************************/
int queueSize (const QueuePtr psQueue)
{
	if (NULL == psQueue)
	{
		processError("queueSize", ERROR_INVALID_Q);
	}
	return pqueueSize(&psQueue->sTheQueue);
}
/**************************************************************************
 Function:			queueIsEmpty

 Description:		Determines if the queue contains any elements or not

 Parameters:		psQueue - a pointer to the queue

 Returned:			True if the list contains 0 elements, else false
 *************************************************************************/
bool queueIsEmpty (const QueuePtr psQueue)
{
	if (NULL == psQueue)
	{
		processError("queueIsEmpty", ERROR_INVALID_Q);
	}
	return pqueueIsEmpty(&psQueue->sTheQueue);
}
/**************************************************************************
 Function:			queueEnqueue

 Description:		Inserts an element into the queue after

 Parameters:		psQueue  - a pointer to the queue
 	 	 	 	 	 	 	 	pBuffer  - a pointer to the data inserted
 	 	 	 	 	 	 	 	size     - the size, in bytes, of pBuffer

 Returned:			None
 *************************************************************************/
void queueEnqueue (QueuePtr psQueue, const void *pBuffer, int size)
{
	if (NULL == psQueue)
	{
		processError("queueEnqueue", ERROR_INVALID_Q);
	}
	if (NULL == pBuffer)
	{
		processError("queueEnqueue", ERROR_NULL_Q_PTR);
	}

	const int PRIORITY = 0;

	pqueueEnqueue(&psQueue->sTheQueue, pBuffer, size, PRIORITY);
}
/**************************************************************************
 Function:			queueDequeue

 Description:		removes the highest priority element from the queue

 Parameters:		psQueue  - a pointer to the queue
 	 	 	 	 	 	 	 	pBuffer  - a buffer to store the data
 	 	 	 	 	 	 	 	size     - the size, in bytes, of pBuffer

 Returned:			A pointer to the data of the removed element
 *************************************************************************/
void *queueDequeue (QueuePtr psQueue, void *pBuffer, int size)
{
	if (NULL == psQueue)
	{
		processError("queueDequeue", ERROR_INVALID_Q);
	}
	if (NULL == pBuffer)
	{
		processError("queueDequeue", ERROR_NULL_Q_PTR);
	}
	if (pqueueIsEmpty(&psQueue->sTheQueue))
	{
		processError("queueDequeue", ERROR_EMPTY_Q);
	}

	int priorityBuf;

	pqueueDequeue(&psQueue->sTheQueue, pBuffer, size, &priorityBuf);

	return pBuffer;
}
/**************************************************************************
 Function:			queuePeek

 Description:		Returns value of the first element through the argument list

 Parameters:		psQueue  - a pointer to the queue
 	 	 	 	 	 	 	 	pBuffer  - a buffer to store the data
 	 	 	 	 	 	 	 	size     - the size, in bytes, of pBuffer

 Returned:			A pointer to the data of the first element
 *************************************************************************/
void *queuePeek (QueuePtr psQueue, void *pBuffer, int size)
{
	if (NULL == psQueue)
	{
		processError("pqueuePeek", ERROR_INVALID_Q);
	}
	if (NULL == pBuffer)
	{
		processError("pqueuePeek", ERROR_NULL_Q_PTR);
	}
	if (pqueueIsEmpty(&psQueue->sTheQueue))
	{
		processError("pqueuePeek", ERROR_EMPTY_Q);
	}

	int priorityBuf;

	pqueuePeek(&psQueue->sTheQueue, pBuffer, size, &priorityBuf);

	return pBuffer;
}
/**************************************************************************
 Function:			queueDequeue

 Description:		removes the highest priority element from the queue

 Parameters:		psQueue  - a pointer to the queue
 	 	 	 	 	 	 	 	pBuffer  - a buffer to store the data
 	 	 	 	 	 	 	 	size     - the size, in bytes, of pBuffer

 Returned:			A pointer to the data of the removed element
 *************************************************************************/
void queueTerminate (QueuePtr psQueue)
{
	if (NULL == psQueue)
	{
		processError("queueTerminate", ERROR_NO_Q_TERMINATE);
	}

	pqueueTerminate(&psQueue->sTheQueue);
}
