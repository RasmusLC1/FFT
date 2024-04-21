#include "Recursive_fft.h"
#include "iterative_fft.h"
#include "dft.h"
#include "karatsuba.h"


// // Initialize a and b with inverse number, I.E 27 = a[0] = 7 and a[1] = 2
    // // Coefficient of x^0 = a[0] and x^1=a[1]
    // a[0] = 7; a[1] = 2; // Polynomial for 27
void Int_to_Array(long long input_int, complex double *output_array){
    int i = 0;
    while (input_int > 0) {
        output_array[i++] = input_int % 10; // Store the last digit in the array
        input_int /= 10;             // Remove the last digit from n
    }
}

// Check to see if results are identical
bool Correctness_Check(long long result_karatsuba, long long result_fft,
                        long long result_iterative_fft) {
    if (result_karatsuba != result_fft || result_fft != result_iterative_fft){
        printf("Results do not match\nresult_dft:\t%ld\nresult_fft:\t%ld\nresult_iterative_fft:\t%ld\n",
                result_karatsuba, result_fft, result_iterative_fft);
        exit(1);
        return false;
    }
    return true; // Arrays are equal
}

void Polynomial_Multiply(int n, int iterations) {
    complex double a[n], b[n];

    // Initialize arrays with zeros for padding
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));
    
    // Seed randomiser with time
    srand(time(NULL));

    // Check if the seed works and we get true random variables
    assert(rand() != rand());
    long long random_Value_a = 0, random_Value_b = 0;

    

    // Set up timers
    double time_dft = 0.0, time_fft = 0.0, time_iterative_fft = 0.0, time_karatsuba = 0.0;
    struct timespec start, end;
    double elapsed_time;

    // Loop through the test multiple times to allow bigger tests
    // Also allows us to test n size vs iterations and their effect
    long long result_fft = 0, result_iterative_fft = 0, result_dft = 0, result_karatsuba = 0;
    for (int i = 0; i < iterations; i++) {
        
        // Calculate random values
        random_Value_a = rand() % (long long)pow(10, n/2);
        random_Value_b = rand() % (long long)pow(10, n/2);

        Int_to_Array(random_Value_a, a);
        Int_to_Array(random_Value_b, b);

        // Time DFT
        // THIS CODE HAS BEEN COMMENTED OUT TO COMPUTATIONAL COST IN TESTING
        // Time Recursive FFT using CLOCK_MONOTONIC for accuracy
        clock_gettime(CLOCK_MONOTONIC, &start);
        // result_dft = polynomial_multiply_DFT(a, b, n);
        clock_gettime(CLOCK_MONOTONIC, &end);
        elapsed_time = end.tv_sec - start.tv_sec + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
        time_dft += elapsed_time;

        // Time Recursive FFT using CLOCK_MONOTONIC for accuracy
        clock_gettime(CLOCK_MONOTONIC, &start);
        result_fft = polynomial_multiply_Recursive_FFT(a, b, n);
        clock_gettime(CLOCK_MONOTONIC, &end);
        elapsed_time = end.tv_sec - start.tv_sec + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
        time_fft += elapsed_time;

        // Time Iterative FFT using CLOCK_MONOTONIC for accuracy
        clock_gettime(CLOCK_MONOTONIC, &start);
        result_iterative_fft = polynomial_multiply_iterative_FFT(a, b, n);
        clock_gettime(CLOCK_MONOTONIC, &end);
        elapsed_time = end.tv_sec - start.tv_sec + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
        time_iterative_fft += elapsed_time;

        // Time Karatsuba using CLOCK_MONOTONIC for accuracy
        clock_gettime(CLOCK_MONOTONIC, &start);
        result_karatsuba = polynomial_multiply_karatsuba(a, b, n);
        clock_gettime(CLOCK_MONOTONIC, &end);
        elapsed_time = end.tv_sec - start.tv_sec + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
        time_karatsuba += elapsed_time;

        if (n <= 16){
            // Check if results are the same outside clock, to not affect timer
            Correctness_Check(result_karatsuba, result_fft, result_iterative_fft);
            // printf("%ld\n", result_fft); //Print results
        } else{
            printf("integer overflow!!!\n");
            exit(1);
        }

    }
    // Output time
    printf("n size: %dm\t iterations: %d\n", n, iterations);
    printf("DFT multiplication time:\t%f seconds.\n", time_dft);
    printf("FFT multiplication time:\t%f seconds.\n", time_fft);
    printf("iterative_FFT multiplication time:\t%f seconds.\n", time_iterative_fft);
    printf("karatsuba multiplication time:\t%f seconds.\n", time_karatsuba);
}




void White_Box_Testing() {
    int n = 16; // test size needs to be power 2
    complex double a[n], b[n]; //setting up arrays
    
    // Initialize arrays with zeros for padding
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));

    //TEST CASE SETUP:

    // Convert numbers to reverse arrays
    Int_to_Array(100, a);
    Int_to_Array(10, b);

    // Compute polynomial multiplication using DFT
    long result_dft = polynomial_multiply_DFT(a, b, n); 

    long result_karatsuba = polynomial_multiply_karatsuba(a, b, n);

    long result_iterative_fft = polynomial_multiply_iterative_FFT(a, b, n);

    // Compute polynomial multiplication using FFT
    long result_fft = polynomial_multiply_Recursive_FFT(a, b, n);

    printf("DFT result:\t%ld\n", result_dft);
    printf("karatsuba result:\t%ld\n", result_karatsuba);
    printf("FFT result:\t%ld\n", result_fft);
    printf("Iterative FFT result:\t%ld\n", result_iterative_fft);

}




int main() {
    int n = 16; // test size needs to be power 2, higher than 16 integer overflow
    int iterations = 100000;
    Polynomial_Multiply(n, iterations);
    // White_Box_Testing();
    return 0;
}