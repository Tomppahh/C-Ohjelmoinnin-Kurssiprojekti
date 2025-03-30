#include "avl_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// palauttaa solmun korkeuden
int height(NODE_BT *node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// palauttaa kahden kokonaisluvun maksimin
int max(int a, int b) {
    return (a > b) ? a : b;
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
        exit(EXIT_FAILURE);
    }
    newNode->pNameList = createNameList(name, NULL);
    newNode->iCount = number;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;  // Uusi solmu lisätään lehdenä
    return newNode;
}

// Adds node to tree
NODE_BT* insertNode_AVL(NODE_BT* node, const char* name, int number) {
    if (root==NULL) {
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

// Can be used to delete nodes
NODE_BT* avlRemove(NODE_BT* root, const char* searchInput) {
    if (root == NULL)
        return root;
    
    // Check if numeric
    char* endPtr;
    int number = strtol(searchInput, &endPtr, 10);
    int isNumeric = (*endPtr == '\0');
    
    if (!isNumeric) {
        printf("Virhe: AVL-puu tukee poistamista vain numeroilla.\n");
        return root;
    }
    
    // Standard deletion
    if (number < root->iCount)
        root->left = avlRemove(root->left, searchInput);
    else if (number > root->iCount)
        root->right = avlRemove(root->right, searchInput);
    else {
        // if node found
        if ((root->left == NULL) || (root->right == NULL)) {
            NODE_BT* temp = root->left ? root->left : root->right;
            
            // No child
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                // one child
                *root = *temp;
            }
            freeNameList(temp);
            free(temp);
        } else {
            // two child
            NODE_BT* temp = minValueNode(root->right);
            strcpy(root->pNameList->aName, temp->pNameList->aName);
            root->iCount = temp->iCount;
            char buffer[20];
            sprintf(buffer, "%d", temp->iCount);
            root->right = avlRemove(root->right, buffer);
        }
    }
    
    if (root == NULL)
        return root;
    
    // Update height
    root->height = 1 + max(height(root->left), height(root->right));
    
    // Calculate balance
    int balance = getBalance(root);
    
    // Tasapainotus tapaukset:
    
    // Vasen vasen
    if (balance > 1 && getBalance(root->left) >= 0)
        return rotateRight(root);
    
    // Vasen oikea
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    
    // Oikea oikea
    if (balance < -1 && getBalance(root->right) <= 0)
        return rotateLeft(root);
    
    // Oikea vasen
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }
    
    return root;
}
