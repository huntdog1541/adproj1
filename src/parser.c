/*
 * parser.c
 *
 *  Created on: Jan 23, 2016
 *      Author: dhunt
 */
#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "lexer.h"
#include "global.h"
#include "error.h"
#include "symbol.h"

int parser(char * fileName)
{
	puts("Parser ran");
	lex(fileName);
	return 0;
}
