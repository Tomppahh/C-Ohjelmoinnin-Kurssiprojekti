#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
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
    NODE_G *nodeList = NULL;
    int iSelection;
    char aReadName[LENGTH];
    do {
        iSelection = GraphMenu();

        if (iSelection == 0){
            printf("Palataan päävalikkoon.\n");
        }
        else if (iSelection == 1){
            fileName(aReadName, "Anna luettavan tiedoston nimi: ");
            nodeList = buildGraphFromFile(nodeList, aReadName);
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

void fileName(char *pFileName, char *pSentence) {
    printf("%s", pSentence);
    scanf("%s", pFileName);
    getchar();
    return;
}

NODE_G* buildGraphFromFile (NODE_G *nodeList, const char *aFile) {
    FILE *Read = NULL;
    NODE_G *sourceNode = NULL;
    char aRow[LENGTH], *p1=NULL,*p2=NULL, *p3=NULL;
    if ((Read = fopen(aFile, "r")) == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan.");
        exit(0);
    }

    fgets(aRow,LENGTH,Read); // Delete header

    while ((fgets(aRow,LENGTH,Read)) != NULL) {
        if ((p1 = strtok(aRow, ";")) == NULL) {
            printf("Merkkijonon '%s' pilkkominen epäonnistui, lopetetaan", aRow);
            exit(0);
        }
        if ((p2 = strtok(NULL, ";")) == NULL) {
            printf("Merkkijonon '%s' pilkkominen epäonnistui, lopetetaan", aRow);
            exit(0);
        }
        if ((p3 = strtok(NULL, "\n")) == NULL) {
            printf("Merkkijonon '%s' pilkkominen epäonnistui, lopetetaan", aRow);
            exit(0);
        }

        sourceNode = createGraphNode(nodeList, p1);
        addEdge(sourceNode, p2, atoi(p3));

    }
    fclose(Read);
    return (nodeList);
}

NODE_G* createGraphNode(NODE_G *nodeList, const char *name) {
    NODE_G *current = nodeList;
    // Goes through the graph and finds if node with the same name exists
    while (current) {
        if (strcmp(current->aSource, name) == 0)
            return current;
        current = current->next;
    }

    // Node was not found so create new one.
    NODE_G *newNode = NULL;
    if ((newNode = (NODE_G*)malloc(sizeof(NODE_G))) == NULL) {
        perror("Muistin varaus epäonnistui, lopetetaan");
        exit(0);
    }

    newNode->aSource = strcpy(name);
    newNode->edges = NULL;
    newNode->next = nodeList;
    nodeList = newNode;
    return newNode;
}

void addEdge(NODE_G *node, const char *aDest, int iDist) {
    EDGE *newEdge = NULL;
    if ((newEdge = (EDGE*)malloc(sizeof(EDGE))) == NULL) {
        perror("Muistin varaus epäonnistui, lopetetaan");
        exit(0);
    }
    newEdge->aDestination = strcpy(aDest);
    newEdge->iDistance = iDist;
    newEdge->next = node->edges;
    node->edges = newEdge;
    return;
}