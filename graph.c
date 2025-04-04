// graph.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#define MAX_FILENAME 256
// Function displaying the graph menu
int GraphMenu(void){
    int iSelection = 0;
    printf("\n");
    printf("Valitse haluamasi toiminto (graafi):\n");
    printf("1) Lue tiedosto\n");
    printf("2) Lisää/päivitä kaari\n");
    printf("3) Poista solmu\n");
    printf("4) Etsi lyhin reitti\n");
    printf("5) Joku muu hieno toiminto\n");
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
        } else if (iSelection == 1){
            fileName(aReadName, "Anna luettavan tiedoston nimi: ");
            nodeList = buildGraphFromFile(nodeList, aReadName);
        } else if (iSelection == 2){
            // funktio 2
        } else if (iSelection == 3){
            fileName(aReadName, "Anna poistettava solmu: ");
            removeGraphNode(&nodeList, aReadName);
        } else if (iSelection == 4){
            char startNode[2], goalNode[2];
            char *pathFile = firstTimeAskName(NULL);
            printf("Anna lähtösolmu: ");
            scanf("%2s", startNode);
            getchar();
            printf("Anna kohdesolmu: ");
            scanf("%2s", goalNode);
            // funktio 4
        } else if (iSelection == 5){
            printGraph(nodeList);
            // funktio 5
        } else {
            printf("Virheellinen valinta, yritä uudelleen.\n");
        }

    } while (iSelection != 0);

    return;
}

void fileName(char *pFileName, char *pSentence) {
    printf("%s", pSentence);
    scanf("%s", pFileName);
    getchar();
    return;
}

char *firstTimeAskName(const char *aFileName){
    static int file_asked = 0;
    static char filename[MAX_FILENAME] = {0};

    if (!file_asked){ // if filename hasn't been asked, use fileName function
        if (aFileName != NULL){
            // Just use the provided filename directly
            strncpy(filename, aFileName, MAX_FILENAME - 1);
            filename[MAX_FILENAME - 1] = '\0'; // Ensure null termination
        }
        else{
            // Ask user for filename directly
            char temp[MAX_FILENAME];
            fileName(temp, "Anna reittitiedoston nimi: ");
            strncpy(filename, temp, MAX_FILENAME - 1);
            filename[MAX_FILENAME - 1] = '\0';
        }
        file_asked = 1;
    }
    return filename;
}

NODE_G* buildGraphFromFile (NODE_G *nodeList, const char *aFile) {
    FILE *Read = NULL;
    NODE_G *sourceNode = NULL;
    NODE_G *destNode = NULL;
    int iDist;
    char aRow[ROW], *p1=NULL,*p2=NULL, *p3=NULL;
    if ((Read = fopen(aFile, "r")) == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan.");
        exit(0);
    }

    fgets(aRow,ROW,Read); // Delete header

    while ((fgets(aRow,ROW,Read)) != NULL) {
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

        iDist = atoi(p3);

        sourceNode = createGraphNode(&nodeList, p1);
        destNode = createGraphNode(&nodeList, p2);
        // Make the edge go both ways.
        addEdge(sourceNode, p2, iDist); // A -> B
        addEdge(destNode, p1, iDist); // B -> A
    }
    fclose(Read);
    return (nodeList);
}



NODE_G* createGraphNode(NODE_G **nodeList, const char *aName) {
    NODE_G *current = *nodeList;
    // Goes through the graph and finds if node with the same name exists
    while (current != NULL) {
        if (strcmp(current->aSource, aName) == 0)
            return current;
        current = current->next;
    }

    // Node was not found so create new one.
    NODE_G *newNode = NULL;
    if ((newNode = (NODE_G*)malloc(sizeof(NODE_G))) == NULL) {
        perror("Muistin varaus epäonnistui, lopetetaan");
        exit(0);
    }

    if ((newNode->aSource = (char*)malloc(strlen(aName)+1)) == NULL) {
        perror("Muistin varaus epäonnistui, lopetetaan");
        exit(0);
    }

    strcpy(newNode->aSource, aName);
    newNode->edges = NULL;
    newNode->next = *nodeList;
    *nodeList = newNode;
    return newNode;
}

