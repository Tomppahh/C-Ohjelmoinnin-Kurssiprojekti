#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "linkedlist.h"


int menu (void) {
    int iSelection = 0;
    printf("Valitse haluamasi toiminto:\n");
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

int main (void) {
    NODE *pStart = NULL, *pEnd = NULL;
    NODE *pNew = NULL, *ptr = NULL;
    int iSelection;
    char aReadName[LENGTH], aWriteName[LENGTH];

    do {
        iSelection = menu();

        if(iSelection == 1) {
            filename(aReadName, "Anna luettavan tiedoston nimi: ");
            pStart = readFile(pStart, aReadName);
            updatePreviousPointers(pStart); // Update previous pointers

        } else if (iSelection == 2) {
            filename(aWriteName, "Anna kirjoitettavan tiedoston nimi: ");
            writeFile(pStart, aWriteName);

        } else if (iSelection == 3) {
            filename(aWriteName, "Anna kirjoitettavan tiedoston nimi: ");
            writeFileReverse(pStart, aWriteName);

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


