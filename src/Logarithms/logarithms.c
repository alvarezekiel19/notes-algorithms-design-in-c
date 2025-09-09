/*
* Logarithms
*
* - This is more about the calculation of logarithms
*   (truncated logarithms).
*
* - This is relevant because the analysis of the time 
*   consumption of many algorithms involves the 
*   logarithmic function.
*
*/

/* 
* Floor of base 2 algorithms
*
* The logarithm in base 2 of a number N is the 
* exponent to which 2 must be raised in order to 
* produce N. The base 2 logarithm of N will be 
* denoted by log N. Of course, log N is defined 
* only if N is strictly positive.
*
* The floor of log N, usually denoted by [log N], 
* is approximately equal to the number of bits in 
* the binary representation of N. The following 
* table shows some values of log N (to three decimal 
* places) as well as the corresponding the values of 
* [log N]:
*
* ------------------------
* N    | log N | [log N] |
* -----|-------|---------|
* 10   | 3.322 | 3       |
* 100  | 6.644 | 6       |
* 1000 | 9.966 | 9       |
* ------------------------
*/

/*
* The function lg receives an integer N > 0
* and returns the floor of log N, that is, 
* the only integer i such that
* 2^i <= N < 2^(i+1).
*
* int lg (int N) {
*     int i, n;
*     i = 0;
*     n = 1;
*     while (n <= N/2) {
*         n = 2 * n;
*         i += 1;
*     }
*
*     return i;
* }
*/

// Instead of repeated multiplications, we can use repeated divisions

int lg (int N) {
     int i = 0;
     int n = N;
     while (n > 1) {
         n = n/2;
         i += 1;
     }
     return i;
}

// Since the expression of n/2 involves only objects 
// of type int, the division operation is integer. 
// Hence, the value of the expression is [n / 2].

// ---

// Exercise

// 1. Criticize the following version of the function lg. 
// It uses the function log10 and floor of the math library.
// Float Based Implementation

#include <math.h>
int lg_exOne (int N) {
    double x;
    x = log10 (N) / log10(2);
    return floor (x);
}

/*
* Criticisms:
* 1. Floating point precision errors
*   - converting between floating point and integer
*   arithmetic can introduce rounding errors that 
*   cause incorrect results for certain values.
* 2. Performance overhead
*   - Uses expensive floating point operation (log10) 
*   when integer arithmetic would suffice.
* 3. Library dependency
*   - Requires math library linking (-lm flag)
* 4. Edge case handling
*   - No validation for N <= 0, which would cause 
*   undefined behavior with log10.
* 5. Potential precision loss
*/

// ---

// 2. Show that the code below can produce wrong 
// results due to arithmetic overflow.
// Overflow-prone Implementation

int lg_exTwo (int N) {
    int i = 0, n = 1;
    while (n <= N) {
        n = 2 * n;
        i += 1;
    }
    return i-1;
}

/*
* Overflow demonstration:
* 
* When N is large, n = 2 * n will eventually 
* overflow.
*
* - if int is 32-bit, the largest power of 2 that fits 
*   is 2^30 = 1,073,741,824.
* - when n = 2^30 and we compute n = 2 * n, we get 2^31 
*   which overflows to a negative number.
* - the condition n <= N becomes true again 
*   (negative <= positive),causing an infinite loop.
*
* Example: for N = 2,000,000,000 the loop will continue 
* past 2^30 and overflow, producing incorrect results.
*/

// ---

// 3. Check that the following alternative version of the 
// function lg is correct
// Corrected Loop Implementation

int lg_exThree (int N) {
    int i = 0;
    for (int n = 2; n <= N; n = 2*n)
        i += 1;
    return i;
}

/*
*
* Analysis: This version is correct and avoids 
* the overflow issue
*
* - start with n = 2 (2^1), so i counts the exponent directly.
* - when n overflows and becomes negative, n <= N becomes false, 
*   terminating the loop safely.
* - Returns i directly (no need for i-1 since we start counting 
*   from exponent 1)
* - handles edge cases properly: lg(1) returns 0, lg(2) returns 1, etc.
*/

// ---

// 4. Criticize the following alternative version of the function lg.
// Redundant Flag Implementation

int lg_exFour (int N) {
    int found = 0, i = 0, n = 1;
    while (!found) {
        n *= 2;
        i += 1;
        if (n > N) found = 1;
    }
    return i - 1;
}

/*
* Criticisms:
*
* 1. Unnecessary complexity
*   - the found flag is redundant could use while (n <= N) directly.
* 2. Still vulnerable to overflow
*   - same overflow issues as exercise 2
* 3. Poor readability
*   - more complex control flow than needed
* 4. Inefficient
*   - Extra variable and condition checking
*/

// ---

// 5. Criticize the following alternative version of the funciton lg
// Special Case Implementation

int lg_exFive (int N) {
    if (N == 1) return 0;
    if (N == 2) return 1;
    int i = 2;
    int n = 4;
    while (n <= N) {
        n = 2 * n;
        i += 1;
    }
    return i - 1;
}

/*
* Criticisms:
*
* 1. Unnecessary special cases
*   - special case for N = 1 and N = 2 are redundant,
*   the general algorithm handles these correctly.
* 2. Code duplication
*   - repeats logic that the loop already handles.
* 3. Maintenance burden
*   - more code paths to test and maintain.
* 4. Still has overflow potential
*   - same overflow issues in the main loop.
* 5. Inconsistent starting point
*   - starting with i = 2, n = 4 is confusing.
*/

// ---

// 6. Efficiency. Criticize the following alternative 
// version of the function lg. It computes, explicitly, 
// the largest power of 2 that does not exceed N.

// Inefficient Recursive Power Implementation

int power (int i) {
    int p = 1;
    for (int j = 1; j <= i; j++) p = 2 * p;
    return p;
}

int lg_exSix (int N) {
    int i = 0;
    for (i = 0; power(i) <= N; i++) {}
    return i - 1;
}

/*
* Criticism
*
* 1. Extremely inefficient
*   - O(n^2) time complexity instead of O(log n)
*       - For each value of i, computes 2^i from scratch.
*       - If lg(N) = k, this does roughly k^2/2 multiplications instead of k.
* 2. Redundant computation
*   - repeatedly calculates the same powers
* 3. Overflow issues
*   - the power() function will overflow for large i
* 4. Poor algorithmic design
*   - completely defeats the purpose of an efficient logarithm function
*/

// ---

// 7. Base10 logarithms. Write a function to calculate the floor 
// of the base10 logarithm of a number.

int lg10 (int N) {
    if (N <= 0) return -1; // Err case
    
    int count = 0;
    while (N >= 10) {
        N /= 10;
        count++;
    }
    return count;
}

/*
* features
* - divison never overflows unlike multiplication, meaning no overflow risk
* - directly counts how many times we can divide by 10 (simpler)
* - clear intent (readable)
* - only 6 lines of actual logic, this is concise
* - O(log10 N) time and O(1) space, no unnecessary operation (efficient time & space complexity)
*/

/*
* KEY NOTES
*
* - floating point arithmetic, introduces precision errors and 
*   dependencies @ Exercise 1
* - an integer overflow is a serious concern @ Exercise 2, 4, 5, 6 
*   that can cause infinite loops or wrong results
* - Exercise 6 O(n^2) approach is impractical, algorithmic efficiency matters
* - Exercise 3 offers robust solution than complex special case handling, 
*   that is more simple (Exercise 3)
*/
