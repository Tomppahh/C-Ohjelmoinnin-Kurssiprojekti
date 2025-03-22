#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "linkedlist.h"
#include "binarytree.h"
#include <locale.h>

//Function displaying the mainmenu
int mainMenu (void) {
    int iSelection = 0;
    printf("Valitse käsiteltävä tietorakenne:\n");
    printf("1) Linkitetty lista\n");
    printf("2) Binääripuu\n");
    printf("0) Lopeta\n");
    printf("Anna valintasi: ");
    scanf("%d", &iSelection);
    getchar();
    return iSelection;
}

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

//Function displaying the binarytree menu
int binaryTreeMenu (void) {
    int iSelection = 0;
    printf("\n");
    printf("Valitse haluamasi toiminto (binääripuu):\n");
    printf("1) Lue tiedosto\n");
    printf("2) Kirjoita puun arvot tiedostoon\n");
    printf("3) Syvyyshaku\n");
    printf("4) Leveyshaku\n");
    printf("5) Tulosta puumaisessa muodossa\n");
    printf("0) Palaa\n");
    printf("Anna valintasi: ");
    scanf("%d", &iSelection);
    getchar();
    return iSelection;
}

void filename(char *pFileName, char *pSentence) {
    printf("%s", pSentence);
    scanf("%s", pFileName);
    getchar();
    return;
}

int main (void) {
    setlocale(LC_ALL, "en_US.UTF-8"); // Set locale to UTF-8
    NODE_LL *pStartList = NULL;
    NODE_BT *pStartTree = NULL;
    
    int iMainSelection, iSubSelection;
    char aReadName[LENGTH], aWriteName[LENGTH];

    do {
        iMainSelection = mainMenu();
        if (iMainSelection == 1) {
            do {
                iSubSelection = linkedListMenu();
                if(iSubSelection == 1) {
                    filename(aReadName, "Anna luettavan tiedoston nimi: ");
                    pStartList = readFile(pStartList, aReadName);
                    updatePreviousPointers(pStartList); // Update previous pointers
        
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
            
        } else if (iMainSelection == 2) {
            do {
                iSubSelection = binaryTreeMenu();
                if (iSubSelection == 1) {
                    filename(aReadName, "Anna luettavan tiedoston nimi: ");
                    pStartTree = buildFromFile(aReadName);
                } else if (iSubSelection == 2) {
                    filename(aWriteName, "Anna kirjoitettavan tiedoston nimi: ");
                    writeFileTree(aWriteName,pStartTree);
                } else if (iSubSelection == 3){
                    char searchTerm[LENGTH];
                    printf("Anna etsittävä nimi tai numero: ");
                    fgets(searchTerm, sizeof(searchTerm), stdin);
                    searchTerm[strcspn(searchTerm, "\n")] = 0; // get rid of newline
                    filename(aWriteName, "Anna kirjoitettavan tiedoston nimi: ");
                    writeFileDF(pStartTree, searchTerm,aWriteName);
                } else if (iSubSelection == 4) {
                    char searchTerm[LENGTH];
                    printf("Anna etsittävä nimi tai numero: ");
                    fgets(searchTerm, sizeof(searchTerm), stdin);
                    searchTerm[strcspn(searchTerm, "\n")] = 0; // get rid of newline
                    filename(aWriteName, "Anna kirjoitettavan tiedoston nimi: ");
                    writeFileWF(pStartTree,searchTerm,aWriteName);
                } else if (iSubSelection == 5) {
                    printTree(pStartTree);
                } else if (iSubSelection == 0) {
                    printf("Palataan päävalikkoon.\n");
                } else {
                    printf("Yritä uudestaan.\n");
                }

            } while (iSubSelection != 0);

        } else if (iMainSelection == 0) {
            printf("Lopetetaan.\n");
        } else {
            printf("Yritä uudestaan.\n");
        }

        printf("\n");

    } while (iMainSelection != 0);
    pStartList = empty(pStartList);
    printf("Kiitos ohjelman käytöstä.\n");
    return (0);
}

