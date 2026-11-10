#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// ===============================
// Task 1: Array Sum
// ===============================

#define ARRAY_SIZE 10000000

long long sumArray(int arr[], int size)
{
    long long sum = 0;

    for (int i = 0; i < size; i++)
    {
        sum += arr[i];
    }

    return sum;
}

// ===============================
// Task 2: Matrix Multiplication
// ===============================

#define MATRIX_SIZE 500

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

// ===============================
// Task 3: N-Queens
// ===============================

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

long long queenSolutions = 0;

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

// ===============================
// Task 4: Merge Sort
// ===============================

void merge(int arr[], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];

    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }

        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

void mergeSort(int arr[], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

// ===============================
// Bubble Sort
// ===============================

void bubbleSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// ===============================
// Task 5: Numerical Integration
// ===============================

#define INTERVALS 100000000

double f(double x)
{
    return 4.0 / (1.0 + x * x);
}

double trapezoidalRule()
{
    double a = 0.0;
    double b = 1.0;

    double h = (b - a) / INTERVALS;

    double sum = (f(a) + f(b)) / 2.0;

    for (int i = 1; i < INTERVALS; i++)
    {
        double x = a + i * h;
        sum += f(x);
    }

    return h * sum;
}

// ===============================
// MAIN
// ===============================

int main()
{
    printf("=============================================\n");
    printf("       SEQUENTIAL COMPUTING RESULTS\n");
    printf("=============================================\n\n");

    // -----------------------------------------
    // TASK 1: ARRAY SUM
    // -----------------------------------------

    printf("TASK 1: ARRAY SUM\n");

    int* arr = new int[ARRAY_SIZE];

    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        arr[i] = i + 1;
    }

    clock_t start = clock();

    long long totalSum = sumArray(arr, ARRAY_SIZE);

    clock_t end = clock();

    double sumTime =
        (double)(end - start) / CLOCKS_PER_SEC;

    printf("Elements: %d\n", ARRAY_SIZE);
    printf("Total Sum: %lld\n", totalSum);
    printf("Execution Time: %.6f seconds\n\n", sumTime);

    delete[] arr;


    // -----------------------------------------
    // TASK 2: MATRIX MULTIPLICATION
    // -----------------------------------------

    printf("TASK 2: MATRIX MULTIPLICATION\n");

    int** A = new int*[MATRIX_SIZE];
    int** B = new int*[MATRIX_SIZE];
    int** C = new int*[MATRIX_SIZE];

    for (int i = 0; i < MATRIX_SIZE; i++)
    {
        A[i] = new int[MATRIX_SIZE];
        B[i] = new int[MATRIX_SIZE];
        C[i] = new int[MATRIX_SIZE];
    }

    for (int i = 0; i < MATRIX_SIZE; i++)
    {
        for (int j = 0; j < MATRIX_SIZE; j++)
        {
            A[i][j] = 1;
            B[i][j] = 1;
            C[i][j] = 0;
        }
    }

    start = clock();

    matrixMultiply(A, B, C, MATRIX_SIZE);

    end = clock();

    double matrixTime =
        (double)(end - start) / CLOCKS_PER_SEC;

    printf("Matrix Size: %d x %d\n",
           MATRIX_SIZE, MATRIX_SIZE);

    printf("C[0][0] = %d\n", C[0][0]);

    printf("Execution Time: %.6f seconds\n\n",
           matrixTime);

    for (int i = 0; i < MATRIX_SIZE; i++)
    {
        delete[] A[i];
        delete[] B[i];
        delete[] C[i];
    }

    delete[] A;
    delete[] B;
    delete[] C;


    // -----------------------------------------
    // TASK 3: N-QUEENS
    // -----------------------------------------

    printf("TASK 3: N-QUEENS\n");

    int n = 8;

    int* board = new int[n];

    for (int i = 0; i < n; i++)
    {
        board[i] = -1;
    }

    queenSolutions = 0;

    start = clock();

    solveNQueensUtil(board, 0, n);

    end = clock();

    double queensTime =
        (double)(end - start) / CLOCKS_PER_SEC;

    printf("N = %d\n", n);
    printf("Solutions Found: %lld\n", queenSolutions);
    printf("Execution Time: %.6f seconds\n\n",
           queensTime);

    delete[] board;


    // -----------------------------------------
    // TASK 4: SORTING
    // -----------------------------------------

    printf("TASK 4: SORTING\n");

    const int SORT_SIZE = 10000;

    int* arr1 = new int[SORT_SIZE];
    int* arr2 = new int[SORT_SIZE];

    srand(1);

    for (int i = 0; i < SORT_SIZE; i++)
    {
        int value = rand() % 100000;

        arr1[i] = value;
        arr2[i] = value;
    }

    // Merge Sort

    start = clock();

    mergeSort(arr1, 0, SORT_SIZE - 1);

    end = clock();

    double mergeTime =
        (double)(end - start) / CLOCKS_PER_SEC;

    printf("Merge Sort:\n");
    printf("Elements: %d\n", SORT_SIZE);
    printf("Execution Time: %.6f seconds\n",
           mergeTime);

    // Bubble Sort

    start = clock();

    bubbleSort(arr2, SORT_SIZE);

    end = clock();

    double bubbleTime =
        (double)(end - start) / CLOCKS_PER_SEC;

    printf("Bubble Sort:\n");
    printf("Elements: %d\n", SORT_SIZE);
    printf("Execution Time: %.6f seconds\n\n",
           bubbleTime);

    delete[] arr1;
    delete[] arr2;


    // -----------------------------------------
    // TASK 5: NUMERICAL INTEGRATION
    // -----------------------------------------

    printf("TASK 5: NUMERICAL INTEGRATION\n");

    start = clock();

    double pi = trapezoidalRule();

    end = clock();

    double integrationTime =
        (double)(end - start) / CLOCKS_PER_SEC;

    printf("Intervals: %d\n", INTERVALS);
    printf("Estimated Pi: %.6f\n", pi);
    printf("Execution Time: %.6f seconds\n\n",
           integrationTime);


    // -----------------------------------------
    // FINAL SUMMARY
    // -----------------------------------------

    printf("=============================================\n");
    printf("              FINAL SUMMARY\n");
    printf("=============================================\n");

    printf("Array Sum:             %.6f seconds\n",
           sumTime);

    printf("Matrix Multiplication: %.6f seconds\n",
           matrixTime);

    printf("N-Queens:              %.6f seconds\n",
           queensTime);

    printf("Merge Sort:            %.6f seconds\n",
           mergeTime);

    printf("Bubble Sort:           %.6f seconds\n",
           bubbleTime);

    printf("Numerical Integration: %.6f seconds\n",
           integrationTime);

    printf("=============================================\n");

    return 0;
}
