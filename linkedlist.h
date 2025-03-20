// linkedlist.h

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#define LENGTH 30

typedef struct nodeList {
    char aName[LENGTH];
    int iCount;
    struct nodeList *pNext;
    struct nodeList *pPrevious;
} NODE_LL;

// Functions

NODE_LL *createNode(NODE_LL *pA, char *pName, int iCount);
NODE_LL *empty(NODE_LL *pA);
void writeFile(NODE_LL *pA, char* pFileName);
void writeFileReverse(NODE_LL *pA, char *pFileName);
NODE_LL *readFile(NODE_LL *pA, char *pFileName);
NODE_LL *sortAscending(NODE_LL *pA);
void updatePreviousPointers(NODE_LL *pA);
int listLength(NODE_LL *pA);
void splitList(NODE_LL* pA, NODE_LL **pLeft, NODE_LL **pRight);
NODE_LL *sortDecending(NODE_LL *pLeft, NODE_LL *pRight);
NODE_LL *mergeSort(NODE_LL *pA);


#endif