/*
 * symbol.c
 *
 *  Created on: Jan 23, 2016
 *      Author: dhunt
 */
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include "global.h"
 #include "error.h"
 #include "lexer.h"
 #include "parser.h"
 #include "symbol.h"

 #define STRMAX 999
 #define SYMMAX 999

 struct entry {
   char * lexptr;
   int token;
 };

 struct entry keywords[] = {
   "begin", BEGIN,
   "end", END,
   "done", DONE,
   "if", IF,
   "while", WHILE,
   "do", DO,
   "for", FOR,
   "int", INT,
   "float", FLOAT,
   "char", CHAR,
   "string", STRING,

   "mod", MOD,
   0, 0
 };

 init()
 {
   struct entry *p;
   for(p = keywords; p->token; p++)
      insert(p->lexptr, p->token);
 }

 int lookup(char s[])
 {
   int p;
   for(p = lastentry; p > 0; p--)
    if(! strcmp(symtable[p].lexptr, s) )
      return p;

    return NOT_FOUND;
 }

 int insert(char s[], int tok)
 {
   int len;
   len = strlen(s);
   if(lastentry + 1 >= SYMMAX)

 }
