//
// Created by estuche on 02/04/18.
//
#include <stdio.h>
#include <stdlib.h>
#include "PQueue.h"
#include "PBC.h"

Queue *newQueue() {
    Queue *queue =(Queue*) malloc(sizeof(Queue));
    queue->counter = 1;
    queue->first = queue->last = NULL;
    queue->current =queue->first;
    return queue;
}

int addToQueue(Queue *queue, int burst, int priority, int time){

    Node *node = malloc(sizeof(Node));

    PCB *pcb = newPCB(queue->counter++, burst, priority, time);

    node->pcb = pcb;

    if (queue->first == NULL && queue->last == NULL) {
        queue->first = queue->last = node;
    }
    else {
        queue->last->next = node;
        queue->last = node;
    }

    return node->pcb->pid;
}

int isQueueEmpty(Queue * queue) {
    return queue->first == NULL && queue->last == NULL;
}

void nextNode(Queue * queue) {
    if (queue->current == queue->last || queue->current == NULL) {
        queue->current = queue->first;
    }
    else {
        queue->current = queue->current->next;
    }

}
void print_Queued_Processes(Queue *queue) {
    printf("\n* ---------> Log <---------\n");
    Node *temp = queue->first;
    while (temp != NULL) {
        if (isProcessReady(temp->pcb)) {
            printPCB(temp->pcb);
        }
        temp = temp->next;
    }
}