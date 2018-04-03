#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include "Process.h"
#include "Socket.h"
#include "Utils.h"

#define PORT 8080
#define HOST "127.0.0.1"

int main() {

    // Instruction used to initialize the random seed
    srand((unsigned int) time(NULL));

    // Randomly create 300 process and send it to server
    for (int i = 0; i < 300; i++) {

        // Random values
        int randomBurst = randIntBetween(0, 100);
        int randomPriority = randIntBetween(1, 20);

        // Process creation
        Process *process = newProcess(randomBurst, randomPriority);
        char *str = toString(process);

        // Connection and communication
        int socket = configureSocket(HOST, PORT);
        startCommunication(socket, str);

    }

    return 0;
}