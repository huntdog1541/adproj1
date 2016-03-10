/*
*  Node.h - David Hunt
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#ifndef NODE_H_
#define NODE_H_

#define BUFFERSIZE 256

typedef struct node {
  char * tokenName;
  int tokenNumber;
  struct node * loperand;
  struct node * roperand;
  struct node * nextNode;
  struct node * alternative;
}node;

typedef struct nodeHandler {
  node * root;
  node * currentNode;
  node * tempNode;
}nodeHandler;

nodeHandler hand;

node * createNode();

void createRoot();

node * bindNode(struct node * currentNode, struct node * tempNode);

node * addLOP(struct node * currentNode);

node * addROP(struct node * currentNode);

nodeHandler * destroyTree();

node * destroyNode(struct node * temp);

void addTokenName(node * temp, char * string);

void addTokenValue(node * temp, int value);

void addTokens(node * temp, char * string, int value);

#endif
