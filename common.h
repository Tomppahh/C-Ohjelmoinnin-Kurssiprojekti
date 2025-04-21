// common.h

#ifndef COMMON_H
#define COMMON_H

#include "linkedlist.h"
#include "binarytree.h"
#include "graph.h"

void filename(char *pFileName, char *pSentence);
NODE_BT* createTreeNode(const char* name, int number);
void freeTree(NODE_BT* root);
NODE_BT* insertNode(NODE_BT* root, const char* name, int number);

#endif