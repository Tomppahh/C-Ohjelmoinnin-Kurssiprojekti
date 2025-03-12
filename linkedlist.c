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

void updatePreviousPointers(NODE *pA)
{
    NODE *ptr = pA;
    NODE *prev = NULL;

    while (ptr != NULL)
    {
        ptr->pPrevious = prev;
        prev = ptr;
        ptr = ptr->pNext;
    }
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

NODE *readFile(NODE *pA, char *pFileName) {
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

        
    }

    fclose(Read);

    return (pA);

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

void writeFileReverse(NODE *pA, char *pFileName)
{
    FILE *Write = NULL;
    NODE *ptr = pA;

    if ((Write = fopen(pFileName, "w")) == NULL)
    {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan.");
        exit(0);
    }
    // listan loppuun
    while (ptr != NULL && ptr->pNext != NULL)
    {
        ptr = ptr->pNext;
    }

    // käy lista läpi väärin päin
    while (ptr != NULL)
    {
        fprintf(Write, "%s,%d\n", ptr->aName, ptr->iCount);
        ptr = ptr->pPrevious;
    }

    fclose(Write);

    return;
}

NODE *sortAscending(NODE *pA) { // Bubble sort algorithm
    if (pA == NULL) return NULL; //if pointer is NULL nothing happens.
    int swap;
    NODE *ptr;
    NODE *last = NULL;
    //sorting until no swaps are required
    do {
        swap = 0;
        ptr = pA;
        //Comparing current node with the next node primary for numbers and secondary for names in alphabetical order. 
        while (ptr->pNext != last) {
            if (ptr->iCount > ptr->pNext->iCount || (ptr->iCount == ptr->pNext->iCount && strcmp(ptr->aName, ptr->pNext->aName) > 0)) {
               int tempCount = ptr->iCount;
               char tempName[30];
               strcpy(tempName, ptr->aName);
               ptr->iCount = ptr->pNext->iCount;
               strcpy(ptr->aName, ptr->pNext->aName);
               ptr->pNext->iCount = tempCount;
               strcpy(ptr->pNext->aName, tempName);
               swap = 1;
            }
            ptr = ptr->pNext;
        }
        last = ptr;
    } while (swap); //repeats the whole process if atleast one swap was performed.
    return pA;
}

int listLength(NODE *pA) { // Returns the length of the linked list
    int iCount = 0;
    NODE *ptr = pA;

    while(ptr != NULL) {
        ptr = ptr->pNext;
        iCount++;
    }
    return (iCount);
}

void splitList(NODE* pA, NODE *pLeft, NODE *pRight) {

    NODE *slow = pA;
    NODE *fast = pA->pNext; // Will start one step ahead of slow to get correct middle split and prevent duplication

    // slow will approach the mid way point and when fast reaches the end of the list we will know that slow is at the middle
    while (fast != NULL && fast->pNext != NULL) {
        slow = slow->pNext;
        fast = fast->pNext;
        fast = fast->pNext;
    }

    pLeft = pA; // First half of the list. Starts from the head and currently is basicly the whole list.
    pRight = slow->pNext; // Second half of the list
    slow->pNext = NULL; // Break the list at the point where second half starts which will make so that the first half ends at this point.

    return;
}

NODE *sortDecending(NODE *pLeft, NODE *pRight) {
    NODE *result = NULL;
    int iEcual;

    if (pLeft == NULL) {
        return pRight;
    }
    if (pRight == NULL) {
        return pLeft;
    }

    if(pLeft->iCount > pRight->iCount) {
        result = pLeft;
        result->pNext = sortDecending(pLeft->pNext, pRight); // Recursive call to this subprogram
    } else if (pLeft->iCount == pRight->iCount) { // If the iCounts are ecual
        iEcual = strcmp(pLeft->aName, pRight->aName);
        if (iEcual < 0) {
            result->pNext = sortDecending(pLeft->pNext, pRight);
        } else {
            result->pNext = sortDecending(pLeft, pRight->pNext);
        }
    } else {
        result = pRight;
        result->pNext = sortDecending(pLeft, pRight->pNext);
    }

    return result;
}

NODE *mergeSort(NODE *pA) { // Merge sort algorithm
    NODE *ptr = pA;
    

    if (ptr == NULL || ptr->pNext == NULL) {
        return pA; // Base case
    }

    // Create 2 new empty NODE structures which will then be used to store the list halfs

    NODE *LeftHalf = NULL;
    NODE *RightHalf = NULL; 

    splitList(ptr, LeftHalf, RightHalf);
    
    // Recursive call to this subprogram
    LeftHalf = mergeSort(LeftHalf);
    RightHalf = mergeSort(RightHalf);

    // Sorts and returns the sorted list
    ptr = sortDecending(LeftHalf, RightHalf);

    return (ptr);
}