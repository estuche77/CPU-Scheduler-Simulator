//
// Created by estuche on 03/04/18.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "JobScheduler.h"

void JobScheduling(Simulation *simulation, unsigned short port) {

    // A server socketID is created
    int sock = configureSocket(port);

    if (sock <= 0) {
        printf("Error creating server socketID: %d\n", sock);
        exit(-1);
    }

    // New struct with socketID id and process queue
    Socket *server_socket = newSocket(simulation,sock);
    activateListen(server_socket);
}

void activateListen(Socket *server_socket){
    pthread_t listeningThread;
    int result;

    // Thread used for listen incoming connections
    result = pthread_create(&listeningThread, NULL, startListening, (void *)server_socket);

    if (result) {
        printf("ERROR; return code from pthread_create() is %d\n", result);
        exit(-1);
    }
    else{
        closing_menu(server_socket->simulation);
    }

    // THIS LINE SHOULD BE ERASED LATER!!!
    pthread_join(listeningThread, NULL);
}



