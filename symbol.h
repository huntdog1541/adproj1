/*
 * symbol.h
 *
 *  Created on: Jan 23, 2016
 *      Author: dhunt
 */
#include <stdio.h>
#include <stdlib.h>
#include "global.h"
#include "error.h"
#include "lexer.h"
#include "parser.h"

#ifndef SYMBOL_H_
#define SYMBOL_H_

/* init - initializes the symbol table
 * return - returns no value
 */
void init();

/* lookup - given a string to lookup in the symbol table
 * return - value of the location of the keyword in the symbol table
 */
int lookup(char s[]);

/* insert - inserts a value into the symbol table
 * return -
 */
int insert(char s[], int tok, char tN[]);

/* getLexeme - gets the keyword from the table given a position in the table
 * return - returns the string taken from the symbol table
 */
char * getLexeme(int pos);

/* getTokenType - gets the token value from the table given a position in the symbol table
 * return - returns the token value
 */
int getTokenType(int pos);

/* printSymbol - prints all the content from the symbol table - a ultilty function
 * return - returns no value
 */
void printSymbol();

/*
 * lookupNumber - looks up token by token value
 * return - returns the position of the token in symbol table
 */
int lookupNumber(int numb);

/*
 * getTokenName - returns the character string for the token name given the position in the table
 * return - returns a character string
 */
char * getTokenName(int pos);

#endif /* SYMBOL_H_ */
