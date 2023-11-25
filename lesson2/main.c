#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main()
{
    // exercise 3
    const char *path_ex3 = "ex3.txt";
    int fd, bytes_written;
    fd = open(path_ex3, O_CREAT | O_WRONLY);
    if (fd == -1)
    {
        printf("Error in opening %s\n", path_ex3);
        exit(1);
    }
    char *data_bt3 = "Hello_world";
    bytes_written = write(fd, data_bt3, strlen(data_bt3));
    if (bytes_written == -1)
    {
        printf("Error in writing %s into %s file\n", data_bt3, path_ex3);
        exit(1);
    }
    printf("%d bytes have been written into %s\n", bytes_written, path_ex3);
    close(fd);

    // exercise 4
    const char *path_ex4 = "ex4.txt";
    fd = open(path_ex4, O_CREAT | O_WRONLY | O_APPEND);
    if (fd == -1)
    {
        printf("Error in opening %s", path_ex4);
        exit(1);
    }
    if (lseek(fd, 0, SEEK_SET) == -1)
    {
        printf("Error in changing position offset in file");
        exit(1);
    }
    char *data_bt4 = "Write something new into ex4.txt";
    bytes_written = write(fd, data_bt4, strlen(data_bt4));
    if (bytes_written == -1)
    {
        printf("Error in writing %s into %s file", data_bt4, path_ex4);
        exit(1);
    }
    printf("%d bytes have been written into %s", bytes_written, path_ex4);
    // when open file with flag O_APPEND the lseek function will be ignore and the position of new data which is written will be the end of file.
    return EXIT_SUCCESS;
}