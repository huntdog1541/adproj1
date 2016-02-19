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

/*
 * struct entry - structure of symbol table where the string and tokenvalue are stored
 */
 struct entry {
   char * lexptr;
   int token;
   char * tokenName;
 };

/* symbol table - stores the string and tokenvalues
 *
 */
struct entry symtable[SYMMAX];

char lexemes[STRMAX];
char tokeName[STRMAX];

int tokenChar = -1;
int lastchar = -1;
int lastentry = 0;


 struct entry keywords[] = {
      {"program", PROGRAM, "PROGRAM",},\
      {"begin", BEGIN, "BEGIN",},\
      {"end", END, "END", },\
      {"done", DONE, "DONE", },\
      {"if", IF, "IF", },\
      {"else", ELSE, "ELSE", },\
      {"end_if", END_IF, "END_IF", },\
      {"while", WHILE, "WHILE", },\
      {"do", DO, "DO", },\
      {"end_while", END_WHILE, "END_WHILE", },\
      {"for", FOR, "FOR", },\
      {"(", LPARENTSIS, "LPARENTSIS", },\
      {")", RPARENTSIS, "RPARENTSIS", },\
      {"[", LBRACKET, "LBRACKET", },\
      {"]", RBRACKET, "RBRACKET", },\
      {";", SEMICOLON, "SEMICOLON", },\
      {".", PERIOD, "PERIOD", },\
      {",", COMMA, "COMMA", },\
      {"_", UNDERSCORE, "UNDERSCORE", },\
      {"//", SINGLECOMMENT, "SINGLECOMMENT", },\
      {"/*", STARTMULTIPLECOMMENT, "STARTMULTIPLECOMMENT", },\
      {"*/", ENDMULTIPLECOMMENT,"ENDMULTIPLECOMMENT", },\
      {"=", ASSIGNMENT, "ASSIGNMENT", },\
      {"==", EQUALITY, "EQUALITY", },\
      {"+", ADDITION, "ADDITION", },\
      {"-", SUBTRACTION, "SUBTRACTION", },\
      {"*", MULTIPLICATION, "MULTIPLICATION", },\
      {"/", DIVISION, "DIVISION", },\
      {"%", MODUS, "MODUS", },\
      {">", GREATERTHAN, "GREATERTHAN", },\
      {"<", LESSERTHAN, "LESSERTHAN", },\
      {">=", GREATERTHANANDEQUAL, "GREATERTHANANDEQUAL", },\
      {"<=", LESSERTHANANDEQUAL, "LESSERTHANANDEQUAL", },\
      {"<=>", STRINGEQUAL, "STRINGEQUAL", },\
      {"int", INT, "INT", },\
      {"float", FLOAT, "FLOAT", },\
      {"char", CHAR, "CHAR", },\
      {"string", STRING, "STRING", },\
      {0, 0, 0}
};

 /* init - initializes the symbol table
  * return - returns no value
  */
 void init()
 {
   struct entry *p;
   for(p = keywords; p->token; p++)
      insert(p->lexptr, p->token, p->tokenName);
 }

 /* lookup - given a string to lookup in the symbol table
  * return - value of the location of the keyword in the symbol table
  */
 int lookup(char s[])
 {
   int p;
   for(p = lastentry; p > 0; p--)
    if(! strcmp(symtable[p].lexptr, s) )
      return p;

    return NOT_FOUND;
 }

 /* insert - inserts a value into the symbol table
  * return -
  */
 int insert(char s[], int tok, char tN[])
 {
   int len, tokLen;
   len = strlen(s);
   tokLen = strlen(tN);
   if(lastentry + 1 >= SYMMAX)
   {
	   struct content con;
	   strcpy(con.errorMessage, "symbol table full\n");
	   error(&con);
   }
   if(lastchar + len + 1 >= STRMAX)
   {
   	  struct content con;
   	  strcpy(con.errorMessage, "lexeme array full\n");
      error(&con);
   }
   if(tokenChar + tokLen + 1 >= STRMAX)
   {
	   struct content con;
	   strcpy(con.errorMessage, "token name array full\n");
     error(&con);
   }
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

 /* getLexeme - gets the keyword from the table given a position in the table
  * return - returns the string taken from the symbol table
  */
char * getLexeme(int pos)
{
  return symtable[pos].lexptr;
}

/* getTokenType - gets the token value from the table given a position in the symbol table
 * return - returns the token value
 */
int getTokenType(int pos)
{
  return symtable[pos].token;
}

/* printSymbol - prints all the content from the symbol table - a ultilty function
 * return - returns no value
 */
void printSymbol()
{
	int i = lastentry;
    for(; i > 0; i--)
      printf("KEYWORD: %s and value %d and KEYWORD Name: %s\n", symtable[i].lexptr, symtable[i].token, symtable[i].tokenName);
}
