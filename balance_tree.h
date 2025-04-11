#ifndef BALANCE_TREE_H
#define BALANCE_TREE_H

NODE_BT* createTreeNode(const char* name, int number);
NODE_BT* insertNode(NODE_BT* root, const char* name, int number);
NODE_BT* buildFromFile_SR(const char* filename);
NODE_BT* balanceTree(NODE_BT *root);
int countNodes(NODE_BT *root);
void makeList(NODE_BT *root, NODE_BT **NodeList, int *iIndex);
NODE_BT *buildBalancedTree(NODE_BT **NodeList, int iStart, int iEnd);

#endif