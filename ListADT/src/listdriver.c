/**************************************************************************
 File name:  	listdriver.c
 Author:     	Cayden Wagner
 Date:				9/21/21
 Class:				CS300
 Assignment:	ListADT
 Purpose:			Create a functional linked list
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "../include/list.h"

/****************************************************************************
 Function: 	 		success

 Description: 	print a success message

 Parameters:		pszStr - the message to print

 Returned:	 		none
 ****************************************************************************/
static void success(char *pszStr) {
	printf("SUCCESS: %s\n", pszStr);
}

/****************************************************************************
 Function: 	 		failure

 Description:		print a failure message

 Parameters:		pszStr - the message to print

 Returned:	 		none
 ****************************************************************************/
static void failure(char *pszStr) {
	printf("FAILURE: %s\n", pszStr);
}

/****************************************************************************
 Function: 		 	assert

 Description: 	if the expression is true, assert success; otherwise, assert
 	 	 	 					failure

 Parameters:		szStr - the message to print

 Returned:	 		none
 ****************************************************************************/
static void assert(bool bExpression, char *pTrue, char *pFalse) {
	if (bExpression) {
		success(pTrue);
	} else {
		failure(pFalse);
	}
}

/**************************************************************************
 Function: 		 	main

 Description: 	test all the functionality of the list
 Parameters:		none

 Returned:	 		Exit Status
 *************************************************************************/

int main() {
  List sMyList;
  char num1 = '1', num2 = '2', num3 = '3', num4 = '4', char1 = 'a';
  char value;

  lstLoadErrorMessages();
  success("Loaded Error Messages");

  lstCreate(&sMyList);

//Purposefully triggering errors in each function
//  lstCreate(NULL);
//
//  lstInsertAfter(NULL, &num1, sizeof(char));
//  lstInsertAfter(&sMyList, NULL, sizeof(char));
//  lstInsertAfter(&sMyList, &num1, sizeof(char));
//  lstNext(&sMyList);
//  lstInsertAfter(&sMyList, &num1, sizeof(char));

//  lstPeek(NULL, &value, sizeof(char));
//  lstPeek(&sMyList, &num1, sizeof(char));
//  lstInsertAfter(&sMyList, &num1, sizeof(char));
//  lstPeek(&sMyList, NULL, sizeof(char));

//  lstSize(NULL);

//  lstTerminate(NULL);

//  lstIsEmpty(NULL);
//  lstFirst(NULL);
//  lstFirst(&sMyList);

  assert(lstIsEmpty(&sMyList), "Stack size is Empty", "Stack size is NOT Empty");

  lstInsertAfter(&sMyList, &num1, sizeof(char));
  lstPeek(&sMyList, &value, sizeof(char));

  assert(lstSize(&sMyList) == 0, "Stack size is 0", "Stack size is NOT 0");
  assert(lstSize(&sMyList) == 1, "Stack size is 1", "Stack size is NOT 1");

  assert(lstIsEmpty(&sMyList), "Stack size is Empty", "Stack size is NOT Empty");

  printf("%c\n", value);

  lstInsertAfter(&sMyList, &num2, sizeof(char));
  lstPeek(&sMyList, &value, sizeof(char));

  printf("%c\n", value);

  lstInsertAfter(&sMyList, &num3, sizeof(char));
  lstPeek(&sMyList, &value, sizeof(char));

  printf("%c\n", value);

  lstInsertAfter(&sMyList, &num4, sizeof(char));
  lstPeek(&sMyList, &value, sizeof(char));

  printf("%c\n", value);

  lstFirst(&sMyList);
  lstPeek(&sMyList, &value, sizeof(char));

  printf("%c\n", value);

  lstInsertAfter(&sMyList, &char1, sizeof(char));
  lstPeek(&sMyList, &value, sizeof(char));

  printf("%c\n", value);

  lstNext(&sMyList);
  lstPeek(&sMyList, &value, sizeof(char));

  printf("%c\n", value);

  lstFirst(&sMyList);

  for(int i = 0; i < lstSize(&sMyList); i++)
  {
  	lstPeek(&sMyList, &value, sizeof(char));
  	printf("%c\n", value);

  	lstNext(&sMyList);
  }

  lstTerminate(&sMyList);

  assert(lstIsEmpty(&sMyList), "Stack size is Empty", "Stack size is NOT Empty");

  assert(lstSize(&sMyList) == 0, "Stack size is 0", "Stack size is NOT 0");
  assert(lstSize(&sMyList) == 1, "Stack size is 1", "Stack size is NOT 1");

  printf("Successful");

  return EXIT_SUCCESS;
}
