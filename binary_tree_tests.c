#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "linkedlist.h"
// going to make a main function where the tests are done. in this function we create an empty list and add to that and titles.
// then we give these lists and the titles to the print function. 


// function to print the linked list, takes in the created list and the title for printing.
void printList(NODE *head, const char *title)
{
    printf("\n%s\n", title);
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
    
    // More tests can be added here

    // ****************************

    // Free the single node for the next test
    list = empty(list);



    // Test 3: Add multiple nodes to the list EXAMPLE FOR THIS WEEKS TESTS
    // list = createNode(list, "Banana", 5);
    // list = createNode(list, "Aatami", 3);
    // list = createNode(list, "Chevrolet", 8);
    // list = createNode(list, "Daavid", 2);
    // updatePreviousPointers(list); // update struct pointers

    // list = sortAscending(list);
    // updatePreviousPointers(list); // update struct pointers again
    // printList(list, "Test 3a: sortAscending function with multiple nodes");
    // runTest(&passed, &failed, list != NULL && strcmp(list->aName, "Daavid") == 0 && list->iCount == 2, "sortAscending with multiple nodes");

    // list = mergeSort(list);
    // updatePreviousPointers(list); // update struct pointers again
    // printList(list, "Test 3b: mergeSort(Sort Descending) function with multiple nodes");
    // runTest(&passed, &failed, list != NULL && strcmp(list->aName, "Chevrolet") == 0 && list->iCount == 8, "mergeSort with multiple nodes");


    // Lets free all memory at the end
    list = empty(list);

    // Print summary of passed and failed tests
    printf("\nSummary: %d tests passed, %d tests failed\n", passed, failed);

    return 0;
}
