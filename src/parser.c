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
		declareData(con);
	}
	else if(t == BEGIN)
	{

	}
	else
	{

	}
	return ans;
}

void findProgram()
{

}

void beginParse(struct content * con)
{
	int t = 0;




}

void declareData(struct content * con)
{
		con->canAddID = 1;
		int t = INT;   //Already checked in previous function
		while(t == INT)
		{
				if(matchToken(ID, con))
				{
					if(matchToken(ASSIGNMENT, con))
					{
						if(!matchToken(NUMERICAL_CONSTANT, con))
						{
							strcpy(con->errorMessage, "Invalid Initialization statement\n");
							error(con);
						}
						if(matchToken(COMMA, con))
						{
							t = INT;
						}
					}
					else if(COMMA)
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
}

void progStatement(struct content * con)
{
	int t = getNextToken(con);
	switch(t)
	{
		case ID:
				break;
		case IF:
				break;
		case WHILE:
				break;
		case END:
					con->isDone = 1;
				break;
		default:
			error("Could not find valid Statement\n");
			break;
	}
}

void controlIf(struct content * con)
{

}

void controlWhile(struct content * con)
{

}

void controlID(struct content * con)
{
		int t = ID;
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
	if(temp == SINGLECOMMENT)
			absorbSingleLine(con);
	else if(temp == STARTMULTIPLECOMMENT)
			absorbMultComment(con);
	else if(temp == tokenValue)
		answer = 1;
	else
	{
		sprintf(con->errorMessage, "Error expect token type value of %d but got %d\n", tokenValue, temp);
		error(con);
	}
}

void absorbSingleLine(struct content * con)
{
	int temp = getNextToken(con);
	while(temp != END_OF_LINE)
	{
		temp = getNextToken(con);
	}
}

void absorbMultLineComment(struct content * con)
{
	int temp = getNextToken(con);
	while(temp != ENDMULTIPLECOMMENT)
	{
		temp = getNextToken(con);
	}
}
