#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "linkedlist.h"
#include "common.h"
#include "namelist.h"
#include "test_results.h"
// going to make a main function where the tests are done. in this function we create an empty list and add to that and titles.
// then we give these lists and the titles to the print function. 


// function to print the linked list, takes in the created list and the title for printing.
void printList(NODE_LL *head, const char *title) {
    printf("\n%s\n", title);
    if (head == NULL)
    {
        printf("list is empty\n\n");
        return;
    }

    NODE_LL *current = head;
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

    NODE_LL *list = NULL; // initialize the list to NULL

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

    // Free the single node for the next test
    list = empty(list);



    // Test 3: Add multiple nodes to the list
    list = createNode(list, "Banana", 5);
    list = createNode(list, "Aatami", 3);
    list = createNode(list, "Chevrolet", 8);
    list = createNode(list, "Daavid", 2);
    updatePreviousPointers(list); // update struct pointers

    list = sortAscending(list);
    updatePreviousPointers(list); // update struct pointers again
    printList(list, "Test 3a: sortAscending function with multiple nodes");
    runTest(&passed, &failed, list != NULL && strcmp(list->aName, "Daavid") == 0 && list->iCount == 2, "sortAscending with multiple nodes");

    list = mergeSort(list);
    updatePreviousPointers(list); // update struct pointers again
    printList(list, "Test 3b: mergeSort(Sort Descending) function with multiple nodes");
    runTest(&passed, &failed, list != NULL && strcmp(list->aName, "Chevrolet") == 0 && list->iCount == 8, "mergeSort with multiple nodes");

    // More tests can be added here
    
    // ****************************
    // Lets free all memory at the end
    list = empty(list);

    // Print summary of passed and failed tests
    printf("\nTEST SORTING SUMMARY: %d tests passed, %d tests failed\n\n", passed, failed);
    recordTestResult("TEST_SORTING", passed, failed); // pass the test results to test_results.c

    return 0;
}
