#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LENGTH 30

typedef struct node {
    char aName[LENGTH];
    int iNumber;
    struct node *pNext;
    struct node *pPrevious;
} NODE;


int menu (void) {
    int iSelection = 0;
    printf("1) Lue tiedosto\n");
    printf("2) Tallenna lista etuperin\n");
    printf("3) Tallenna lista takaperin\n");
    printf("4) Tyhjennä lista\n");
    printf("0) Lopeta\n");
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

NODE *empty(NODE *pA) {
    NODE *ptr = pA;
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

int main (void) {
    NODE *pStart = NULL, *pEnd = NULL;
    NODE *pNew = NULL, *ptr = NULL;
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
    printf("Kiitos ohjelman käytöstä.\n");
    return (0);
}

