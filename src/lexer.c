/*
 * lexer.c
 *
 *  Created on: Jan 23, 2016
 *      Author: dhunt
 */
#include <stdlib.h>
#include <stdio.h>
#include "lexer.h"

int lex(char * fileName)
{

	printf("File is %s \n", fileName);
	FILE * fin = fopen("test.txt", "r");
	if(!fin)
	{
		perror("File opening failed");
		exit(1);
	}
	int t = fgetc(fin);
	while(t != EOF)
	{
		printf("%c", t);
		fgetc(fin);
	}
	printf("\n");
	fclose(fin);
	return 0;
}
