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
	int canAddID;
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

int declareData(struct content * con);

int beginProgramParse(int tok, struct content * con);

int declareData(struct content * con);

int progStatement(int tok, struct content * con);

void controlIf(int tok, struct content * con);

void controlWhile(int tok, struct content * con);

int controlExpression(struct content * con);

int controlExpressionTail(int tok, struct content * con);

int controlCondition(struct content * con);


void controlID(int tok, struct content * con);

int matchOperator(int t, struct content * con);

void startProgram(struct content * con);

int matchToken(int tokenValue, struct content * con);

#endif /* PARSER_H_ */
