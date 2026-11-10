
#include <stdio.h>
#include <chrono>

#define MATRIX_SIZE 1000

void matrixMultiply(int** A, int** B, int** C, int n)
{
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

int main()
{
    int** A = new int*[MATRIX_SIZE];
    int** B = new int*[MATRIX_SIZE];
    int** C = new int*[MATRIX_SIZE];

    // Allocate matrices
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
    auto start = std::chrono::steady_clock::now();

    matrixMultiply(A, B, C, MATRIX_SIZE);

    // End timing
    auto end = std::chrono::steady_clock::now();

    double elapsed =
        std::chrono::duration<double>(end - start).count();

    printf("Sequential Matrix Multiplication\n");
    printf("Matrix Size: %d x %d\n",
           MATRIX_SIZE, MATRIX_SIZE);
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
