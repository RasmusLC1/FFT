#ifndef karatsuba_H
#define karatsuba_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>


//PseudoCode from Wiki

// function karatsuba(num1, num2)
//     if (num1 < 10 or num2 < 10)
//         return num1 × num2 /* fall back to traditional multiplication */
    
//     /* Calculates the size of the numbers. */
//     m = max(size_base10(num1), size_base10(num2))
//     m2 = floor(m / 2) 
//     /* m2 = ceil (m / 2) will also work */
    
//     /* Split the digit sequences in the middle. */
//     high1, low1 = split_at(num1, m2)
//     high2, low2 = split_at(num2, m2)
    
//     /* 3 recursive calls made to numbers approximately half the size. */
//     z0 = karatsuba(low1, low2)
//     z1 = karatsuba(low1 + high1, low2 + high2)
//     z2 = karatsuba(high1, high2)
    
//     return (z2 × 10 ^ (m2 × 2)) + ((z1 - z2 - z0) × 10 ^ m2) + z0

long karatsuba(long num1, long num2);

int get_size(long value);

long polynomial_multiply_karatsuba(complex double *a, complex double *b, int n);

#endif