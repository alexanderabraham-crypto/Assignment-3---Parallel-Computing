#include <stdio.h>
#include <time.h>

#define N 100000000 // intervals

double f(double x) {
    return 4.0 / (1.0 + x * x);
}

double trapezoidalRule() 
{
    double a = 0.0;
    double b = 1.0;
    double h = (b - a) / N;

    double sum = (f(a) + f(b)) / 2.0;

    for (int i = 1; i < N; i++)
    {
        double x = a + i * h;
        sum += f(x);
    }

    return h * sum;
}

int main() 
{
    clock_t start = clock();

    double pi = trapezoidalRule();

    clock_t end = clock();

    double elapsed = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Estimated value of π: %f\n", pi);
    printf("Execution time: %.6f seconds\n", elapsed);

    return 0;
}
