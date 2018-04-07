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
Node* firstReadyProccess(Node *current)
{
    Node *temp=current;
    while(temp != NULL ){
        if(isProcessReady(temp->pcb)){
            return temp;
        }
        temp=temp->next;
    }
    if(temp != NULL && isProcessEnded(temp->pcb)){
        return NULL;
    }
    return temp;
}
/*_______________FIFO___________________*/
Node* getLowerPID(Node *current, Node *lower)
{
    if(current->pcb->pid < lower->pcb->pid){
        return current;
    }
    return lower;
}
Node* searchLowerPID(Queue *queue)
{
    Node *temp=queue->first;
    while(temp != NULL && isProcessEnded(temp->pcb)){
        temp=temp->next;
    }
    return temp;
}
/*_______________SJF___________________*/
Node* getLowerBurst(Node *current,Node *lower)
{
    if(current->pcb->burstLeft == lower->pcb->burstLeft){
        return getLowerPID(current, lower);
    }
    else if(current->pcb->burstLeft < lower->pcb->burstLeft){
        return current;
    }
    return lower;
}
Node* searchLowerBurst(Queue *queue)
{
    Node *temp=firstReadyProccess(queue->first);
    Node *lower=temp;
    while(temp != NULL ){
        if(isProcessReady(temp->pcb)){
            lower=getLowerBurst(temp,lower);
        }
        temp=temp->next;
    }

    return lower;
}
/*_______________HPF___________________*/
Node* getHighPriority(Node *current,Node *lower)
{
    if(current->pcb->priority == lower->pcb->priority){
        return getLowerPID(current, lower);
    }
    else if(current->pcb->priority < lower->pcb->priority){
        return current;
    }
    return lower;
}
Node* searchHighPriority(Queue *queue)
{
    Node *temp=firstReadyProccess(queue->first);
    Node *lower=temp;
    while(temp != NULL ){
        if(isProcessReady(temp->pcb)){
            lower=getHighPriority(temp,lower);
        }
        temp=temp->next;
    }
    return lower;
}
/*_______________RR___________________*/
Node* searchNextProcessRR(Queue *queue)
{
    Node *temp;
    /*update the current node to the next ready process in
     * the queue, it can be the same input node*/
    queue->current=firstReadyProccess(queue->current);
    temp=queue->current;
    nextNode(queue);
    return temp;
}
/*_________________Planning________________________*/
void setPCB_Burst(Node *process, int value)
{
    process->pcb->burstLeft-=value;
    if(process->pcb->burstLeft <=0){
        process->pcb->burstLeft=0;
        setState(process->pcb,ENDED);
    }
}

void process_To_Execute(Node *process){
    printf("\n* Process To Execute: \n");
    printPCB(process->pcb);
}

void runProcess(Node *process,Simulation *simulation)
{
    // there are no ready processes
    if(process==NULL){

        increaseClockTimes(simulation);
        increaseIdleTime(simulation);
        sleep(1);

    } else{//there is an active process
        setState(process->pcb,ACTIVE);
        process_To_Execute(process);
        for(int i=1;!isProcessEnded(process->pcb);i++){
            increaseClockTimes(simulation);
            setPCB_Burst(process, 1);
            setExitTime(process->pcb,simulation->clockTimes);
            sleep(1);
            //if the simulation has quantum the process stops
            if(simulation->quantum && i == simulation->quantum){
                if(!isProcessEnded(process->pcb)){
                    setState(process->pcb,READY);
                }
                return;
            }
        }
    }
}
Node* contextSwitch(Simulation *simulation)
{
    Node *process=NULL;
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
            process=searchNextProcessRR(simulation->processQueue);
            break;

        default:
            break;
    }
    // cancels the process if it has finished
    if(process!=NULL && isProcessEnded(process->pcb))
        return NULL;
    return process;
}
void *executePlanning(void *s)
{
    Simulation *simulation=(Simulation*) s;
    Node *selectedProcess=NULL;
    do{
        selectedProcess=contextSwitch(simulation);
        runProcess(selectedProcess,simulation);

    }while(simulation->ended!=1);
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