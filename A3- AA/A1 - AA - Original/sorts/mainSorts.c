#include "sorts.h"

int main() 
{
    srand(time(NULL));

    // Dynamically allocate arrays
    int *arr1 = (int*)malloc(SIZE * sizeof(int));
    int *arr2 = (int*)malloc(SIZE * sizeof(int));

    if (!arr1 || !arr2) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Populate arrays with random values
    for (int i = 0; i < SIZE; i++) {
        int val = rand() % MAX_VAL;
        arr1[i] = val;
        arr2[i] = val;
    }

    // Time Merge Sort
    clock_t startMerge = clock();

    mergeSort(arr1, 0, SIZE - 1);

    clock_t endMerge = clock();

    double mergeTime = (double)(endMerge - startMerge) / CLOCKS_PER_SEC;

    printf("Merge Sort execution time: %.6f seconds\n", mergeTime);

    // Time Bubble Sort
    clock_t startBubble = clock();

    bubbleSort(arr2, SIZE);

    clock_t endBubble = clock();

    double bubbleTime = (double)(endBubble - startBubble) / CLOCKS_PER_SEC;

    printf("Bubble Sort execution time: %.6f seconds\n", bubbleTime);

    free(arr1);
    free(arr2);

    return 0;
}
