
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 15

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

    long long totalSolutions = 0;

    // Start timing
    double start = omp_get_wtime();

    // Parallelize first-column row placements
    #pragma omp parallel for num_threads(NUM_THREADS) reduction(+:totalSolutions) schedule(static)
    for (int row = 0; row < N; row++)
    {
        int board[N];

        for (int i = 0; i < N; i++)
        {
            board[i] = -1;
        }

        if (isSafe(board, row, 0, N))
        {
            board[0] = row;

            long long localSolutions = 0;

            solveNQueensUtil(
                board, 1, N, &localSolutions
            );

            totalSolutions += localSolutions;
        }
    }

    // End timing
    double end = omp_get_wtime();

    double elapsed = end - start;

    // Display results
    printf("\nOpenMP N Queens\n");
    printf("N = %d\n", N);
    printf("Number of Threads: %d\n", NUM_THREADS);
    printf("Solutions Found: %lld\n", totalSolutions);
    printf("Execution Time: %.6f seconds\n", elapsed);

    return 0;
}
