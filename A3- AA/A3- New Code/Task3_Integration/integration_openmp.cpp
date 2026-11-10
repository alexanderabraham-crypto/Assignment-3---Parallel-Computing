
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

#define INTERVALS 1000000000LL

double f(double x)
{
    return 4.0 / (1.0 + x * x);
}

double trapezoidalRule(int numThreads)
{
    double a = 0.0;
    double b = 1.0;

    double h = (b - a) / INTERVALS;

    double sum = (f(a) + f(b)) / 2.0;

    #pragma omp parallel for num_threads(numThreads) reduction(+:sum) schedule(static)
    for (long long i = 1; i < INTERVALS; i++)
    {
        double x = i * h;
        sum += f(x);
    }

    return h * sum;
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

    // Start timing
    double start = omp_get_wtime();

    // Perform OpenMP integration
    double pi = trapezoidalRule(NUM_THREADS);

    // End timing
    double end = omp_get_wtime();

    double elapsed = end - start;

    // Display results
    printf("\nOpenMP Trapezoidal Rule Integration\n");
    printf("Intervals: %lld\n", INTERVALS);
    printf("Number of Threads: %d\n", NUM_THREADS);
    printf("Estimated Pi: %.12f\n", pi);
    printf("Execution Time: %.6f seconds\n", elapsed);

    return 0;
}
