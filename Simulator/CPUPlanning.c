//
// Created by root on 04/04/18.
//

#include "CPUPlanning.h"
#include "PQueue.h"
#include "Simulation.h"
#include <unistd.h>
#include "PBC.h"
#include "PQueue.h"

void setPCB_Burst(Node *process, int value){
    process->pcb->burstLeft-=value;
    if(process->pcb->burstLeft <=0){
        process->pcb->burstLeft=0;
        setState(process->pcb,ENDED);
    }
}

/*________________FIFO____________________*/

Node* getLowerPID(Node* current,Node* lower){
    if(current->pcb->pid < lower->pcb->pid){
        return current;
    }
    return lower;
}
Node* searchLowerPID(Queue *queue){
    Node *temp=queue->first;
    while(temp != NULL && !isProcessActived(temp->pcb)){
        temp=temp->next;
    }
    if(isProcessEnded(temp)){
        return NULL;
    }
    return temp;
}

void FIFOAlgorithm(Queue *queue){
    Node *lowerPID=searchLowerPID(queue);
    if(lowerPID==NULL){

    }
    setState(lowerPID->pcb,ACTIVE);
    setPCB_Burst(lowerPID, 1);

}

void executePlanning(Simulation *simulation){

    do{

        switch (simulation->algorithm){

            case FIFO:
                FIFOAlgorithm(simulation->processQueue);
                break;

            case SJF:
                break;

            case HPF:
                break;

            case RR:
                break;

            default:
                break;
        }
        sleep(1);
        simulation->clockTimes++;

    }while(simulation->ended);

}