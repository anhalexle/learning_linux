#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    pid_t child_proc;

    child_proc = fork();
    if (child_proc == -1) {
        printf("Error in creating child process\n");
        exit(1);
    }
    else if (child_proc == 0) {
        printf("I'm child process, my pid is %d and my parent pid is %d\n", getpid(), getppid());
        exit(0);
    }
    else {
        printf("I'm parent process, my pid is %d\n", getpid());
    }
    return EXIT_SUCCESS;
}