// binarytree.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binarytree.h"
#include "namelist.h"
#include "avl_tree.h"
#include "balance_tree.h"
#include "rb_tree.h"
#include "common.h"

//Function displaying the binarytree menu
int binaryTreeMenu (void) {
    int iSelection = 0;
    printf("\n");
    printf("Valitse haluamasi toiminto (binääripuu):\n");
    printf("1) Lue tiedosto\n");
    printf("2) Kirjoita puun arvot tiedostoon\n");
    printf("3) Syvyyshaku\n");
    printf("4) Leveyshaku\n");
    printf("5) Binääripuuhaku\n");
    printf("6) Poista arvo\n");
    printf("7) Tulosta puumaisessa muodossa\n");
    printf("8) Valitse tasapainotus algoritmi\n");
    printf("0) Palaa\n");
    printf("Anna valintasi: ");
    scanf("%d", &iSelection);
    getchar();
    return iSelection;
}

int balanceSelectionMenu (void) {
    int iSelection = 0;
    printf("\n");
    printf("Valitse haluamasi tasapainoitus algoritmi:\n");
    printf("1) Static rebuild\n");
    printf("2) AVL-Tree\n");
    printf("3) Red-Black-Tree\n");
    printf("Anna valintasi: ");
    scanf("%d", &iSelection);
    getchar();
    return iSelection;
}



void treeMenuLogic(void) {
    NODE_BT *pStartTree = NULL;
    int iSubSelection, iBalanceSelection;
    char aReadName[LENGTH], aWriteName[LENGTH];
    do {
        iSubSelection = binaryTreeMenu();
        if (iSubSelection == 1) {
            filename(aReadName, "Anna luettavan tiedoston nimi: ");
            pStartTree = buildFromFile_SR(aReadName);
        } else if (iSubSelection == 2) {
            filename(aWriteName, "Anna kirjoitettavan tiedoston nimi: ");
            writeFileTree(aWriteName,pStartTree);
        } else if (iSubSelection == 3){
            char searchTerm[LENGTH];
            printf("Anna etsittävä nimi tai numero: ");
            fgets(searchTerm, sizeof(searchTerm), stdin);
            searchTerm[strcspn(searchTerm, "\n")] = 0; // get rid of newline
            filename(aWriteName, "Anna kirjoitettavan tiedoston nimi: ");
            writeFileDF(pStartTree, searchTerm,aWriteName);
        } else if (iSubSelection == 4) {
            char searchTerm[LENGTH];
            printf("Anna etsittävä nimi tai numero: ");
            fgets(searchTerm, sizeof(searchTerm), stdin);
            searchTerm[strcspn(searchTerm, "\n")] = 0; // get rid of newline
            filename(aWriteName, "Anna kirjoitettavan tiedoston nimi: ");
            writeFileWF(pStartTree,searchTerm,aWriteName);
        } else if (iSubSelection == 5) {
            char searchTerm[LENGTH];
            printf("Anna etsittävä nimi tai numero: ");
            fgets(searchTerm, sizeof(searchTerm), stdin);
            searchTerm[strcspn(searchTerm, "\n")] = 0; // get rid of newline
            BinaryTreeSearch(pStartTree, searchTerm);
        } else if (iSubSelection == 7) {
            printTree(pStartTree);
        } else if (iSubSelection == 6) {
            char searchTerm[LENGTH];
            printf("Anna poistettava arvo: ");
            fgets(searchTerm, sizeof(searchTerm),stdin);
            searchTerm[strcspn(searchTerm, "\n")] = 0; // get rid of newline
            pStartTree = removeNode(pStartTree, searchTerm);
        } else if (iSubSelection == 8) {
            iBalanceSelection = balanceSelectionMenu();
            if (iBalanceSelection == 1) {
                filename(aReadName, "Anna luettavan tiedoston nimi: ");
                pStartTree = buildFromFile_SR(aReadName);
            } else if (iBalanceSelection == 2) {
                filename(aReadName, "Anna luettavan tiedoston nimi: ");
                pStartTree = buildFromFile_AVL(aReadName);
            } else if (iBalanceSelection == 3) {
                filename(aReadName, "Anna luettavan tiedoston nimi: ");
                pStartTree = buildFromFile_RB(aReadName);
            }

        } else if (iSubSelection == 0) {
            printf("Palataan päävalikkoon.\n");
        } else {
            printf("Yritä uudestaan.\n");
        }

    } while (iSubSelection != 0);
    freeTree(pStartTree);
    return;
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

    // Anna oikealle alipuulle tilaa:
    printTreeHelper(root->right, iSpace + SPACING, iPrinted, iMaxPrinted);

    if (*iPrinted < iMaxPrinted) {
        printf("\n");
        // Tässä sisennetään "iSpace" verran eikä aloiteta "SPACING:sta"
        for (int i = 0; i < iSpace; i++)
            printf(" ");
        printf("%s %d\n", root->pNameList->aName, root->iCount);
        (*iPrinted)++;
    }

    // Anna vasemmalle alipuulle tilaa:
    printTreeHelper(root->left, iSpace + SPACING, iPrinted, iMaxPrinted);
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

