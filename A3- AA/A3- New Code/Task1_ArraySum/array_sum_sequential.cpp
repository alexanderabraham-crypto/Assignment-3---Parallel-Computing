
#include <stdio.h>
#include <chrono>

#define SIZE 1000000000

long long sumArray(int arr[], int size)
{
    long long sum = 0;

    for (int i = 0; i < size; i++)
    {
        sum += arr[i];
    }

    return sum;
}

int main()
{
    // Allocate array
    int* arr = new int[SIZE];

    // Initialize array (same as Assignment 1)
    for (int i = 0; i < SIZE; i++)
    {
        arr[i] = i + 1;
    }

    // Start timing
    auto start_time = std::chrono::steady_clock::now();

    // Perform sequential array sum
    long long totalSum = sumArray(arr, SIZE);

    // End timing
    auto end_time = std::chrono::steady_clock::now();

    // Calculate elapsed time
    double elapsed =
        std::chrono::duration<double>(end_time - start_time).count();

    printf("Sequential Array Sum\n");
    printf("Array Size: %d\n", SIZE);
    printf("Total Sum: %lld\n", totalSum);
    printf("Time taken: %.6f seconds\n", elapsed);

    // Free memory
    delete[] arr;

    return 0;
}
