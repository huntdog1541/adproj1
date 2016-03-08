/*
 * error.h
 *
 *  Created on: Jan 23, 2016
 *      Author: dhunt
 */
 #include <stdio.h>
 #include <stdlib.h>
 #include "global.h"
 #include "parser.h"
 #include "lexer.h"


#ifndef ERROR_H_
#define ERROR_H_



/* error - adds the message, line number, and line position
 * return - no return value
 */
void error(struct content * con);

/*
 *  Fatal Error is an error function that exits after printing error message
 *  return - no value returned
 */
void fatalError(struct content * con);

/* addError - add error messages to the content;
 * return - no value returned
 */
void addError(struct content * con);

/* findErrorMessage - finds the last error message
 * return - returns error message structure
 */
struct err * findErrorMessage(struct content * con);

/* printAllErrors - goes through the list of errors and prints them out one by one
 * return - no value returned
 */
void printAllErrors(struct content * con);

/* printSingleError - prints out a single error message as it goes through the list
 * return - no value returned
 */
void printSingleError(struct err * er);

/* insertError - inserts error message in to error list
 * return - no value returned
 */
void insertError(char * str, struct content * con);

#endif /* ERROR_H_ */
