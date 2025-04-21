// namelist.c

#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include "binarytree.h"
#include "namelist.h"

NAME_LIST* createNameList(const char* name, int* size) {
    // If size is NULL, allocate memory for it and initialize it to 1
    if (size == NULL) {
        size = (int*)malloc(sizeof(int));
        *size = 1;
    }

    NAME_LIST* nameList = (NAME_LIST*)malloc(sizeof(NAME_LIST));
    nameList->pNext = NULL;
    nameList->size = size;
    strcpy(nameList->aName, name);
    return nameList;
}

void append(NAME_LIST* head, const char* name) {
    if (head == NULL) {
        return;
    }
    NAME_LIST* current = head;

    // Find the last node in the list
    // todo might optimize this by keeping a pointer to the last node
    while (current->pNext != NULL) {
        current = current->pNext;
    }

    NAME_LIST* newNode = createNameList(name, current->size);
    current->pNext = newNode;
    
    (*(current->size))++; // Increase the size of the list
}

bool nameExists(NAME_LIST* head, const char* name) {
    if (head == NULL) {
        return false;
    }

    NAME_LIST* current = head;
    // Check if the name exists in the list
    while (current != NULL) {
        if (strcmp(current->aName, name) == 0) {
            return true;
        }
        current = current->pNext;
    }
    return false;
}

char* getNames(NAME_LIST* head) {
    if (head == NULL) {
        return NULL;
    }

    // if there is only one name, return it
    if (*(head->size) == 1) {
        return head->aName;
    }
    // if there are two names, return them separated by a comma
    else if (*(head->size) == 2) {
        char* buffer = (char*)malloc((LENGTH + 2) * 2);
        sprintf(buffer, "%s, %s", head->aName, head->pNext->aName);
        return buffer;
    } 
    // if there are more than two names, return the first name and the number of the remaining names
    else {
        // Create the suffix string using sprintf into a temporary buffer
        char* buffer = (char*)malloc((LENGTH + 2) * 2);
        sprintf(buffer, "%s, ... %d muuta", head->aName, *(head->size) - 1);

        return buffer;
    }
} 