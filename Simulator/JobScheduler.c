//
// Created by estuche on 03/04/18.
//

#include <stdlib.h>
#include "JobScheduler.h"
#include "Socket.h"

void JobScheduling(Simulation *simulation, unsigned short port) {

    // A server socket is created
    int sock = configureSocket(port);

    if (sock <= 0) {
        printf("Error creating server socket: %d\n", sock);
        exit(-1);
    }

    // New struct with socket id and process queue
    Socket *server_socket = malloc(sizeof(Socket));
    server_socket->socket = sock;
    server_socket->queue = simulation->processQueue;

    pthread_t listeningThread;
    int result;

    // Thread used for listen incoming connections
    result = pthread_create(&listeningThread, NULL, startListening, (void *)server_socket);

    if (result) {
        printf("ERROR; return code from pthread_create() is %d\n", result);
        exit(-1);
    }

    // THIS LINE SHOULD BE ERASED LATER!!! Escuchó Jake???
    pthread_join(listeningThread, NULL);

}