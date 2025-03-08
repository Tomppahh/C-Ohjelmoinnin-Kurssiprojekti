// linkedlist.h

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#define LENGTH 30

typedef struct node {
    char aName[LENGTH];
    int iCount;
    struct node *pNext;
    struct node *pPrevious;
} NODE;

// Functions

NODE *addNode(NODE *pA, char *pName, int iCount);
NODE *empty(NODE *pA);
void writeFile(NODE *pA, char* pFileName);
void writeFileReverse(NODE *pA, char *pFileName);
NODE *readFile(NODE *pA, char *pFileName);


#endif