/**************************************************************************
 File name:		list.h
 Author:        CS, Pacific University
 Date:          09.19.2019
 Class:         CS300
 Assignment:    List Interface
 Purpose:       This file defines the constants, data structures, and
                function prototypes for implementing a list data structure.
                In essence, the list API is defined for other modules.
 *************************************************************************/

#ifndef LIST_H_
#define LIST_H_

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

//*************************************************************************
// Constants
//*************************************************************************
#define MAX_ERROR_LIST_CHARS 64

enum {NO_ERROR = 0,
			ERROR_NO_LIST_CREATE,
			ERROR_NO_LIST_TERMINATE,
			ERROR_INVALID_LIST,
			ERROR_FULL_LIST,
			ERROR_NO_NEXT,
			ERROR_NO_CURRENT,
			ERROR_NULL_PTR,
			ERROR_EMPTY_LIST}; // If this error name changes, change stmt below
#define NUMBER_OF_LIST_ERRORS ERROR_EMPTY_LIST - NO_ERROR + 1


//*************************************************************************
// Error Messages
//*************************************************************************
#define LOAD_LIST_ERRORS strcpy (gszListErrors[NO_ERROR], "No Error.");\
strcpy (gszListErrors[ERROR_NO_LIST_CREATE], "Error: No List Create.");\
strcpy (gszListErrors[ERROR_NO_LIST_TERMINATE], "Error: No List Terminate.");\
strcpy (gszListErrors[ERROR_INVALID_LIST], "Error: Invalid List.");\
strcpy (gszListErrors[ERROR_FULL_LIST], "Error: Full List.");\
strcpy (gszListErrors[ERROR_NO_NEXT], "Error: No List Next Node.");\
strcpy (gszListErrors[ERROR_NO_CURRENT], "Error: No List Current Node.");\
strcpy (gszListErrors[ERROR_NULL_PTR], "Error: NULL Pointer.");\
strcpy (gszListErrors[ERROR_EMPTY_LIST], "Error: Empty List.");

//*************************************************************************
// User-defined types
//*************************************************************************
typedef struct ListElement *ListElementPtr;
typedef struct ListElement
{
	// Note: The memory allocated for data cannot contain any pointers to
	//		 additional data or terminate will not work correctly; therefore,
	//		 data must point to a contiguous block of data and contain no
	// 		 additional pointers.
	void *pData;
	ListElementPtr psNext;
} ListElement;


// A list is a dynamic data structure where the current pointer and number
// of elements are maintained at all times

typedef struct List *ListPtr;
typedef struct List
{
	ListElementPtr psFirst;
	ListElementPtr psLast;
	ListElementPtr psCurrent;
	int numElements;
} List;

//*************************************************************************
// Allocation and Deallocation
//*************************************************************************
extern void lstCreate (ListPtr psList);
// results: If the list can be created, then the list exists and is empty;
//			otherwise, ERROR_NO_LIST_CREATE if psList is NULL

extern void lstTerminate (ListPtr psList);
// results: If the list can be terminated, then the list no longer exists
//			and is empty; otherwise, ERROR_NO_LIST_TERMINATE

extern void lstLoadErrorMessages ();
// results:	Loads the error message strings for the error handler to use
//			No error conditions. // see how to do this in stk.c

//*************************************************************************
// Checking number of elements in list
//*************************************************************************
extern int lstSize (const ListPtr psList);
// results: Returns the number of elements in the list
// 			error code priority: ERROR_INVALID_LIST

extern bool lstIsEmpty (const ListPtr psList);
// results: If list is empty, return true; otherwise, return false
// 			error code priority: ERROR_INVALID_LIST

//*************************************************************************
//												List Testing
//*************************************************************************
extern bool lstHasCurrent (const ListPtr psList);
// results: Returns true if the current node pointed to by psCurrent is
//			not NULL; otherwise, false is returned
// 			error code priority: ERROR_INVALID_LIST

