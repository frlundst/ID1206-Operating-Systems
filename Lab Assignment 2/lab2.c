#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int buffer = 0;
pthread_mutex_t lock;

int *thread_function(void *vargp)
{
    int *myid = (int *)vargp, iterator = 0;

    while (1)
    {
        pthread_mutex_lock(&lock);
        if (buffer < 15)
        {
            printf("Thread Id: %d, Process ID %d, buffer: %d \n", *myid, getpid(), buffer++);
            iterator++;
            pthread_mutex_unlock(&lock);
            sleep(0.01);
        }
        else
        {
            pthread_mutex_unlock(&lock);
            return iterator;
        }
    }
}

int main()
{
    pthread_t tid[3];
    int counts[3], sum = 0;

    pthread_mutex_init(&lock, NULL);

    for (int i = 0; i < 3; i++)
    {
        pthread_create(&tid[i], NULL, thread_function, (void *)&tid[i]);
    }

    for (int i = 0; i < 3; i++)
    {
        pthread_join(tid[i], (int *)&counts[i]);
        printf("TID %d worked on the buffer %d \033[0;32mtimes\033[0m \n", tid[i], counts[i]);
        sum += counts[i];
    }

    printf("Total buffer accesses: %d \n", sum);

    pthread_mutex_destroy(&lock);
    return 0;
}