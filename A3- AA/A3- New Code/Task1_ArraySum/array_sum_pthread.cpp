
#include <stdio.h>
#include <pthread.h>
#include <chrono>
#include <stdlib.h>

#define SIZE 1000000000

int* arr;
long long* partialSums;

struct ThreadData
{
    int start;
    int end;
    int threadID;
};

// Pthreads function to calculate partial sums
void* sumArray(void* arg)
{
    ThreadData* data = (ThreadData*)arg;

    long long sum = 0;

    for (int i = data->start; i < data->end; i++)
    {
        sum += arr[i];
    }

    partialSums[data->threadID] = sum;

    return NULL;
}

int main(int argc, char* argv[])
{
    int NUM_THREADS = 2;

    // Read thread count from command line
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

    // Allocate memory
    arr = new int[SIZE];
    partialSums = new long long[NUM_THREADS];

    // Initialize array
    for (int i = 0; i < SIZE; i++)
    {
        arr[i] = i + 1;
    }

    pthread_t* threads = new pthread_t[NUM_THREADS];
    ThreadData* threadData = new ThreadData[NUM_THREADS];

    // Start timing
    auto start = std::chrono::steady_clock::now();

    int elementsPerThread = SIZE / NUM_THREADS;

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++)
    {
        threadData[i].start = i * elementsPerThread;

        threadData[i].end = (i == NUM_THREADS - 1)
            ? SIZE
            : (i + 1) * elementsPerThread;

        threadData[i].threadID = i;

        int result = pthread_create(
            &threads[i],
            NULL,
            sumArray,
            &threadData[i]
        );

        if (result != 0)
        {
            printf("Error creating thread %d\n", i);
            return 1;
        }
    }

    // Wait for all threads
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    // Combine partial sums
    long long totalSum = 0;

    for (int i = 0; i < NUM_THREADS; i++)
    {
        totalSum += partialSums[i];
    }

    // End timing
    auto end = std::chrono::steady_clock::now();

    double elapsed =
        std::chrono::duration<double>(end - start).count();

    // Display results
    printf("\nPthreads Array Sum\n");
    printf("Array Size: %d\n", SIZE);
    printf("Number of Threads: %d\n", NUM_THREADS);
    printf("Total Sum: %lld\n", totalSum);
    printf("Execution Time: %.6f seconds\n", elapsed);

    // Free memory
    delete[] arr;
    delete[] partialSums;
    delete[] threads;
    delete[] threadData;

    return 0;
}
