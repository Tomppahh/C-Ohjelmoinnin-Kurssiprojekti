#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "linkedlist.h"
#include "common.h"
#include "namelist.h"
#include "test_results.h"

// Function to print the linked list, takes in the created list and the title for printing.
void printList(NODE_LL *head, const char *title){
    printf("\n%s\n", title);
    if (head == NULL){
        printf("list is empty\n\n");
        return;
    }

    NODE_LL *current = head;
    while (current != NULL){
        printf("%s: %d\n", current->aName, current->iCount);
        current = current->pNext;
    }
    printf("\n");
}

// Function takes integers passed and failed from main, with the condition to pass the test and the message to print.
void runTest(int *passed, int *failed, int condition, const char *message){
    if (condition){
        printf("PASS: %s\n", message);
        (*passed)++;
    }
    else{
        printf("FAIL: %s\n", message);
        (*failed)++;
    }
}

// Helper function to verify if a list is sorted in ascending order
int isAscendingSorted(NODE_LL *head){
    if (head == NULL || head->pNext == NULL)
        return 1; // Empty or single element list is sorted

    NODE_LL *current = head;
    while (current->pNext != NULL){
        // Check if current node is greater than next node
        if (current->iCount > current->pNext->iCount ||
            (current->iCount == current->pNext->iCount && strcmp(current->aName, current->pNext->aName) > 0)){
            return 0; // Not sorted
        }
        current = current->pNext;
    }
    return 1; // Sorted
}

// Helper function to verify if a list is sorted in descending order
int isDescendingSorted(NODE_LL *head){
    if (head == NULL || head->pNext == NULL)
        return 1; // Empty or single element list is sorted

    NODE_LL *current = head;
    while (current->pNext != NULL){
        // Check if current node is less than next node
        if (current->iCount < current->pNext->iCount ||
            (current->iCount == current->pNext->iCount && strcmp(current->aName, current->pNext->aName) < 0)){
            return 0; // Not sorted
        }
        current = current->pNext;
    }
    return 1; // Sorted
}

// Helper function to create a list with identical count values
NODE_LL *createIdenticalCountList(){
    NODE_LL *list = NULL;
    list = createNode(list, "Zeta", 5);
    list = createNode(list, "Xylophooni", 5);
    list = createNode(list, "What", 5);
    list = createNode(list, "Viulu", 5);
    list = createNode(list, "Apple", 5);
    updatePreviousPointers(list);
    return list;
}

// Helper function to create a list that's already sorted in ascending order
NODE_LL *createAscendingSortedList(){
    NODE_LL *list = NULL;
    list = createNode(list, "Aleksi", 1);
    list = createNode(list, "Berliini", 2);
    list = createNode(list, "Gabriel", 3);
    list = createNode(list, "Deeku", 4);
    list = createNode(list, "Eppu", 5);
    updatePreviousPointers(list);
    return list;
}

// Helper function to create a list that's already sorted in descending order
NODE_LL *createDescendingSortedList(){
    NODE_LL *list = NULL;
    list = createNode(list, "Eetu", 5);
    list = createNode(list, "Danny", 4);
    list = createNode(list, "Gimli", 3);
    list = createNode(list, "Banaani", 2);
    list = createNode(list, "Aatami", 1);
    updatePreviousPointers(list);
    return list;
}

// Helper function to create a list with duplicate names but different counts
NODE_LL *createDuplicateNamesList(){
    NODE_LL *list = NULL;
    list = createNode(list, "Duplicate", 5);
    list = createNode(list, "Duplicate", 3);
    list = createNode(list, "Duplicate", 7);
    list = createNode(list, "Unique", 4);
    list = createNode(list, "Duplicate", 1);
    updatePreviousPointers(list);
    return list;
}

