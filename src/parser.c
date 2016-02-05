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
	lex(&con);
	return 0;
}

void contentInit(struct content * con)
{
	int i;
	con->lineNumber = 0;
	con->positionNumber = 0;
	con->isDone =0;
	for(i = 0; i < BSIZE; i++)
	{
		con->fileName[i] = 0;
		con->errorMessage[i] = 0;
		con->outputFile[i] = 0;
	}
}
