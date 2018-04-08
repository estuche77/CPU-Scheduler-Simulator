#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include "Process.h"
#include "Socket.h"
#include "Utils.h"
#include <unistd.h>

#define LOWERBURST 3
#define HIGHBURST 8
#define LOWERPRIORITY 5
#define HIGHPRIORITY 1
#define PORT 8080
#define HOST "127.0.0.1"

int main() {

    // Instruction used to initialize the random seed
    srand((unsigned int) time(NULL));

    // Randomly create 300 process and send it to server
    for (int i = 0; i < 5; i++) {

        // Random values
        int randomBurst = randIntBetween(LOWERBURST, HIGHBURST);
        int randomPriority = randIntBetween(HIGHPRIORITY, LOWERPRIORITY);

        // Process creation
        Process *process = newProcess(randomBurst, randomPriority);
        char *str = toString(process);

        // Connection and communication
        int socket = connectSocket(HOST, PORT);
        startCommunication(socket, str);
        sleep(1);
    }

    return 0;
}