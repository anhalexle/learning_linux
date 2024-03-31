#include <string.h>
#include <unistd.h> // read, write

#include "chat_func.h"
#include "handle_error.h"

#define BUFF_SIZE 256
void chat_func(int socket_fd, bool isServer)
{
    int bytes_read, bytes_write;
    char send_buffer[BUFF_SIZE], receive_buffer[BUFF_SIZE];
    while (1)
    {
        memset(send_buffer, '0', BUFF_SIZE);
        memset(receive_buffer, '0', BUFF_SIZE);

        if (isServer)
        {
            bytes_read = read(socket_fd, receive_buffer, BUFF_SIZE);
            if (bytes_read == -1)
                handle_error("read()");
            if (strncmp("exit", receive_buffer, 4) == 0)
            {
                printf("Client shutdown ...");
                break;
            }

            printf("\nMessage from Client: %s\n", receive_buffer);
            printf("Please respond the message: ");
            fgets(send_buffer, BUFF_SIZE, stdin); // the new way to receive the string data

            bytes_write = write(socket_fd, send_buffer, BUFF_SIZE);
            if (bytes_write == -1)
                handle_error("write()");
            if (strncmp("exit", send_buffer, 4) == 0)
            {
                printf("Server shutdown ...\n");
                break;
            }
        }
        else
        {
            printf("\nPlease type the message to the server: ");
            fgets(send_buffer, BUFF_SIZE, stdin);
            bytes_write = write(socket_fd, send_buffer, BUFF_SIZE);
            if (bytes_write == -1)
                handle_error("write()");
            if (strncmp("exit", send_buffer, 4) == 0)
            {
                printf("Client shutdown ...\n");
                break;
            }
            bytes_read = read(socket_fd, receive_buffer, BUFF_SIZE);
            if (bytes_read < 0)
                handle_error("read()");
            if (strncmp("exit", receive_buffer, 4) == 0)
            {
                printf("Client shutdown ...\n");
                break;
            }
            printf("Response from server %s\n", receive_buffer);
        }
        sleep(1);
    }
    close(socket_fd);
}