//
// Created by estuche on 03/04/18.
//
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "PQueue.h"
#include "Simulation.h"
#include "PBC.h"
#include "PQueue.h"

/*looks for the next process ready in
 *the queue, can be the same input node*/
Node* firstReadyProcess(Node *current) {
    Node *temp = current;
    while (temp != NULL ) {
        if(isProcessReady(temp->pcb)) {
            return temp;
        }
        temp = temp->next;
    }
    return temp;
}

/*_______________FIFO___________________*/
Node* getLowerPID(Node *current, Node *lower) {
    if(current->pcb->pid < lower->pcb->pid){
        return current;
    }
    return lower;
}

Node* searchLowerPID(Queue *queue) {
    Node *temp = queue->first;
    while(temp != NULL && isProcessEnded(temp->pcb)){
        temp = temp->next;
    }
    return temp;
}

/*_______________SJF___________________*/
Node* getLowerBurst(Node *current, Node *lower) {
    if(current->pcb->burstLeft == lower->pcb->burstLeft){
        return getLowerPID(current, lower);
    }
    else if(current->pcb->burstLeft < lower->pcb->burstLeft){
        return current;
    }
    return lower;
}

Node* searchLowerBurst(Queue *queue) {
    Node *temp = firstReadyProcess(queue->first);
    Node *lower = temp;
    while (temp != NULL ) {
        if (isProcessReady(temp->pcb)) {
            lower = getLowerBurst(temp, lower);
        }
        temp = temp->next;
    }

    return lower;
}

/*_______________HPF___________________*/
Node* getHighPriority(Node *current, Node *lower) {
    if(current->pcb->priority == lower->pcb->priority){
        return getLowerPID(current, lower);
    }
    else if(current->pcb->priority < lower->pcb->priority){
        return current;
    }
    return lower;
}

Node* searchHighPriority(Queue *queue) {
    Node *temp = firstReadyProcess(queue->first);
    Node *lower = temp;
    while (temp != NULL ) {
        if (isProcessReady(temp->pcb)) {
            lower = getHighPriority(temp, lower);
        }
        temp = temp->next;
    }
    return lower;
}

/*_______________RR___________________*/
Node* searchNextProcessRR(Queue *queue) {
    nextNode(queue);
    /* update the current node to the next ready process
     * in the queue, it can be the same input node */
    queue->current = firstReadyProcess(queue->current);
    return queue->current;
}

/*_________________Planning________________________*/
void setPCB_Burst(Node *process, int value) {
    process->pcb->burstLeft -= value;

    if(process->pcb->burstLeft <= 0) {
        process->pcb->burstLeft = 0;
        setState(process->pcb, ENDED);
    }
}

void printProcessInfo(int log, Node *process) {
    if (log) {
        printf("\n* Process To Execute: \n");
        printPCB(process->pcb);
    }
}

void runProcess(Node *process, Simulation *simulation) {

    // There is an active process
    if (process != NULL) {

        // Process info
        printProcessInfo(simulation->log, process);

        // Change process status to Active
        setState(process->pcb, ACTIVE);

        // For each burst in the process
        for (int i = 1; isProcessActive(process->pcb); i++) {

            // Increment the clock times
            increaseClockTimes(simulation);
            setPCB_Burst(process, 1);

            // Simulate the burst time
            sleep(simulation->burstTime);

            // If Round Robin and the quantum has been reached and the process is still active
            if (simulation->algorithm == RR && i == simulation->quantum && isProcessActive(process->pcb)) {
                setState(process->pcb, READY);
            }
        }

        // If the process has ended
        if (isProcessEnded(process->pcb)) {
            setExitTime(process->pcb, simulation->clockTimes);
        }
    }
    // There are no ready processes
    else {
        // Increment the clock time and idle time
        increaseClockTimes(simulation);
        increaseIdleTime(simulation);

        // Simulate the burst time
        sleep(simulation->burstTime);
    }
}

Node* contextSwitch(Simulation *simulation) {
    Node *process = NULL;
    switch (simulation->algorithm){

        case FIFO:
            process = searchLowerPID(simulation->processQueue);
            break;

        case SJF:
            process = searchLowerBurst(simulation->processQueue);
            break;

        case HPF:
            process = searchHighPriority(simulation->processQueue);
            break;

        case RR:
            process = searchNextProcessRR(simulation->processQueue);
            break;

        default:
            break;
    }
    // Cancels the process if it has finished
    if (process != NULL && isProcessEnded(process->pcb))
        return NULL;

    return process;
}

void *executePlanning(void *s)
{
    Simulation *simulation = (Simulation*) s;
    Node *selectedProcess = NULL;

    // Waits until the Job Scheduler add the first process
    while(isQueueEmpty(simulation->processQueue)) {
        sleep(1);
    }

    do {
        // The following process is selected
        selectedProcess = contextSwitch(simulation);

        // And simulated
        runProcess(selectedProcess, simulation);

    } while(simulation->ended != 1);

    pthread_exit(NULL);
}

void CpuScheduling(Simulation *simulation) {
    pthread_t schedulerThread;
    int result;

    // Thread used for listen incoming connections
    result = pthread_create(&schedulerThread, NULL, executePlanning, (void *)simulation);

    if (result) {
        printf("ERROR; return code from pthread_create() is %d\n", result);
        exit(-1);
    }
}