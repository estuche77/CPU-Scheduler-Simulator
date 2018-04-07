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
    int quantum;
    int ended;
} Simulation;

Simulation *newSimulation(enum pAlgorithm algorithm);
enum pAlgorithm types_of_Algorithms();
void closing_menu(Simulation *simulation);
void increaseIdleTime(Simulation *simulation);
void increaseClockTimes(Simulation *simulation);
void printSummary(Simulation *simulation);
void generate_summary(Simulation *simulation);
#endif //SIMULATOR_SIMULATION_H
