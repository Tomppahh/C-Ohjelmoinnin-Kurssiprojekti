#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binarytree.h"
#include "namelist.h"
#include "avl_tree.h"

// palauttaa solmun korkeuden
int height(NODE_BT *node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// palauttaa kahden kokonaisluvun maksimin
int max(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }    
}

NODE_BT *rotateRight(NODE_BT *y) {
    NODE_BT *x = y->left;
    NODE_BT *T2 = x->right;
    
    // Turns
    x->right = y;
    y->left = T2;
    
    // Update height
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    
    return x; // New node
}

NODE_BT *rotateLeft(NODE_BT *x) {
    NODE_BT *y = x->right;
    NODE_BT *T2 = y->left;
    
    // Turn
    y->left = x;
    x->right = T2;
    
    // Update height
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    
    return y; // New node
}

// Returns balance factor
int getBalance(NODE_BT *node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

// Creates new AVL node
NODE_BT* createNode_AVL(const char* name, int number) {
    NODE_BT* newNode = (NODE_BT*)malloc(sizeof(NODE_BT));
    if (newNode == NULL) {
        perror("Muistin varaus epäonnistui");
        exit(0);
    }
    newNode->pNameList = createNameList(name, NULL);
    newNode->iCount = number;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;  // Uusi solmu lisätään lehdenä
    return newNode;
}

// Adds node to tree
NODE_BT* insertNode_AVL(NODE_BT* root, const char* name, int number) {
    if (root == NULL) {
        return createNode_AVL(name,number);
    }
    if (number < root->iCount || (number == root->iCount && strcmp(name, root->pNameList->aName) < 0)) {
        root->left = insertNode_AVL(root->left, name, number);
    } else {
        root->right = insertNode_AVL(root->right, name, number);
    }
    
    // Updates height
    node->height = 1 + max(height(node->left), height(node->right));
    
    // Calculate balance
    int balance = getBalance(node);
    
    // Double left turn
    if (balance > 1 && (number < node->left->iCount || (number == node->left->iCount && strcmp(name, node->left->pNameList->aName) < 0)))
        return rotateRight(node);
    
    // Double right turn
    if (balance < -1 && (number > node->right->iCount || (number == node->right->iCount && strcmp(name, node->right->pNameList->aName) > 0)))
        return rotateLeft(node);
    
    // Left right turn
    if (balance > 1 && (number > node->left->iCount || (number == node->left->iCount && strcmp(name, node->left->pNameList->aName) > 0))) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    
    // Right left turn
    if (balance < -1 && (number < node->right->iCount || (number == node->right->iCount && strcmp(name, node->right->pNameList->aName) < 0))) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    
    return node;
}

// finds smallest node
NODE_BT *minValueNode(NODE_BT* node) {
    NODE_BT* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}
