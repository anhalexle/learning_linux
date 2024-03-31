#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include "chat_func.h"
#define MAX_LISTEN 50
void handle_error(char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}
int main(int argc, char *argv[])
{
    int server_fd, new_socket_fd;
    int port_no, len, opt;
    struct sockaddr_in server_addr, client_addr;
    if (argc < 2)
    {
        printf("Please provide port\n Command: ./server <port number>\n");
        exit(EXIT_FAILURE);
    }
    // convert from string to int
    port_no = atoi(argv[1]);
    // domain, type, protocol
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1)
    {
        handle_error("socket()");
    }
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        handle_error("setsockopt()");
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port_no);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        handle_error("bind()");
    }
    if (listen(server_fd, MAX_LISTEN) == -1)
    {
        handle_error("listen()");
    }
    len = sizeof(client_addr);
    while (1)
    {
        printf("Server is listening at port: %d \n... \n", port_no);
        new_socket_fd = accept(server_fd, (struct sockaddr *)&client_addr, (socklen_t *)&len);
        if (new_socket_fd == -1)
            handle_error("accept() ");
    }
}