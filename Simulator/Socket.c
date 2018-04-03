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

    pthread_t listeningThread;
    int result;

    // Thread used for listen incoming connections
    result = pthread_create(&listeningThread, NULL, startListening, (void *)&sock);

    if (result) {
        printf("ERROR; return code from pthread_create() is %d\n", result);
        exit(-1);
    }

    // THIS LINE SHOULD BE ERASED LATER!!! Escuchó Jake???
    pthread_join(listeningThread, NULL);

}

void *startListening(void *v) {
    int *sockPtr = (int *)v;
    int sock = *sockPtr;

    struct sockaddr server_addr;
    int addrLength = sizeof(server_addr);

    int newSocket;

    while (1) {
        if (listen(sock, 3) < 0)
        {
            perror("listen");
            exit(EXIT_FAILURE);
        }
        if ((newSocket = accept(sock, &server_addr, (socklen_t*)&addrLength)) < 0)
        {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        pthread_t communication;
        int result;

        result = pthread_create(&communication, NULL, startCommunication, (void *)&newSocket);

        if (result) {
            printf("ERROR; return code from pthread_create() is %d\n", result);
            exit(-1);
        }
    }
}

void *startCommunication(void *v) {
    int *sockPtr = (int *)v;
    int newSocket = *sockPtr;

    char buffer[40] = {0};
    read(newSocket, buffer, 40);
    printf("%s\n", buffer);
    send(newSocket, "1", sizeof(char), 0);
    printf("Message sent\n");
}