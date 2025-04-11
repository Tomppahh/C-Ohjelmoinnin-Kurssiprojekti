// Static Rebuild
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binarytree.h"
#include "balance_tree.h"
#include "namelist.h"

//Creates a new node in the binary tree
NODE_BT* createTreeNode(const char* name, int number) {
    NODE_BT* newNode = (NODE_BT*)malloc(sizeof(NODE_BT));
    NAME_LIST* nameList = createNameList(name, NULL);
    newNode->iCount = number;
    newNode->color = RED; // New nodes are red
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;
    newNode->pNameList = nameList;
    return newNode;
} 

//Functionality to insert a node into the binary tree
NODE_BT* insertNode(NODE_BT* root, const char* name, int number) {
    if (root==NULL) {
        return createTreeNode(name,number);
    }
    if (number < root->iCount || (number == root->iCount && strcmp(name, root->pNameList->aName) < 0)) {
        root->left = insertNode(root->left, name, number);
    } else {
        root->right = insertNode(root->right, name, number);
    }
    return root;
}

//Functionality to build a binary tree from a text file, reads the file and builds a tree from it
NODE_BT* buildFromFile_SR(const char* filename) {
    FILE* read = NULL;
    if ((read = fopen(filename, "r")) == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }
    NODE_BT* root = NULL;
    char row[100];
    //skipping the header row of the file
    if (fgets(row,sizeof(row),read)) {
        row[strcspn(row, "\n")] = 0;
        if (strcmp(row,"Etunimi;Lukumäärä") == 0) {
        }
    }
    while (fgets(row, sizeof(row), read)) {
        row[strcspn(row, "\n")] = 0;
        char name[30];
        int number;
        if (sscanf(row, "%[^;];%d", name, &number) == 2) {
            root = insertNode(root, name, number); // Change insertNode to insertNode_RBT or insertNode_AVL
        } else {
            printf("Error: Invalid formatting in row\n");
        }
    }
    fclose(read);

    root = balanceTree(root); // Balances the tree
    return root;
}

// The main function that is called to balance a tree.
NODE_BT* balanceTree(NODE_BT *root) {
    int iIndex = 0;
    int iNodeCount = countNodes(root);
    if (iNodeCount == 0) {
        return (NULL);
    }

    NODE_BT **NodeList = (NODE_BT **)malloc(iNodeCount * sizeof(NODE_BT));
    if (NodeList == NULL) {
        perror("Muistin varaus epäonnistui, lopetetaan");
        exit(0);
    }

    makeList(root, NodeList, &iIndex);

    
    NODE_BT *newRoot = buildBalancedTree(NodeList, 0, iNodeCount - 1);
    free(NodeList);
    return (newRoot);
}

// Counts the number of nodes
int countNodes(NODE_BT *root) {
    if(root == NULL) {
        return 0;
    }
    // Use recursion to count all nodes from left and to right.
    return (1 + countNodes(root->left) + countNodes(root->right));
} 

// Use recursion to make a largest to smallest list
void makeList(NODE_BT *root, NODE_BT **NodeList, int *iIndex) {
    if (root == NULL) {
        return;
    }
    makeList(root->left, NodeList, iIndex); // Goes all the way to the left of the tree
    NodeList[*iIndex] = root; // Adds the node to the list
    (*iIndex)++;
    makeList(root->right, NodeList, iIndex); // Goes to the right node
    return;
}

// Use recursion to balance the tree based on the created list
NODE_BT *buildBalancedTree(NODE_BT **NodeList, int iStart, int iEnd) {
    int iMiddle;
    
    if (iStart > iEnd) {
        return NULL;
    }

    iMiddle = (iStart + iEnd)>>1; // Gets the lists middle point
    NODE_BT *root = NodeList[iMiddle]; // Sets the node to be the node in the middle of the list.

    // Recursive calls
    root->left = buildBalancedTree(NodeList, iStart, iMiddle -1);
    root->right = buildBalancedTree(NodeList, iMiddle + 1, iEnd);

    return root;
}