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

void graphMenuLogic(void){ // ehdotus miten valikko tehtäisiin - Tommi
                            // try except virheenkäsittelyn voisi lisätä vielä
    int iSelection;

    do {
        iSelection = GraphMenu();

        if (iSelection == 0){
            printf("Palataan päävalikkoon.\n");
        }
        else if (iSelection == 1){
            // funktio 1
        }
        else if (iSelection == 2){
            // funktio 2
        }
        else if (iSelection == 3){
            // funktio 3
        }
        else if (iSelection == 4){
            // funktio 4
        }
        else if (iSelection == 5){
            // funktio 5
        }
        else if (iSelection == 6){
            // funktio 6
        }
        else{
            printf("Virheellinen valinta, yritä uudelleen.\n");
        }

    } while (iSelection != 0);
}