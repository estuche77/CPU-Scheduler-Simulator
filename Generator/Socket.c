//
// Created by estuche on 01/04/18.
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

Socket *newSocket(int socketID, const char *message) {
    Socket *s = malloc(sizeof(Socket));

    s->socketID = socketID;
    s->message = malloc(40);
    strcpy(s->message, message);

    return s;
}

int connectSocket(const char *serverAddress, unsigned short port) {

    int sock = 0;
    char zero = '0';

    struct sockaddr_in server_addr;

    // Obtain a socket descriptor by setting up the connection
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Socket creation error\n");
        return -1;
    }

    // I don't remember what this lines does
    memset(&server_addr, zero, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, serverAddress, &server_addr.sin_addr) <= 0)
    {
        printf("Invalid address: Address not supported\n");
        return -1;
    }

    // Connects to server host
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        printf("Connection Failed\n");
        return -1;
    }

    // Returns the socket descriptor connection in order to be used to communicate
    return sock;
}

void startCommunication(const int socketDescriptor, const char *msg) {

    // Creates this structure to be sent to the new thread
    Socket *socket = newSocket(socketDescriptor, msg);

    pthread_t pthread;
    int result = pthread_create(&pthread, NULL, runCommunication, (void *)socket);

    if (result) {
        printf("Thread creation failed with code %d\n", result);
        return;
    }
}

void *runCommunication(void* v) {
    Socket *socket = (Socket *) v;
    char buffer[1024] = {0};

    // Sends the process message
    printf("Sending process...\n");
    send(socket->socketID, socket->message, strlen(socket->message), 0);

    // Receive the PID and print it
    read(socket->socketID, buffer, 1024);
    printf("Assigned PID: ");
    printf("%s\n", buffer);

    // Close the socket and exits the thread
    close(socket->socketID);
    pthread_exit(NULL);
}
