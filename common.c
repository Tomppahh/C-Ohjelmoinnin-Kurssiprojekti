#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "linkedlist.h"
#include "binarytree.h"
#include "graph.h"
#include "common.h"
#include "namelist.h"

void filename(char *pFileName, char *pSentence) {
    printf("%s", pSentence);
    scanf("%s", pFileName);
    getchar();
    return;
}

//Creates a new node in the binary tree
NODE_BT* createTreeNode(const char* name, int number) {
    NODE_BT* newNode = (NODE_BT*)malloc(sizeof(NODE_BT));
    NAME_LIST* nameList = createNameList(name, NULL);
    newNode->iCount = number;
    newNode->color = RED; // New nodes are red
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;
    newNode->pNameList = nameList;
    return newNode;
} 