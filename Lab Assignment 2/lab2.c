#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  
#include <pthread.h>
 
int buffer = 0;
pthread_mutex_t lock;

void *thread_function(void *vargp)
{
    
    int *myid = (int *)vargp;
    
        pthread_mutex_lock(&lock);
        printf("Thread Id: %d, Process ID %d, buffer: %d \n", *myid, getpid(), buffer++);
        pthread_mutex_unlock(&lock);


    return NULL;
}
  
int main()
{
        pthread_t tid1, tid2, tid3;

        pthread_mutex_init(&lock, NULL);
        
            pthread_create(&tid1, NULL, thread_function, (void *)&tid1);
            pthread_create(&tid2, NULL, thread_function, (void *)&tid2);
            pthread_create(&tid3, NULL, thread_function, (void *)&tid3);
        for(int i = 0; i<5; i++){
        pthread_join(tid1, NULL);
        pthread_join(tid2, NULL);
        pthread_join(tid3, NULL);
        }
        pthread_mutex_destroy(&lock);

        return 0;
}