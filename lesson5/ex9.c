#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/times.h>

void sig_handler(int signum)
{
    printf("\nI'm sigint handler\n");
}

int main()
{
    sigset_t new_set, old_set;
    if (signal(SIGINT, sig_handler) == SIG_ERR)
    {
        fprintf(stderr, "Cannot handle SIGINT\n");
        exit(EXIT_FAILURE);
    }
    sigemptyset(&new_set);
    sigemptyset(&old_set);
    printf("Try to block sigint\n");
    sigaddset(&new_set, SIGINT);
    if (sigprocmask(SIG_SETMASK, &new_set, &old_set) == 0)
    {
        if (sigismember(&new_set, SIGINT) == 1)
        {
            printf("SIGINT block exist\n");
        }
        else if (sigismember(&new_set, SIGINT) == 0)
        {
            printf("SIGINT block does not exist\n");
        }
    }
    sleep(2);
    printf("Try to unblock sigint\n");
    sigdelset(&new_set, SIGINT);
    if (sigprocmask(SIG_SETMASK, &new_set, &old_set) == 0)
    {
        if (sigismember(&new_set, SIGINT) == 1)
        {
            printf("SIGINT block exist\n");
        }
        else if (sigismember(&new_set, SIGINT) == 0)
        {
            printf("SIGINT block does not exist\n");
            kill(getpid(), SIGINT);
        }
    }
    return 0;
}