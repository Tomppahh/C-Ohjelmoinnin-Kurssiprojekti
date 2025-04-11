// linkedlist.c

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "linkedlist.h"
#include "common.h"

#define ROW 60

//Function displaying linkedlist menu
int linkedListMenu (void) {
    int iSelection = 0;
    printf("\n");
    printf("Valitse haluamasi toiminto (linkitetty lista):\n");
    printf("1) Lue tiedosto\n");
    printf("2) Tallenna lista etuperin\n");
    printf("3) Tallenna lista takaperin\n");
    printf("4) Tyhjennä lista\n");
    printf("5) Järjestä nousevaan järjestykseen\n");
    printf("6) Järjestä laskevaan järjestykseen\n");
    printf("0) Palaa\n");
    printf("Anna valintasi: ");
    scanf("%d", &iSelection);
    getchar();
    return(iSelection);
}

void linkedListMenuLogic(void) {
    NODE_LL *pStartList = NULL;
    int iSubSelection;
    char aReadName[LENGTH], aWriteName[LENGTH];
    do {
        iSubSelection = linkedListMenu();
        if(iSubSelection == 1) {
            filename(aReadName, "Anna luettavan tiedoston nimi: ");
            pStartList = readFile(pStartList, aReadName);
            updatePreviousPointers(pStartList); // Update previous pointer
        } else if (iSubSelection == 2) {
            filename(aWriteName, "Anna kirjoitettavan tiedoston nimi: ");
            writeFile(pStartList, aWriteName);
        } else if (iSubSelection == 3) {
            filename(aWriteName, "Anna kirjoitettavan tiedoston nimi: ");
            writeFileReverse(pStartList, aWriteName);
        } else if (iSubSelection == 4) {
            pStartList = empty(pStartList);
        } else if (iSubSelection == 5) {
            pStartList = sortAscending(pStartList);
            updatePreviousPointers(pStartList); //update previous pointers
            printf("Lista lajiteltu nousevaan järjestykseen.\n");
        } else if (iSubSelection == 6) {
            pStartList = mergeSort(pStartList);
            updatePreviousPointers(pStartList); //update previous pointers
            printf("Lista lajiteltu laskevaan järjestykseen.\n");
        } else if (iSubSelection == 0) {
            printf("Palataan päävalikkoon.\n");
        } else {
            printf("Yritä uudestaan.\n");
        }

    } while(iSubSelection != 0);
    empty(pStartList);
    return;
}




NODE_LL *createNode(NODE_LL *pA, char *pName, int iCount) {
    NODE_LL *pNew = NULL, *ptr = NULL;

    if ((pNew = (NODE_LL*)malloc(sizeof(NODE_LL))) == NULL) {
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

void updatePreviousPointers(NODE_LL *pA)
{
    NODE_LL *ptr = pA;
    NODE_LL *prev = NULL;

    while (ptr != NULL)
    {
        ptr->pPrevious = prev;
        prev = ptr;
        ptr = ptr->pNext;
    }
}

NODE_LL *empty(NODE_LL *pA) {
    NODE_LL *ptr = pA;
    while (ptr != NULL) {
        pA = ptr->pNext;
        free(ptr);
        ptr = pA;
    }
    return(pA);
}

NODE_LL *readFile(NODE_LL *pA, char *pFileName) {
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

void writeFile(NODE_LL *pA, char* pFileName) {
    FILE *Write = NULL;
    NODE_LL *ptr = pA;

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

void writeFileReverse(NODE_LL *pA, char *pFileName)
{
    FILE *Write = NULL;
    NODE_LL *ptr = pA;

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

NODE_LL *sortAscending(NODE_LL *pA) { // Bubble sort algorithm
    if (pA == NULL) return NULL; //if pointer is NULL nothing happens.
    int swap;
    NODE_LL *ptr;
    NODE_LL *last = NULL;
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

int listLength(NODE_LL *pA) { // Returns the length of the linked list
    int iCount = 0;
    NODE_LL *ptr = pA;

    while(ptr != NULL) {
        ptr = ptr->pNext;
        iCount++;
    }
    return (iCount);
}

void splitList(NODE_LL* pA, NODE_LL **pLeft, NODE_LL **pRight) {
    if (pA == NULL || pA->pNext == NULL) { // Base case: 0 or 1 node
        *pLeft = pA;
        *pRight = NULL;
        return;
    }

    NODE_LL *slow = pA;
    NODE_LL *fast = pA->pNext; // Will start one step ahead of slow to get correct middle split and prevent duplication

    // slow will approach the mid way point and when fast reaches the end of the list we will know that slow is at the middle
    while (fast != NULL && fast->pNext != NULL) {
        slow = slow->pNext;
        fast = fast->pNext;
        fast = fast->pNext;
    }

    *pLeft = pA; // First half of the list. Starts from the head and currently is basicly the whole list.
    *pRight = slow->pNext; // Second half of the list
    slow->pNext = NULL; // Break the list at the point where second half starts which will make so that the first half ends at this point.

    return;
}

NODE_LL *sortDecending(NODE_LL *pLeft, NODE_LL *pRight) {
    NODE_LL *result = NULL;
    
    if (pLeft == NULL) return pRight;
    if (pRight == NULL) return pLeft;

    if (pLeft->iCount > pRight->iCount) {
        result = pLeft;
        result->pNext = sortDecending(pLeft->pNext, pRight);
    } else if (pLeft->iCount == pRight->iCount) { 
        if (strcmp(pLeft->aName, pRight->aName) < 0) {
            result = pRight;
            result->pNext = sortDecending(pLeft, pRight->pNext);
        } else {
            result = pLeft;
            result->pNext = sortDecending(pLeft->pNext, pRight);
        }
    } else {
        result = pRight;
        result->pNext = sortDecending(pLeft, pRight->pNext);
    }

    return result;
}

NODE_LL *mergeSort(NODE_LL *pA) { // Merge sort algorithm
    
    if (pA == NULL || pA->pNext == NULL) {
        return pA; // Base case
    }

    // Create 2 new empty node structures which will then be used to store the list halfs

    NODE_LL *LeftHalf = NULL;
    NODE_LL *RightHalf = NULL; 

    splitList(pA, &LeftHalf, &RightHalf);

    
    // Recursive call to this subprogram
    LeftHalf = mergeSort(LeftHalf);
    RightHalf = mergeSort(RightHalf);

    // Sorts and returns the sorted list
    pA = sortDecending(LeftHalf, RightHalf);

    return (pA);
}