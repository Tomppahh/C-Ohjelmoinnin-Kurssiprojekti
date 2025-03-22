//binarytree.h

#ifndef BINARYTREE_H
#define BINARYTREE_H

#define LENGTH 30
#define SPACING 4 // Can change the space between printed nodes

//defining a binary tree node
typedef struct nodeTree {
    struct nameList *pNameList;
    int iCount;
    struct nodeTree *left;
    struct nodeTree *right;
} NODE_BT;


NODE_BT* createTreeNode(const char* name, int number);
NODE_BT* insertNode(NODE_BT* root, const char* name, int number);
NODE_BT* buildFromFile(const char* filename);
NODE_BT *depthFirstSearch(NODE_BT *root, const char *searchInput);
NODE_BT *widthFirstSearch(NODE_BT *root, const char *searchInput);
void writeFileTree(const char* filename, NODE_BT* root);
int askValue(void);
void printTree(NODE_BT* root);
void printTreeHelper(NODE_BT* root, int iSpace, int* iPrinted, int iMaxPrinted);
void writeFileDF(NODE_BT* root, const char* searchInput, const char* filename);
NODE_BT *writeFileDFHelper(NODE_BT* root, const char* searchInput, FILE* write);
void writeFileWF(NODE_BT* root, const char* searchInput, const char* filename);

#endif