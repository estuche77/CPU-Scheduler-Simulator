//
// Created by estuche on 02/04/18.
//

#ifndef SIMULATOR_PBC_H
#define SIMULATOR_PBC_H

#include <stdio.h>

enum pState {READY, ACTIVE, ENDED};

typedef struct PCB {
    int pid;
    int burst;
    int burstLeft;
    int priority;
    int arrival_time;
    int exit_time;
    enum pState state;
    int tat;
    int wt;
} PCB;

PCB *newPCB(int pid,int burst, int priority, int arrival_time);
void calculate_TAT(PCB *pcb);
void calculate_WT(PCB *pcb);
void printPCB(PCB *pcb);
void printFinalPCB(PCB *pcb);
int isProcessEnded(PCB *process);
int isProcessActived(PCB *process);
int isProcessReady(PCB *process);
int setState(PCB *process,enum pState state);

#endif //SIMULATOR_PBC_H
