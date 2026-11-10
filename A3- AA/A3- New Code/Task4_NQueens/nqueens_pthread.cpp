
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <chrono>

#define N 15

struct ThreadData
{
    int startRow;
    int endRow;
    long long solutions;
};

bool isSafe(int board[], int row, int col, int n)
{
    for (int i = 0; i < col; i++)
    {
        if (board[i] == row ||
            abs(board[i] - row) == abs(i - col))
        {
            return false;
        }
    }

    return true;
}

void solveNQueensUtil(int board[], int col, int n,
                      long long* solutions)
{
    if (col == n)
    {
        (*solutions)++;
        return;
    }

    for (int row = 0; row < n; row++)
    {
        if (isSafe(board, row, col, n))
        {
            board[col] = row;

            solveNQueensUtil(
                board, col + 1, n, solutions
            );
        }
    }
}

void* solveNQueens(void* arg)
{
    ThreadData* data = (ThreadData*)arg;

    long long localSolutions = 0;

    for (int row = data->startRow;
         row < data->endRow; row++)
    {
        int board[N];

        for (int i = 0; i < N; i++)
        {
            board[i] = -1;
        }

        if (isSafe(board, row, 0, N))
        {
            board[0] = row;

            solveNQueensUtil(
                board, 1, N, &localSolutions
            );
        }
    }

    data->solutions = localSolutions;

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

    pthread_t* threads = new pthread_t[NUM_THREADS];
    ThreadData* threadData = new ThreadData[NUM_THREADS];

    // Start timing
    auto start = std::chrono::steady_clock::now();

    int rowsPerThread = N / NUM_THREADS;

    // Create threads
    int createdThreads = 0;

    for (int i = 0; i < NUM_THREADS; i++)
    {
        threadData[i].startRow = i * rowsPerThread;

        threadData[i].endRow = (i == NUM_THREADS - 1)
            ? N
            : (i + 1) * rowsPerThread;

        threadData[i].solutions = 0;

        int result = pthread_create(
            &threads[i],
            NULL,
            solveNQueens,
            &threadData[i]
        );

        if (result != 0)
        {
            printf("Error creating thread %d\n", i);
            break;
        }

        createdThreads++;
    }

    // Wait for successfully created threads
    long long totalSolutions = 0;

    for (int i = 0; i < createdThreads; i++)
    {
        pthread_join(threads[i], NULL);

        totalSolutions += threadData[i].solutions;
    }

    // End timing
    auto end = std::chrono::steady_clock::now();

    double elapsed =
        std::chrono::duration<double>(end - start).count();

    // Display results
    printf("\nPthreads N Queens\n");
    printf("N = %d\n", N);
    printf("Number of Threads: %d\n", NUM_THREADS);
    printf("Solutions Found: %lld\n", totalSolutions);
    printf("Execution Time: %.6f seconds\n", elapsed);

    delete[] threads;
    delete[] threadData;

    return createdThreads == NUM_THREADS ? 0 : 1;
}
