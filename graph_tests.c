// New file for week 12 tests, copy base stuff from binary_tree_tests without the tests and modify for graph.h/graph.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "graph.h"
#include "common.h"
#include "namelist.h"
#include "test_results.h"

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

// Helper function to create a test graph file
void createTestGraphFile(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL){
        printf("Error creating test file\n");
        return;
    }

    // Write header
    fprintf(file, "Source;Destination;Distance\n");

    // Write graph data
    fprintf(file, "A;B;5\n");
    fprintf(file, "A;C;7\n");
    fprintf(file, "B;D;9\n");
    fprintf(file, "C;D;12\n");
    fprintf(file, "D;E;3\n");

    fclose(file);
}

// Helper function to check if a node has an edge to a destination with expected distance
int hasEdge(NODE_G *node, const char *destination, int expectedDistance){
    if (node == NULL)
        return 0;

    EDGE *edge = node->edges;
    while (edge != NULL){
        if (strcmp(edge->aDestination, destination) == 0 && edge->iDistance == expectedDistance){
            return 1;
        }
        edge = edge->next;
    }
    return 0;
}

// Helper function to find a node in the graph
NODE_G *findNode(NODE_G *graph, const char *name){
    NODE_G *current = graph;
    while (current != NULL){
        if (strcmp(current->aSource, name) == 0){
            return current;
        }
        current = current->next;
    }
    return NULL;
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

    // Test 7: Remove node B
    removeGraphNode(&nodeList, "B");
    runTest(&passed, &failed, findNode(nodeList, "B") == NULL, "Solmu 'B' pitäisi olla poistunut graafista");


    // Free the first test graph
    freeGraph(nodeList);
    nodeList = NULL;

    // Test 8: Create a test graph file and build graph from file
    const char *testFile = "test_graph.txt";
    createTestGraphFile(testFile);
    nodeList = buildGraphFromFile(nodeList, testFile);

    runTest(&passed, &failed, nodeList != NULL, "Graafin rakentaminen tiedostosta onnistui");

    // Test 9: Verify nodes from file exist
    NODE_G *nodeA_file = findNode(nodeList, "A");
    NODE_G *nodeB_file = findNode(nodeList, "B");
    NODE_G *nodeC_file = findNode(nodeList, "C");
    NODE_G *nodeD_file = findNode(nodeList, "D");
    NODE_G *nodeE_file = findNode(nodeList, "E");

    runTest(&passed, &failed, nodeA_file != NULL, "Solmu 'A' löytyy tiedostosta rakennetusta graafista");
    runTest(&passed, &failed, nodeB_file != NULL, "Solmu 'B' löytyy tiedostosta rakennetusta graafista");
    runTest(&passed, &failed, nodeC_file != NULL, "Solmu 'C' löytyy tiedostosta rakennetusta graafista");
    runTest(&passed, &failed, nodeD_file != NULL, "Solmu 'D' löytyy tiedostosta rakennetusta graafista");
    runTest(&passed, &failed, nodeE_file != NULL, "Solmu 'E' löytyy tiedostosta rakennetusta graafista");

    // Test 10: Verify edges were created correctly
    runTest(&passed, &failed, hasEdge(nodeA_file, "B", 5), "Solmulla 'A' on reuna solmuun 'B' etäisyydellä 5");
    runTest(&passed, &failed, hasEdge(nodeA_file, "C", 7), "Solmulla 'A' on reuna solmuun 'C' etäisyydellä 7");
    runTest(&passed, &failed, hasEdge(nodeB_file, "A", 5), "Solmulla 'B' on reuna solmuun 'A' etäisyydellä 5");
    runTest(&passed, &failed, hasEdge(nodeB_file, "D", 9), "Solmulla 'B' on reuna solmuun 'D' etäisyydellä 9");

    // Test 11: Add a new edge between existing nodes
    addEdge(nodeA_file, "D", 8);
    runTest(&passed, &failed, hasEdge(nodeA_file, "D", 8), "Uusi reuna lisätty solmusta 'A' solmuun 'D'");

    // Test 12: Update an existing edge
    addEdge(nodeA_file, "B", 6);
    runTest(&passed, &failed, hasEdge(nodeA_file, "B", 6), "Olemassa oleva reuna päivitetty solmusta 'A' solmuun 'B'");

    // Test 13: Remove a node and verify its edges are removed
    removeGraphNode(&nodeList, "C");
    runTest(&passed, &failed, findNode(nodeList, "C") == NULL, "Solmu 'C' on poistettu graafista");
    runTest(&passed, &failed, !hasEdge(nodeA_file, "C", 7), "Reuna solmusta 'A' solmuun 'C' on poistettu");
    runTest(&passed, &failed, !hasEdge(nodeD_file, "C", 12), "Reuna solmusta 'D' solmuun 'C' on poistettu");

    // Free the second test graph
    freeGraph(nodeList);

    // Remove test file
    remove(testFile);

    printf("\nGRAPH TEST SUMMARY: %d tests passed, %d tests failed\n\n", passed, failed);
    recordTestResult("GRAPH_TESTS", passed, failed); // pass test results to test_results.c
    return 0;
}
