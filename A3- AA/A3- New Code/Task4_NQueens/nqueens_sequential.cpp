
#include <stdio.h>
#include <stdlib.h>
#include <chrono>

#define N 15

long long queenSolutions = 0;

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

void solveNQueensUtil(int board[], int col, int n)
{
    if (col == n)
    {
        queenSolutions++;
        return;
    }

    for (int row = 0; row < n; row++)
    {
        if (isSafe(board, row, col, n))
        {
            board[col] = row;

            solveNQueensUtil(board, col + 1, n);
        }
    }
}

int main()
{
    int* board = new int[N];

    for (int i = 0; i < N; i++)
    {
        board[i] = -1;
    }

    queenSolutions = 0;

    // Start timing
    auto start = std::chrono::steady_clock::now();

    solveNQueensUtil(board, 0, N);

    // End timing
    auto end = std::chrono::steady_clock::now();

    double elapsed =
        std::chrono::duration<double>(end - start).count();

    printf("Sequential N Queens\n");
    printf("N = %d\n", N);
    printf("Solutions Found: %lld\n", queenSolutions);
    printf("Execution Time: %.6f seconds\n", elapsed);

    delete[] board;

    return 0;
}
