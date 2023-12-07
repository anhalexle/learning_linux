#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_var = PTHREAD_COND_INITIALIZER;
int current_thread = 1;
int volatile should_exit = 0;
const char *path = "thongtinsinhvien.txt";
int string_length = 0;
int fd;

typedef struct
{
    char name[100];
    char DateOfBirth[10];
    char hometown[100];
} student;

student newStudent;

void *thread1_handler(void *arg)
{
    while (!should_exit)
    {
        pthread_mutex_lock(&mutex);
        while (current_thread != 1 && !should_exit)
        {
            pthread_cond_wait(&cond_var, &mutex);
        }
        // Clear
        strcpy(newStudent.name, "");
        strcpy(newStudent.DateOfBirth, "");
        strcpy(newStudent.hometown, "");

        // Get input from the user for each field
        printf("Enter student name: ");
        fgets(newStudent.name, sizeof(newStudent.name), stdin);
        newStudent.name[strcspn(newStudent.name, "\n")] = '\0';

        printf("Enter Date of Birth: ");
        fgets(newStudent.DateOfBirth, sizeof(newStudent.DateOfBirth), stdin);
        newStudent.DateOfBirth[strcspn(newStudent.DateOfBirth, "\n")] = '\0';

        printf("Enter hometown: ");
        fgets(newStudent.hometown, sizeof(newStudent.hometown), stdin);
        newStudent.hometown[strcspn(newStudent.hometown, "\n")] = '\0';

        printf("%s %s %s\n", newStudent.name, newStudent.DateOfBirth, newStudent.hometown);

        current_thread = 2;
        pthread_cond_broadcast(&cond_var);
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

void *thread2_handler(void *arg)
{
    while (!should_exit)
    {
        pthread_mutex_lock(&mutex);
        while (current_thread != 2 && !should_exit)
        {
            pthread_cond_wait(&cond_var, &mutex);
        }
        int bytes_written;
        fd = open(path, O_CREAT | O_WRONLY | O_APPEND);
        if (fd == -1)
        {
            printf("Error in opening file %s\n", path);
            should_exit = 1;
            pthread_cond_broadcast(&cond_var);
            pthread_mutex_unlock(&mutex);
            pthread_exit(NULL);
        }
        char data_buffer[256];
        snprintf(data_buffer, sizeof(data_buffer), "Name: %s, DOB: %s, Village: %s\n", newStudent.name, newStudent.DateOfBirth, newStudent.hometown);
        string_length = strlen(data_buffer);
        bytes_written = write(fd, data_buffer, strlen(data_buffer));
        if (bytes_written == -1)
        {
            printf("Error in writing file %s\n", path);
            should_exit = 1;
            pthread_cond_broadcast(&cond_var);
            pthread_mutex_unlock(&mutex);
            pthread_exit(NULL);
        }
        printf("%d bytes have been written into %s\n", bytes_written, path);
        close(fd);
        current_thread = 3;
        pthread_cond_broadcast(&cond_var);
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

void *thread3_handler(void *arg)
{
    while (!should_exit)
    {
        pthread_mutex_lock(&mutex);
        while (current_thread != 3 && !should_exit)
        {
            pthread_cond_wait(&cond_var, &mutex);
        }
        int bytes_read;
        fd = open(path, O_CREAT | O_RDONLY);
        if (fd == -1)
        {
            printf("Error in opening file %s\n", path);
            should_exit = 1;
            pthread_cond_broadcast(&cond_var);
            pthread_mutex_unlock(&mutex);
            pthread_exit(NULL);
        }
        lseek(fd, string_length * -1, SEEK_END);
        char buffer_read[1024];
        bytes_read = read(fd, buffer_read, sizeof(buffer_read));
        if (bytes_read == -1)
        {
            printf("Error in reading file %s\n", path);
            should_exit = 1;
            pthread_cond_broadcast(&cond_var);
            pthread_mutex_unlock(&mutex);
            pthread_exit(NULL);
        }
        printf("\n%s\n", buffer_read);
        current_thread = 1;
        pthread_cond_broadcast(&cond_var);
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

int main()
{
    pthread_t thread1, thread2, thread3;
    pthread_create(&thread1, NULL, thread1_handler, NULL);
    pthread_create(&thread2, NULL, thread2_handler, NULL);
    pthread_create(&thread3, NULL, thread3_handler, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    return 0;
}