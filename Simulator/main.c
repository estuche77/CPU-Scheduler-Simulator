#include <stdio.h>
#include <stdlib.h>
#include "PBC.h"
#include "PQueue.h"
#include "Socket.h"

#define PORT 8080

int main() {

    Queue *queue = newQueue();

    addToQueue(queue, 10, 20);
    addToQueue(queue, 10, 20);
    addToQueue(queue, 10, 20);
    addToQueue(queue, 10, 20);
    addToQueue(queue, 10, 20);

    printQueue(queue);

    configureSocket(PORT);

    return 0;
}