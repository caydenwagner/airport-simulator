/**************************************************************************
 File name:  	listdriver.c
 Author:     	Cayden Wagner
 Date:			9/21/21
 Class:			CS300
 Assignment:
 Purpose:
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "../include/list.h"

/****************************************************************************
 Function: 	 	success

 Description: 	print a success message

 Parameters:	pszStr - the message to print

 Returned:	 	none
 ****************************************************************************/
static void success(char *pszStr) {
	printf("SUCCESS: %s\n", pszStr);
}

/****************************************************************************
 Function: 	 	failure

 Description:	print a failure message

 Parameters:	pszStr - the message to print

 Returned:	 	none
 ****************************************************************************/
static void failure(char *pszStr) {
	printf("FAILURE: %s\n", pszStr);
}

/****************************************************************************
 Function: 	 	assert

 Description: 	if the expression is true, assert success; otherwise, assert
 	 	 	 	failure

 Parameters:	szStr - the message to print

 Returned:	 	none
 ****************************************************************************/
static void assert(bool bExpression, char *pTrue, char *pFalse) {
	if (bExpression) {
		success(pTrue);
	} else {
		failure(pFalse);
	}
}

/**************************************************************************
 Function: 	 	main
 Description: 	test all the functionality of the list
 Parameters:	none
 Returned:	 	Exit Status
 *************************************************************************/

int main() {
  List sMyList;
  int num1 = 1, num2 = 2, num3 = 3;

  lstLoadErrorMessages();
  success("Loaded Error Messages");

  lstCreate(&sMyList);

  lstInsertAfter(&sMyList, &num1, sizeof(int));
  lstInsertAfter(&sMyList, &num2, sizeof(int));
  lstInsertAfter(&sMyList, &num3, sizeof(int));




  printf("Successful");

  return EXIT_SUCCESS;
}

