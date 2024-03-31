#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
// fifo
#include <sys/types.h>
#include <sys/stat.h>
// flag
#include <fcntl.h>

#define FIFO_FILE "./myfifo"
#define BUFF_SIZE 1024

int main(int argc, char const *argv[])
{
    char buff[BUFF_SIZE];
    int fd;
    // create FIFO
    mkfifo(FIFO_FILE, 0666);

    while (1)
    {
        printf("Send something to consumer: ");
        fflush(stdin); // clear input stream
        fgets(buff, BUFF_SIZE, stdin);
        fd = open(FIFO_FILE, O_WRONLY);
        write(fd, buff, strlen(buff) + 1);
        close(fd);
    }
    return 0;
}