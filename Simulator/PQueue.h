//
// Created by estuche on 02/04/18.
//

#ifndef SIMULATOR_PQUEUE_H
#define SIMULATOR_PQUEUE_H

#include "PBC.h"

typedef struct Node {
    PCB *pcb;
    struct Node *next;
} Node;

typedef struct Queue {
    int counter;
    Node *first;
    Node *last;
    Node *current;
} Queue;

Queue *newQueue();
int addToQueue(Queue *queue, int burst, int priority);
void printQueue(Queue *queue);

#endif //SIMULATOR_PQUEUE_H
