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
	printSymbol();
	strcpy(con.fileName, fileName);
	//lex(&con);
	startParse();
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
	if(!con->isDone)
	{
		t = getNextToken(con);
		printf("The token returned is %d\n", t);
		while(t != PROGRAM)
				t = getNextToken(con);
		declareData(con);
	}
	return ans;
}

void findProgram()
{

}

void declareData(struct content * con)
{
		con->canAddID = 1;
		int t = getNextToken(con);
		while(t == INT)
		{
				t = getNextToken(con);
				if(t == ID)
				{

				}
				else
				{
					strcpy(con->errorMessage, "Didn't find ID");
					error(con);
				}
		}
}

void initializeData(struct content * con)
{
	int t = getNextToken(con);

}

void startProgram(struct content * con)
{
		con->canAddID = 0;
		int t =getNextToken(con);

}
