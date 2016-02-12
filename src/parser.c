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

int parser(char * fileName)
{
	puts("Parser ran");
	struct content con;
	contentInit(&con);
	//printSymbol();
	strcpy(con.fileName, fileName);
	//lex(&con);
	startParse();
	//printSymbol();
	printf("Successful Parse\n");
	return 0;
}

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

void findProgram()
{

}

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
			error("Could not find valid Statement\n");
			break;
	}
	return getNextToken(con);
}

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

int controlExpression(struct content * con)
{
	int answer = 0, t = getNextToken(con);
	if((t == ID) || (t == NUMERICAL_CONSTANT))
	{
		if(matchOperator(con) == OPERATOR)
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
			strcpy(con->errorMessage, "Didn't find operator\n");
			error(con);
		}
	}
	return answer;
}

int controlCondition(struct content * con)
{
	int answer = 0, t = getNextToken(con);
	if((t == ID) || (t == NUMERICAL_CONSTANT))
	{
		if(matchOperator(con) == COMPARATOR)
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

int matchOperator(struct content * con)
{
	int ans = 0, t = getNextToken(con);
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
		default:
				break;
	}
	return ans;
}

void startProgram(struct content * con)
{
		con->canAddID = 0;
		int t = getNextToken(con);
}

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
}
