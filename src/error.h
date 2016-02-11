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
 */
void fatalError(struct content * con);

/* addError - add error messages to the content;
 *
 */
void addError(struct content * con);

/*
 *
 */
struct err * findErrorMessage(struct content * con);

void printAllErrors(struct content * con);

void printSingleError(struct err * er);

void insertError(char * str, struct content * con);

#endif /* ERROR_H_ */
