/*
 * error.c
 *
 *  Created on: Jan 23, 2016
 *      Author: dhunt
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error.h"
#include "lexer.h"
#include "parser.h"

/* error - adds the message, line number, and line position
 * return - no return value
 */
 void error(struct content * con)
 {
   fprintf(stderr, "Error at line %d position %d :%s \n\n", con->lineNumber, con->positionNumber, con->errorMessage);
   fclose(fin);
   fclose(fout);
   exit(1);
 }

 /*
  *  Fatal Error is an error function that exits after printing error message
  *  return - no value returned
  */
 void fatalError(struct content * con)
 {
	 fprintf(stderr, "Error: %s\n Exiting\n", con->errorMessage);
	 exit(1);
 }

 /* insertError - inserts error message in to error list
  * return - no value returned
  */
 void insertError(char * str, struct content * con)
 {
	 sprintf(con->errorMessage, "Error at line %d position %d : %s \n", con->lineNumber, con->positionNumber, con->errorMessage);
	 addError(con);
 }

 /* addError - add error messages to the content;
  * return - no value returned
  */
 void addError(struct content * con)
 {
 	struct err * temp = findErrorMessage(con);

 	temp->nextMessage = (struct err*)malloc(sizeof(struct err));
 	temp = temp->nextMessage;
 	strcpy(temp->mess, con->errorMessage);
 	temp->lineNumber = con->lineNumber;
 	temp->posNumber = con->positionNumber;
 	con->errorNumber++;
 }

 /* findErrorMessage - finds the last error message
  * return - returns error message structure
  */
struct err * findErrorMessage(struct content * con)
{
	struct err * temp = con->error;
	while(temp->nextMessage != NULL)
	{
		temp = temp->nextMessage;
	}
	return temp;
}

/* printAllErrors - goes through the list of errors and prints them out one by one
 * return - no value returned
 */
void printAllErrors(struct content * con)
{
	if(con->errorNumber == 0)
		printf("Success! No Errors\n");

	struct err * temp = con->error;
	printSingleError(temp);
	while(temp->nextMessage != NULL)
		temp = temp->nextMessage;
}

/* printSingleError - prints out a single error message as it goes through the list
 * return - no value returned
 */
void printSingleError(struct err * er)
{
	fprintf(stderr, "%s\n", er->mess);
	fprintf(stderr, "at line number: %d and position: %d\n", er->lineNumber, er->posNumber);
}
