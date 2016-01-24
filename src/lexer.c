/*
 * lexer.c
 *
 *  Created on: Jan 23, 2016
 *      Author: dhunt
 */
#include <stdlib.h>
#include <stdio.h>
#include "lexer.h"
#include "global.h"
#include "error.h"
#include "parser.h"
#include "symbol.h"

int lex(char * fileName)
{
	puts("Lexical Analysis ran");
	printf("File is %s \n", fileName);
	return 0;
}
