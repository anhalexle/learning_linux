#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> //read, write
#include <signal.h>

#define MSG_SIZE 20

char *my_msg = "hello world";

char pipe_buff[MSG_SIZE];
int fds[2];

void sig_handler1(int num)
{
    printf("I'm signal handler 1: %d\n", num);
    write(fds[1], my_msg, MSG_SIZE);
}

int main(int argc, char const *argv[])
{
    if (signal(SIGINT, sig_handler1) == SIG_ERR)
    {
        printf("Error in overriding SIGINT\n");
        exit(EXIT_FAILURE);
    }
    if (pipe(fds) < 0)
    {
        printf("Error in creating pipe\n");
        exit(EXIT_FAILURE);
    }
    read(fds[0], pipe_buff, MSG_SIZE);
    printf("Data from pipe: %s", pipe_buff);
    return 0;
}