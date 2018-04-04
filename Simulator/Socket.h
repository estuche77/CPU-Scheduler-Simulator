//
// Created by estuche on 02/04/18.
//

#ifndef SIMULATOR_SOCKET_H
#define SIMULATOR_SOCKET_H

#include "PQueue.h"

typedef struct Socket {
    int socket;
    Queue *queue;
} Socket;

int configureSocket(unsigned short port);
void *startListening(void *v);
void *startCommunication(void *v);

#endif //SIMULATOR_SOCKET_H
