#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

/*
Synchronization: OpenMP provides functions and directives for synchronizing threads.
The #pragma omp barrier directive can be used to ensure that all threads have reached
a specific point in the code before continuing.

#pragma omp barrier

normal output:
Hello from thread 0 of 2
This is the second main thread
Hello from thread 1 of 2

output with barrier:
Hello from thread 0 of 2
Hello from thread 1 of 2
This is the second main thread
*/
void barrier()
{
    int thread_count = omp_get_num_threads();
    int rank = omp_get_thread_num();

    print("Hello from thread %d of %d\n", rank, thread_count);
#pragma omp barrier
    if (rank == 0)
        printf("This is the second main thread\n");
}

int main()
{
    int thread_count = 2;

#pragma omp parallel num_threads(thread_count)
    barrier();

    return 0;
}