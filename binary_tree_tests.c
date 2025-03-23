#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "binarytree.h"
#include "namelist.h"


// Function takes integers passed and failed from main, with the condition to pass the test and the message to print.
void runTest(int *passed, int *failed, int condition, const char *message) {
    if (condition) {
        printf("PASS: %s\n", message);
        (*passed)++;
    } else {
        printf("FAIL: %s\n", message);
        (*failed)++;
    }
    printf("\n");
}

// Create a test input file for buildFromFile()
void createTestInputFile(const char* pFileName) {
    FILE* Write = NULL;
    if ((Write = fopen(pFileName, "w")) == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }
    fprintf(Write, "Etunimi;Lukumäärä\n");
    fprintf(Write, "Tuomas;10\n");
    fprintf(Write, "Tommi;15\n");
    fprintf(Write, "Eelis;20\n");
    fclose(Write);
    return;
}

// main function where the tests are done.

int main() {
    int passed = 0;
    int failed = 0;
    
    // Tests can be added here

    // Test 1: createTreeNode
    NODE_BT* Node = NULL;
    Node = createTreeNode("TestNode", 12345);
    runTest(&passed, &failed, Node != NULL && strcmp(Node->pNameList->aName, "TestNode") == 0 && Node->iCount == 12345, "createTreeNode creates node correctly");


    // Test 2: instertNode
    NODE_BT* root = NULL;
    root = insertNode(root, "Tuomas", 15); // Root
    root = insertNode(root, "Tommi", 10); // Should be left child
    root = insertNode(root, "Eelis", 20); // Should be right child

    runTest(&passed, &failed, root != NULL && root->iCount == 15, "insertNode sets root correctly");
    runTest(&passed, &failed, root->left != NULL && root->left->iCount == 10, "insertNode inserts left child correctly");
    runTest(&passed, &failed, root->right != NULL && root->right->iCount == 20, "insertNode inserts right child correctly");


    // Test 3: depthFirstSearch
    // Search by name
    NODE_BT* result = NULL;
    result = depthFirstSearch(root, "Tommi");
    runTest(&passed, &failed, result != NULL && strcmp(result->pNameList->aName, "Tommi") == 0, "depthFirstSearch finds node by name");

    // Search by number
    result = depthFirstSearch(root, "20");
    runTest(&passed, &failed, result != NULL && result->iCount == 20, "depthFirstSearch finds node by number");

    // Test 4: widthFirstSearch
    result = widthFirstSearch(root, "20");
    runTest(&passed, &failed, result != NULL && strcmp(result->pNameList->aName, "Eelis") == 0, "widthFirstSearch finds node by number");

    // Search for a non-existent term
    result = widthFirstSearch(root, "Nonexistent");
    runTest(&passed, &failed, result == NULL, "widthFirstSearch returns NULL for non-existent node");


    // Test 5: buildFromFile
    const char* testInputFilename = "test_input.txt";
    createTestInputFile(testInputFilename);
    NODE_BT* fileTree = buildFromFile(testInputFilename);
    // ("Tuomas", 10) becomes the root.
    // ("Tommi", 15) is inserted → goes to right) and then ("Eelis", 20) → goes to Tommi's right).
    runTest(&passed, &failed, fileTree != NULL && strcmp(fileTree->pNameList->aName, "Tuomas") == 0, "buildFromFile builds tree with correct root");
    runTest(&passed, &failed,
            fileTree->right != NULL && strcmp(fileTree->right->pNameList->aName, "Tommi") == 0, "buildFromFile inserts second node correctly");
    runTest(&passed, &failed, fileTree->right->right != NULL && strcmp(fileTree->right->right->pNameList->aName, "Eelis") == 0, "buildFromFile inserts third node correctly");

    // Test 6: Names with same numbers in the test input file for the width and depth search
    root = NULL;
    root = insertNode(root, "Tuomas", 15); // Root
    root = insertNode(root, "Tommi", 10);  // Should be left child
    root = insertNode(root, "Eelis", 20);  // Should be right child
    root = insertNode(root, "Justus", 20); // Should be right child of Eelis
    root = insertNode(root, "Kalle", 20); // Should be right child of Justus
    root = insertNode(root, "Kaijakoo", 15);  // Should be left child of Tuomas
    root = insertNode(root, "Kaija", 15);  // Should be right child of Kaijakoo

    // search with number 20 should return all the names with number 20, does nameList contain all names with number 20
    result = depthFirstSearch(root, "20");
    
    // free memory
    freeTree(root);
    
    // Print summary of passed and failed tests
    printf("\nSummary: %d tests passed, %d tests failed\n", passed, failed);

    return 0;
}
