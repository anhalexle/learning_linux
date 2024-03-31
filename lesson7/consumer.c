#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FIFO_FILE "./myfifo"
#define BUFF_SIZE 1024

int main(int argc, char const *argv[])
{
    char buff[BUFF_SIZE];
    int fd;

    mkfifo(FIFO_FILE, 0666);
    while (1)
    {
        fd = open(FIFO_FILE, O_RDONLY);
        read(fd, buff, BUFF_SIZE);
        printf("Product message: %s", buff);
        close(fd);
    }
    return 0;
}