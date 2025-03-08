// linkedlist.c

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "linkedlist.h"

#define ROW 60

NODE *createNode(NODE *pA, char *pName, int iCount) {
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

void readFile(NODE *pA, char *pFileName) {
    FILE *Read = NULL;
    char aRow[ROW], *p1=NULL,*p2=NULL;


    if ((Read = fopen(pFileName, "r")) == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }

    fgets(aRow,ROW,Read); // Poistetaan ensimmäinen rivi

    while ((fgets(aRow,ROW,Read)) != NULL) {
        if ((p1 = strtok(aRow, ";")) == NULL) {
            printf("Merkkijonon '%s' pilkkominen epäonnistui, lopetetaan", aRow);
            exit(0);
        }
        if ((p2 = strtok(NULL, "\n")) == NULL) {
            printf("Merkkijonon '%s' pilkkominen epäonnistui, lopetetaan", aRow);
            exit(0);
        }

        pA = createNode(pA, p1, atoi(p2));

        fclose(Read);
    }

    return;

}

void writeFile(NODE *pA, char* pFileName) {
    FILE *Write = NULL;
    NODE *ptr = pA;

    if ((Write = fopen(pFileName, "w")) == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan.");
        exit(0);
    }

    while (ptr != NULL) {
        fprintf(Write, "%s,%d\n", ptr->aName, ptr->iCount);
        ptr = ptr->pNext;
    }

    fclose(Write);

    return;
}