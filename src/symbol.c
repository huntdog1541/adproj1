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
   char * tokenName;
 };

struct entry symtable[SYMMAX];

char lexemes[STRMAX];
char tokeName[STRMAX];

int tokenChar = -1;
int lastchar = -1;
int lastentry = 0;


 struct entry keywords[] = {
   "program", PROGRAM, "PROGRAM",
   "begin", BEGIN, "BEGIN",
   "end", END, "END",
   "done", DONE, "DONE",
   "if", IF, "IF",
   "while", WHILE, "WHILE",
   "do", DO, "DO",
   "for", FOR, "FOR",
   "(", LPARENTSIS, "LPARENTSIS",
    ")", RPARENTSIS, "RPARENTSIS",
    "[", LBRACKET, "LBRACKET",
    "]", RBRACKET, "RBRACKET",
    ";", SEMICOLON, "SEMICOLON",
    ".", PERIOD, "PERIOD",
    "_", UNDERSCORE, "UNDERSCORE",
    "//", SINGLECOMMENT, "SINGLECOMMENT",
    "/*", STARTMULTIPLECOMMENT, "STARTMULTIPLECOMMENT",
    "*/", ENDMULTIPLECOMMENT,"ENDMULTIPLECOMMENT",
    "=", ASSIGNMENT, "ASSIGNMENT",
    "==", EQUALITY, "EQUALITY",
    "+", ADDITION, "ADDITION",
    "-", SUBTRACTION, "SUBTRACTION",
    "*", MULTIPLICATION, "MULTIPLICATION",
    "/", DIVISION, "DIVISION",
    "%", MODUS, "MODUS",
    ">", GREATERTHAN, "GREATERTHAN",
    "<", LESSERTHAN, "LESSERTHAN",
    ">=", GREATERTHANANDEQUAL, "GREATERTHANANDEQUAL",
    "<=", LESSERTHANANDEQUAL, "LESSERTHANANDEQUAL",
    "<=>", STRINGEQUAL, "STRINGEQUAL",
   "int", INT, "INT",
   "float", FLOAT, "FLOAT",
   "char", CHAR, "CHAR",
   "string", STRING, "STRING",
   0, 0, 0
 };

 void init()
 {
   struct entry *p;
   for(p = keywords; p->token; p++)
      insert(p->lexptr, p->token, p->tokenName);
 }

 int lookup(char s[])
 {
   int p;
   for(p = lastentry; p > 0; p--)
    if(! strcmp(symtable[p].lexptr, s) )
      return p;

    return NOT_FOUND;
 }

 int insert(char s[], int tok, char tN[])
 {
   int len, tokLen;
   len = strlen(s);
   tokLen = strlen(tN);
   if(lastentry + 1 >= SYMMAX)
      error("symbol table full");
   if(lastchar + len + 1 >= STRMAX)
      error("lexeme array full");
   if(tokenChar + tokLen + 1 >= STRMAX)
      error("token name array full");
   lastentry = lastentry + 1;
   symtable[lastentry].token = tok;
   symtable[lastentry].lexptr = &lexemes[lastchar + 1];
   symtable[lastentry].tokenName = &tokeName[tokenChar + 1];
   lastchar = lastchar + len + 1;
   tokenChar = tokenChar + tokLen + 1;
   strcpy(symtable[lastentry].lexptr, s);
   strcpy(symtable[lastentry].tokenName, tN);
   return lastentry;
 }

char * getLexeme(int pos)
{
  return symtable[pos].lexptr;
}

int getTokenType(int pos)
{
  return symtable[pos].token;
}

void printSymbol()
{
    struct entry *p;
    for(p = keywords; p->token; p++)
      printf("KEYWORD: %s and value %d and KEYWORD Name: %s\n", p->lexptr, p->token, p->tokenName);
}
