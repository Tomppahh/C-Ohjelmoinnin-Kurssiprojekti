#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binarytree.h"
#include "namelist.h"

//Creates a new node in the binary tree
NODE_BT* createTreeNode(const char* name, int number) {
    NODE_BT* newNode = (NODE_BT*)malloc(sizeof(NODE_BT));
    NAME_LIST* nameList = createNameList(name, NULL);
    newNode->iCount = number;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->pNameList = nameList;
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
    else { 
        append(root->pNameList, name); // If the number is the same, add the name to the namelist
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
        printf("%6d\n", root->iCount);  // Allocate 6 spaces for alignment
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

    // lets free the namelist
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

    // lastly we free the root node
    free(root);
    
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
    }
    // free memory!
    free(queue);
    fclose(write);
}