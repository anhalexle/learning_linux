#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

// shared memory lib
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FILE_NAME "alex_mmap"
#define SM_SIZE 100

int main(int argc, char const *argv[])
{
    // alocate shared_memory
    int fd = shm_open(FILE_NAME, O_CREAT | O_RDWR, 0666);

    if (fd == -1)
    {
        printf("Error in creating shared memory\n");
        exit(EXIT_FAILURE);
    }

    // set size
    ftruncate(fd, SM_SIZE);

    // map memory
    // 0 -> assgin kernel to choose memory for mapping
    // MAP SHARED -> Shared file mapping
    // 0 -> offset
    char *data = (char *)mmap(0, SM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    printf("%s: Write data %s\n", __FILE__, data);
    munmap(data, SM_SIZE);
    close(fd);
    // shm_unlink(FILE_NAME);
    return 0;
}