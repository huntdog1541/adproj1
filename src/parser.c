/*
 * parser.c
 *
 *  Created on: Jan 23, 2016
 *      Author: dhunt
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "lexer.h"
#include "global.h"
#include "error.h"
#include "symbol.h"

/* parser - parser takes the steps to initialize steps
 * return - return 0 if error, else returns 1
 */
int parser(char * fileName)
{
	puts("Parser ran");
	struct content con;
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
	con->isDone =0;
	con->canAddID = 0;
	for(i = 0; i < BSIZE; i++)
	{
		con->fileName[i] = 0;
		con->errorMessage[i] = 0;
		con->outputFile[i] = 0;
	}
}

/* startParse - starts the parsing steps
* return - return 0 if error, else returns 1
*/
int startParse(struct content * con)
{
	int ans = 0, t = 0;
	openLexFile(con);
	while(!matchToken(PROGRAM, con))
	{
		t = getNextToken(con);
	}
	t = getNextToken(con);
	if(t == INT)
	{
		t = declareData(con);
	}
	if(t == BEGIN)
	{
		t = beginProgramParse(t, con);
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
int beginProgramParse(int tok, struct content * con)
{
	if(tok == BEGIN)
	{
		tok = getNextToken(con);
		while((!con->isDone) && (tok != END))
		{
			tok = progStatement(tok, con);
		}
	}
	return tok;
}

/*
 * declareData - adds id names to symbol table as well as initialize data
 * return - returns the token value for the next token not absorbed
 */
int declareData(struct content * con)
{
		con->canAddID = 1;
		int t = INT;   //Already checked in previous function
		while(t == INT)
		{
				if(matchToken(ID, con))
				{
					t = getNextToken(con);
					if(t == ASSIGNMENT)
					{
						if(!matchToken(NUMERICAL_CONSTANT, con))
						{
							strcpy(con->errorMessage, "Invalid Initialization statement\n");
							error(con);
						}
						t = getNextToken(con);
						if(t == COMMA)
						{
							t = INT;
						}
						if(t == SEMICOLON)
						{
							t = getNextToken(con);
						}
					}
					else if(t == COMMA)
					{
						t = INT;
						continue;
					}
					else if(t == SEMICOLON)
					{
						t = getNextToken(con);
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
		con->canAddID = 0;
		return t;
}

/* progStatement - checks how to evaluate the next statement (IF, WHILE, or EXPRESSION)
 * return - returns the value of token not absorbed
 */
int progStatement(int tok, struct content * con)
{
	switch(tok)
	{
		case ID:
				controlID(tok, con);
				break;
		case IF:
				controlIf(tok, con);
				break;
		case WHILE:
				controlWhile(tok, con);
				break;
		case END:
					con->isDone = 1;
				break;
		default:
			strcpy(con->errorMessage, "Could not find valid statement\n");
			error(con);
			break;
	}
	return getNextToken(con);
}

/* controlIf - absorbs the if expression in the program
 * return - no return value
 */
void controlIf(int tok, struct content * con)
{
		if(tok == IF)
		{
			if(controlCondition(con))
			{
				tok = getNextToken(con);
				while((tok != ELSE) && (tok != END_IF))
				{
					tok = progStatement(tok, con);
				}
				if(tok == ELSE)
				{
						tok = getNextToken(con);
						while((tok !=  END_IF) && (con->isDone == 0))
						{
							tok = progStatement(tok, con);
						}
						if(tok != END_IF)
						{
							strcpy(con->errorMessage, "Invalid End of While loop\n");
							error(con);
						}
				}
				else if(tok == END_IF)
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
void controlWhile(int tok, struct content * con)
{
	if(tok == WHILE)
	{
		if(controlCondition(con))
		{
			matchToken(DO, con);
			tok = getNextToken(con);
			while((tok != END_WHILE) && (con->isDone == 0))
			{
				tok = progStatement(tok, con);
			}
			if(tok == END_WHILE)
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
int controlExpression(struct content * con)
{
	int answer = 0, t = getNextToken(con);
	if((t == ID) || (t == NUMERICAL_CONSTANT))
	{
		t = getNextToken(con);
		if(!controlExpressionTail(t, con))
		{
			strcpy(con->errorMessage, "Error handling expression tail\n");
			error(con);
		}
	}
	return answer;
}

/* controlExpressionTail - absorbs the end of the expression, allows for longer expressions
 * return - returns the value of the token not absorbed
 */
int controlExpressionTail(int tok, struct content * con)
{
	int answer = 0;
	if(matchOperator(tok, con) == OPERATOR)
	{
		tok = getNextToken(con);
		if(!(tok == ID) && !(tok == NUMERICAL_CONSTANT))
		{
			strcpy(con->errorMessage, "Didn't find second id or number\n");
			error(con);
		}
		tok = getNextToken(con);
		if(tok == SEMICOLON)
				answer = 1;
		else
				answer = controlExpressionTail(tok, con);
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
int controlCondition(struct content * con)
{
	int answer = 0, t = getNextToken(con);
	if((t == ID) || (t == NUMERICAL_CONSTANT))
	{
		t = getNextToken(con);
		if(matchOperator(t, con) == COMPARATOR)
		{
			t = getNextToken(con);
			if(!(t == ID) && !(t == NUMERICAL_CONSTANT))
			{
				strcpy(con->errorMessage, "Didn't find ending id or number\n");
				error(con);
			}
			matchToken(SEMICOLON, con);
			answer = 1;
		}
		else
		{
			strcpy(con->errorMessage, "Didn't find comparator\n");
			error(con);
		}
	}
	return answer;
}

/*  controlID - absorbs the expression that starts with an ID token
 * return - no return
 */
void controlID(int tok, struct content * con)
{
		if(tok == ID)
		{
			if(matchToken(ASSIGNMENT, con))
			{
				if(controlExpression(con))
				{

				}
			}
		}
}

/* matchOperator - returns the value of operator or comparator according to the token's group
 * return - returns either OPERATOR, COMPARATOR, or SEMICOLON
 */
int matchOperator(int t, struct content * con)
{
	int ans = 0;
	switch(t)
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
	int temp = getNextToken(con);
	if(temp == tokenValue)
		answer = 1;
	else
	{
		sprintf(con->errorMessage, "Error expect token type value of %d but got %d\n", tokenValue, temp);
		error(con);
	}
	return answer;
}
