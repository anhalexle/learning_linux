#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_t thread_1, thread_2;

typedef struct
{
    int year;
    char number[12];
    char hometown[100];
    char name[100];
} Human;

static void *thread_handler(void *arg)
{
    pthread_t tid = pthread_self();
    if (pthread_equal(tid, thread_1))
    {
        printf("Hello I'm thread 1\n");
    }
    else
    {
        Human *threadData = (Human *)arg;
        printf("My name is %s, I'm %d years old, I come from %s and my number is %s\n", threadData->name, threadData->year, threadData->hometown, threadData->number);
    }
    pthread_exit(NULL);
}

int main()
{
    int ret;
    Human myLife = {2001, "09123112", "HCM", "Alex"};
    if (ret = pthread_create(&thread_1, NULL, thread_handler, NULL))
    {
        printf("Error in creating thread 1\n");
        return EXIT_FAILURE;
    }
    if (ret = pthread_create(&thread_2, NULL, thread_handler, &myLife))
    {
        printf("Error in creating thread 2\n");
        return EXIT_FAILURE;
    }
    pthread_join(thread_1, NULL);
    pthread_join(thread_2, NULL);
    return EXIT_SUCCESS;
}