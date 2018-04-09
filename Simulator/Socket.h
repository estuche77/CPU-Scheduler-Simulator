//
// Created by estuche on 02/04/18.
//

#ifndef SIMULATOR_SOCKET_H
#define SIMULATOR_SOCKET_H
#define DIVIDER "\t"

#include "Simulation.h"
#include "PBC.h"
typedef struct Socket {
    int socketID;
    Simulation *simulation;
} Socket;

Socket* newSocket(Simulation *simulation, int id);

int configureSocket(unsigned short port);
void *startListening(void *v);
void *startCommunication(void *v);
void threadCommunication(Socket *new_socket);
int insertNewPCB(char *message,Simulation *simulation);
#endif //SIMULATOR_SOCKET_H
