#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>

void signal_handler(int signal) {
    printf("Hi I'm in the signal handelr now\n");
    wait(NULL);
}

int main() {
    pid_t child_pid;
    int status;
    child_pid = fork();
    if (child_pid == 0) {
        printf("Hi I'm child process and my pid is %d\n", getpid());
    }
    else {
        // wait(&status);
        signal(SIGCHLD, signal_handler);
        printf("Hi I'm parent process\n");
        while(1);
    }
    return EXIT_SUCCESS;
}