// test_results.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test_results.h"

#define MAX_TESTS 10
#define RESULTS_FILE "test_results.txt"

void recordTestResult(const char *testName, int passed, int failed){
    FILE *file = fopen(RESULTS_FILE, "a");
    if (file){
        fprintf(file, "%s:%d:%d\n", testName, passed, failed);
        fclose(file);
    }
}

void printTestSummary(){
    FILE *file = fopen(RESULTS_FILE, "r");
    if (!file){
        printf("No test results found.\n");
        return;
    }

    printf("===== TEST SUMMARIES =====\n");
    char line[256];
    char testName[100];
    int passed, failed;
    int totalPassed = 0, totalFailed = 0;

    while (fgets(line, sizeof(line), file)){
        if (sscanf(line, "%[^:]:%d:%d", testName, &passed, &failed) == 3){
            printf("%s: %d passed, %d failed\n", testName, passed, failed);
            totalPassed += passed;
            totalFailed += failed;
        }
    }

    printf("\n===== FINAL SUMMARY =====\n");
    printf("TOTAL: %d passed, %d failed\n", totalPassed, totalFailed);

    if (totalFailed == 0){
        printf("\nALL TESTS PASSED!\n");
    }
    else{
        printf("\nSome tests failed.\n");
    }

    fclose(file);

    // Remove the results file to start fresh next time
    remove(RESULTS_FILE);
}