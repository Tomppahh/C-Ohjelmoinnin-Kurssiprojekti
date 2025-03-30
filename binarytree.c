#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binarytree.h"
#include "namelist.h"
#include "avl_tree.h"

//Creates a new node in the binary tree
NODE_BT* createTreeNode(const char* name, int number) {
    NODE_BT* newNode = (NODE_BT*)malloc(sizeof(NODE_BT));
    NAME_LIST* nameList = createNameList(name, NULL);
    newNode->iCount = number;
    //newNode->color = RED; // New nodes are red
    newNode->left = NULL;
    newNode->right = NULL;
    //newNode->parent = NULL;
    newNode->pNameList = nameList;
    return newNode;
} 

//Functionality to insert a node into the binary tree
NODE_BT* insertNode(NODE_BT* root, const char* name, int number) {
    if (root==NULL) {
        return createTreeNode(name,number);
    }
    if (number < root->iCount || (number == root->iCount && strcmp(name, root->pNameList->aName) < 0)) {
        root->left = insertNode(root->left, name, number);
    } else {
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
            root = insertNode(root, name, number); // Change insertNode to insertNode_RBT or insertNode_AVL
        } else {
            printf("Error: Invalid formatting in row\n");
        }
    }
    fclose(read);
    
    int iNodeCount = countNodes(root);
    int iIndex = 0;
    NODE_BT* newRoot = NULL;

    NODE_BT **NodeList = (NODE_BT **)malloc(iNodeCount * sizeof(NODE_BT));
    if (NodeList == NULL) {
        perror("Muistin varaus epäonnistui, lopetetaan");
        exit(0);
    }

    makeList(root, NodeList, &iIndex);

    for (int i = 0; i < iNodeCount; i++) {
        newRoot = insertNode_AVL(newRoot, NodeList[i]->pNameList->aName, NodeList[i]->iCount);
    }
    
    //root = balanceTree(root); // Balances the tree
    return newRoot;
}

