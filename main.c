#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LENGTH 30

typedef struct customer {
    char name[LENGTH];
    int iNumber;
    struct customer *pNext;
    struct customer *pPrevious;
} CUSTOMER;


int menu (void) {
    int iSelection = 0;
    printf("1) Lue tiedosto\n");
    printf("2) Tallenna lista etuperin\n");
    printf("3) Tallenna lista takaperin\n");
    printf("4) Tyhjennä lista\n");
    printf("0) Lopeta");
    printf("Anna valintasi: ");
    scanf("%d", &iSelection);
    getchar();
    return(iSelection);
}

void filename(char *pFileName, char *pSentence) {
    printf("%s", pSentence);
    scanf("%s", pFileName);
    getchar();
    return;
}

CUSTOMER *empty(CUSTOMER *pA) {
    CUSTOMER *ptr = pA;
    while (ptr != NULL) {
        pA = ptr->pNext;
        free(ptr);
        ptr = pA;
    }
    return(pA);
}

NODE *addNode(NODE *pA, char *pName, int iCount) {
    NODE *pNew = NULL, *ptr = NULL;

    if ((pNew = (NODE*)malloc(sizeof(NODE))) == NULL) {
        perror("Muistin varaus epäonnistui, lopetetaan");
        exit(0);
    }

    strcpy(pNew->pName, pName);
    pNew->iCount = iCount;
    pNew->pNext = NULL;
    pNew->pPrev = NULL;

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

int main (void) {
    CUSTOMER *pStart = NULL, *pEnd = NULL;
    CUSTOMER *pNew = NULL, *ptr = NULL;
    int iSelection;
    char aReadName[LENGTH], aWriteName[LENGTH];

    do {
        iSelection = menu();

        if(iSelection == 1) {
            filename(aReadName, "Anna luettavan atiedoston nimi: ");

        } else if (iSelection == 2) {
            filename(aWriteName, "Anna kirjoitettavan tiedoston nimi: ");

        } else if (iSelection == 3) {
            filename(aWriteName, "Anna kirjoitettavan tiedoston nimi: ");

        } else if (iSelection == 4) {
            empty(pStart);
        } else if (iSelection == 0) {
            printf("Lopetetaan.\n");
        } else {
            printf("Yritä uudestaan.\n");
        }

        printf("\n");

    } while(iSelection != 0);
    printf("Kiitos ohjelman käytöstä.");
    return (0);
}

