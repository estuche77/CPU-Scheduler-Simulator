//
// Created by estuche on 02/04/18.
//

#ifndef SIMULATOR_PQUEUE_H
#define SIMULATOR_PQUEUE_H

typedef struct Node {
    struct PCB *pcb;
    struct Node *next;
} Node;

typedef struct Queue {
    int counter;
    Node *first;
    Node *last;
    Node *current;
} Queue;

Queue *newQueue();
int addToQueue(Queue *queue, int burst, int priority, int time);
void print_Queued_Processes(Queue *queue);
int isQueueEmpty(Queue * queue);
void nextNode(Queue * queue);
#endif //SIMULATOR_PQUEUE_H
