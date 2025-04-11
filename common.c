#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "linkedlist.h"
#include "binarytree.h"
#include "graph.h"
#include "common.h"
#include "namelist.h"

void filename(char *pFileName, char *pSentence) {
    printf("%s", pSentence);
    scanf("%s", pFileName);
    getchar();
    return;
}

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

// Function to free the memory of the binary tree
void freeTree(NODE_BT* root) {
    if (root == NULL) {
       return;
    }

    // using the function to traverse the binary tree recursively
    freeTree(root->left);
    freeTree(root->right);
    freeNameList(root);
    // lastly we free the root node
    free(root);
    
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