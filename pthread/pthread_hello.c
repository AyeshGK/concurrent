#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

long thread_count = 4; // global variable

void *hello(void *rank)
{
    long my_rank = (long)rank;
    printf("Hello world - %ld of %d\n", my_rank, thread_count);
    return NULL;
}

int main()
{
    long thread;
    pthread_t *thread_handles;

    thread_handles = malloc(thread_count * sizeof(pthread_t));

    for (int i = 0; i < thread_count; i++)
        pthread_create(&thread_handles[i], NULL, hello, (void *)i);

    for (int i = 0; i < thread_count; i++)
        pthread_join(thread_handles[i], NULL);

    free(thread_handles);
    return 0;
}