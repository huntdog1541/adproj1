/*
*  Node.c - by David Hunt
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"

struct node * createNode()
{
  struct node * temp = (struct node *)calloc(sizeof(struct node));
  temp->tokenNumber = NULL;
  temp->loperand = NULL;
  temp->roperand = NULL;
  temp->nextNode = NULL;
  temp->alternative  = NULL;
  return temp;
}

struct nodeHandler * createRoot()
{
  hand->root = createNode();
  return hand;
}

struct node * bindNode(struct node * currentNode, struct node * tempNode)
{
  currentNode->nextNode = tempNode;
  return tempNode;
}

struct node * addLOP(struct node * currentNode)
{
  currentNode->loperand = createNode();
  return currentNode->loperand;
}

struct node * addROP(struct node * currentNode)
{
  currentNode->roperand = createNode();
  return currentNode->roperand;
}

struct nodeHandler * destroyTree(struct nodeHandler * hand)
{
  hand->tempNode = NULL;
  hand->currentNode = NULL;
  hand->root = destroyNode(hand->root);
  return hand;
}

struct node * destroyNode(struct node * temp)
{
  if(temp->nextNode != NULL)
    destroyNode(temp->nextNode);
  if(temp->loperand != NULL)
    destroyNode(temp->loperand);
  if(temp->roperand = NULL)
    destroyNode(temp->roperand);
  if(temp->alternative != NULL)
    destroyNode(temp->alternative);
  temp = free(temp);
  return temp;
}
