//
// Created by estuche on 01/04/18.
//

#include <sys/socket.h>
#include <arpa/inet.h>
#include <printf.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include "Socket.h"

int createConnection(const char *serverAddress, unsigned short port) {

    int sock = 0;
    struct sockaddr_in server_addr;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Socket creation error\n");
        return -1;
    }

    memset(&server_addr, '0', sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, serverAddress, &server_addr.sin_addr) <= 0)
    {
        printf("Invalid address: Address not supported\n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        printf("Connection Failed\n");
        return -1;
    }

    return sock;
}

void startCommunication(const int socketDescriptor, const char *msg) {
    char buffer[1024] = {0};
    send(socketDescriptor, msg, strlen(msg), 0);
    read(socketDescriptor, buffer, 1024);
    printf("Assigned PID: ");
    printf("%s\n", buffer);
}
