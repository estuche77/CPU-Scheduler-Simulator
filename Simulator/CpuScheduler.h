//
// Created by estuche on 03/04/18.
//

#ifndef SIMULATOR_CPUSCHEDULER_H
#define SIMULATOR_CPUSCHEDULER_H
#include "PQueue.h"
#include "Simulation.h"

Node* firstReadyProccess(Node *current);
/*_______________FIFO___________________*/
Node* getLowerPID(Node *current,Node *lower);
Node* searchLowerPID(Queue *queue);
/*_______________SJF___________________*/
Node* getLowerBurst(Node *current,Node *lower);
Node* searchLowerBurst(Queue *queue);
/*_______________HPF___________________*/
Node* getHighPriority(Node *current,Node *lower);
Node* searchHighPriority(Queue *queue);
/*_______________RR___________________*/
Node* searchNextProcessRR(Queue *queue);
/*_________________Planning________________________*/
void setPCB_Burst(Node *process, int value);
void process_To_Execute(Node *process);
void runProcess(Node *process,struct Simulation *simulation);
Node* contextSwitch(struct Simulation *simulation);
void executePlanning(void *s);
void CpuScheduling(Simulation *simulation);

#endif //SIMULATOR_CPUSCHEDULER_H
