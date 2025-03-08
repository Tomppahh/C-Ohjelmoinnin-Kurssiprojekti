// linkedlist.c

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "linkedlist.h"

NODE *addNode(NODE *pA, char *pName, int iCount) {
    NODE *pNew = NULL, *ptr = NULL;

    if ((pNew = (NODE*)malloc(sizeof(NODE))) == NULL) {
        perror("Muistin varaus epäonnistui, lopetetaan");
        exit(0);
    }

    strcpy(pNew->aName, pName);
    pNew->iCount = iCount;
    pNew->pNext = NULL;
    pNew->pPrevious = NULL;

    if (pA == NULL) {
        pA = pNew;
    } else {
        ptr = pA;
        while (ptr->pNext != NULL) {
            ptr = ptr->pNext;
        }
        ptr->pNext = pNew;
    }

    return(pA);
}


NODE *empty(NODE *pA) {
    NODE *ptr = pA;
    while (ptr != NULL) {
        pA = ptr->pNext;
        free(ptr);
        ptr = pA;
    }
    return(pA);
}

void writeFile(NODE *pA, char* pFileName) {
    File *Write = NULL;

    if ((Write = fopen(pFileName, "w")) == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan.");
        exit(0);
    }

    NODE *ptr = pA;
    while (ptr != NULL) {
        fprintf(Write, "%s,%d\n", ptr->aName, ptr->iCount);
        ptr = ptr->pNext;
    }

    return;
}