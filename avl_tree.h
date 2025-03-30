#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "binarytree.h"
#include "namelist.h"

// Lisää solmu AVL-puuhun
NODE_BT* avlInsert(NODE_BT* node, const char* name, int number);

// Poistaa solmun AVL-puusta
NODE_BT* avlRemove(NODE_BT* root, const char* searchInput);

#endif
