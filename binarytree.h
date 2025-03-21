//binarytree.h

#ifndef BINARYTREE_H
#define BINARYTREE_H

#define LENGTH 30
#define SPACING 4 // Can change the space between printed nodes
#define MAX_PRINTED_NODES 20 // Can change how many nodes are printed

//defining a binary tree node
typedef struct nodeTree {
    char aName[LENGTH];
    int iCount;
    struct nodeTree *left;
    struct nodeTree *right;
} NODE_BT;


NODE_BT* createTreeNode(const char* name, int number);
NODE_BT* insertNode(NODE_BT* root, const char* name, int number);
NODE_BT* buildFromFile(const char* filename);
void writeFileTree(const char* filename, NODE_BT* root);
void printTree(NODE_BT* root);
void printTreeHelper(NODE_BT* root, int iSpace, int iPrinted);

#endif