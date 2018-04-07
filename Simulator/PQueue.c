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
    queue->first = queue->last = queue->current = NULL;
    return queue;
}

int addToQueue(Queue *queue, int burst, int priority) {

    Node *node = malloc(sizeof(Node));
    PCB *pcb = malloc(sizeof(PCB));

    pcb->pid = queue->counter++;
    pcb->burst = burst;
    pcb->priority = priority;
    pcb->state = READY;
    pcb->tat = 0;
    pcb->wt = 0;

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

int addPCBToQueue(Queue *queue, int burst, int priority,int time){
    Node *node = malloc(sizeof(Node));
    PCB *pcb = newPCB(0,burst,priority, time);
    pcb->pid = queue->counter++;

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

int isQueueEmpty(Queue * queue){
    return queue->first==NULL && queue->last==NULL;
}
void printQueue(Queue *queue) {
    Node *tmp = queue->first;

    while (tmp != NULL) {
        printf("%d - ", tmp->pcb->pid);
        tmp = tmp->next;
    }
    printf("\n");
}
