/*
*  Node.h - David Hunt
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#ifndef NODE_H_
#define NODE_H_

#define BUFFERSIZE 256

struct node {
  char tokenValue[BUFFERSIZE];
  int tokenNumber;
  struct node * loperand;
  struct node * roperand;
  struct node * nextNode;
  struct node * next;
}

struct nodeHandler {
  struct node * root;
  struct node * currentNode;
  struct node * tempNode;
}

struct nodeHandler hand;

struct node * createNode();

struct node * createRoot();

struct node * bindNode(struct node * currentNode, struct node * tempNode);

struct node * addLOP(struct node * currentNode);

struct node * addROP(struct node * currentNode);

struct nodeHandler * destroyTree();

struct node * destroyNode(struct node * temp);

#endif
