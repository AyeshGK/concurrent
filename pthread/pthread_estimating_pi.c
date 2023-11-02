#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

long thread_count = 4; // global variable
long work_load = 40000000;
double global_sum = 0;
pthread_mutex_t mutex;

void *estimating_pi(void *rank)
{
    int my_rank = (int)rank;
    int local_work_load = work_load / thread_count;
    int starting_number = local_work_load * my_rank;
    int ending_number = starting_number + work_load;
    int local_sum = 0;

    int factor = 1;

    if (starting_number % 2 != 0)
        factor = -1;

    for (int i = starting_number; i < ending_number; i++, factor = -factor)
        local_sum += factor / (2 * i + 1);

    pthread_mutex_lock(&mutex);
    global_sum += local_sum;
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main()
{
    pthread_t *thread_handles;
    pthread_mutex_init(&mutex, NULL);
    thread_handles = malloc(thread_count * sizeof(pthread_t));

    for (int i = 0; i < thread_count; i++)
        pthread_create(&thread_handles[i], NULL, estimating_pi, (void *)i);

    free(thread_handles);
    pthread_mutex_destroy(&mutex);
    return 0;
}