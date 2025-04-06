// New file for week 12 tests, copy base stuff from binary_tree_tests without the tests and modify for graph.h/graph.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "graph.h"

// Function takes integers passed and failed from main, with the condition to pass the test and the message to print.
void runTest(int *passed, int *failed, int condition, const char *message) {
    if (condition) {
        printf("PASS: %s\n", message);
        (*passed)++;
    } else {
        printf("FAIL: %s\n", message);
        (*failed)++;
    }
}

// main function where the tests are done.

int main() {
    int passed = 0;
    int failed = 0;

    NODE_G *nodeList = NULL; // Make a list

    // Test 1: Create node "A"
    NODE_G *nodeA = createGraphNode(&nodeList, "A");
    runTest(&passed, &failed, nodeA != NULL, "Solmun 'A' luonti palauttaa ei-NULL osoittimen");
    runTest(&passed, &failed, strcmp(nodeA->aSource, "A") == 0, "Solmun 'A' aSource on 'A'");
    runTest(&passed, &failed, nodeA->edges == NULL, "Solmulla 'A':lla ei ole reunoja aluksi");

    // Test 2: Create second node "B"
    NODE_G *nodeB = createGraphNode(&nodeList, "B");
    runTest(&passed, &failed, nodeB != NULL, "Solmun 'B' luonti palauttaa ei-NULL osoittimen");
    runTest(&passed, &failed, strcmp(nodeB->aSource, "B") == 0, "Solmun 'B' aSource on 'B'");

    // Test 3: Try to recreate A. Expect it to find the already existing one.
    NODE_G *nodeA2 = createGraphNode(&nodeList, "A");
    runTest(&passed, &failed, nodeA2 == nodeA, "Duplikaattisolmua 'A' ei luoda, vaan palautetaan olemassa oleva");

    // Test 4: Add edge to node A
    addEdge(nodeA, "B", 10);
    runTest(&passed, &failed, nodeA->edges != NULL, "Reunan lisäämisen jälkeen solmulla 'A' on vähintään yksi reuna");
    runTest(&passed, &failed, strcmp(nodeA->edges->aDestination, "B") == 0, "Ensimmäisen reunan määränpään tulee olla 'B'");
    runTest(&passed, &failed, nodeA->edges->iDistance == 10, "Ensimmäisen reunan etäisyydeksi tulee 10");

    // Test 5: Add second edge to node A
    addEdge(nodeA, "C", 20);
    // addEdge adds an edge at the beginning of the list, so new edge should be first.
    runTest(&passed, &failed, strcmp(nodeA->edges->aDestination, "C") == 0, "Toisen reunan lisäyksen jälkeen ensimmäisen reunan määränpään tulee olla 'C'");
    runTest(&passed, &failed, nodeA->edges->iDistance == 20, "Toisen reunan etäisyydeksi tulee 20");
    // Make sure the next is still the previous edge B
    runTest(&passed, &failed, nodeA->edges->next != NULL, "Solmulla 'A' on nyt vähintään kaksi reunaa");
    runTest(&passed, &failed, strcmp(nodeA->edges->next->aDestination, "B") == 0, "Toisena reunana solmussa 'A' tulee olla 'B'");

    // Test 6: Remove node B
    removeGraphNode(&nodeList, "B");
    runTest(&passed, &failed, nodeList->next == NULL, "Solmu 'B' pitäisi olla poistunut graafista");

    printf("\nSummary: %d tests passed, %d tests failed\n", passed, failed);
    return 0;
}