//Recursive function that helps with the writing process.
void writeTreeNodes(FILE* write, NODE_BT* root) {
    if (root != NULL) {

        NAME_LIST *origin = root->pNameList; // Save the original pointer to the namelist, to prevent losing the pointer, when iterating through the list
        while (root->pNameList != NULL) {
            fprintf(write, "%s,%d\n", root->pNameList->aName, root->iCount);
            root->pNameList = root->pNameList->pNext;
        }
        root->pNameList = origin; // Restore the original pointer

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

// Asks the amount of nodes to be printed
int askValue(void) {
    int iValue = 0;
    printf("\n");
    printf("Anna kuinka monta alkiota tulostetaan (1 - 100): ");
    scanf("%d", &iValue);
    getchar();
    return(iValue);
}

// Calls the print function and asks user how many nodes to print.
void printTree(NODE_BT* root) {
    int iPrintedCount = 0;
    int iMaxPrinted = 0;
    
    do {
        iMaxPrinted = askValue();

        if(iMaxPrinted > 0 && iMaxPrinted <= 100) {
            break; // Valid input
        } else {
            printf("Virheellinen syöte.\n");
        }

    } while (iMaxPrinted < 1 || iMaxPrinted > 100);
    
    
    printTreeHelper(root, 0, &iPrintedCount, iMaxPrinted);
    return;
}

// Function that prints the tree as a tree like structure
void printTreeHelper(NODE_BT* root, int iSpace, int* iPrinted, int iMaxPrinted) {
    if (root == NULL || *iPrinted >= iMaxPrinted) {
        return;
    }

    iSpace += SPACING;

    printTreeHelper(root->right, iSpace, iPrinted, iMaxPrinted);

    if (*iPrinted < iMaxPrinted) {
        printf("\n");
        for (int i = SPACING; i < iSpace; i++)
            printf(" ");
        printf("%s %d\n",root->pNameList->aName, root->iCount);
        (*iPrinted)++;
    }

    printTreeHelper(root->left, iSpace, iPrinted, iMaxPrinted);

    return;
}

// Function to free the memory of the binary tree
void freeTree(NODE_BT* root) {
    if (root == NULL) {
       return;
    }

    // using the function to traverse the binary tree recursively
    freeTree(root->left);
    freeTree(root->right);
    freeNameList(root);
    // lastly we free the root node
    free(root);
    
}

void freeNameList(NODE_BT* root) {
    NAME_LIST* current = root->pNameList;
    NAME_LIST* next;

    // free size pointer
    if (current && current->size){
        free(current->size);
    }

    // then we free all name nodes
    while(current) {
        next = current->pNext;
        free(current);
        current = next;
    }
}

// Depth first search function for a name or count
NODE_BT *depthFirstSearch(NODE_BT *root, const char *searchInput){
    if (root == NULL) {
        printf("Puu on tyhjä");
        return NULL; // If the tree is empty or the search input is not found in the tree return NULL
    }

    // does the current node match the users search input
    if (nameExists(root->pNameList, searchInput) || atoi(searchInput) == root->iCount){   
        printf("Syvyyshaun tulos, löytetty alkio: %s, %d\n", getNames(root->pNameList), root->iCount); // if the searchInput is found, print the result
        return root; // return back the node that matches
    }

    // Keep going left if possible
    NODE_BT *searchLeft = depthFirstSearch(root->left, searchInput);
    if (searchLeft != NULL){
        return searchLeft; // If found on the left side, retun 
        
    }

    // Recursively search in the right subtree
    NODE_BT *searchRight = depthFirstSearch(root->right, searchInput);
    if (searchRight != NULL){
        return searchRight; // If found in the right subtree, return it
    }

    // If no match is found, print searchinput not found to user
    if (root->left == NULL && root->right == NULL){
        printf("Puussa ei ole arvoa '%s'.\n", searchInput);
    }
    return NULL;
}

NODE_BT *widthFirstSearch(NODE_BT *root, const char *searchInput)
{
    if (root == NULL){
        printf("Puu on tyhjä");
        return NULL; // Empty tree
    }

    // Initialize queue with dynamic memory allocation
    int capacity = 5000; // Start with 5000 nodes (miehet_2025.txt has 10.6k nodes for example)
    int front = 0;
    int rear = 0;

    NODE_BT **queue = (NODE_BT **)malloc(capacity * sizeof(NODE_BT *));
    if (queue == NULL)
    {
        perror("Muistin varaus epäonnistui");
        exit(0);
    }

    // Add root to the queue
    queue[rear++] = root;

    // lets go through the nodes until we have checked all of them
    while (front < rear)
    {
        // Check if queue needs resizing, if so we will double its size
        if (rear >= capacity)
        {
            int newCapacity = capacity * 2;
            NODE_BT **newQueue = (NODE_BT **)realloc(queue, newCapacity * sizeof(NODE_BT *));

            if (newQueue == NULL)
            {
                perror("Muistin uudelleen varaus epäonnistui");
                free(queue);
                return NULL;
            }

            queue = newQueue;
            capacity = newCapacity;
            printf("Queue capacity increased to %d\n", capacity);
        }

        // Get next node from queue
        NODE_BT *current = queue[front++];

        // Check if current node matches search criteria
        if (nameExists(current->pNameList, searchInput) || atoi(searchInput) == current->iCount)
        {
            printf("Leveyshaun tulos, löytetty alkio: %s, %d\n", getNames(current->pNameList), current->iCount);
            free(queue); // free memory
            return current;
        }

        // add left and right nodes to the queue
        if (current->left != NULL)
        {
            queue[rear++] = current->left;
        }
        if (current->right != NULL)
        {
            queue[rear++] = current->right;
        }
    }

    // if no match found tell the user
    if (front > rear){
        printf("Puussa ei ole arvoa %s.\n", searchInput);
    }
    
    free(queue); // free memory!
    return NULL;
}

NODE_BT *BinaryTreeSearch(NODE_BT *root, const char *searchInput){
    NODE_BT *original = root;
    if (root == NULL){
        printf("Puu on tyhjä\n");
        return NULL;
    }

    // Check if the input is numeric
    char *endPtr;
    int number = strtol(searchInput, &endPtr, 10);

    if (*endPtr != '\0'){ // if endPtr is anything else than null terminator, the input is not numeric.
        printf("Virhe: Binääripuuhaku tukee vain numeroita.\n");
        return NULL;
    }

    // Perform binary search
    while (root != NULL){
        if (number == root->iCount){
            printf("Nopein haun tulos, löytetty alkio: %s, %d\n", getNames(root->pNameList), root->iCount);
            root = original;
            return NULL;
        }
        // Traverse left or right based on the comparison
        // if number is smaller than root->iCount, root->left, else root->right.
        root = (number < root->iCount) ? root->left : root->right;
    }
    // If not found tell the user about it. 
    printf("Puussa ei ole arvoa '%d'.\n", number);
    root = original;
    return NULL;
}

void writeFileDF(NODE_BT* root, const char* searchInput, const char* filename) {
    FILE *write = NULL;
    if ((write = fopen(filename, "w")) == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }
    writeFileDFHelper(root, searchInput, write);
    fclose(write);
}

NODE_BT *writeFileDFHelper(NODE_BT* root, const char* searchInput, FILE* write) {
    if (root == NULL) {
        return NULL; //If root is null, exit function
    }
    // Check if current node matches search criteria and write it to the file if it matches.
    if (nameExists(root->pNameList, searchInput) || atoi(searchInput) == root->iCount) {
        fprintf(write, "%s,%d\n", root->pNameList->aName, root->iCount);
        return root; 
    }
    //Write node to file
    fprintf(write, "%s,%d\n", root->pNameList->aName, root->iCount);
    NODE_BT *searchLeft = writeFileDFHelper(root->left,searchInput,write);
    if (searchLeft != NULL) {
        return searchLeft;
    }
    NODE_BT *searchRight = writeFileDFHelper(root->right,searchInput,write);
    if (searchRight != NULL) {
        return searchRight;
    }
    return NULL;
}

void writeFileWF(NODE_BT* root, const char* searchInput, const char* filename) {
    if (root == NULL) {
        return; // If the root is null, exit function
    }
    FILE *write = NULL;
    if ((write = fopen(filename, "w")) == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }
    // Initialize queue with dynamic memory allocation
    int capacity = 5000;
    int front = 0, rear = 0;
    NODE_BT **queue = (NODE_BT **)malloc(capacity* sizeof(NODE_BT*));
    if (queue==NULL) {
        perror("Muistin varaus epäonnistui, lopetetaan");
        fclose(write);
        exit (0);
    }
     // Add root to the queue
    queue[rear++] = root;
    while (front<rear) {
        if (rear>=capacity) {
            int newCapacity = capacity * 2;
            NODE_BT **newQueue = (NODE_BT**)realloc(queue,newCapacity*sizeof(NODE_BT*));
            if (newQueue == NULL) {
                perror("Muistin uudelleen varaus epäonnistui");
                free(queue);
                fclose(write);
                exit(0);
            }
            queue = newQueue;
            capacity = newCapacity;
        }
        // Get next node from queue
        NODE_BT *current = queue[front++];
        // Check if current node matches search criteria
        if (nameExists(current->pNameList, searchInput) || atoi(searchInput) == current->iCount) {
            fprintf(write, "%s,%d\n", current->pNameList->aName, current->iCount);
            break;
        }
        fprintf(write, "%s,%d\n", current->pNameList->aName, current->iCount);
        // add left and right nodes to the queue
        if (current->left != NULL) {
            queue[rear++] = current->left;
        }
        if (current->right != NULL) {
            queue[rear++] = current->right;
        }
    // free memory!
    free(queue);
    fclose(write);
    }
}

/* Red-Black Tree. Didn't work with codegrade.
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
*/

/* Static rebuild. Didn't work entirely with Codegrade.
// The main function that is called to balance a tree.
NODE_BT* balanceTree(NODE_BT *root) {
    int iIndex = 0;
    int iNodeCount = countNodes(root);
    if (iNodeCount == 0) {
        return (NULL);
    }

    NODE_BT **NodeList = (NODE_BT **)malloc(iNodeCount * sizeof(NODE_BT));
    if (NodeList == NULL) {
        perror("Muistin varaus epäonnistui, lopetetaan");
        exit(0);
    }

    makeList(root, NodeList, &iIndex);

    
    NODE_BT *newRoot = buildBalancedTree(NodeList, 0, iNodeCount - 1);
    free(NodeList);
    return (newRoot);
}
*/
// Counts the number of nodes
int countNodes(NODE_BT *root) {
    if(root == NULL) {
        return 0;
    }
    // Use recursion to count all nodes from left and to right.
    return (1 + countNodes(root->left) + countNodes(root->right));
} 

// Use recursion to make a largest to smallest list
void makeList(NODE_BT *root, NODE_BT **NodeList, int *iIndex) {
    if (root == NULL) {
        return;
    }
    makeList(root->right, NodeList, iIndex); // Goes all the way to the right of the tree
    NodeList[*iIndex] = root; // Adds the node to the list
    (*iIndex)++;
    makeList(root->left, NodeList, iIndex); // Goes to the left node
    return;
}
/*
// Use recursion to balance the tree based on the created list
NODE_BT *buildBalancedTree(NODE_BT **NodeList, int iStart, int iEnd) {
    int iMiddle;
    
    if (iStart > iEnd) {
        return NULL;
    }

    iMiddle = (iStart + iEnd)>>1; // Gets the lists middle point
    NODE_BT *root = NodeList[iMiddle]; // Sets the node to be the node in the middle of the list.

    // Recursive calls
    root->left = buildBalancedTree(NodeList, iStart, iMiddle -1);
    root->right = buildBalancedTree(NodeList, iMiddle + 1, iEnd);

    return root;
}
*/



//Function to remove nodes from the tree
NODE_BT* removeNode(NODE_BT* root, const char* searchInput) {
    if (root == NULL) {
        return NULL;
    }
    //determines whether or not the input is numeric or string
    char* endPtr;
    int number = strtol(searchInput, &endPtr, 10);
    int isNumeric = (*endPtr == '\0');
    //check if current node matches the input
    if ((isNumeric && root->iCount == number) || (!isNumeric && nameExists(root->pNameList, searchInput))) {
        if (root->left == NULL && root->right == NULL) {
            //The removed node is leaf node meaning no children nodes
            freeNameList(root);
            free(root);
            return NULL;
        } else if (root->left == NULL) {
            //If the removed node has only a right child
            NODE_BT* temp = root->right;
            freeNameList(root);
            free(root);
            return temp;
        } else if (root->right == NULL) {
            //If the removed node has only a left child
            NODE_BT* temp = root->left;
            freeNameList(root);
            free(root);
            return temp;
        } else {
            //If the removed node has two children
            NODE_BT* successor = root->right;
            NODE_BT* parentOfSuccessor = root;

            while (successor->left != NULL) {
                parentOfSuccessor = successor;
                successor = successor->left;
            }

            strcpy(root->pNameList->aName, successor->pNameList->aName);
            root->iCount = successor->iCount;

            if (parentOfSuccessor->left == successor) {
                parentOfSuccessor->left = successor->right;
            }
            else {
                parentOfSuccessor->right = successor->right;
            }

            freeNameList(successor);
            free(successor);
        }
    }
    else {
        // For numeric searches, traverse based on count comparison
        if (isNumeric){
            if (number < root->iCount) {
                root->left = removeNode(root->left, searchInput);
            }
            else {
                root->right = removeNode(root->right, searchInput);
            }
        }
        else {
            // For name searches, we must check both subtrees
            root->left = removeNode(root->left, searchInput);
            root->right = removeNode(root->right, searchInput);
        }
    }
    return root;
}

