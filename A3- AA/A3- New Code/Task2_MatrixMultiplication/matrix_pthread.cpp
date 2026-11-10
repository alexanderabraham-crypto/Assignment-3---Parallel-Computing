
#include <stdio.h>
#include <pthread.h>
#include <chrono>
#include <stdlib.h>

#define MATRIX_SIZE 1000

int** A;
int** B;
int** C;

struct ThreadData
{
    int startRow;
    int endRow;
};

void* matrixMultiply(void* arg)
{
    ThreadData* data = (ThreadData*)arg;

    for (int i = data->startRow; i < data->endRow; i++)
    {
        for (int j = 0; j < MATRIX_SIZE; j++)
        {
            C[i][j] = 0;

            for (int k = 0; k < MATRIX_SIZE; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

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

    // Allocate matrices
    A = new int*[MATRIX_SIZE];
    B = new int*[MATRIX_SIZE];
    C = new int*[MATRIX_SIZE];

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

    pthread_t* threads = new pthread_t[NUM_THREADS];
    ThreadData* threadData = new ThreadData[NUM_THREADS];

    // Start timing
    auto start = std::chrono::steady_clock::now();

    int rowsPerThread = MATRIX_SIZE / NUM_THREADS;

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++)
    {
        threadData[i].startRow = i * rowsPerThread;

        threadData[i].endRow = (i == NUM_THREADS - 1)
            ? MATRIX_SIZE
            : (i + 1) * rowsPerThread;

        int result = pthread_create(
            &threads[i],
            NULL,
            matrixMultiply,
            &threadData[i]
        );

        if (result != 0)
        {
            printf("Error creating thread %d\n", i);
            return 1;
        }
    }

    // Wait for threads
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    // End timing
    auto end = std::chrono::steady_clock::now();

    double elapsed =
        std::chrono::duration<double>(end - start).count();

    // Display results
    printf("\nPthreads Matrix Multiplication\n");
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
    delete[] threads;
    delete[] threadData;

    return 0;
}
