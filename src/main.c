/*
 * main.c
 *
 *  Created on: Jan 23, 2016
 *      Author: dhunt
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol.h"
#include "parser.h"
#include "lexer.h"
#include "global.h"
#include "error.h"

int main(int argc, char ** argv)
{
	puts("Hello World!");
	char str[256];
	strcpy(str, "test.txt");
	parser(str);

	return 0;
}
