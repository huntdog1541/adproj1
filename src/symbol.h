/*
 * symbol.h
 *
 *  Created on: Jan 23, 2016
 *      Author: dhunt
 */


#ifndef SYMBOL_H_
#define SYMBOL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "error.h"
#include "lexer.h"
#include "parser.h"

 init();

 int lookup(char s[]);

 int insert(char s[], int tok);

char * getLexeme(int pos);

int getTokenType(int pos);

void printSymbol();

#endif /* SYMBOL_H_ */
