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
	puts("Hello World!");
	char str[256];
	strcpy(str, "test.txt");
	/*if(argc == 2)
	{
		printf("File name is %s\n", argv[1]);
	}*/
	char dir[256];
	getcwd(dir, sizeof(dir));
	printf("The directory is %s\n", dir);
	init();
	parser(str);

	return 0;
}
