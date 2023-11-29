#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t child_proc, parent_proc;
    int status;

    child_proc = fork();
    switch (child_proc)
    {
        case -1: 
        {
            printf("Error in creating child process\n");
            exit(1);
        }
        case 0:
        {
            printf("Hi I'm child process, my pid is %d and my parent pid is %d\n", getpid(), getppid());
            // Testing killing by signal
            // while(1);
            exit(0);
        }
        default:
        {
            parent_proc = waitpid(child_proc, &status, WUNTRACED | WCONTINUED);
            if (parent_proc == -1) {
                printf("Error in waiting pid\n");
                exit(1);
            }
            if (WIFEXITED(status)) {
                printf("Child process exited normally, the exit status is %d\n", WEXITSTATUS(status));
            }
            else if (WIFSIGNALED(status)) {
                printf("Child process has been killed by signal %d\n", WTERMSIG(status));
            }
            
        }
    }
    return EXIT_SUCCESS;
}