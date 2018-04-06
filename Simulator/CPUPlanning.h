//
// Created by root on 04/04/18.
//

#ifndef SIMULATOR_CPUPLANNING_H
#define SIMULATOR_CPUPLANNING_H

void setPCB_Burst(struct Node* process, int value);

/*________________FIFO____________________*/
struct Node* getLowerPID(struct Node* current,struct Node* lower);
struct Node* searchLowerPID(struct Queue *queue);
void FIFOAlgorithm(struct Queue *queue);

/*_________________SJF______________________*/
struct Node* searchLowerBurst(struct Queue *queue);
void SJFAlgorithm(struct Simulation *simulation);

/*_________________HPF______________________*/
struct Node* searchLowerPriority(struct Queue *queue);
void HPFAlgorithm(struct Simulation *simulation);

/*_________________RR________________________*/
//struct Node* searchLowerPriority(struct Queue *queue);
void RRAlgorithm(struct Simulation *simulation);

/*_________________Planning________________________*/
void applyAlgorithm(struct Simulation *simulation);
void planning(struct Simulation *simulation);
#endif //SIMULATOR_CPUPLANNING_H
