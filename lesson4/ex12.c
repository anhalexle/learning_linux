#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/times.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_var = PTHREAD_COND_INITIALIZER;
int current_thread = 1;

void *thread1_handler(void *arg)
{
    while (1)
    {
        pthread_mutex_lock(&mutex);
        while (current_thread != 1)
        {
            pthread_cond_wait(&cond_var, &mutex);
        }
        printf("Thread 1 is running\n");
        sleep(1);
        current_thread = 2;
        pthread_cond_broadcast(&cond_var);
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

void *thread2_handler(void *arg)
{
    while (1)
    {
        pthread_mutex_lock(&mutex);
        while (current_thread != 2)
        {
            pthread_cond_wait(&cond_var, &mutex);
        }
        printf("Thread 2 is running\n");
        sleep(1);
        current_thread = 3;
        pthread_cond_broadcast(&cond_var);
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

void *thread3_handler(void *arg)
{
    while (1)
    {
        pthread_mutex_lock(&mutex);
        while (current_thread != 3)
        {
            pthread_cond_wait(&cond_var, &mutex);
        }
        printf("Thread 3 is running\n");
        sleep(1);
        current_thread = 1;
        pthread_cond_broadcast(&cond_var);
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

int main()
{
    pthread_t thread1, thread2, thread3;
    pthread_create(&thread1, NULL, thread1_handler, NULL);
    pthread_create(&thread2, NULL, thread2_handler, NULL);
    pthread_create(&thread3, NULL, thread3_handler, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    return 0;
}