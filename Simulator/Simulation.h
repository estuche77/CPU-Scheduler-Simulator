//
// Created by estuche on 03/04/18.
//

#ifndef SIMULATOR_SIMULATION_H
#define SIMULATOR_SIMULATION_H

#include "PQueue.h"
enum pAlgorithm {FIFO, SJF, HPF, RR};

typedef struct Simulation {
    Queue *processQueue;
    enum pAlgorithm algorithm;
    int log;
    int clockTimes;
    int idleTime;
    unsigned int burstTime;
    int quantum;
    int ended;
} Simulation;

Simulation *newSimulation(enum pAlgorithm algorithm);
void activatedLog(Simulation *simulation);
void types_of_Algorithms(Simulation *simulation);
void simulationMenu(Simulation *simulation);
void increaseIdleTime(Simulation *simulation);
void increaseClockTimes(Simulation *simulation);
void printSummary(Simulation *simulation);
void generate_summary(Simulation *simulation);
int isPaused(Simulation *simulation);
void setPuase(Simulation *simulation);
#endif //SIMULATOR_SIMULATION_H
