// test_results.h
#ifndef TEST_RESULTS_H
#define TEST_RESULTS_H

#define RESULTS_FILE "test_results.txt"

// Function to record test results to a file
void recordTestResult(const char *testName, int passed, int failed);

// Function to print summary of all test results
void printTestSummary();

#endif