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


/* openLexFile - sets the global file pointer
 * return - no return value
 */
void openLexFile()
{
	fin = fopen(con.fileName, "r");
	printf("File Name: %s\n", con.fileName);
	if(!fin)
	{
		perror("File Not Found\n");
		exit(EXIT_FAILURE);
	}
}

void closeLexFile()
{
	fclose(fin);
}

/* getID - gets the ID name from the file.
 * return - no return value, sets the tokenval integer.
 */
void getID()
{
		int i = 0, p = 0;
		char temp = fgetc(fin);
		char lexbuf[BSIZE];
		while(isalnum(temp))
		{
			lexbuf[i++] = temp;
			temp = fgetc(fin);
			con.positionNumber++;
			if(temp == '_')  //Check to see if a character has an underscore
			{
				if(isalnum(lookahead(con)))  //See if the next character is a letter or number
				{
					lexbuf[i++] = temp;
					temp = fgetc(fin);
					con.positionNumber++;
				}
				else
				{
					fprintf(stderr, "Error\n");
					strcpy(con.errorMessage, "Error: Invalid ID name");
					error(&con);
				}
			}
			if(i >= BSIZE)
			{
				strcpy(con.errorMessage, "Exceeded buffer size");
				error(&con);
			}
		}
		ungetc(temp, fin);
		con.positionNumber--;
		lexbuf[i] = EOS;
		if(temp == EOF)
		{
			ungetc(temp, fin);  //Ungets the EOF so to avoid error when calling getc again after end of file
			con.isDone = 1;
		}
		p = lookup(lexbuf);
		if((p == NOT_FOUND) && (con.canAddID == 1))
			p = insert(lexbuf, ID, "ID");
		else if(p == NOT_FOUND)
		{
			if(con.canAddID == 0)
			{
				strcpy(con.errorMessage, "Can't add ID");
				error(&con);
			}
		}
		p = getTokenType(p);
		setTokenValue(lexbuf, p);
		//printf("Token Value %d\n", tokenval);
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
void getNextToken()
{
	char temp;
	temp = fgetc(fin);
	if(temp == EOF)
	{
		con.isDone = 1;
		return;
	}
	else if((temp == ' ') || (temp == '\t'))
	{
		absorbSpace(con);
		return (getNextToken(con));
	}
  	else if(temp == '\n')
	{
		con.lineNumber++;
		return (getNextToken(con));
	}
	else if(isalpha(temp))
	{
		ungetc(temp, fin);
		getID(con);
	}
	else if(isdigit(temp))
	{
		ungetc(temp, fin);
		getNumber(con);
	}
	checkSpecialChar(temp);
}

/* absorbSpace - runs a loop to absorb all spaces between words
 * return - no return value
 */
void absorbSpace()
{
	char temp = fgetc(fin);
	while((temp == ' ') || (temp == '\t'))
	{
		con.positionNumber++;
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
void getNumber()
{
	char t = fgetc(fin);
	con.positionNumber++;
	char buffer[BSIZE];
	int i = 0;
	buffer[i++] = t;
	while(isdigit(t))
	{
		buffer[i++] = t;
		t = fgetc(fin);
		con.positionNumber++;
	}
	ungetc(t, fin);
	con.positionNumber--;
	atoi(buffer);
	/*int value = atoi(buffer);
	if(value )
	{
		tokenval = NUMERICAL_CONSTANT;
	}*/
	setTokenValue(buffer, NUMERICAL_CONSTANT);
}

/* checkSpecialChar -  check special characters that are not alphabetical or digits
 * return - returns the token value for the special sequence found
 */
void checkSpecialChar(char temp)
{
	switch(temp)
	{
		case '=':
			if((lookahead() == '='))
			{
				fgetc(fin);
				con.positionNumber++;
				setTokenValue("==", EQUALITY);
			}
			else
				setTokenValue("=", ASSIGNMENT);
			break;
		case '/':
			if((lookahead() == '/'))
			{
				fgetc(fin);
				con.positionNumber++;
				absorbSingleLineComment(con);
				getNextToken(con);
			}
			else if((lookahead() == '*'))
			{
				ungetc(temp, fin);
				con.positionNumber--;
				absorbMultComment(con);
			}
			else
				setTokenValue("/", DIVISION);
			break;
		case '+':
				setTokenValue("+", ADDITION);
				break;
		case '-':
				setTokenValue("-", SUBTRACTION);
				break;
		case '>':
			if((lookahead() == '='))
			{
				fgetc(fin);
				con.positionNumber++;
				setTokenValue(">=", GREATERTHANANDEQUAL);
			}
			else
				setTokenValue(">", GREATERTHAN);
			break;
		case '<':
			if((lookahead() == '='))
			{
				fgetc(fin);
				con.positionNumber++;
				if((lookahead() == '>'))
				{
					fgetc(fin);
					con.positionNumber++;
					setTokenValue("<=>" ,STRINGEQUAL);
				}
				else
					setTokenValue("<=" ,LESSERTHANANDEQUAL);
			}
			else
				setTokenValue("<" ,LESSERTHAN);
			break;
		case ';' :
			setTokenValue(";", SEMICOLON);
			break;
		case ',' :
			setTokenValue(",", COMMA);
			break;
		case '(' :
			setTokenValue("(", LPARENTSIS);
			break;
		case ')' :
			setTokenValue(")", RPARENTSIS);
		default: break;
	}
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
void absorbMultComment()
{
	char temp;
	if(checkStartMultipleComment(con))
	{
		temp = fgetc(fin);
		con.positionNumber++;
		while(checkEndMultipleComment(temp))
		{
			temp = fgetc(fin);
			if(temp == '\0')
			{
				con.lineNumber++;
				con.positionNumber = 0;
			}
			else
				con.positionNumber++;
		}
	}
	else
	{
			strcpy(con.errorMessage, "Error with multiple line comment");
			error(&con);
	}
}

void absorbSingleLineComment()
{
	char temp = getc(fin);
	while(temp != '\n')
	{
		temp = getc(fin);
	}
	con.lineNumber++;
	con.positionNumber = 0;
}
/* checkStartMultipleComment - checks to see if the start characters are equal to start multiple line comment
 * return - returns 0 - if error and 1 - if true
 */
int checkStartMultipleComment()
{
	int answer = 0;
	char temp1, temp2;
	temp1 = fgetc(fin);
	if(temp1 == '/')
	{
		temp2 = getc(fin);
		if(temp2 == '*')
			answer = 1;
		else
			ungetc(temp2, fin);
	}
	else
	{
		ungetc(temp1, fin);
	}
	return answer;
}

/* checkEndMultipleComment - checks to see if the end characters are equal end multiple comment sequence
 * return - returns 0 - if error and 1 - if true
 */
int checkEndMultipleComment(char temp)
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

void setTokenValue(char * string, int value)
{
	strcpy(tokenval.buffer, string);
	tokenval.tokenNumber = value;
}
