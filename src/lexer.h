/*
 * lexer.h
 *
 *  Created on: Jan 23, 2016
 *      Author: dhunt
 */
#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "global.h"



#ifndef LEXER_H_
#define LEXER_H_

struct tokenType
{
  char buffer[BSIZE];
  int tokenNumber;
};

FILE * fin;

struct tokenType tokenval;

/* getID - gets the ID name from the file.
 * return - no return value, sets the tokenval integer.
 */
void getID();

/* openLexFile - sets the global file pointer
 * return - no return value
 */
void openLexFile();

void closeLexFile();



/* getToken -
 *
 */
char * getToken(char * buffer, char t);

/* isValidID - checks to if valid character for ID
 * return - 0 if false, otherwise 1
 */
int isValidID(char t);

/* getNextToken - gets the next token
 * return - returns the token value
 */
void getNextToken();

/* checkSpecialChar -  check special characters that are not alphabetical or digits
 * return - returns the token value for the special sequence found
 */
void checkSpecialChar(char temp);

/* getNumber - gets a constant value from the program
 * return - no return value, but does set the tokenval
 */
void getNumber();

/* lookahead - gets a the next character value but returns the character to the file
 * return - returns the next value from the file
 */
char lookahead();

/* absorbSpace - runs a loop to absorb all spaces between words
 * return - no return value
 */
void absorbSpace();

/* printAllString - prints out the entire content of a string, even space characters
 * return - no return value
 */
void printAllString(char * string);

/* openLexFile - sets the global file pointer
 * return - no return value
 */
void openLexFile();

void absorbSingleLineComment();

/* absorbMultComment - runs loop to absorb all content from between a multiple line comment signs
 * return - no return value
 */
void absorbMultComment();

/* checkStartMultipleComment - checks to see if the start characters are equal to start multiple line sequence
 * return - returns 0 - if error and 1 - if true
 */
int checkStartMultipleComment();

/* checkEndMultipleComment - checks to see if the end characters are equal end multiple comment sequence
 * return - returns 0 - if error and 1 - if true
 */
int checkEndMultipleComment(char temp);

void setTokenValue(char * string, int value);

#endif /* LEXER_H_ */
