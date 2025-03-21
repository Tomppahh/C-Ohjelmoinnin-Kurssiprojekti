#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binarytree.h"

//Creates a new node in the binary tree
NODE_BT* createTreeNode(const char* name, int number) {
    NODE_BT* newNode = (NODE_BT*)malloc(sizeof(NODE_BT));
    strcpy(newNode->aName, name);
    newNode->iCount = number;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

//Functionality to insert a node into the binary tree
NODE_BT* insertNode(NODE_BT* root, const char* name, int number) {
    if (root==NULL) {
        return createTreeNode(name,number);
    }
    if (number < root->iCount) {
        root->left = insertNode(root->left, name, number);
    } else if (number > root->iCount) {
        root->right = insertNode(root->right, name, number);
    }
    return root;
}

//Functionality to build a binary tree from a text file, reads the file and builds a tree from it
NODE_BT* buildFromFile(const char* filename) {
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
            root = insertNode(root, name, number);
        } else {
            printf("Error: Invalid formatting in row\n");
        }
    }
    fclose(read);
    return root;
}

//Recursive function that helps with the writing process.
void writeTreeNodes(FILE* write, NODE_BT* root) {
    if (root != NULL) {
        fprintf(write, "%s,%d\n", root->aName, root->iCount);
        writeTreeNodes(write, root->left);
        writeTreeNodes(write, root->right);
    }
}

//Function that writes the entire binary tree to the file
void writeFileTree(const char* filename, NODE_BT* root) {
    FILE* write = NULL;
    if ((write = fopen(filename, "w")) == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }
    writeTreeNodes(write,root);
    fclose(write);
} 

// Calls the print function.
void printTree(NODE_BT* root) {
    int iPrintedCount = 0;
    printTreeHelper(root, 0, &iPrintedCount);
    return;
}

// Function that prints the tree as a tree like structure
void printTreeHelper(NODE_BT* root, int iSpace, int* iPrinted) {
    if (root == NULL || *iPrinted >= MAX_PRINTED_NODES) {
        return;
    }

    iSpace += SPACING;

    printTreeHelper(root->right, iSpace, iPrinted);

    if (*iPrinted < MAX_PRINTED_NODES) {
        printf("\n");
        for (int i = SPACING; i < iSpace; i++)
            printf(" ");
        printf("%6d\n", root->iCount);  // Allocate 6 spaces for alignment
        (*iPrinted)++;
    }

    printTreeHelper(root->left, iSpace, iPrinted);

    return;
}