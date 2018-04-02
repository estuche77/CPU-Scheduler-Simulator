#include <stdio.h>
#include <stdlib.h>
#include "PBC.h"
#include "PQueue.h"

int main() {

    Queue *queue = newQueue();

    addToQueue(queue, 10, 20);
    addToQueue(queue, 10, 20);
    addToQueue(queue, 10, 20);
    addToQueue(queue, 10, 20);
    addToQueue(queue, 10, 20);

    printQueue(queue);

    return 0;
}