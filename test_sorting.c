#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "linkedlist.h"
// going to make a main function where the tests are done. in this function we create an empty list and add to that and titles.
// then we give these lists and the titles to the print function. 


// function to print the linked list, takes in the created list and the title for printing.
void printList(NODE *head, const char *title)
{
    printf("%s\n", title);
    if (head == NULL)
    {
        printf("list is empty\n\n");
        return;
    }

    NODE *current = head;
    while (current != NULL)
    {
        printf("%s: %d\n", current->aName, current->iCount);
        current = current->pNext;
    }
    printf("\n");
}


// main function where the tests are done.

int main() {
    NODE *list = NULL; // initialize the list to NULL

    // Test 1: Empty list
    printList(list, "Test 1: Empty list");
    list = sortAscending(list);
    printList(list, "Test 1a: sortAscending function with empty list");
    list = mergeSort(list);
    printList(list, "Test 1b: mergeSort(Sort Descending) function with empty list");

    // Test 2: Add a single node to the list
    list = createNode(list, "SingleNode", 1);
    updatePreviousPointers(list); // update struct pointers

    printList(list, "Test 2: Single node list");

    list = sortAscending(list);
    updatePreviousPointers(list); // update struct pointers again
    printList(list, "Test 2a: sortAscending function with single node list");

    list = mergeSort(list);
    updatePreviousPointers(list); // update struct pointers again
    printList(list, "Test 2b: mergeSort(Sort Descending) function with single node list");
}
