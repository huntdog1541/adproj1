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
		//printf("%c", t);
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
			ungetc(t, fin);
			getID(con);
		}
		else if(t == EOF)
			con->isDone = 1;
		else {
			tokenval = NONE;
			printf("  %c:%d\n", t, t);
		}

		t = fgetc(fin);
	}
	printf("\n");
	fclose(fin);
	return 0;
}

void getID(struct content * con)
{
		int i = 0, p = 0;
		char temp = fgetc(fin);
		char lexbuf[BSIZE];
		while(isalnum(temp))
		{
			lexbuf[i] = temp;
			i++;
			temp = fgetc(fin);
			if(temp == '_')
			{
				printf("Found underscore\n");
				if(isalnum(lookahead(con)))
				{
					lexbuf[i++] = temp;
					temp = fgetc(fin);
				}
				else
				{
					fprintf(stderr, "Error\n");
				}
			}
			if(i >= BSIZE)
			{
				strcpy(con->errorMessage, "Exceeded buffer size");
				error(con);
			}
		}
		lexbuf[i] = EOS;
		if(temp == EOF)
		{
			ungetc(temp, fin);
			con->isDone = 1;
		}
		printf("got alpha[%s]\n", lexbuf);
		printAllString(lexbuf);
		p = lookup(lexbuf);
		if(p == NOT_FOUND)
			p = insert(lexbuf, ID);
		tokenval = p;
		printf("Token Value %d\n", tokenval);
		printf("%d\n", getTokenType(p));
}

/*
char * getToken(char * buffer, char t)
{
	int temp = t, i = 0;
	while(isValidID(t))
	{

	}
	return buffer;
}*/

int getNextToken(struct content * con)
{
	char temp;
	int p, b = 0, ans = 0;
	temp = fgetc(fin);
	if(temp == EOF)
	{
		con->isDone = 1;
		return 0;
	}
	if((temp == ' ') || (temp == '\t'))
	{
		absorbSpace(con);
		temp = fgetc(fin);
	}
  if(temp == '\n')
	{
		con->lineNumber++;
		temp = fgetc(fin);
	}
	if(isalnum(temp))
	{
		ungetc(temp, fin);
		getID(con);
		return 0;
	}
	if(isdigit(temp))
	{
		ungetc(temp, fin);
		getNumber();
		return 0;
	}
	int r = checkSpecialChar(temp);
	return r;
}

void absorbSpace(struct content * con)
{
	char temp = fgetc(fin);
	while((temp == ' ') || (temp == '/t'))
	{
		con->positionNumber++;
		temp = fgetc(fin);
	}
	ungetc(temp, fin);
}

char lookahead(struct content * con)
{
	char t = fgetc(fin);
	ungetc(t, fin);
	return t;
}


void getNumber()
{
	char t = fgetc(fin);
	char buffer[BSIZE];
	int i = 0;
	buffer[i++] = t;
	/*
	while(isDigit(t))
	{
		buffer[i++] = t;
		t = fgetc(fin);
	}
	*/
	ungetc(t, fin);
}


int checkSpecialChar(char temp)
{
	switch(temp)
	{
		case '=':
		case '/':
		case '+':
		case '-':
		default: break;
	}
	return 1;
}

void printAllString(char * string)
{
	int i, size = strlen(string);
	for(i = 0; i < size; i++)
	{
		printf("Char: %c :: Num: %d\n", string[i], string[i]);
	}
}
