
//Red-Black Tree.

//Creates a new node in the binary tree
NODE_BT* createTreeNode(const char* name, int number) {
    NODE_BT* newNode = (NODE_BT*)malloc(sizeof(NODE_BT));
    NAME_LIST* nameList = createNameList(name, NULL);
    newNode->iCount = number;
    newNode->color = RED; // New nodes are red
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;
    newNode->pNameList = nameList;
    return newNode;
} 

//Functionality to build a binary tree from a text file, reads the file and builds a tree from it
NODE_BT* buildFromFile_RB(const char* filename) {
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
            root = insertNode_RBT(root, name, number); // Change insertNode to insertNode_RBT or insertNode_AVL
        } else {
            printf("Error: Invalid formatting in row\n");
        }
    }
    fclose(read);
    
    return root;
}

void rotateLeft(NODE_BT** root, NODE_BT* x) {
    NODE_BT* y = x->right;
    x->right = y->left;
    if (y->left != NULL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if(x->parent == NULL) {
        *root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
    return;
}

void rotateRight(NODE_BT** root, NODE_BT* y) {
    NODE_BT* x = y->left;
    y->left = x->right;
    if (x->right != NULL) {
        x->right->parent = y;
    }
    x->parent = y->parent;
    if (y->parent == NULL) {
        *root = x;
    } else if (y == y->parent->left) {
        y->parent->left = x;
    } else {
        y->parent->right = x;
    }
    x->right = y;
    y->parent = x;
}

void fixInsert(NODE_BT** root, NODE_BT* z) {
    while (z->parent && z->parent->color == RED) {
        NODE_BT* gp = z->parent->parent; // gp is grandparent

        if (z->parent == gp->left) {
            NODE_BT* y = gp->right; // uncle
            if (y && y->color == RED) {
                // Case 1: uncle is red -> recolor
                z->parent->color = BLACK;
                y->color = BLACK;
                gp->color = RED;
                z = gp; // Move up the tree
            } else {
                // Case 2 & 3: uncle is black
                if (z == z->parent->right) {
                    // Case 2: left-right -> rotate left
                    z = z->parent;
                    rotateLeft(root, z);
                }
                // Case 3: left-left -> rotate right
                z->parent->color = BLACK;
                gp->color = RED;
                rotateRight(root, gp);
            }
        } else {
            // Mirror case (right side)
            NODE_BT* y = gp->left; // uncle
            if (y && y->color == RED) {
                // Case 1: uncle is red -> recolor
                z->parent->color = BLACK;
                y->color = BLACK;
                gp->color = RED;
                z = gp;
            } else {
                // Case 2 & 3: uncle is black
                if (z == z->parent->left) {
                    // Case 2: right-left -> rotate right
                    z = z->parent;
                    rotateRight(root, z);
                }
                // Case 3: right-right -> rotate left
                z->parent->color = BLACK;
                gp->color = RED;
                rotateLeft(root, gp);
            }
        }
    }
    (*root)->color = BLACK; // Always make root black
}

NODE_BT* insertNode_RBT(NODE_BT* root, const char* name, int number) {
    NODE_BT* parent = NULL;
    NODE_BT* current = root;

    // Standard insertion. 
    while (current) {
        parent = current;
        if (number == current->iCount) {
            // Duplicate iCount
            append(root->pNameList, name);
            return root;
        } else if (number < current->iCount) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    // Create new node and link it
    NODE_BT* newNode = createTreeNode(name, number);
    newNode->parent = parent;

    if (parent == NULL) {
        root = newNode; // Tree was empty
    } else if (number < parent->iCount) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }

    // Restore Red-Black Tree balance
    fixInsert(&root, newNode);
    return root;
}
