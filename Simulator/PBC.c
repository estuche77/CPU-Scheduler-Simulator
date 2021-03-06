//
// Created by estuche on 02/04/18.
//

#include "PBC.h"
#include <stdlib.h>
#include <stdio.h>

PCB *newPCB(int pid,int burst, int priority,
            int arrival_time){

    PCB *pcb = (PCB*)malloc(sizeof(PCB));

    pcb->pid = pid;
    pcb->state = READY;
    pcb->burst = burst;
    pcb->burstLeft = burst;
    pcb->priority = priority;
    pcb->arrival_time = arrival_time;
    pcb->exit_time = 0;
    pcb->tat = 0;
    pcb->wt = 0;

    return pcb;
}

int isProcessEnded(PCB *process){
    return process->state == ENDED;
}

int isProcessActive(PCB *process){
    return process->state == ACTIVE;
}

int isProcessReady(PCB *process){
    return process->state == READY;
}

int setState(PCB *process, enum pState state){
    process->state = state;
}

int setExitTime(PCB *process,int time){
    if(isProcessEnded(process)){
        process->exit_time = time;
    }
}

void calculate_TAT(PCB *pcb){
    pcb->tat = pcb->exit_time - pcb->arrival_time;
}

void calculate_WT(PCB *pcb){
    pcb->wt = pcb->tat - pcb->burst;
}

void printPCB(PCB *pcb){
    printf("\n* --> PID: %d | Initial Burst: %d | Actual burst: %d | Priority: %d | Arrival time: %d\n",
           pcb->pid,pcb->burst,pcb->burstLeft, pcb->priority, pcb->arrival_time);
}

void printFinalPCB(PCB *pcb){
    printf("* PID: %d | TAT: %d | WT: %d | Exit_time %d\n",
           pcb->pid,pcb->tat, pcb->wt,pcb->exit_time);
}