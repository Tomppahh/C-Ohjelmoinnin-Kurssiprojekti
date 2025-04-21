// main.c

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "linkedlist.h"
#include "binarytree.h"
#include "graph.h"
#include <locale.h>


//Function displaying the mainmenu
int mainMenu (void) {
    int iSelection = 0;
    printf("Valitse käsiteltävä tietorakenne:\n");
    printf("1) Linkitetty lista\n");
    printf("2) Binääripuu\n");
    printf("3) Graafiverkko\n");
    printf("0) Lopeta\n");
    printf("Anna valintasi: ");
    scanf("%d", &iSelection);
    getchar();
    return iSelection;
}

int main (void) {
    setlocale(LC_ALL, "en_US.UTF-8"); // Set locale to UTF-8
    
    int iMainSelection;

    do {
        iMainSelection = mainMenu();
        if (iMainSelection == 1) {
            linkedListMenuLogic();
        } else if (iMainSelection == 2) {
            treeMenuLogic();
        } else if (iMainSelection == 3){
            graphMenuLogic();
        } else if (iMainSelection == 0) {
            printf("Lopetetaan.\n");
        } else {
            printf("Yritä uudestaan.\n");
        }

        printf("\n");

    } while (iMainSelection != 0);
    printf("Kiitos ohjelman käytöstä.\n");
    return (0);
}

