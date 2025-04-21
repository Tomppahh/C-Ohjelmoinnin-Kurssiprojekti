//binarytree.h

#ifndef BINARYTREE_H
#define BINARYTREE_H

#define LENGTH 30
#define SPACING 15 // Can change the space between printed nodes

typedef enum { RED, BLACK } COLOR; // Red == 0 and Black == 1

//defining a binary tree node
typedef struct nodeTree {
    struct nameList *pNameList;
    int iCount;
    int height;
    COLOR color;
    struct nodeTree *left;
    struct nodeTree *right;
    struct nodeTree *parent;
} NODE_BT;

int binaryTreeMenu (void);
int balanceSelectionMenu (void);
void treeMenuLogic(void);
NODE_BT *depthFirstSearch(NODE_BT *root, const char *searchInput);
NODE_BT *widthFirstSearch(NODE_BT *root, const char *searchInput);
void writeFileTree(const char* filename, NODE_BT* root);
int askValue(void);
void printTree(NODE_BT* root);
void printTreeHelper(NODE_BT* root, int iSpace, int* iPrinted, int iMaxPrinted);
void freeNameList(NODE_BT* root);
void writeFileDF(NODE_BT* root, const char* searchInput, const char* filename);
NODE_BT *writeFileDFHelper(NODE_BT* root, const char* searchInput, FILE* write);
void writeFileWF(NODE_BT* root, const char* searchInput, const char* filename);
NODE_BT *BinaryTreeSearch(NODE_BT *root, const char *searchInput);
NODE_BT *removeNode(NODE_BT *root, const char *searchInput);
void makeList(NODE_BT *root, NODE_BT **NodeList, int *iIndex);
int countNodes(NODE_BT *root);
NODE_BT *buildBalancedTree(NODE_BT **NodeList, int iStart, int iEnd);



#endif