// main function where the tests are done.
int main(){
    int passed = 0;
    int failed = 0;

    NODE_LL *list = NULL; // initialize the list to NULL

    // Test 1: Empty list
    printList(list, "Test 1: Empty list");
    list = sortAscending(list);
    printList(list, "Test 1a: sortAscending function with empty list");
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
    runTest(&passed, &failed, list != NULL && strcmp(list->aName, "Daavid") == 0 && list->iCount == 2, "sortAscending with multiple nodes - first node check");
    runTest(&passed, &failed, isAscendingSorted(list), "sortAscending produces a correctly sorted list");

    list = mergeSort(list);
    updatePreviousPointers(list); // update struct pointers again
    printList(list, "Test 3b: mergeSort(Sort Descending) function with multiple nodes");
    runTest(&passed, &failed, list != NULL && strcmp(list->aName, "Chevrolet") == 0 && list->iCount == 8, "mergeSort with multiple nodes - first node check");
    runTest(&passed, &failed, isDescendingSorted(list), "mergeSort produces a correctly sorted list");

    // Free the list for the next test
    list = empty(list);

    // Test 4: Test with identical count values (should sort by name)
    list = createIdenticalCountList();
    printList(list, "Test 4: List with identical count values");

    list = sortAscending(list);
    updatePreviousPointers(list);
    printList(list, "Test 4a: sortAscending with identical count values");
    runTest(&passed, &failed, strcmp(list->aName, "Apple") == 0, "sortAscending with identical counts sorts by name - first node check");
    runTest(&passed, &failed, isAscendingSorted(list), "sortAscending with identical counts produces a correctly sorted list");

    // Free the list for the next test
    list = empty(list);

    // Test 5: Test with already sorted list (ascending)
    list = createAscendingSortedList();
    printList(list, "Test 5: Already ascending sorted list");

    
    list = sortAscending(list);
    updatePreviousPointers(list);
    printList(list, "Test 5a: sortAscending with already sorted list");
    runTest(&passed, &failed, isAscendingSorted(list), "sortAscending with already sorted list maintains correct order");

    list = mergeSort(list);
    updatePreviousPointers(list);
    printList(list, "Test 5b: mergeSort with previously ascending sorted list");
    runTest(&passed, &failed, isDescendingSorted(list), "mergeSort reverses an ascending sorted list correctly");

    // Free the list for the next test
    list = empty(list);

    // Test 6: Test with already sorted list (descending)
    list = createDescendingSortedList();
    printList(list, "Test 6: Already descending sorted list");

    list = sortAscending(list);
    updatePreviousPointers(list);
    printList(list, "Test 6a: sortAscending with already descending sorted list");
    runTest(&passed, &failed, isAscendingSorted(list), "sortAscending reverses a descending sorted list correctly");

    list = mergeSort(list);
    updatePreviousPointers(list);
    printList(list, "Test 6b: mergeSort with previously ascending sorted list");
    runTest(&passed, &failed, isDescendingSorted(list), "mergeSort with already descending sorted list maintains correct order");

    // Free the list for the next test
    list = empty(list);

    // Test 7: Test with duplicate names but different counts
    list = createDuplicateNamesList();
    printList(list, "Test 7: List with duplicate names but different counts");

    list = sortAscending(list);
    updatePreviousPointers(list);
    printList(list, "Test 7a: sortAscending with duplicate names");
    runTest(&passed, &failed, list->iCount == 1 && strcmp(list->aName, "Duplicate") == 0, "sortAscending with duplicate names sorts by count first");
    runTest(&passed, &failed, isAscendingSorted(list), "sortAscending with duplicate names produces a correctly sorted list");

    list = mergeSort(list);
    updatePreviousPointers(list);
    printList(list, "Test 7b: mergeSort with duplicate names");
    runTest(&passed, &failed, list->iCount == 7 && strcmp(list->aName, "Duplicate") == 0, "mergeSort with duplicate names sorts by count first");
    runTest(&passed, &failed, isDescendingSorted(list), "mergeSort with duplicate names produces a correctly sorted list");

    // Free the list at the end
    list = empty(list);

    // Print summary of passed and failed tests
    printf("\nTEST SORTING SUMMARY: %d tests passed, %d tests failed\n\n", passed, failed);
    recordTestResult("TEST_SORTING", passed, failed); // pass the test results to test_results.c

    return 0;
}