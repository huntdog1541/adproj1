/*
 * main.c
 *
 *  Created on: Jan 23, 2016
 *      Author: dhunt
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "symbol.h"
#include "global.h"

int main(int argc, char ** argv)
{
	if(argc == 2)
	{
		printf("Running parser for file name %s\n", argv[1]);
		init();
		parser(argv[1]);
	}
	else
	{
		fprintf(stderr, "Enter file name at execution");
	}
//	init();
//	char cwd[1024];
//	if (getcwd(cwd, sizeof(cwd)) != NULL)
//		fprintf(stdout, "Current working dir: %s\n", cwd);
//	parser("test.txt");

	return 0;
}
