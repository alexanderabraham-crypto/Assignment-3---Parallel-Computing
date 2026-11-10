
#include <stdio.h>
#include <chrono>

#define INTERVALS 1000000000LL

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

    for (long long i = 1; i < INTERVALS; i++)
    {
        double x = a + i * h;
        sum += f(x);
    }

    return h * sum;
}

int main()
{
    // Start timing
    auto start = std::chrono::steady_clock::now();

    double pi = trapezoidalRule();

    // End timing
    auto end = std::chrono::steady_clock::now();

    double elapsed =
        std::chrono::duration<double>(end - start).count();

    printf("Sequential Trapezoidal Rule Integration\n");
    printf("Intervals: %lld\n", INTERVALS);
    printf("Estimated Pi: %.12f\n", pi);
    printf("Execution Time: %.6f seconds\n", elapsed);

    return 0;
}
