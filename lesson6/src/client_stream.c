#include <sys/socket.h> //  Chứa cấu trúc cần thiết cho socket.
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h> //  Thư viện chứa các hằng số, cấu trúc khi sử dụng địa chỉ trên internet
#include <arpa/inet.h>  // convert values between host and network byte order

#include "handle_error.h"
#include "chat_func.h"

#define BUFF_SIZE 256

int main(int argc, char *argv[])
{
    int port_number, socket_fd;
    struct sockaddr_in serv_addr;
    if (argc < 3)
    {
        printf("command : ./client <server address> <port number>\n");
        exit(EXIT_FAILURE);
    }
    port_number = atoi(argv[2]);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port_number);
    /*
        AF_INET: address family -> designate the type of address that the socket wanna use -> INET v4 (safest option)
        AF_INET6: INET v6
    */
    // convert IPV4 to binary
    if (inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) == -1)
        handle_error("inet_pton()");
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd == -1)
        handle_error("socket()");
    if (connect(socket_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
        handle_error("connect()");
    chat_func(socket_fd, false);
    exit(EXIT_SUCCESS);
}
