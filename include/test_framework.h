#ifndef TEST_FRAMEWORK_H
#define TEST_FRAMEWORK_H

#include "common.h"

// test framework macros
#define TEST_ASSERT(condition, message) do { \
    if (!(condition)) { \
        fprintf(stderr, "ASSERTION FAILED: %s at %s:%d\n", (message), __FILE__, __LINE__); \
        test_failures++; \
        return false; \
    } \
} while(0)

#define TEST_ASSERT_EQUAL(expected, actual) do { \
    if ((expected) != (actual)) { \
        fprintf(stderr, "ASSERTION FAILED: Expected %d, got %d at %s:%d\n", \
                (expected), (actual), __FILE__, __LINE__); \
        test_failures++; \
        return false; \
    } \
} while(0)

#define TEST_ASSERT_NULL(ptr) TEST_ASSERT((ptr) == NULL, #ptr " should be NULL")
#define TEST_ASSERT_NOT_NULL(ptr) TEST_ASSERT((ptr) != NULL, #ptr " should not be NULL")

#define RUN_TEST(test_func) do { \
    printf("Running %s... ", #test_func); \
    fflush(stdout); \
    test_count++; \
    if (test_func()) { \
        printf("PASSED\n"); \
        test_passed++; \
    } else { \
        printf("FAILED\n"); \
    } \
} while(0)

#define TEST_SUMMARY() do { \
    printf("\n=== Test Summary ===\n"); \
    printf("Tests run: %d\n", test_count); \
    printf("Tests passed: %d\n", test_passed); \
    printf("Tests failed: %d\n", test_count - test_passed); \
    printf("Assertions failed: %d\n", test_failures); \
    printf("Success rate: %.2f%%\n", test_count > 0 ? (100.0 * test_passed / test_count) : 0.0); \
    return (test_count == test_passed) ? 0 : 1; \
} while(0)

// global test counters
extern int test_count;
extern int test_passed;
extern int test_failures;

// performance testing
#define BENCHMARK(code, iterations) do { \
    clock_t start = clock(); \
    for(int i = 0; i < (iterations); i++) { \
        code; \
    } \
    clock_t end = clock(); \
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC * 1000; \
    printf("Benchmark: %.3f ms for %d iterations (%.6f ms per iteration)\n", \
           time_taken, (iterations), time_taken / (iterations)); \
} while(0)

#endif /* TEST_FRAMEWORK_H */
