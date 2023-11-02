#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

long thread_count;
int matrix[4][3];
int vector[3];
int result[4];
int work = 4;

void *matrix_vector_mul(void *rank)
{
    long my_rank = (long)rank;

    int local_work = work / thread_count;
    int local_start = local_work * my_rank;
    int local_end = local_start + local_work;

    for (int i = local_start; i < local_end; i++)
        for (int j = 0; j < 3; j++)
            result[i] += matrix[i][j] * vector[j];

    return NULL;
}

int main()
{
    pthread_t *thread_handles;

    thread_count = 4;
    thread_handles = malloc(thread_count * sizeof(thread_handles));

    // matrix creation
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            matrix[i][j] = i * 3 + j;
        }
    }

    // vector creation
    for (int i = 0; i < 4; i++)
    {
        vector[i] = i * 5 + 2;
    }

    for (int thread = 0; thread < thread_count; thread++)
        pthread_create(&thread_handles[thread], NULL, matrix_vector_mul, (void *)thread);

    return 0;
}