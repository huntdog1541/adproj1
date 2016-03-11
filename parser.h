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
//global variable that will hold important variables
struct content con;

//file pointer to file output
FILE * fout;


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
void startParse();


/*
 * declareData - adds id names to symbol table as well as initialize data
 * return - returns the token value for the next token not absorbed
 */
void declareData();

/*
 * controlWrite - writes generated code for write function
 * return - no return value
 */
void controlWrite();

/*
 * controlRead - writes generated code for a read function
 * return - no return value
 */
void controlRead();

/*
 * ifControlWrite - a control write function inside a if statement
 * return - no return value
 */
void ifControlWrite(char * string);

/*
 * ifControlRead - a read statement inside a if statement - writes generated code to string
 * return - no return value
 */
void ifControlRead(char * string);

/*
 * declaration - declares integers into the program
 * return - no return value
 */
void declaration();

/*
 * declarAssignment - assigns a number to the variable previoouly declared
 * return - no return value
 */
void declarAssignment();

/* beginProgramParse - starts parsing statement after the begin keyword
 * return - returns the value of token not absorbed
 */
void beginProgramParse();

/* progStatement - checks how to evaluate the next statement (IF, WHILE, or EXPRESSION)
 * return - returns the value of token not absorbed
 */
void progStatement();

/*
 * ifProgStatement - statement selector inside a if statement - all generated code is written to the string
 * return - no return value
 */
void ifProgStatement(char * string);

/* controlIf - absorbs the if expression in the program
 * return - no return value
 */
void controlIf();

/* ifControlIf - absorbs the if expression in the program
 * return - no return value
 */
void ifControlIf(char * string);

/* controlWhile - absorbs the while expression in the program
 * return - no return
 */
void controlWhile();

/* controlWhile - absorbs the while expression in the program
 * return - no return
 */
void ifControlWhile(char * string);

/* controlExpression - absorbs an expression statement in the program
 * return - returns the value of the token not absorbed
 */
int controlExpression();

/* controlExpressionTail - absorbs the end of the expression, allows for longer expressions
 * return - returns the value of the token not absorbed
 */
int controlExpressionTail();

/* controlCondition - absorbs the test conditions before a control loop
 * return - returns 0 if false, and 1 if true
 */
int controlCondition();

/* controlIfCondition - absorbs the test conditions before a control loop
 * return - returns 0 if false, and 1 if true
 */
int controlIfCondition(char * string);

/*
 * controlWhileCondition - a condition for a while statement
 * return - returns 1 if success
 */
int controlWhileCondition(char * string);

/*  controlID - absorbs the expression that starts with an ID token
 * return - no return
 */
void controlID();

/*  ifControlID - absorbs the expression that starts with an ID token in if statement
 * return - no return
 */
void ifControlID(char * string);

/* matchOperator - returns the value of operator or comparator according to the token's group
 * return - returns either OPERATOR, COMPARATOR, or SEMICOLON
 */
int matchOperator();

/* matchToken - compares a token value to the value expected
 * return - returns 0 if false and 1 if true
 */
int matchToken(int tokenValue);
/*
 * errorReport - formats the string for error report then calls error
 * return - no return value
 */
void errorReport(int tokenValue);

#endif /* PARSER_H_ */
