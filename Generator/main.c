#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include "Process.h"
#include "Socket.h"

#define PORT 8080
#define HOST "127.0.0.1"

double randomDouble();

int main() {

    srand((unsigned int) time(NULL));


    for (int i = 0; i < 50; i++) {

        int randomBurst = (int)(randomDouble() * 20);
        int randomPriority = (int)(randomDouble() * 20);

        Process *process = newProcess(randomBurst, randomPriority);
        char *str = toString(process);

        int socket = configureSocket(HOST, PORT);
        startCommunication(socket, str);

    }

    return 0;
}

double randomDouble() {
    return (double)rand() / (double)RAND_MAX;
}