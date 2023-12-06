#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/times.h>
#include <unistd.h>

#define N 10

int fibonacci_single_thread(int n)
{
    if (n <= 1)
        return n;
    return fibonacci_single_thread(n - 1) + fibonacci_single_thread(n - 2);
}

typedef struct
{
    int n;
    int result;
} ThreadData;

static void *fibonacci_multi_thread(void *args)
{
    ThreadData *data = (ThreadData *)args;
    if (data->n <= 1)
    {
        data->result = data->n;
    }
    else
    {
        ThreadData data1 = {data->n - 1, 0};
        ThreadData data2 = {data->n - 2, 0};
        pthread_t thread1, thread2;
        pthread_create(&thread1, NULL, fibonacci_multi_thread, &data1);
        pthread_create(&thread2, NULL, fibonacci_multi_thread, &data2);
        pthread_join(thread1, NULL);
        pthread_join(thread2, NULL);
        data->result = data1.result + data2.result;
    }
}

double calculate_time(clock_t start, clock_t end)
{
    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

int main()
{
    // Single thread
    clock_t start_time = clock();
    int res_single_thread = fibonacci_single_thread(N);
    clock_t end_time = clock();
    printf("Single thread result: %d, Time: %f seconds\n", res_single_thread, calculate_time(start_time, end_time));

    // Multi-thread
    ThreadData data = {N, 0};
    pthread_t main_thread;
    int ret;
    start_time = clock();
    if (ret = pthread_create(&main_thread, NULL, fibonacci_multi_thread, &data))
    {
        printf("Error in creating thread\n");
        return EXIT_FAILURE;
    }
    pthread_join(main_thread, NULL);
    end_time = clock();
    printf("Multi thread result: %d, Time: %f seconds\n", data.result, calculate_time(start_time, end_time));

    return EXIT_SUCCESS;
}