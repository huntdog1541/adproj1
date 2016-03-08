/*
  Abstract Syntax Tree
*/



#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parser.h"
#include "symbol.h"
#include "lexer.h"
#include "error.h"
#include "syntax.h"
#include "node.h"

FILE * fin;


/* openLexFile - sets the global file pointer
 * return - no return value
 */
void openSyntaxFile()
{
	fin = fopen(con.fileName, "r");
	printf("File Name: %s\n", con.fileName);
	if(!fin)
	{
		perror("File Not Found\n");
		exit(EXIT_FAILURE);
	}
}

void closeSyntaxFile()
{
	fclose(fin);
}

void startSyntaxTree()
{
  openSyntaxFile();

}
