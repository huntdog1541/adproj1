/*
 * parser.c
 *
 *  Created on: Jan 23, 2016
 *      Author: dhunt
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "global.h"
#include "parser.h"
#include "error.h"
#include "symbol.h"

#define ELSE 305
#define END_WHILE 309
#define END_IF 306
#define OPERATOR 412
#define COMPARATOR 413

/* parser - parser takes the steps to initialize steps
 * return - return 0 if error, else returns 1
 */
int parser(char * fileName)
{
	puts("Parser ran");
	contentInit(&con);
	strcpy(con.fileName, fileName);
	startParse();
	printf("Successful Parse\n");
	return 0;
}

/* contentInit - initializes the struct content
 * return - returns no value
 */
void contentInit(struct content * con)
{
	int i;
	con->lineNumber = 0;
	con->positionNumber = 0;
	con->isDone = 0;
	con->canAddID = 0;
	for(i = 0; i < BSIZE; i++)
	{
		con->fileName[i] = '\0';
		con->errorMessage[i] = '\0';
		con->outputFile[i] = '\0';
	}
}

/* startParse - starts the parsing steps
* return - return 0 if error, else returns 1
*/
int startParse(struct content * con)
{
	int ans = 0, t = 0;
	openLexFile();
	while(!matchToken(PROGRAM))
	{
		getNextToken();
	}
	getNextToken();
	if(matchToken(INT))
	{
		declareData();
	}
	if(matchToken(BEGIN))
	{
		beginProgramParse();
	}
	else
	{
		strcpy(con->errorMessage, "No Statements to run\n");
		error(con);
	}
	return ans;
}

/* beginProgramParse - starts parsing statement after the begin keyword
 * return - returns the value of token not absorbed
 */
void beginProgramParse(int tok)
{
	if(matchToken(BEGIN))
	{
		getNextToken();
		while((!con.isDone) && (matchToken(END)))
		{
			progStatement(tok);
		}
	}
	return;
}

/*
 * declareData - adds id names to symbol table as well as initialize data
 * return - returns the token value for the next token not absorbed
 */
void declareData()
{
		con.canAddID = 1;
		while(matchToken(INT))
		{
				if(matchToken(ID))
				{
					getNextToken();
					if(matchToken(ASSIGNMENT))
					{
						if(!matchToken(NUMERICAL_CONSTANT))
						{
							strcpy(con->errorMessage, "Invalid Initialization statement\n");
							error(con);
						}
						getNextToken();
						if(matchToken(COMMA))
						{
							getNextToken();
						}
						if(matchToke(SEMICOLON))
						{
							getNextToken();
						}
					}
					else if(matchToken(COMMA))
					{
						getNextToken();
						continue;
					}
					else if(matchToken(SEMICOLON))
					{
						getNextToken();
					}
					else
					{
						strcpy(con->errorMessage, "Invalid Assignment statement\n");
						error(con);
					}
				}
				else
				{
					strcpy(con->errorMessage, "Didn't find ID");
					error(con);
				}
		}
		con.canAddID = 0;
		return;
}

/* progStatement - checks how to evaluate the next statement (IF, WHILE, or EXPRESSION)
 * return - returns the value of token not absorbed
 */
void progStatement()
{
	switch(tokenval.tokenNumber)
	{
		case ID:
				controlID();
				break;
		case IF:
				controlIf();
				break;
		case WHILE:
				controlWhile();
				break;
		case END:
					con.isDone = 1;
				break;
		default:
			strcpy(con->errorMessage, "Could not find valid statement\n");
			error(con);
			break;
	}
	return;
}

/* controlIf - absorbs the if expression in the program
 * return - no return value
 */
void controlIf()
{
		if(matchToke(IF))
		{
			if(controlCondition(con))
			{
				getNextToken(con);
				while((!matchToken(ELSE)) && (!matchToken(END_IF)))
				{
					progStatement();
				}
				if(matchToken(ELSE))
				{
						getNextToken(con);
						while((!matchToke(END_IF)) && (con.isDone == 0))
						{
							progStatement();
						}
						if(!matchToken(END_IF))
						{
							strcpy(con->errorMessage, "Invalid End of While loop\n");
							error(con);
						}
				}
				else if(matchToken(END_IF))
				{

				}
			}
			else
			{
				strcpy(con->errorMessage, "Invalid Expression\n");
				error(con);
			}
		}
}

