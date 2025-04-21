#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "binarytree.h"
#include "namelist.h"
#include "avl_tree.h"
#include "rb_tree.h" // Make sure this is included for Red-Black Tree functions

// Function takes integers passed and failed from main, with the condition to pass the test and the message to print.
void runTest(int *passed, int *failed, int condition, const char *message){
    if (condition){
        printf("PASS: %s\n", message);
        (*passed)++;
    }
    else{
        printf("FAIL: %s\n", message);
        (*failed)++;
    }
    printf("\n");
}
// Helper function to check AVL balance property
void checkAVLBalance(NODE_BT *node, int *isBalanced){
    if (node == NULL)
        return;

    int balanceFactor = height(node->left) - height(node->right);
    if (abs(balanceFactor) > 1){
        *isBalanced = 0;
        return;
    }

    checkAVLBalance(node->left, isBalanced);
    checkAVLBalance(node->right, isBalanced);
}
// Create a test input file for buildFromFile_AVL()
void createTestInputFile(const char *pFileName){
    FILE *Write = NULL;
    if ((Write = fopen(pFileName, "w")) == NULL){
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
int main(){
    int passed = 0;
    int failed = 0;

    // Tests can be added here

    // Test 1: createTreeNode
    NODE_BT *Node = NULL;
    Node = createTreeNode("TestNode", 12345);
    runTest(&passed, &failed, Node != NULL && strcmp(Node->pNameList->aName, "TestNode") == 0 && Node->iCount == 12345, "createTreeNode creates node correctly");

    // Test 2: instertNode
    NODE_BT *root = NULL;
    root = insertNode(root, "Tuomas", 15); // Root
    root = insertNode(root, "Tommi", 10);  // Should be left child
    root = insertNode(root, "Eelis", 20);  // Should be right child

    runTest(&passed, &failed, root != NULL && root->iCount == 15, "insertNode sets root correctly");
    runTest(&passed, &failed, root->left != NULL && root->left->iCount == 10, "insertNode inserts left child correctly");
    runTest(&passed, &failed, root->right != NULL && root->right->iCount == 20, "insertNode inserts right child correctly");

    // Test 3: depthFirstSearch
    // Search by name
    NODE_BT *result = NULL;
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

    // Test 5: buildFromFile_AVL
    const char *testInputFilename = "test_input.txt";
    createTestInputFile(testInputFilename);
    NODE_BT *fileTree = buildFromFile_AVL(testInputFilename);

    // Instead of checking exact tree structure, verify:
    // 1. The tree contains all three nodes
    // 2. The tree maintains AVL balance property
    // 3. The values are correctly stored

    // Check that all three names exist in the tree
    NODE_BT *tuomasNode = depthFirstSearch(fileTree, "Tuomas");
    NODE_BT *tommiNode = depthFirstSearch(fileTree, "Tommi");
    NODE_BT *eelisNode = depthFirstSearch(fileTree, "Eelis");

    runTest(&passed, &failed, tuomasNode != NULL && tuomasNode->iCount == 10,
            "buildFromFile_AVL correctly stores 'Tuomas' with count 10");

    runTest(&passed, &failed, tommiNode != NULL && tommiNode->iCount == 15,
            "buildFromFile_AVL correctly stores 'Tommi' with count 15");

    runTest(&passed, &failed, eelisNode != NULL && eelisNode->iCount == 20,
            "buildFromFile_AVL correctly stores 'Eelis' with count 20");

    // Check AVL balance property - no node should have a balance factor > 1
    int isBalanced = 1;
    checkAVLBalance(fileTree, &isBalanced);
    runTest(&passed, &failed, isBalanced,
            "buildFromFile_AVL creates a balanced AVL tree");

    // Test 6: Names with same numbers in the test input file for the width and depth search
    root = NULL;
    result = NULL;
    root = insertNode(root, "Tuomas", 15);   // Root
    root = insertNode(root, "Tommi", 10);    // Should be left child
    root = insertNode(root, "Eelis", 20);    // Should be right child
    root = insertNode(root, "Justus", 20);   // Should be right child of Eelis
    root = insertNode(root, "Kalle", 20);    // Should be right child of Justus
    root = insertNode(root, "Kaijakoo", 15); // Should be left child of Kalle
    root = insertNode(root, "Kaija", 15);    // Should be right child of Kaijakoo
    // search with number 20 should return all the names with number 20, does nameList contain all names with number 20
    result = depthFirstSearch(root, "20");

    // WEEK 11 TESTS
    // Test 1: BinaryTreeSearch function finds the first name with a value, there can be same values.
    root = NULL;
    result = NULL;
    root = insertNode(root, "Tuomas", 15);   // Root
    root = insertNode(root, "Tommi", 10);    // Should be left child
    root = insertNode(root, "Eelis", 20);    // Should be right child
    root = insertNode(root, "Justus", 20);   // Should be right child of Eelis
    root = insertNode(root, "Kalle", 20);    // Should be right child of Justus
    root = insertNode(root, "Kaijakoo", 15); // Should be left child of Kalle
    root = insertNode(root, "Kaija", 15);    // Should be right child of Kaijakoo
    result = BinaryTreeSearch(root, "20");   //  should return Eelis

    // Test 2: BinaryTreeSearch search with a name, not a number, should tell user that isnt possible to search with name
    root = NULL;
    result = NULL;
    root = insertNode(root, "Tuomas", 15);    // Root
    root = insertNode(root, "Tommi", 10);     // Should be left child
    root = insertNode(root, "Eelis", 20);     // Should be right child
    root = insertNode(root, "Justus", 20);    // Should be right child of Eelis
    root = insertNode(root, "Kalle", 20);     // Should be right child of Justus
    root = insertNode(root, "Kaijakoo", 15);  // Should be left child of Kalle
    root = insertNode(root, "Kaija", 15);     // Should be right child of Kaijakoo
    result = BinaryTreeSearch(root, "Kalle"); // should tell user that cant find with name

    // Test 3: RemoveNode function removes nodes from tree correctly.
    root = NULL;
    result = NULL;
    root = insertNode(root, "Tuomas", 15);    // Root
    root = insertNode(root, "Tommi", 10);     // Should be left child
    root = insertNode(root, "Eelis", 20);     // Should be right child
    root = insertNode(root, "Justus", 20);    // Should be right child of Eelis
    root = insertNode(root, "Kalle", 20);     // Should be right child of Justus
    root = insertNode(root, "Kaijakoo", 15);  // Should be left child of Kalle
    root = insertNode(root, "Kaija", 15);     // Should be right child of Kaijakoo
    result = removeNode(root, "Kalle");       // delete Kalle node
    result = depthFirstSearch(root, "Kalle"); // search for Kalle
    runTest(&passed, &failed, result == NULL, "removeNode successfully removed 'Kalle' node");

    // Test 4: BalanceTree function
    printf("Testing balanceTree function...\n");

    // First create a deliberately unbalanced tree (right-skewed)
    root = NULL;
    result = NULL;
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
    runTest(&passed, &failed, balancedRoot != NULL && (balancedRoot->iCount == 30 || balancedRoot->iCount == 40),
            "balanceTree places median value near root");

    // Test 7: Test AVL tree balancing
    printf("\nTesting AVL tree balancing...\n");

    // Create an unbalanced tree that should trigger AVL rotations
    NODE_BT *avlRoot = NULL;
    avlRoot = insertNode_AVL(avlRoot, "Z", 50);
    avlRoot = insertNode_AVL(avlRoot, "Y", 40);
    avlRoot = insertNode_AVL(avlRoot, "X", 30); // Should trigger a right rotation

    // Check if tree is balanced after insertions
    // Using direct height comparisons instead of the height function
    int avlLeftHeight = 0, avlRightHeight = 0;
    NODE_BT *leftNode = avlRoot->left;
    NODE_BT *rightNode = avlRoot->right;

    while (leftNode != NULL){
        avlLeftHeight++;
        leftNode = leftNode->left;
    }

    while (rightNode != NULL){
        avlRightHeight++;
        rightNode = rightNode->right;
    }

    runTest(&passed, &failed, abs(avlLeftHeight - avlRightHeight) <= 1,
            "AVL tree maintains balance after insertions");

    // Test right rotation happened correctly
    runTest(&passed, &failed, strcmp(avlRoot->pNameList->aName, "Y") == 0,
            "AVL right rotation places correct node as root");

    // Test for double rotation (left-right case)
    NODE_BT *avlRoot2 = NULL;
    avlRoot2 = insertNode_AVL(avlRoot2, "A", 10);
    avlRoot2 = insertNode_AVL(avlRoot2, "C", 30);
    avlRoot2 = insertNode_AVL(avlRoot2, "B", 20); // Should trigger a left-right rotation

    runTest(&passed, &failed, strcmp(avlRoot2->pNameList->aName, "B") == 0,
            "AVL left-right rotation places correct node as root");

    // Test 8: Red-Black Tree properties
    printf("\nTesting Red-Black Tree properties...\n");

    NODE_BT *rbRoot = NULL;
    // Changed insertNode_RB to insertNode_RBT based on the error message
    rbRoot = insertNode_RBT(rbRoot, "A", 10);
    rbRoot = insertNode_RBT(rbRoot, "B", 20);
    rbRoot = insertNode_RBT(rbRoot, "C", 30);
    rbRoot = insertNode_RBT(rbRoot, "D", 40);
    rbRoot = insertNode_RBT(rbRoot, "E", 50);

    // Check if root is black
    runTest(&passed, &failed, rbRoot->color == BLACK,
            "Red-Black Tree root is black");

    // Check path from root to any leaf has same number of black nodes
    int blackCount = 0;
    NODE_BT *temp2 = rbRoot; // Using temp2 instead of redefining temp
    while (temp2 != NULL){
        if (temp2->color == BLACK)
            blackCount++;
        temp2 = temp2->left;
    }

    int rightBlackCount = 0;
    temp2 = rbRoot;
    while (temp2 != NULL){
        if (temp2->color == BLACK)
            rightBlackCount++;
        temp2 = temp2->right;
    }

    runTest(&passed, &failed, blackCount == rightBlackCount,
            "Red-Black Tree has same number of black nodes on left and right paths");

    // Test 9: Binary tree search with duplicate values
    printf("\nTesting binary search with duplicates...\n");

    NODE_BT *dupRoot = NULL;
    dupRoot = insertNode(dupRoot, "First", 10);
    dupRoot = insertNode(dupRoot, "Second", 10);
    dupRoot = insertNode(dupRoot, "Third", 10);

    result = BinaryTreeSearch(dupRoot, "10");
    runTest(&passed, &failed, result == NULL,
            "BinaryTreeSearch returns NULL for search result (prints to stdout)");

    // Test 10: Test tree traversal with complex tree
    printf("\nTesting tree traversal with complex tree...\n");

    NODE_BT *complexRoot = NULL;
    result = NULL;
    complexRoot = insertNode(complexRoot, "Root", 50);
    complexRoot = insertNode(complexRoot, "Left", 25);
    complexRoot = insertNode(complexRoot, "Right", 75);
    complexRoot = insertNode(complexRoot, "LeftLeft", 12);
    complexRoot = insertNode(complexRoot, "LeftRight", 37);
    complexRoot = insertNode(complexRoot, "RightLeft", 62);
    complexRoot = insertNode(complexRoot, "RightRight", 87);

    // Test depth-first search finds deepest nodes
    result = depthFirstSearch(complexRoot, "12");
    runTest(&passed, &failed, result != NULL && strcmp(result->pNameList->aName, "LeftLeft") == 0,
            "Depth-first search finds deep left node");

    result = depthFirstSearch(complexRoot, "87");
    runTest(&passed, &failed, result != NULL && strcmp(result->pNameList->aName, "RightRight") == 0,
            "Depth-first search finds deep right node");
    result = NULL;

    // free memory
    freeTree(root);
    balancedRoot = NULL;
    freeTree(fileTree);
    freeTree(avlRoot);
    freeTree(avlRoot2);
    freeTree(rbRoot);
    freeTree(dupRoot);
    freeTree(complexRoot);
    freeTree(Node);

    // Print summary of passed and failed tests
    printf("\nSummary: %d tests passed, %d tests failed\n", passed, failed);

    return 0;
}