#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <time.h>
#include <errno.h>

// Common constants
#define MAX_SIZE 1000
#define MAX_STRING_LENGTH 256
#define SUCCESS 0
#define FAILURE -1

// Common utility macros
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define SWAP(a, b) do { typeof(a) temp = a; a = b; b = temp; } while(0)
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

// Memory allocation helpers
#define MALLOC(type, count) ((type*)malloc(sizeof(type) * (count)))
#define CALLOC(type, count) ((type*)calloc((count), sizeof(type)))
#define REALLOC(ptr, type, count) ((type*)realloc((ptr), sizeof(type) * (count)))

// Error handling
#define CHECK_NULL(ptr) do { \
    if ((ptr) == NULL) { \
        fprintf(stderr, "Memory allocation failed at %s:%d\n", __FILE__, __LINE__); \
        exit(EXIT_FAILURE); \
    } \
} while(0)

#define CHECK_ERROR(condition, message) do { \
    if (condition) { \
        fprintf(stderr, "Error: %s at %s:%d\n", (message), __FILE__, __LINE__); \
        exit(EXIT_FAILURE); \
    } \
} while(0)

// Debug printing
#ifdef DEBUG
#define DEBUG_PRINT(fmt, ...) fprintf(stderr, "DEBUG: " fmt "\n", ##__VA_ARGS__)
#else
#define DEBUG_PRINT(fmt, ...) do {} while(0)
#endif

#endif /* COMMON_H */
