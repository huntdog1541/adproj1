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


/* getID - gets the ID name from the file.
 * return - no return value, sets the tokenval integer.
 */
void getID(struct content * con);

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
int getNextToken(struct content * con);

/* checkSpecialChar -  check special characters that are not alphabetical or digits
 * return - returns the token value for the special sequence found
 */
int checkSpecialChar(char temp, struct content * con);

/* getNumber - gets a constant value from the program
 * return - no return value, but does set the tokenval
 */
void getNumber(struct content * con);

/* lookahead - gets a the next character value but returns the character to the file
 * return - returns the next value from the file
 */
char lookahead();

/* absorbSpace - runs a loop to absorb all spaces between words
 * return - no return value
 */
void absorbSpace(struct content * con);

/* printAllString - prints out the entire content of a string, even space characters
 * return - no return value
 */
void printAllString(char * string);

/* openLexFile - sets the global file pointer
 * return - no return value
 */
void openLexFile(struct content * con);

/* absorbMultComment - runs loop to absorb all content from between a multiple line comment signs
 * return - no return value
 */
int absorbMultComment(struct content * con);

/* checkStartMultipleComment - checks to see if the start characters are equal to start multiple line sequence
 * return - returns 0 - if error and 1 - if true
 */
int checkStartMultipleComment(struct content * con);

/* checkEndMultipleComment - checks to see if the end characters are equal end multiple comment sequence
 * return - returns 0 - if error and 1 - if true
 */
int checkEndMultipleComment(char temp, struct content * con);

#endif /* LEXER_H_ */
