#include <stdio.h>
#include <omp.h>

int main()
{
    int thread_count = 4;

    omp_set_num_threads(thread_count);

#pragma omp parallel
    {
        int thread_count = omp_get_num_threads();
        int rank = omp_get_thread_num();
#pragma omp for
        for (int i = 0; i < 100; i++)
        {
            printf("i - %d Hello from thread %d of %d\n", i, rank, thread_count);
        }
    }
    return 0;
}