#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// New file for week 12

// Function displaying the binarytree menu
int GraphMenu(void){
    int iSelection = 0;
    printf("\n");
    printf("Valitse haluamasi toiminto (binääripuu):\n");
    printf("1) Lue tiedosto\n");
    printf("2) X\n");
    printf("3) X\n");
    printf("4) X\n");
    printf("5) X\n");
    printf("6) X\n");
    printf("0) Palaa\n");
    printf("Anna valintasi: ");
    scanf("%d", &iSelection);
    getchar();
    return iSelection;
}