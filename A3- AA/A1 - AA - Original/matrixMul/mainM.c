#include <windows.h>
#include "matrixMul.h"


int main() 
{
    int** A = (int**)malloc(N * sizeof(int*));
    int** B = (int**)malloc(N * sizeof(int*));
    int** C = (int**)malloc(N * sizeof(int*));
    
    for (int i = 0; i < N; ++i) {
        A[i] = (int*)malloc(N * sizeof(int));
        B[i] = (int*)malloc(N * sizeof(int));
        C[i] = (int*)malloc(N * sizeof(int));
    }

    if (A == NULL || B == NULL || C == NULL) {
        printf("Memory allocation failed!\n");
        return -1;
    }

    printf("Matrices allocated successfully.\n");

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            A[i][j] = 1;
            B[i][j] = 1;
            C[i][j] = 0;
        }
    }

    printf("Matrices initialized successfully.\n");

    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;

    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);

    matrixMultiply(A, B, C, N);

    QueryPerformanceCounter(&end);

    double elapsed = (double)(end.QuadPart - start.QuadPart)
                     / frequency.QuadPart;

    printf("Matrix multiplication complete!\n");
    printf("C[0][0] = %d\n", C[0][0]);
    printf("Execution time: %.6f seconds\n", elapsed);

    for (int i = 0; i < N; ++i) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }

    free(A);
    free(B);
    free(C);

    return 0;
}