extern bool lstHasNext (const ListPtr psList);
 // results: Returns true if the current node pointed to by psCurrent
 //					 has a successor; otherwise, false is returned
 // 				 error code priority: ERROR_INVALID_LIST

//*************************************************************************
//													Peek Operations
//*************************************************************************
extern void *lstPeek (const ListPtr psList, void *pBuffer, int size);
// requires:  List is not empty
// results:   The value of the current element pointed to by psCurrent
//            is returned
// IMPORTANT: Do not change psCurrent
//            error code priority: ERROR_INVALID_LIST, ERROR_NULL_PTR,
//							       ERROR_EMPTY_LIST, ERROR_NO_CURRENT

extern void *lstPeekNext (const ListPtr psList, void *pBuffer, int size);
// requires:  List contains two or more elements and psCurrent is not last
// results:   The data value of psCurrent's successor is returned
// IMPORTANT: Do not change psCurrent
//            error code priority: ERROR_INVALID_LIST, ERROR_NULL_PTR,
//								   ERROR_EMPTY_LIST, ERROR_NO_CURRENT,
//								   ERROR_NO_NEXT

//*************************************************************************
//							Updating current
//*************************************************************************
extern void lstFirst (ListPtr psList);
// requires:  List is not empty
// results:   If the list is not empty, psCurrent is changed to
//            the first element
//            error code priority: ERROR_INVALID_LIST,
//								   ERROR_EMPTY_LIST

extern void lstNext (ListPtr psList);
// requires:  List is not empty
// results:   If the list is not empty,
//			  psCurrent is changed to the successor of the current element
//            pointed to by psCurrent
//            error code priority: ERROR_INVALID_LIST,
//								   ERROR_EMPTY_LIST, ERROR_NO_CURRENT

extern void lstLast (ListPtr psList);
// requires:  List is not empty
// results:   If the list is not empty,
//		      psCurrent is changed to psLast
//            error code priority: ERROR_INVALID_LIST,
//								   ERROR_EMPTY_LIST

//*************************************************************************
//									Insertion, Deletion, and Updating
//*************************************************************************

extern void lstInsertAfter (ListPtr psList, const void *pBuffer, int size);
// requires: List is not full
// results:  If the list is not empty, insert the new element as the
//           successor of the current element pointed to by psCurrent
//           and make the inserted element the current element pointed to
//           by psCurrent;
//			 otherwise, insert element and make it current.
//           error code priority: ERROR_INVALID_LIST, ERROR_NULL_PTR,
//								  ERROR_NO_CURRENT

extern void *lstDeleteCurrent (ListPtr psList, void *pBuffer, int size);
// requires: List is not empty
// results: The current element is deleted and its successor and
//			predecessor become each others successor and predecessor. If
//			the deleted element had a predecessor, then make it the new
// 			current element; otherwise, make the first element current if
// 			it exists. The value of the deleted element is returned.
//          error code priority: ERROR_INVALID_LIST, ERROR_NULL_PTR,
//			                     ERROR_EMPTY_LIST, ERROR_NO_CURRENT

extern void lstInsertBefore (ListPtr psList, const void *pBuffer,
														 int size);
// requires: List is not full
// results:  If the list is not empty, insert the new element as the
//           predecessor of the current element and make the inserted
//           element the current element; otherwise, insert element
//           and make it current.
//           error code priority: ERROR_INVALID_LIST, ERROR_NULL_PTR,
//			     				  ERROR_NO_CURRENT

extern void lstUpdateCurrent (ListPtr psList, const void *pBuffer,
														  int size);
// requires: List is not empty
// results:  The value of pBuffer is copied into the current element
//           error code priority: ERROR_INVALID_LIST, ERROR_NULL_PTR,
//					              ERROR_EMPTY_LIST, ERROR_NO_CURRENT
// IMPORTANT: user could update with smaller, larger, or the same size data
//			  so free data, then reallocate based on size before updating

extern void lstReverse(ListPtr psList); // optional. Reverses the List

#endif /* LIST_H_ */