/* controlWhile - absorbs the while expression in the program
 * return - no return
 */
void controlWhile()
{
	if(matchToken(WHILE))
	{
		if(controlCondition(con))
		{
			matchToken(DO);
			getNextToken();
			while((!matchToken(END_WHILE)) && (con.isDone == 0))
			{
				progStatement();
			}
			if(matchToken(END_WHILE))
			{
				//Do Nothing
			}
			else
			{
				strcpy(con->errorMessage, "Invalid End of While loop\n");
				error(con);
			}
		}
	}
}

/* controlExpression - absorbs an expression statement in the program
 * return - returns the value of the token not absorbed
 */
void controlExpression()
{
	int answer = 0;
	getNextToken();
	if((matchToken(ID)) || (matchToken(NUMERICAL_CONSTANT)))
	{
		getNextToken();
		if(!controlExpressionTail())
		{
			strcpy(con->errorMessage, "Error handling expression tail\n");
			error(con);
		}
	}
	return;
}

/* controlExpressionTail - absorbs the end of the expression, allows for longer expressions
 * return - returns the value of the token not absorbed
 */
int controlExpressionTail()
{
	int answer = 0;
	if(matchOperator() == OPERATOR)
	{
		getNextToken();
		if(!(matchToken(ID)) && !(matchToken(NUMERICAL_CONSTANT)))
		{
			strcpy(con->errorMessage, "Didn't find second id or number\n");
			error(con);
		}
		getNextToken();
		if(matchToken(SEMICOLON))
				answer = 1;
		else
				answer = controlExpressionTail();
	}
	else
	{
		strcpy(con->errorMessage, "Error with Expression tail\n");
		error(con);
	}
	return answer;
}

/* controlCondition - absorbs the test conditions before a control loop
 * return - returns 0 if false, and 1 if true
 */
void controlCondition()
{
	int answer = 0;
	getNextToken();
	if((matchToken(ID)) || (matchToken(NUMERICAL_CONSTANT)))
	{
		getNextToken(con);
		if(matchOperator() == COMPARATOR)
		{
			getNextToken();
			if(!(match(ID) && !(match(NUMERICAL_CONSTANT))
			{
				strcpy(con->errorMessage, "Didn't find ending id or number\n");
				error(con);
			}
			matchToken(SEMICOLON);
			answer = 1;
		}
		else
		{
			strcpy(con->errorMessage, "Didn't find comparator\n");
			error(con);
		}
	}
	return;
}

/*  controlID - absorbs the expression that starts with an ID token
 * return - no return
 */
void controlID()
{
		if(matchToken(ID))
		{
			if(matchToken(ASSIGNMENT))
			{
				if(controlExpression())
				{

				}
			}
		}
}

/* matchOperator - returns the value of operator or comparator according to the token's group
 * return - returns either OPERATOR, COMPARATOR, or SEMICOLON
 */
int matchOperator(struct content * con)
{
	int ans = 0;
	switch(tokenval.tokenNumber)
	{
		case ADDITION:
		case SUBTRACTION:
		case DIVISION:
		case MODUS:
		case MULTIPLICATION:
				 ans = OPERATOR;
				 break;
		case GREATERTHAN:
		case GREATERTHANANDEQUAL:
		case LESSERTHAN:
		case LESSERTHANANDEQUAL:
		case STRINGEQUAL:
				ans = COMPARATOR;
				break;
		case SEMICOLON:
				ans = SEMICOLON;
				break;
		default:
				strcpy(con->errorMessage, "Couldn't find Operator or Comparator\n");
				error(con);
				break;
	}
	return ans;
}

/* matchToken - compares a token value to the value expected
 * return - returns 0 if false and 1 if true
 */
int matchToken(int tokenValue, struct content * con)
{
	int answer = 0;
	if(tokenval.tokenNumber == tokenValue)
		answer = 1;
	else
	{
		sprintf(con->errorMessage, "Error expect token type value of %d but got %d\n", tokenValue, tokenval.tokenNumber);
		error(con);
	}
	return answer;
}
