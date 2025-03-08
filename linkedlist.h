// linkedlist.h

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#define LENGTH 30

typedef struct node {
    char aName[LENGTH];
    int iNumber;
    struct node *pNext;
    struct node *pPrevious;
} NODE;

// Functions

NODE *addNode(NODE *pA, char *pName, int iCount);


#endif