#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void Hello()
{
    int num_threads = omp_get_num_threads();
    int rank = omp_get_thread_num();

    printf("Hello thread from %d of %d\n", rank, num_threads);
}

int main()
{
    int thread_count = 5;

#pragma omp parallel num_threads(thread_count)
    Hello();

    return 0;
}