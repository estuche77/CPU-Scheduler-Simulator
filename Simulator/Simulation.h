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
    int ended;
} Simulation;

Simulation *newSimulation(enum pAlgorithm algorithm);

#endif //SIMULATOR_SIMULATION_H
