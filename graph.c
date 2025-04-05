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
            getchar();
            shortestPath(nodeList, startNode, goalNode, pathFile);
            // funktio 4
        } else if (iSelection == 5){
            printGraph(nodeList);
            // funktio 5
        } else {
            printf("Virheellinen valinta, yritä uudelleen.\n");
        }

    } while (iSelection != 0);
    freeGraph(nodeList);
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
void freeGraph(NODE_G *graph){
    NODE_G *current = graph;
    NODE_G *next;

    while (current != NULL){
        // Free all edges
        EDGE *edge = current->edges;
        while (edge != NULL){
            EDGE *nextEdge = edge->next;
            free(edge->aDestination);
            free(edge);
            edge = nextEdge;
        }

        next = current->next;
        free(current->aSource);
        free(current);
        current = next;
    }
}
NODE_G shortestPath(NODE_G *graph, const char *startNode, const char *goalNode, const char *outputFile){
    DLIST *unvisited = NULL;
    DLIST *visited = NULL;
    NODE_G *current = graph;
    FILE *file = NULL;
    int foundStart = 0;
    int foundGoal = 0;

    while (current != NULL){
        DLIST *newEntry = malloc(sizeof(DLIST));
        if (!newEntry){
            perror("Muistin varaus epäonnistui, lopetetaan");
            while (unvisited != NULL){
                DLIST *temp = unvisited;
                unvisited = unvisited->next;
                free(temp->aCurrent);
                free(temp->iDistanceBetween);
                if (temp->aPreviousNode !=NULL){
                    free(temp->aPreviousNode);
                }
                free(temp);
            }
            exit(0);
        }

        // copy the current nodes name to the newEntry
        newEntry->aCurrent = malloc(strlen(current->aSource) + 1);
        if (!newEntry->aCurrent){
            perror("Muistin varaus epäonnistui, lopetetaan");
            free(newEntry);
            exit(0);
        }
        strcpy(newEntry->aCurrent, current->aSource);

        // allocate memory for distance
        newEntry->iDistanceBetween = malloc(sizeof(int));
        if (newEntry->iDistanceBetween == NULL){
            perror("Muistin varaus epäonnistui, lopetetaan");
            free(newEntry->aCurrent);
            free(newEntry);
            exit(0);
        }

        // we need to set INT_MAX to all except start node
        if (strcmp(current->aSource, startNode) == 0){
            *newEntry->iDistanceBetween = 0; // the length between start node and start node is always 0
            foundStart = 1; //if we find the user input start node in the graph, foundStart switch is "on"
        } else {
            *newEntry->iDistanceBetween =  __INT_MAX__; // googled that INT_MAX is highest possible integer macro in compiler C
        }

        // now lets set previous node to NULL initially
        newEntry -> aPreviousNode = NULL;
        // connects new node to the unvisited list, sets next pointer of the new entry -> head of unvisited list.
        // if invisited is NULL, newEntry->next is NULL.
        newEntry->next = unvisited;
        unvisited = newEntry;

        // Check if we found the goal while adding nodes to lists.
        if (strcmp(current->aSource, goalNode) == 0){
            foundGoal = 1;
        }
        // then we move to next node to iterate through.
        current = current->next;
    }

    if (!foundStart || !foundGoal){ // 
        printf("Lähtö- tai kohdesolmua ei löytynyt, kokeile uudelleen.\n");
        
        // Free memory before returning
        while (unvisited != NULL){
            DLIST *temp = unvisited;
            unvisited = unvisited->next;
            free(temp->aCurrent);
            free(temp->iDistanceBetween);
            if (temp->aPreviousNode != NULL){
                free(temp->aPreviousNode);
            }
            free(temp);
        }
        return *graph;
    }
    // the main algorithm to find shortest path
    while (unvisited != NULL){
        DLIST *current = unvisited;
        DLIST *rootNode = current;
        while (current != NULL){
            // while we have unvisited nodes and the current node isnt empty, 
            // if current nodes distance is smaller than  rootNodes, rootnode becomes current node.
            if (*current->iDistanceBetween < *rootNode->iDistanceBetween){
                rootNode = current;
            }
            current = current->next; // move to next node
        }
        // if rootNode has "infinite" distance, there is no paths.
        if (*rootNode->iDistanceBetween == __INT_MAX__){
            break;
        }

        // we have now visited root node and so lets move it to be the next one
        if (rootNode == unvisited){ // if rootNode in unvisited list first pointer, 
            unvisited = unvisited->next; // update head pointer to be the next one in the list for next found comparison.
        } else { 
            // if rootNode is somewhere else in the list, find previous node and change its next pointer.
            DLIST *prev = unvisited; // find unvisited node with the smallest distance that isnt rootNode
            while (prev->next != rootNode) {
                prev = prev->next; // move to the next node
            }
            // now prev is the node before rootNode
            prev->next = rootNode->next; // skip rootnode and remove it from the list. 
        }
        // lets add rootNode to visited node list
        rootNode->next = visited;
        visited = rootNode;

        // check if rootNode is the goal user gave, if so we stop
        if (strcmp(rootNode->aCurrent, goalNode) == 0) {
            break;
        }

        // update distances of neighbouring nodes.
        NODE_G *graphNode = graph;
        // old rootNode is deleted and there is a new one updated, lets find that one from graph
        while (graphNode != NULL) {
            if (strcmp(graphNode->aSource, rootNode->aCurrent) == 0){
                // found the matching rootNode from graph, lets look at edge nodes
                EDGE *edge = graphNode->edges;
                while(edge != NULL) {
                    // look for edge destinatios in unvisited list
                    DLIST *neighbor = unvisited;
                    while (neighbor != NULL){
                        if (strcmp(neighbor->aCurrent, edge->aDestination) == 0){
                            // calculate the distances
                            int newDist = *rootNode->iDistanceBetween + edge->iDistance;
                            // check if this distance is more accurate than the old one, is so update
                            if (newDist < *neighbor->iDistanceBetween){
                                *neighbor->iDistanceBetween = newDist;
                                if (neighbor->aPreviousNode != NULL){
                                    free(neighbor->aPreviousNode);
                                }
                                neighbor->aPreviousNode = malloc(strlen(rootNode->aCurrent) + 1);
                                if (neighbor->aPreviousNode != NULL){
                                    strcpy(neighbor->aPreviousNode, rootNode->aCurrent);
                                }
                            }
                            break;
                        } // update neighbor, graphNode and edge pointers for next round
                        neighbor = neighbor->next;
                    }
                    edge = edge->next;
                }
                break;
            }
            graphNode = graphNode->next;
        }
    }
    // open the user given outputfile.txt
    if ((file = fopen(outputFile, "a")) == NULL){
        perror("Tiedoston avaaminen epäonnistui, lopetetaan.");
        exit(0);
    }

    // check if goalnode is in the visited list
    DLIST *goalList = visited;
    while (goalList != NULL && strcmp(goalList->aCurrent, goalNode) != 0){
        goalList = goalList->next;
    }

    if (goalList == NULL || *goalList->iDistanceBetween == __INT_MAX__){
        printf("Reittiä ei löydy solmusta %s solmuun %s, kokeile eri syötteitä.\n", startNode, goalNode);

    } else {
        char *path[50]; // array to store path nodes
        int pathCount = 0; // count to count the distance from start to goal
        // travel from goal node back to start node and count path
        DLIST *curr = goalList;
        path[pathCount++] = curr->aCurrent;  // add current goal to path array in path[0], then path[1] next one etc

        while (curr != NULL && curr->aPreviousNode != NULL){
            // Find node with matching name
            DLIST *prev = visited;
            while (prev != NULL){
                if (strcmp(prev->aCurrent, curr->aPreviousNode) == 0){
                    path[pathCount++] = prev->aCurrent;
                    curr = prev;
                    break;
                }
                prev = prev->next;
            }

            if (prev == NULL){
                break; // if theres no previous, node lets break
            }
        }
            // Finally time to print the thing to user and file. write is on append mode.
        printf("Lyhin reitti solmusta %s solmuun %s: \n", startNode, goalNode);
        for (int i = pathCount - 1; i >= 0; i--){
            // we have the path array, start reversed because we appended path array goal first wrong way
            printf("%s", path[i]); // print travelled node, then ->, if no nodes left, print distance.
            fprintf(file, "%s", path[i]);
            if (i > 0){
                printf(" -> ");
                fprintf(file, " -> ");
            }
                
            }
            printf(" = %d\n", *goalList->iDistanceBetween);      // print the distance
            fprintf(file, " = %d\n", *goalList->iDistanceBetween); // in file
            fclose(file); // close file after
            printf("Reitti tallennettu tiedostoon %s\n", outputFile);
            // free memory from all lists untill they are empty
            while (visited != NULL)
            {
                DLIST *temp = visited;
                visited = visited->next;
                free(temp->aCurrent);
                free(temp->iDistanceBetween);
                if (temp->aPreviousNode != NULL){
                    free(temp->aPreviousNode);
                }
                free(temp);
            }

        while (unvisited != NULL){
            DLIST *temp = unvisited;
            unvisited = unvisited->next;
            free(temp->aCurrent);
            free(temp->iDistanceBetween);
            if (temp->aPreviousNode != NULL){
                free(temp->aPreviousNode);
            }
            free(temp);
        }
    }
    return *graph;
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
    current->edges = NULL;

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
