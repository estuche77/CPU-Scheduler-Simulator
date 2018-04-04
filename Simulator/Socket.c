//
// Created by estuche on 02/04/18.
//

#include <sys/socket.h>
#include <arpa/inet.h>
#include <printf.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "Socket.h"
#include "Utils.h"

int configureSocket(unsigned short port) {

    int sock = 0;
    int opt = 1;

    struct sockaddr_in server_addr;

    // Obtain a socket descriptor by setting up the connection
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Socket creation error\n");
        return -1;
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        perror("Setsockopt failed");
        return -1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    // Forcefully attaching socket to the port 8080
    if (bind(sock, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0)
    {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    return sock;
}

void *startListening(void *v) {
    Socket *server_socket = (Socket *)v;

    struct sockaddr server_address;
    int addressLength = sizeof(server_address);

    while (1) {
        if (listen(server_socket->socket, 3) < 0)
        {
            perror("listen");
            exit(EXIT_FAILURE);
        }

        // New struct with socket id and process queue
        Socket *new_socket = malloc(sizeof(Socket));
        new_socket->socket = 0;
        new_socket->queue = server_socket->queue;

        // Keeps waiting for an incoming connection
        if ((new_socket->socket = accept(server_socket->socket, &server_address, (socklen_t*)&addressLength)) < 0)
        {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        pthread_t communication;
        int result;

        // A communication thread is created
        result = pthread_create(&communication, NULL, startCommunication, (void *)new_socket);

        if (result) {
            printf("ERROR; return code from pthread_create() is %d\n", result);
            exit(-1);
        }
    }
}

void *startCommunication(void *v) {
    Socket *socket = (Socket *)v;

    // The data is fetched
    char buffer[40] = {0};
    read(socket->socket, buffer, 40);
    printf("%s\n", buffer);

    // Here the data should be analyzed and inserted
    int pid = addToQueue(socket->queue, 10, 10);

    // And pid is converted to string
    char *str_pid = intToString(pid);

    printf("%d\n", pid);

    // After inserting the new process, the assigned pid is sent
    send(socket->socket, str_pid, sizeof(str_pid), 0);
    printf("Message sent\n");
}