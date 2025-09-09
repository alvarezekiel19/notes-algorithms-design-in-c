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

// Exercise

// 1. Criticize the following version of the function lg. 
// It uses the function log10 and floor of the math library.

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

// 2. Show that the code below can produce wrong 
// results due to arithmetic overflow.

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
