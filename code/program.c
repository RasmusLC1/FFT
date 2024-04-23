#include "Recursive_fft.h"
#include "iterative_fft.h"
#include "dft.h"
#include "karatsuba.h"
#include "test/WhiteBox_test.h"
#include "Helper_Functions.h"

void Polynomial_Multiply() {
    int n = 16; // test size needs to be power 2, higher than 16 integer overflow
    int iterations = 10000;
    // Set up correctness meassure
    int fail = 0, success = 0;


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
    double time_default = 0.0, time_dft = 0.0, time_fft = 0.0,
            time_iterative_fft = 0.0, time_karatsuba = 0.0;
    struct timespec start, end;
    double elapsed_time;


    // Loop through the test multiple times to allow bigger tests
    // Also allows us to test n size vs iterations and their effect
    long long result_fft = 0, result_iterative_fft = 0, result_dft = 0, result_karatsuba = 0;
    for (int i = 1; i <= iterations; i++) {
        
        // Calculate random values
        random_Value_a = rand() % (long long)pow(10, n/2);
        random_Value_b = rand() % (long long)pow(10, n/2);

        clock_gettime(CLOCK_MONOTONIC, &start);
        // result_dft = polynomial_multiply_DFT(random_Value_a, random_Value_b, n);
        clock_gettime(CLOCK_MONOTONIC, &end);
        elapsed_time = end.tv_sec - start.tv_sec + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
        time_default = elapsed_time;

        // Time DFT
        // THIS CODE HAS BEEN COMMENTED OUT TO COMPUTATIONAL COST IN TESTING
        // Time Recursive FFT using CLOCK_MONOTONIC for accuracy
        clock_gettime(CLOCK_MONOTONIC, &start);
        // result_dft = polynomial_multiply_DFT(random_Value_a, random_Value_b, n);
        clock_gettime(CLOCK_MONOTONIC, &end);
        elapsed_time = end.tv_sec - start.tv_sec + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
        time_dft += elapsed_time - time_default;

        // Time Recursive FFT using CLOCK_MONOTONIC for accuracy
        clock_gettime(CLOCK_MONOTONIC, &start);
        result_fft = polynomial_multiply_Recursive_FFT(random_Value_a, random_Value_b, n);
        clock_gettime(CLOCK_MONOTONIC, &end);
        elapsed_time = end.tv_sec - start.tv_sec + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
        time_fft += elapsed_time - time_default;

        // Time Iterative FFT using CLOCK_MONOTONIC for accuracy
        clock_gettime(CLOCK_MONOTONIC, &start);
        result_iterative_fft = polynomial_multiply_iterative_FFT(random_Value_a, random_Value_b, n);
        clock_gettime(CLOCK_MONOTONIC, &end);
        elapsed_time = end.tv_sec - start.tv_sec + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
        time_iterative_fft += elapsed_time - time_default;

        // Time Karatsuba using CLOCK_MONOTONIC for accuracy
        clock_gettime(CLOCK_MONOTONIC, &start);
        result_karatsuba = polynomial_multiply_karatsuba(random_Value_a, random_Value_b, n);
        clock_gettime(CLOCK_MONOTONIC, &end);
        elapsed_time = end.tv_sec - start.tv_sec + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
        time_karatsuba += elapsed_time - time_default;
        
        if (n <= 32){
            // Check if results are the same outside clock, to not affect timer
            if (Correctness_Check(result_fft, result_iterative_fft) && Correctness_Check(result_fft, result_karatsuba)){
                success++;
            } else{
                fail++;
            }
            // printf("%ld\n", result_fft); //Print results
        } else{
            printf("integer overflow!!!\n");
            exit(1);
        }
        Loading_Screen(iterations, i);

    }
    // Output time
    printf("\nn size: %d\t iterations: %d\n", n, iterations);
    printf("Successful calculations:\t%d\nWrong calculations:\t%d\n", success, fail);
    printf("DFT multiplication time:\t%f seconds.\n", time_dft);
    printf("Recursive_FFT multiplication time:\t%f seconds.\n", time_fft);
    printf("Iterative_FFT multiplication time:\t%f seconds.\n", time_iterative_fft);
    printf("karatsuba multiplication time:\t%f seconds.\n", time_karatsuba);
}






int main() {
    
    Polynomial_Multiply();
    // Test_Setup();
    return 0;
}