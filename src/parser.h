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

struct content con;
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
 * declareData - adds id names to symbol table as well as initialize data
 * return - returns the token value for the next token not absorbed
 */
void declareData(struct content * con);

/* beginProgramParse - starts parsing statement after the begin keyword
 * return - returns the value of token not absorbed
 */
void beginProgramParse(int tok, struct content * con);

/* progStatement - checks how to evaluate the next statement (IF, WHILE, or EXPRESSION)
 * return - returns the value of token not absorbed
 */
void progStatement(int tok, struct content * con);

/* controlIf - absorbs the if expression in the program
 * return - no return value
 */
void controlIf(int tok, struct content * con);

/* controlWhile - absorbs the while expression in the program
 * return - no return
 */
void controlWhile(int tok, struct content * con);

/* controlExpression - absorbs an expression statement in the program
 * return - returns the value of the token not absorbed
 */
void controlExpression(struct content * con);

/* controlExpressionTail - absorbs the end of the expression, allows for longer expressions
 * return - returns the value of the token not absorbed
 */
void controlExpressionTail(int tok, struct content * con);

/* controlCondition - absorbs the test conditions before a control loop
 * return - returns 0 if false, and 1 if true
 */
void controlCondition(struct content * con);

/*  controlID - absorbs the expression that starts with an ID token
 * return - no return
 */
void controlID(int tok, struct content * con);

/* matchOperator - returns the value of operator or comparator according to the token's group
 * return - returns either OPERATOR, COMPARATOR, or SEMICOLON
 */
int matchOperator(int t, struct content * con);

/* matchToken - compares a token value to the value expected
 * return - returns 0 if false and 1 if true
 */
int matchToken(int tokenValue, struct content * con);


#endif /* PARSER_H_ */
