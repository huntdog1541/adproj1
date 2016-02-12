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
	fin = fopen(con->fileName, "r");
	if(!fin)
	{
		strcpy(con->errorMessage, "Can't open file");
		fatalError(con);
	}
	int t = fgetc(fin);
	if(t == EOF)
	{
	strcpy(con->errorMessage, "Empty File");
	error(con);
	}

	printf("%c", t);
	if((t == ' ') || (t == '/t'))
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
	else if(isdigit(t))
	{
		ungetc(t, fin);
		getNumber(con);
	}
	else {
		checkSpecialChar(t, con);
		printf("  %c:%d\n", t, t);
	}
		t = fgetc(fin);
	printf("\n");
	fclose(fin);
	return 0;
}

/* openLexFile - sets the global file pointer
 * return - no return value
 */
void openLexFile(struct content * con)
{
	fin = fopen(con->fileName, "r");
	printf("File Name: %s\n", con->fileName);
	if(!fin)
	{
		perror("File Not Found\n");
		exit(EXIT_FAILURE);
	}
}

/* getID - gets the ID name from the file.
 * return - no return value, sets the tokenval integer.
 */
void getID(struct content * con)
{
		int i = 0, p = 0;
		char temp = fgetc(fin);
		char lexbuf[BSIZE];
		while(isalnum(temp))
		{
			lexbuf[i++] = temp;
			temp = fgetc(fin);
			con->positionNumber++;
			if(temp == '_')  //Check to see if a character has an underscore
			{
				if(isalnum(lookahead(con)))  //See if the next character is a letter or number
				{
					lexbuf[i++] = temp;
					temp = fgetc(fin);
					con->positionNumber++;
				}
				else
				{
					fprintf(stderr, "Error\n");
					strcpy(con->errorMessage, "Error: Invalid ID name");
					error(con);
				}
			}
			if(i >= BSIZE)
			{
				strcpy(con->errorMessage, "Exceeded buffer size");
				error(con);
			}
		}
		ungetc(temp, fin);
		con->positionNumber--;
		lexbuf[i] = EOS;
		if(temp == EOF)
		{
			ungetc(temp, fin);  //Ungets the EOF so to avoid error when calling getc again after end of file
			con->isDone = 1;
		}
		printf("got alpha[%s]\n", lexbuf);
		//printAllString(lexbuf);
		p = lookup(lexbuf);
		if((p == NOT_FOUND) && (con->canAddID == 1))
			p = insert(lexbuf, ID, "ID");
		else if(p == NOT_FOUND)
		{
			if(con->canAddID == 0)
			{
				strcpy(con->errorMessage, "Can't add ID");
				error(con);
			}
		}
		tokenval = getTokenType(p);
		printf("Token Value %d\n", tokenval);
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

/* getNextToken - gets the next token
 * return - returns the token value
 */
int getNextToken(struct content * con)
{
	char temp;
	int b = 0, ans = 0, r = 0;
	temp = fgetc(fin);
	if(temp == EOF)
	{
		con->isDone = 1;
		return 0;
	}
	else if((temp == ' ') || (temp == '\t'))
	{
		absorbSpace(con);
		return (getNextToken(con));
	}
  	else if(temp == '\n')
	{
		con->lineNumber++;
		return (getNextToken(con));
	}
	else if(isalpha(temp))
	{
		ungetc(temp, fin);
		getID(con);
		return tokenval;
	}
	else if(isdigit(temp))
	{
		ungetc(temp, fin);
		getNumber(con);
		return tokenval;
	}
	r = checkSpecialChar(temp, con);
	return r;
}

/* absorbSpace - runs a loop to absorb all spaces between words
 * return - no return value
 */
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

/* lookahead - gets a the next character value but returns the character to the file
 * return - returns the next value from the file
 */
char lookahead()
{
	char t = fgetc(fin);
	ungetc(t, fin);
	return t;
}

/* getNumber - gets a constant value from the program
 * return - no return value, but does set the tokenval
 */
void getNumber(struct content * con)
{
	char t = fgetc(fin);
	con->positionNumber++;
	char buffer[BSIZE];
	int i = 0;
	buffer[i++] = t;
	while(isdigit(t))
	{
		buffer[i++] = t;
		t = fgetc(fin);
		con->positionNumber++;
	}
	ungetc(t, fin);
	con->positionNumber--;
	int value = atoi(buffer);
	tokenval = NUMERICAL_CONSTANT;
}

/* checkSpecialChar -  check special characters that are not alphabetical or digits
 * return - returns the token value for the special sequence found
 */
int checkSpecialChar(char temp, struct content * con)
{
	char t;
	int ans = 0, er = 0;
	switch(temp)
	{
		case '=':
			if((lookahead() == '='))
			{
				t = fgetc(fin);
				con->positionNumber++;
				ans = EQUALITY;
			}
			else
				ans = ASSIGNMENT;
			break;
		case '/':
			if((lookahead() == '/'))
			{
				t = fgetc(fin);
				con->positionNumber++;
				absorbSingleLineComment(con);
				ans = getNextToken(con);
			}
			else if((lookahead() == '*'))
			{
				ungetc(temp, fin);
				con->positionNumber--;
				er = absorbMultComment(con);
				if(er == 0)
					ans = STARTMULTIPLECOMMENT;
				else
				{
					strcpy(con->errorMessage, "Multiple Line comment Error");
					error(con);
				}
			}
			else
				ans = DIVISION;
			break;
		case '+':
				ans = ADDITION;
				break;
		case '-':
				ans = SUBTRACTION;
				break;
		case '>':
			if((lookahead() == '='))
			{
				t = fgetc(fin);
				con->positionNumber++;
				ans = GREATERTHANANDEQUAL;
			}
			else
				ans = GREATERTHAN;
			break;
		case '<':
			if((lookahead() == '='))
			{
				t = fgetc(fin);
				con->positionNumber++;
				if((lookahead() == '>'))
				{
					t = fgetc(fin);
					con->positionNumber++;
					ans = STRINGEQUAL;
				}
				ans = LESSERTHANANDEQUAL;
			}
			else
				ans = LESSERTHAN;
			break;
		case ';' :
			ans = SEMICOLON;
			break;
		case ',' :
			ans = COMMA;
			break;
		default: break;
	}
	return ans;
}

/* printAllString - prints out the entire content of a string, even space characters
 * return - no return value
 */
void printAllString(char * string)
{
	int i, size = strlen(string);
	for(i = 0; i < size; i++)
	{
		printf("Char: %c :: Num: %d\n", string[i], string[i]);
	}
}

/* absorbMultComment - runs loop to absorb all content from between a multiple line comment signs
 * return - no return value
 */
int absorbMultComment(struct content * con)
{
	int answer = 1;
	char temp;
	if(checkStartMultipleComment(con))
	{
		temp = fgetc(fin);
		con->positionNumber++;
		while(checkEndMultipleComment(temp, con))
		{
			temp = fgetc(fin);
			con->positionNumber++;
		}
	}
	else
		answer = 0;
	return answer;
}

void absorbSingleLineComment(struct content * con)
{
	char temp = getc(fin);
	while(temp != '\n')
	{
		temp = getc(fin);
	}
	con->lineNumber++;
	con->positionNumber = 0;
}
/* checkStartMultipleComment - checks to see if the start characters are equal to start multiple line comment
 * return - returns 0 - if error and 1 - if true
 */
int checkStartMultipleComment(struct content * con)
{
	int answer = 0;
	char temp1, temp2;
	temp1 = fgetc(fin);
	temp2 = fgetc(fin);
	if(temp1 == '/')
		if(temp2 == '*')
			answer = 1;

	return answer;
}

/* checkEndMultipleComment - checks to see if the end characters are equal end multiple comment sequence
 * return - returns 0 - if error and 1 - if true
 */
int checkEndMultipleComment(char temp, struct content * con)
{
	int answer = 1;
	if(temp == '*')
	{
		if(lookahead() == '/')
		{
			temp = fgetc(fin);
			answer = 0;
		}
	}
	return answer;
}
