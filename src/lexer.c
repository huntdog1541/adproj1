/*
 * lexer.c
 *
 *  Created on: Jan 23, 2016
 *      Author: dhunt
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parser.h"
#include "symbol.h"
#include "lexer.h"
#include "error.h"

FILE * fin;
int tokenval = 0;

int lex(struct content * con)
{
	printf("File is %s \n", con->fileName);
	char lexbuf[BSIZE];
	fin = fopen(con->fileName, "r");
	if(!fin)
	{
		strcpy(con->errorMessage, "Can't open file");
		error(con);
	}
	int t = fgetc(fin);
	if(t == EOF)
	{
		strcpy(con->errorMessage, "Empty File");
		error(con);
	}
	while(con->isDone != 1)
	{
		printf("%c", t);
		if((t == ' ') && (t == '/t'))
		{
			con->positionNumber++;//Avoid whitespace
		}
		else if(t == '\n')
		{
				con->lineNumber++;
				con->positionNumber = 0;
		}
		else if(isalpha(t))
		{
			printf("found id\n");
			int p, b = 0;
			while(isalnum(t)){
				lexbuf[b] = t;
				t = fgetc(fin);
				b++;
				if(b >= BSIZE)
				{
					strcpy(con->errorMessage, "Exceeded buffer size");
					error(con);
				}
			}
			lexbuf[b] = EOS;
			if(t == EOF)
				ungetc(t, fin);
			printf("got alpha[%s]\n", lexbuf);
			p = lookup(lexbuf);
			if(p == NOT_FOUND)
				p = insert(lexbuf, ID);
			tokenval = p;
			printf("%d\n", getTokenType(p));
		}
		else if(t == EOF)
			con->isDone = 1;
		else {
			tokenval = NONE;
			printf("%c:%d\n", t, t);
		}

		t = fgetc(fin);
	}
	printf("\n");
	fclose(fin);
	return 0;
}
