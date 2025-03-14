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

// Function takes integers passed and failed from main, with the condition to pass the test and the message to print.
void runTest(int *passed, int *failed, int condition, const char *message) {
    if (condition) {
        printf("PASS: %s\n", message);
        (*passed)++;
    } else {
        printf("FAIL: %s\n", message);
        (*failed)++;
    }
}

// main function where the tests are done.

int main() {
    int passed = 0;
    int failed = 0;

    NODE *list = NULL; // initialize the list to NULL

    // Test 1: Empty list
    printList(list, "Test 1: Empty list");
    list = sortAscending(list);
    printList(list, "Test 1a: sortAscending function with empty list");
    // so runTest here we take pointers to the integers, see if condition is true
    // and the print message has to match the test print for the test to pass.
    runTest(&passed, &failed, list == NULL, "sortAscending with empty list");

    list = mergeSort(list);
    printList(list, "Test 1b: mergeSort(Sort Descending) function with empty list");
    runTest(&passed, &failed, list == NULL, "mergeSort with empty list");

    // Test 2: Add a single node to the list
    list = createNode(list, "SingleNode", 1);
    updatePreviousPointers(list); // update struct pointers

    printList(list, "Test 2: Single node list");

    list = sortAscending(list);
    updatePreviousPointers(list); // update struct pointers again
    printList(list, "Test 2a: sortAscending function with single node list");
    runTest(&passed, &failed, list != NULL && strcmp(list->aName, "SingleNode") == 0 && list->iCount == 1, "sortAscending with single node list");

    list = mergeSort(list);
    updatePreviousPointers(list); // update struct pointers again
    printList(list, "Test 2b: mergeSort(Sort Descending) function with single node list");
    runTest(&passed, &failed, list != NULL && strcmp(list->aName, "SingleNode") == 0 && list->iCount == 1, "mergeSort with single node list");

    // Print summary of passed and failed tests
    printf("\nSummary: %d tests passed, %d tests failed\n", passed, failed);

    return 0;
}
