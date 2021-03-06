//
// Created by estuche on 01/04/18.
//

#ifndef GENERATOR_SOCKET_H
#define GENERATOR_SOCKET_H

typedef struct Socket {
    int socketID;
    char *message;
} Socket;

// Constructor
Socket *newSocket(int socketID, const char *message);

// Configure socket by HOSTNAME and PORT and returns a connected socket
int connectSocket(const char *, unsigned short);

// Starts a new thread to send the message
void startCommunication(int, const char*);

// Function used for socket threading communication
void *runCommunication(void*);

#endif //GENERATOR_SOCKET_H
