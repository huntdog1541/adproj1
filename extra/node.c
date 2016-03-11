/*
*  Node.c - by David Hunt
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"

node * createNode()
{
  struct node * temp = (struct node *)calloc(1, sizeof(struct node));
  temp->tokenName = NULL;
  temp->tokenNumber = 0;
  temp->loperand = NULL;
  temp->roperand = NULL;
  temp->nextNode = NULL;
  temp->alternative  = NULL;
  return temp;
}

void createRoot()
{
  hand.root = createNode();
}

node * bindNode(struct node * currentNode, struct node * tempNode)
{
  currentNode->nextNode = tempNode;
  return tempNode;
}

node * addLOP(struct node * currentNode)
{
  currentNode->loperand = createNode();
  return currentNode->loperand;
}

node * addROP(struct node * currentNode)
{
  currentNode->roperand = createNode();
  return currentNode->roperand;
}

nodeHandler * destroyTree(struct nodeHandler * hand)
{
  hand->tempNode = NULL;
  hand->currentNode = NULL;
  hand->root = destroyNode(hand->root);
  return hand;
}

node * destroyNode(struct node * temp)
{
  if(temp->nextNode != NULL)
    destroyNode(temp->nextNode);
  if(temp->loperand != NULL)
    destroyNode(temp->loperand);
  if(temp->roperand != NULL)
    destroyNode(temp->roperand);
  if(temp->alternative != NULL)
    destroyNode(temp->alternative);
  free(temp);
  return temp;
}

void addTokenName(node * temp, char * string)
{
  temp->tokenName = string;
}

void addTokenValue(node * temp, int value)
{
  temp->tokenNumber = value;
}

void addTokens(node * temp, char * string, int value)
{
  addTokenName(temp, string);
  addTokenValue(temp, value);
}
