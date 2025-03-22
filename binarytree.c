#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binarytree.h"

//Creates a new node in the binary tree
NODE_BT* createTreeNode(const char* name, int number) {
    NODE_BT* newNode = (NODE_BT*)malloc(sizeof(NODE_BT));
    strcpy(newNode->aName, name);
    newNode->iCount = number;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

//Functionality to insert a node into the binary tree
NODE_BT* insertNode(NODE_BT* root, const char* name, int number) {
    if (root==NULL) {
        return createTreeNode(name,number);
    }
    if (number < root->iCount) {
        root->left = insertNode(root->left, name, number);
    } else if (number > root->iCount) {
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
            root = insertNode(root, name, number);
        } else {
            printf("Error: Invalid formatting in row\n");
        }
    }
    fclose(read);
    return root;
}

//Recursive function that helps with the writing process.
void writeTreeNodes(FILE* write, NODE_BT* root) {
    if (root != NULL) {
        fprintf(write, "%s,%d\n", root->aName, root->iCount);
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
        printf("%6d\n", root->iCount);  // Allocate 6 spaces for alignment
        (*iPrinted)++;
    }

    printTreeHelper(root->left, iSpace, iPrinted, iMaxPrinted);

    return;
}

// Depth first search function for a name or count
NODE_BT *depthFirstSearch(NODE_BT *root, const char *searchInput){
    if (root == NULL) {
        return NULL; // If the tree is empty or the search input is not found in the tree return NULL
    }

    // does the current node match the users search input
    if (strcmp(root->aName, searchInput) == 0 || atoi(searchInput) == root->iCount){   
        printf("Syvyyshaun tulos, löytetty alkio: %s, %d\n", root->aName, root->iCount); // if the searchInput is found, print the result
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
        return searchRight;                                       // If found in the right subtree, return it
    }

    return NULL;
}

NODE_BT *widthFirstSearch(NODE_BT *root, const char *searchInput)
{
    if (root == NULL)
    {
        printf("Puu on tyhjä.\n");
        return NULL; // Empty tree
    }

    // Initialize queue with dynamic memory allocation
    int capacity = 10000; // Start with 5000 nodes (miehet_2025.txt has 10.6k nodes for example)
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
        if (strcmp(current->aName, searchInput) == 0 || atoi(searchInput) == current->iCount)
        {
            printf("Leveyshaun tulos, löytetty alkio: %s, %d\n", current->aName, current->iCount);
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
    printf("Hakutermiä ei löytynyt puusta (Leveyshaku).\n");
    free(queue); // free memory!
    return NULL;
}
