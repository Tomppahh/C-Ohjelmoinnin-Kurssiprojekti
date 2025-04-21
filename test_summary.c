/**
 * test_summary.c
 *
 * A simple program to run all test executables and display a consolidated summary
 * of test results using the test_results framework.
 */

#include <stdio.h>
#include <stdlib.h>
#include "test_results.h"

int main(){
    // Clear any previous test results
    remove(RESULTS_FILE);

    printf("Running all tests...\n\n");

    // Run each test executable
    printf("Running test_sorting...\n");
    system("./test_sorting");

    printf("\nRunning binary_tree_tests...\n");
    system("./binary_tree_tests");

    printf("\nRunning graph_tests...\n");
    system("./graph_tests");

    // Print the combined summary
    printTestSummary();

    return 0;
}