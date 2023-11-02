#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int work;

double func(double v)
{
    return 1;
}

void trapazoidal_count(double a, double b, int n, double *global_sum)
{
    int rank = omp_get_thread_num();
    int thread_count = omp_get_num_threads();
    int local_work = work / thread_count;
    double local_sum = 0;
    double local_a, local_b;
    double h = (a - b) / n;
    int x = 0;

    local_a = h * rank * local_work;
    local_b = local_a + h * local_work;
    local_sum = (func(local_a) + func(local_b)) / 2;

    for (int i = local_a; i < local_b; i++)
    {
        x = local_a + i * h;
        local_sum += func(x);
    }

    local_sum *= h;

#pragma omp critical
    *global_sum += local_sum;
}

int main()
{
    int thread_count = 5;
    double global_sum = 0;
    double a, b; // boundries
    int n;

#pragma omp parallel num_threads(thread_count)
    trapazoidal_count(a, b, n, &global_sum);

    return 0;
}