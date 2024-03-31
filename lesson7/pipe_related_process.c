#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdbool.h>

#define MSG_SIZE 256

char *msg_1 = "Hello world 1";
char *msg_2 = "Hello world 2";
char *msg_3 = "Hello world 3";

int main(int argc, char *argv[])
{
    int fds[2], num_read;
    char in_buff[MSG_SIZE];
    pid_t child_pid;
    if (pipe(fds) == -1)
    {
        printf("Error in creating pipe\n");
        exit(EXIT_FAILURE);
    }
    child_pid = fork();

    if (child_pid == 0)
    {
        printf("I'm child process\n");
        if (close(fds[1]) == -1)
        {
            printf("close fds[1] failed\n");
            exit(EXIT_FAILURE);
        } // write end is unused -> child is reader
        bool exitchildproc = false;
        while (!exitchildproc)
        {
            num_read = read(fds[0], in_buff, MSG_SIZE);
            switch (num_read)
            {
            case -1:
                printf("read() failed\n");
                exit(EXIT_FAILURE);
            case 0:
                printf("pipe end-of-pipe\n");
                exitchildproc = true;
                break;
            default:
                printf("msg: %s\n", in_buff);
            }
        }
        exit(EXIT_SUCCESS);
    }
    else
    {
        printf("I'm parent process\n"); // writer
        if (close(fds[0]) == -1)
        {
            printf("Error in closing fds[0]\n");
            exit(EXIT_FAILURE);
        }

        write(fds[1], msg_1, MSG_SIZE);
        write(fds[1], msg_2, MSG_SIZE);
        write(fds[1], msg_3, MSG_SIZE);

        if (close(fds[1]) == -1)
        {
            printf("Error in closing fds[1]\n");
            exit(EXIT_FAILURE);
        } // -> now the reader will see end of pipe (child proc)

        // while (1)
        //     ;
    }
    return 0;
}