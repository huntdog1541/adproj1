/*
 * lexer.h
 *
 *  Created on: Jan 23, 2016
 *      Author: dhunt
 */
#include <stdio.h>
#include <stdlib.h>
#include "parser.h"



#ifndef LEXER_H_
#define LEXER_H_

int lex(struct content * con);

void getID(struct content * con);

char * getToken(char * buffer, char t);

int isValidID(char t);

void absorbSpace();

int getNextToken(struct content * con);

#endif /* LEXER_H_ */
