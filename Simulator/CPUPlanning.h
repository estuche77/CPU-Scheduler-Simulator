//
// Created by root on 04/04/18.
//

#ifndef SIMULATOR_CPUPLANNING_H
#define SIMULATOR_CPUPLANNING_H

#include "PQueue.h"
void setPCB_Burst(Node *process, int value);

/*________________FIFO____________________*/
Node* getLowerPID(Node *current,Node *lower);
Node* searchLowerPID(Queue *queue);
void FIFOAlgorithm(Queue *queue);

/*_________________SJF______________________*/
Node* searchLowerBurst(Queue *queue);
void SJFAlgorithm(struct Simulation *simulation);

/*_________________HPF______________________*/
Node* searchLowerPriority(Queue *queue);
void HPFAlgorithm(struct Simulation *simulation);

/*_________________RR________________________*/
//struct Node* searchLowerPriority(struct Queue *queue);
void RRAlgorithm(struct Simulation *simulation);

/*_________________Planning________________________*/
void applyAlgorithm(struct Simulation *simulation);
void planning(struct Simulation *simulation);
#endif //SIMULATOR_CPUPLANNING_H
