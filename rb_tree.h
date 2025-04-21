// rb_tree.h

#ifndef RB_TREE_H
#define RB_TREE_H

NODE_BT* createTreeNode(const char* name, int number);
NODE_BT* buildFromFile_RB(const char* filename);
void rotateLeft_RB(NODE_BT** root, NODE_BT* x);
void rotateRight_RB(NODE_BT** root, NODE_BT* y);
void fixInsert(NODE_BT** root, NODE_BT* z);
NODE_BT* insertNode_RBT(NODE_BT* root, const char* name, int number);

#endif