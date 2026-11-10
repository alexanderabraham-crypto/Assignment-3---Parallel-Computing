
#include <stdio.h>
#include <pthread.h>
#include <chrono>
#include <stdlib.h>

#define INTERVALS 1000000000LL

double f(double x)
{
    return 4.0 / (1.0 + x * x);
}

struct ThreadData
{
    long long start;
    long long end;
    double h;
    double partialSum;
};

void* trapezoidalRule(void* arg)
{
    ThreadData* data = (ThreadData*)arg;

    double sum = 0.0;

    for (long long i = data->start; i < data->end; i++)
    {
        double x = i * data->h;
        sum += f(x);
    }

    data->partialSum = sum;

    return NULL;
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

    double a = 0.0;
    double b = 1.0;

    double h = (b - a) / INTERVALS;

    pthread_t* threads = new pthread_t[NUM_THREADS];
    ThreadData* threadData = new ThreadData[NUM_THREADS];

    // Start timing
    auto start = std::chrono::steady_clock::now();

    // Divide interior intervals among threads
    long long interiorIntervals = INTERVALS - 1;

    long long intervalsPerThread =
        interiorIntervals / NUM_THREADS;

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++)
    {
        threadData[i].start =
            1 + i * intervalsPerThread;

        threadData[i].end =
            (i == NUM_THREADS - 1)
            ? INTERVALS
            : 1 + (i + 1) * intervalsPerThread;

        threadData[i].h = h;
        threadData[i].partialSum = 0.0;

        int result = pthread_create(
            &threads[i],
            NULL,
            trapezoidalRule,
            &threadData[i]
        );

        if (result != 0)
        {
            printf("Error creating thread %d\n", i);
            return 1;
        }
    }

    // Calculate endpoint contributions
    double sum = (f(a) + f(b)) / 2.0;

    // Wait for threads and combine partial sums
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);

        sum += threadData[i].partialSum;
    }

    // Calculate final integral
    double pi = h * sum;

    // End timing
    auto end = std::chrono::steady_clock::now();

    double elapsed =
        std::chrono::duration<double>(end - start).count();

    // Display results
    printf("\nPthreads Trapezoidal Rule Integration\n");
    printf("Intervals: %lld\n", INTERVALS);
    printf("Number of Threads: %d\n", NUM_THREADS);
    printf("Estimated Pi: %.12f\n", pi);
    printf("Execution Time: %.6f seconds\n", elapsed);

    // Free memory
    delete[] threads;
    delete[] threadData;

    return 0;
}
