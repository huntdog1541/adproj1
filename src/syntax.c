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

/* openLexFile - sets the global file pointer
 * return - no return value
 */

void startSyntaxTree()
{
  int temp = 0;
  openLexFile();
  getNextToken();
  while(!matchToken(PROGRAM))
  {
    getNextToken();
  }
  temp = lookupNumber(PROGRAM);
  addToken(hand->root, getTokenName(temp), getTokenType(temp));
}
