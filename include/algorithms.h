#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "common.h"

// logarithm functions
int lg(int n);                    // Floor of log base 2
int lg10(int n);                  // Floor of log base 10
double log_base(double x, double base);

// sorting algorithms
void bubble_sort(int arr[], int n);
void insertion_sort(int arr[], int n);
void selection_sort(int arr[], int n);
void merge_sort(int arr[], int left, int right);
void quick_sort(int arr[], int low, int high);
void heap_sort(int arr[], int n);
void radix_sort(int arr[], int n);

// searching algorithms
int linear_search(int arr[], int n, int target);
int binary_search(int arr[], int n, int target);
int binary_search_recursive(int arr[], int left, int right, int target);

// String algorithms
int string_length(const char* str);
char* string_copy(char* dest, const char* src);
int string_compare(const char* str1, const char* str2);
char* string_find(const char* haystack, const char* needle);
int* kmp_search(const char* text, const char* pattern);

// recursive algorithms
int factorial(int n);
int fibonacci(int n);
int gcd(int a, int b);
int power(int base, int exponent);
void hanoi_towers(int n, char from, char to, char aux);

// utility functions
void print_array(int arr[], int n);
bool is_sorted(int arr[], int n);
void shuffle_array(int arr[], int n);
double get_time_ms(void);

#endif /* ALGORITHMS_H */
