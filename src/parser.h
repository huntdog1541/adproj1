/*
 * parser.h
 *
 *  Created on: Jan 23, 2016
 *      Author: dhunt
 */
#include <stdio.h>
#include <stdlib.h>
#include "global.h"

#ifndef PARSER_H_
#define PARSER_H_

struct err {
	char mess[BSIZE];
	int lineNumber;
	int posNumber;
	struct err * nextMessage;
};

struct content {
	char fileName[BSIZE];
	int lineNumber;
	int positionNumber;
	char errorMessage[BSIZE];
	int isDone;
	char outputFile[BSIZE];
	struct err * error;
	int errorNumber;
};

/* parser - parser takes the steps to initialize steps
 * return - return 0 if error, else returns 1
 */
int parser(char * fileName);

/* contentInit - initializes the struct content
 * return - returns no value
 */
void contentInit(struct content * con);

/* startParse - starts the parsing steps
* return - return 0 if error, else returns 1
*/
int startParse();

/*
 *
 */
void findProgram();

#endif /* PARSER_H_ */
