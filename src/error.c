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
#include "parser.h" 

 void error(struct content * con)
 {
   fprintf(stderr, "Error at line %d position %d :%s \n", con->lineNumber, con->positionNumber, con->errorMessage);
   exit(1);
 }

 void fatalError(struct content * con)
 {
	 fprintf(stderr, "Error: %s\n Exiting\n", con->errorMessage);
	 exit(1);
 }

 void addError(struct content * con)
 {
 	struct err * temp = con->error;
 	if(con->errorNumber > 0)
 	{
 		temp = findErrorMessage(con);
 	}
 	else
 	{
 		con->error = (struct err*)malloc(sizeof(struct err));
 		temp = con->error;
 	}
 	strcpy(temp->mess, con->errorMessage);
 	temp->lineNumber = con->lineNumber;
 	temp->posNumber = con->positionNumber;
 	con->errorNumber++;
 }

struct err * findErrorMessage(struct content * con)
{
	struct err * temp = con->error;
	while(temp->nextMessage != NULL)
	{
		temp = temp->nextMessage;
	}
	return temp;
}

void printAllErrors(struct content * con)
{
	if(con->errorNumber == 0)
		printf("Success! No Errors\n");

	struct err * temp = con->error;
	printSingleError(temp);
	while(temp->nextMessage != NULL)
		temp = temp->nextMessage;
}

void printSingleError(struct err * er)
{
	fprintf(stderr, "%s\n", er->mess);
	fprintf(stderr, "at line number: %d and position: %d\n", er->lineNumber, er->posNumber);
}
