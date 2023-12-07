#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/times.h>

int count = 0;

void sig_int_handler(int sigHandler)
{
    printf("\nHello I'm %d and counter is %d\n", sigHandler, ++count);
}

void sig_usr_handler(int sigHandler)
{
    switch (sigHandler)
    {
    case SIGUSR1:
    {
        printf("\nHi I'm sigusr1\n");
        printf("Hello I'm %d and counter is %d\n", sigHandler, ++count);
        break;
    }
    case SIGUSR2:
    {
        printf("\nHi I'm sigusr2\n");
        printf("Hello I'm %d and counter is %d\n", sigHandler, ++count);
        break;
    }
    default:
    {
        printf("\nError in catching sig usr\n");
        exit(EXIT_FAILURE);
    }
    };
}

int main()
{
    if (signal(SIGINT, sig_int_handler) == SIG_ERR)
    {
        fprintf(stderr, "Error in handling sigint\n");
        exit(EXIT_FAILURE);
    }
    sleep(2);
    kill(getpid(), SIGINT);
    signal(SIGUSR1, sig_usr_handler);
    signal(SIGUSR2, sig_usr_handler);
    sleep(2);
    kill(getpid(), SIGUSR1);
    sleep(2);
    kill(getpid(), SIGUSR2);
    return 0;
}