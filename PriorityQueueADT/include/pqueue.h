/**************************************************************************
 File name:		  pqueue.h
 Author:        CS, Pacific University
 Date:          10/18/17
 Class:         CS300
 Assignment:    Priority Queue Implementation
 Purpose:       This file defines the constants, data structures, and
                function prototypes for implementing a priority queue data
                structure.
 *************************************************************************/

#ifndef PQUEUE_H_
#define PQUEUE_H_

#include <stdbool.h>
#include "../../ListADT/include/list.h"

//*************************************************************************
// Constants
//*************************************************************************
#define MAX_ERROR_PQ_CHARS 64

enum {NO_PQ_ERROR = 0,
			ERROR_NO_PQ_CREATE,
			ERROR_NO_PQ_TERMINATE,
			ERROR_INVALID_PQ,
			ERROR_FULL_PQ,
			ERROR_NULL_PQ_PTR,
			ERROR_EMPTY_PQ}; // If this error name changes, change stmt below
#define NUMBER_OF_PQ_ERRORS ERROR_EMPTY_PQ - NO_PQ_ERROR + 1

//*************************************************************************
// Error Messages
//*************************************************************************
#define LOAD_PQ_ERRORS strcpy(gszPQErrors[NO_PQ_ERROR], "No Error.");\
strcpy(gszPQErrors[ERROR_NO_PQ_CREATE], "Error: No PQ Create.");\
strcpy(gszPQErrors[ERROR_NO_PQ_TERMINATE], "Error: No PQ Terminate.");\
strcpy(gszPQErrors[ERROR_INVALID_PQ], "Error: Invalid PQ.");\
strcpy(gszPQErrors[ERROR_FULL_PQ], "Error: Full Priority Queue.");\
strcpy(gszPQErrors[ERROR_NULL_PQ_PTR], "Error: NULL Pointer.");\
strcpy(gszPQErrors[ERROR_EMPTY_PQ], "Error: Empty Priority Queue.");

//*************************************************************************
// User-defined types
//*************************************************************************

typedef struct PriorityQueueElement
{
	int priority;
	void* pData;
} PriorityQueueElement;
typedef PriorityQueueElement* PriorityQueueElementPtr;


typedef struct PriorityQueue *PriorityQueuePtr;
typedef struct PriorityQueue
{
	List sTheList;
} PriorityQueue;

//*************************************************************************
//										Allocation and Deallocation
//*************************************************************************
extern void pqueueCreate (PriorityQueuePtr psQueue);
// results: If PQ can be created, then PQ exists and is empty
//					otherwise, ERROR_NO_PQ_CREATE


extern void pqueueTerminate (PriorityQueuePtr psQueue);
// results: If PQ can be terminated, then PQ no longer exists and is empty
//				   otherwise, ERROR_NO_PQ_TERMINATE

extern void pqueueLoadErrorMessages ();
// results:	Loads the error message strings for the error handler to use
//					No error conditions

//*************************************************************************
//									Checking number of elements in priority queue
//*************************************************************************

extern int pqueueSize (const PriorityQueuePtr psQueue);
// results: Returns the number of elements in the PQ
// 					error code priority: ERROR_INVALID_PQ if PQ is NULL

extern bool pqueueIsEmpty (const PriorityQueuePtr psQueue);
// results: If PQ is empty, return true; otherwise, return false
// 					error code priority: ERROR_INVALID_PQ


//*************************************************************************
//									Inserting and retrieving values
//*************************************************************************

extern void pqueueEnqueue (PriorityQueuePtr psQueue, const void *pBuffer,
										int size, int priority);
// requires: psQueue is not full
// results: Insert the element into the priority queue based on the
//          priority of the element.
//					error code priority: ERROR_INVALID_PQ, ERROR_NULL_PQ_PTR,
//															 ERROR_FULL_PQ


extern void *pqueueDequeue (PriorityQueuePtr psQueue, void *pBuffer,
														int size, int  *pPriority);

// requires: psQueue is not empty
// results: Remove the element from the front of a non-empty queue
//					error code priority: ERROR_INVALID_PQ, ERROR_NULL_PQ_PTR,
//															 ERROR_EMPTY_PQ

//*************************************************************************
//													Peek Operations
//*************************************************************************

extern void *pqueuePeek (PriorityQueuePtr psQueue, void *pBuffer, int size,
												 int *priority);
// requires: psQueue is not empty
// results: The priority and value of the first element is returned through
//					the argument list
// IMPORTANT: Do not remove element from the queue
// 						error code priority: ERROR_INVALID_PQ, ERROR_NULL_PQ_PTR,
//																 ERROR_EMPTY_PQ

extern void pqueueChangePriority (PriorityQueuePtr psQueue,
																	int change);
// results: The priority of all elements is increased by the amount in
//					change error code priority: ERROR_INVALID_PQ

#endif /* PQUEUE_H_ */
