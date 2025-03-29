//binarytree.h

#ifndef BINARYTREE_H
#define BINARYTREE_H

#define LENGTH 30
#define SPACING 4 // Can change the space between printed nodes

// typedef enum { RED, BLACK } COLOR;

//defining a binary tree node
typedef struct nodeTree {
    struct nameList *pNameList;
    int iCount;
    // COLOR color;
    struct nodeTree *left;
    struct nodeTree *right;
    // struct nodeTree *parent;
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
void freeTree(NODE_BT* root);
void writeFileDF(NODE_BT* root, const char* searchInput, const char* filename);
NODE_BT *writeFileDFHelper(NODE_BT* root, const char* searchInput, FILE* write);
void writeFileWF(NODE_BT* root, const char* searchInput, const char* filename);

/* Red-Black Tree. Didn't work with codegrade.
NODE_BT* insertNode_RBT(NODE_BT* root, const char* name, int number);
void fixInsert(NODE_BT** root, NODE_BT* z);
void rotateRight(NODE_BT** root, NODE_BT* y);
void rotateLeft(NODE_BT** root, NODE_BT* x);
*/
NODE_BT *removeNode(NODE_BT *root, const char *searchInput);
NODE_BT *buildBalancedTree(NODE_BT **NodeList, int iStart, int iEnd);
void makeList(NODE_BT *root, NODE_BT **NodeList, int *iIndex);
int countNodes(NODE_BT *root);
NODE_BT* balanceTree(NODE_BT *root);

#endif
