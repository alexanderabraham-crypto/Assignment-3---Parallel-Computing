
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

#define SIZE 1000000000

long long sumArray(int arr[], int size, int numThreads)
{
    long long sum = 0;

    #pragma omp parallel for num_threads(numThreads) reduction(+:sum) schedule(static)
    for (int i = 0; i < size; i++)
    {
        sum += arr[i];
    }

    return sum;
}

int main(int argc, char* argv[])
{
    int NUM_THREADS = 2;

    // Get thread count from command line
    if (argc > 1)
    {
        NUM_THREADS = atoi(argv[1]);
    }

    // Validate thread count
    if (NUM_THREADS != 1 && NUM_THREADS != 2 &&
        NUM_THREADS != 5 && NUM_THREADS != 7 &&
        NUM_THREADS != 9)
    {
        printf("Use 1, 2, 5, 7, or 9 threads.\n");
        return 1;
    }

    // Allocate array
    int* arr = new int[SIZE];

    // Initialize array
    for (int i = 0; i < SIZE; i++)
    {
        arr[i] = i + 1;
    }

    // Start timing
    double start = omp_get_wtime();

    // Calculate array sum using OpenMP
    long long totalSum = sumArray(arr, SIZE, NUM_THREADS);

    // End timing
    double end = omp_get_wtime();

    double elapsed = end - start;

    // Display results
    printf("\nOpenMP Array Sum\n");
    printf("Array Size: %d\n", SIZE);
    printf("Number of Threads: %d\n", NUM_THREADS);
    printf("Total Sum: %lld\n", totalSum);
    printf("Execution Time: %.6f seconds\n", elapsed);

    // Free memory
    delete[] arr;

    return 0;
}
