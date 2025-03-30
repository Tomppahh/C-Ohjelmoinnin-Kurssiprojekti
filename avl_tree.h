#ifndef AVL_TREE_H
#define AVL_TREE_H



int height(NODE_BT *node);
int max(int a, int b);
NODE_BT *rotateRight(NODE_BT *y);
NODE_BT *rotateLeft(NODE_BT *x);
int getBalance(NODE_BT *node);
NODE_BT* createNode_AVL(const char* name, int number);
NODE_BT* insertNode_AVL(NODE_BT* node, const char* name, int number);

#endif
