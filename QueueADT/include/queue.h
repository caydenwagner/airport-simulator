/**************************************************************************
 File name:		  queue.h
 Author:        CS, Pacific University
 Date:
 Class:         CS300
 Assignment:    Airport Simulation
 Purpose:       This file defines the constants, data structures, and
                function prototypes for implementing a queue data
                structure using your existing Priority Queue.
 *************************************************************************/


#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdbool.h>
#include "../../PriorityQueueADT/include/pqueue.h"

//*************************************************************************
// Constants
//*************************************************************************
#define MAX_ERROR_Q_CHARS 64

enum {NO_Q_ERROR = 0,
			ERROR_NO_Q_CREATE,
			ERROR_NO_Q_TERMINATE,
			ERROR_INVALID_Q,
			ERROR_FULL_Q,
			ERROR_NULL_Q_PTR,
			ERROR_EMPTY_Q}; // If this error name changes, change stmt below
#define NUMBER_OF_Q_ERRORS ERROR_EMPTY_Q - NO_Q_ERROR + 1


//*************************************************************************
// Error Messages
//*************************************************************************
#define LOAD_Q_ERRORS strcpy(gszQErrors[NO_Q_ERROR], "No Error.");\
strcpy(gszQErrors[ERROR_NO_Q_CREATE], "Error: No Queue Create.");\
strcpy(gszQErrors[ERROR_NO_Q_TERMINATE], "Error: No Queue Terminate.");\
strcpy(gszQErrors[ERROR_INVALID_Q], "Error: Invalid Queue.");\
strcpy(gszQErrors[ERROR_FULL_Q], "Error: Full Queue.");\
strcpy(gszQErrors[ERROR_NULL_Q_PTR], "Error: NULL Pointer.");\
strcpy(gszQErrors[ERROR_EMPTY_Q], "Error: Empty Queue.");

//*************************************************************************
// User-defined types
//*************************************************************************
typedef struct Queue *QueuePtr;
typedef struct Queue
{
	PriorityQueue sTheQueue;
} Queue;

/**************************************************************************
*										Allocation and Deallocation
**************************************************************************/
extern void queueCreate (QueuePtr psQueue);
// results: If Q can be created, then Q exists and is empty
//					otherwise, ERROR_NO_Q_CREATE


extern void queueTerminate (QueuePtr psQueue);
// results: If Q can be terminated, then Q no longer exists and is empty
//				   otherwise, ERROR_NO_Q_TERMINATE

extern void queueLoadErrorMessages ();
// results:	Loads the error message strings for the error handler to use
//					No error conditions

/**************************************************************************
*									Checking number of elements in queue
**************************************************************************/
extern int queueSize (const QueuePtr psQueue);
// results: Returns the number of elements in the Q
// 					error code priority: ERROR_INVALID_Q if Q is NULL

extern bool queueIsEmpty (const QueuePtr psQueue);
// results: If Q is empty, return true; otherwise, return false
// 					error code priority: ERROR_INVALID_Q



/**************************************************************************
*									Inserting and retrieving values
**************************************************************************/
extern void queueEnqueue (QueuePtr psQueue, const void *pBuffer, int size);
// requires: psQueue is not full
// results: Insert the element into the FIFO queue.
//					error code priority: ERROR_INVALID_Q, ERROR_NULL_Q_PTR

extern void *queueDequeue (QueuePtr psQueue, void *pBuffer, int size);
// requires: psQueue is not empty
// results: Remove the element from the front of a non-empty queue
//					error code priority: ERROR_INVALID_Q, ERROR_NULL_Q_PTR,
//															 ERROR_EMPTY_Q

/**************************************************************************
*													Peek Operations
**************************************************************************/
extern void *queuePeek (QueuePtr psQueue, void *pBuffer, int size);
// requires: psQueue is not empty
// results: The value of the first element is returned through the
//					argument list
// IMPORTANT: Do not remove element from the queue
// 						error code priority: ERROR_INVALID_Q, ERROR_NULL_Q_PTR,
//																 ERROR_EMPTY_Q

#endif /* QUEUE_H_ */
