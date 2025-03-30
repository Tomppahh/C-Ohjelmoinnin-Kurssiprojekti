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
    root = insertNode(root, "Kaijakoo", 15);  // Should be left child of Kalle
    root = insertNode(root, "Kaija", 15);  // Should be right child of Kaijakoo

    // search with number 20 should return all the names with number 20, does nameList contain all names with number 20
    result = depthFirstSearch(root, "20");
    // WEEK 11 TESTS

    // Test 1: BinaryTreeSearch function finds the first name with a value, there can be same values.
    root = NULL;
    root = insertNode(root, "Tuomas", 15);   // Root
    root = insertNode(root, "Tommi", 10);    // Should be left child
    root = insertNode(root, "Eelis", 20);    // Should be right child
    root = insertNode(root, "Justus", 20);   // Should be right child of Eelis
    root = insertNode(root, "Kalle", 20);    // Should be right child of Justus
    root = insertNode(root, "Kaijakoo", 15); // Should be left child of Kalle
    root = insertNode(root, "Kaija", 15);    // Should be right child of Kaijakoo
    result =  BinaryTreeSearch(root, "20"); //  should return Eelis

    // Test 2: BinaryTreeSearch search with a name, not a number, should tell user that isnt possible to search with name
    root = NULL;
    root = insertNode(root, "Tuomas", 15);   // Root
    root = insertNode(root, "Tommi", 10);    // Should be left child
    root = insertNode(root, "Eelis", 20);    // Should be right child
    root = insertNode(root, "Justus", 20);   // Should be right child of Eelis
    root = insertNode(root, "Kalle", 20);    // Should be right child of Justus
    root = insertNode(root, "Kaijakoo", 15); // Should be left child of Kalle
    root = insertNode(root, "Kaija", 15);    // Should be right child of Kaijakoo
    result = BinaryTreeSearch(root, "Kalle"); // should tell user that cant find with name

    // Test 3: RemoveNode function removes nodes from tree correctly.
    root = NULL;
    root = insertNode(root, "Tuomas", 15);    // Root
    root = insertNode(root, "Tommi", 10);     // Should be left child
    root = insertNode(root, "Eelis", 20);     // Should be right child
    root = insertNode(root, "Justus", 20);    // Should be right child of Eelis
    root = insertNode(root, "Kalle", 20);     // Should be right child of Justus
    root = insertNode(root, "Kaijakoo", 15);  // Should be left child of Kalle
    root = insertNode(root, "Kaija", 15);     // Should be right child of Kaijakoo
    result = removeNode(root, "Kalle"); // delete Kalle node
    result = depthFirstSearch(root, "Kalle");  // search for Kalle
    runTest(&passed, &failed, result == NULL, "removeNode successfully removed 'Kalle' node");

    // Test 4: BalanceTree function
    printf("Testing balanceTree function...\n");

    // First create a deliberately unbalanced tree (right-skewed)
    root = NULL;
    root = insertNode(root, "A", 10);
    root = insertNode(root, "B", 20);
    root = insertNode(root, "C", 30);
    root = insertNode(root, "D", 40);
    root = insertNode(root, "E", 50);
    root = insertNode(root, "F", 60);

    // Verify the tree is unbalanced (right-skewed) before balancing
    int depthRight = 0;
    NODE_BT *temp = root;
    while (temp != NULL){
        depthRight++;
        temp = temp->right;
    }
    runTest(&passed, &failed, depthRight >= 5, "Created a right-skewed unbalanced tree for testing");

    // Count nodes before balancing
    int nodeCountBefore = countNodes(root);
    // Apply balanceTree
    NODE_BT *balancedRoot = balanceTree(root);
    // Count nodes after balancing
    int nodeCountAfter = countNodes(balancedRoot);
    runTest(&passed, &failed, nodeCountBefore == nodeCountAfter,
            "balanceTree preserves all nodes from original tree");

    // Check if the balanced tree is more balanced by comparing depths
    int leftDepth = 0;
    int rightDepth = 0;
    temp = balancedRoot;
    while (temp != NULL){
        leftDepth++;
        temp = temp->left;
    }
    temp = balancedRoot;
    while (temp != NULL){
        rightDepth++;
        temp = temp->right;
    }
    runTest(&passed, &failed, abs(leftDepth - rightDepth) <= 1,
            "balanceTree creates a more balanced tree with similar left and right depths");

    // Verify all values can still be found in the balanced tree
    runTest(&passed, &failed, depthFirstSearch(balancedRoot, "10") != NULL,
            "balanceTree preserves node with value 10");
    runTest(&passed, &failed, depthFirstSearch(balancedRoot, "30") != NULL,
            "balanceTree preserves node with value 30");
    runTest(&passed, &failed, depthFirstSearch(balancedRoot, "60") != NULL,
            "balanceTree preserves node with value 60");

    // For a balanced tree with 6 nodes, the root should be near the median value
    runTest(&passed, &failed,balancedRoot != NULL &&(balancedRoot->iCount == 30 || balancedRoot->iCount == 40),
            "balanceTree places median value near root");

    // free memory
    freeTree(root);
    
    // Print summary of passed and failed tests
    printf("\nSummary: %d tests passed, %d tests failed\n", passed, failed);

    return 0;
}
