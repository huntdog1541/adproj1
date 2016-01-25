/*
 * lexer.h
 *
 *  Created on: Jan 23, 2016
 *      Author: dhunt
 */


#ifndef LEXER_H_
#define LEXER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "error.h"
#include "parser.h"
#include "symbol.h"


int lex(char * fileName);


#endif /* LEXER_H_ */
