
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

#define MATRIX_SIZE 1000

void matrixMultiply(int** A, int** B, int** C, int n, int numThreads)
{
    #pragma omp parallel for num_threads(numThreads) schedule(static)
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j] = 0;

            for (int k = 0; k < n; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
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

    // Allocate matrices
    int** A = new int*[MATRIX_SIZE];
    int** B = new int*[MATRIX_SIZE];
    int** C = new int*[MATRIX_SIZE];

    for (int i = 0; i < MATRIX_SIZE; i++)
    {
        A[i] = new int[MATRIX_SIZE];
        B[i] = new int[MATRIX_SIZE];
        C[i] = new int[MATRIX_SIZE];
    }

    // Initialize matrices
    for (int i = 0; i < MATRIX_SIZE; i++)
    {
        for (int j = 0; j < MATRIX_SIZE; j++)
        {
            A[i][j] = 1;
            B[i][j] = 1;
            C[i][j] = 0;
        }
    }

    // Start timing
    double start = omp_get_wtime();

    // Perform OpenMP matrix multiplication
    matrixMultiply(A, B, C, MATRIX_SIZE, NUM_THREADS);

    // End timing
    double end = omp_get_wtime();

    double elapsed = end - start;

    // Display results
    printf("\nOpenMP Matrix Multiplication\n");
    printf("Matrix Size: %d x %d\n",
           MATRIX_SIZE, MATRIX_SIZE);
    printf("Number of Threads: %d\n", NUM_THREADS);
    printf("C[0][0] = %d\n", C[0][0]);
    printf("Execution Time: %.6f seconds\n", elapsed);

    // Free memory
    for (int i = 0; i < MATRIX_SIZE; i++)
    {
        delete[] A[i];
        delete[] B[i];
        delete[] C[i];
    }

    delete[] A;
    delete[] B;
    delete[] C;

    return 0;
}