void addEdge(NODE_G *node, const char *aDest, int iDist) {
    EDGE *newEdge = NULL;
    if ((newEdge = (EDGE*)malloc(sizeof(EDGE))) == NULL) {
        perror("Muistin varaus epäonnistui, lopetetaan");
        exit(0);
    }
    if ((newEdge->aDestination = (char*)malloc(strlen(aDest)+1)) == NULL) {
        perror("Muistin varaus epäonnistui, lopetetaan");
        exit(0);
    }
    strcpy(newEdge->aDestination, aDest);
    newEdge->iDistance = iDist;
    newEdge->next = node->edges;
    node->edges = newEdge;
    return;
}

void printGraph(const NODE_G *nodeList) {
    const NODE_G *currentNode = nodeList;
    while (currentNode != NULL) {
        printf("Solmu: %s\n", currentNode->aSource);
        
        // Tulostetaan solmun reunat, jos niitä on
        EDGE *currentEdge = currentNode->edges;
        if (currentEdge == NULL) {
            printf("  (Ei reunoja)\n");
        } else {
            while (currentEdge != NULL) {
                printf("   -> %s (Etäisyys: %d)\n", currentEdge->aDestination, currentEdge->iDistance);
                currentEdge = currentEdge->next;
            }
        }
        printf("\n");
        currentNode = currentNode->next;
    }
    return;
}

void removeGraphNode(NODE_G **nodeList, const char *aName) {
    NODE_G *current = *nodeList;
    NODE_G *previous = NULL;

    // Finding the node that needs to be removed
    while (current != NULL && strcmp(current->aSource, aName) != 0) {
        previous = current;
        current = current->next;
    }
    if (current == NULL) {
        printf("Solmua ei löytynyt\n");
        return;
    }

    // Print edges before removal
    printf("Edges before removal of node %s:\n", aName);
    EDGE *edgePrint = current->edges;
    while (edgePrint != NULL) {
        printf("   -> %s (Distance: %d)\n", edgePrint->aDestination, edgePrint->iDistance);
        edgePrint = edgePrint->next;
    }

    // Remove edges from other nodes that point to the current node
    EDGE *edge = current->edges;
    while (edge != NULL) {
        // Store the next edge before potentially freeing the current one
        EDGE *nextEdge = edge->next;

        // Remove edge from destination node
        NODE_G *destination = *nodeList;
        while (destination != NULL) {
            if (strcmp(destination->aSource, edge->aDestination) == 0) {
                EDGE *previousEdge = NULL;
                EDGE *currentEdge = destination->edges;

                // Find the edge that points to the current node
                while (currentEdge != NULL && strcmp(currentEdge->aDestination, current->aSource) != 0) {
                    previousEdge = currentEdge;
                    currentEdge = currentEdge->next;
                }

                // If the edge is found, remove it
                if (currentEdge != NULL) {
                    if (previousEdge == NULL) {
                        // Removing the first edge
                        destination->edges = currentEdge->next;
                    } else {
                        // Removing the last or middle edge
                        previousEdge->next = currentEdge->next;
                    }
                    free(currentEdge->aDestination); 
                    free(currentEdge); 
                }
                // Break out because no need to check other nodes
                break;
            }
            destination = destination->next;
        }

        // Free the current edge after processing
        free(edge->aDestination); 
        free(edge); 

        // Move to the next edge
        edge = nextEdge;
    }

    // Print edges after removal
    printf("Edges after removal of node %s:\n", aName);
    edgePrint = current->edges;
    while (edgePrint != NULL) {
        printf("   -> %s (Distance: %d)\n", edgePrint->aDestination, edgePrint->iDistance);
        edgePrint = edgePrint->next;
    }

    // Remove the node from the list
    if (previous == NULL) {
        // If the node is the first node
        *nodeList = current->next;
    } else {
        // Bypassing the current node
        previous->next = current->next;
    }
    free(current->aSource); 
    free(current); 
    printf("Poistetaan solmua %s... Poisto suoritettu.\n", aName);
}
