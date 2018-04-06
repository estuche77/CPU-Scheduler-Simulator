//
// Created by estuche on 03/04/18.
//

#include <stdlib.h>
#include "Simulation.h"
#include <pthread.h>
#include "PQueue.h"

Simulation *newSimulation(enum pAlgorithm algorithm) {
    Simulation *s =(Simulation*) malloc(sizeof(Simulation));

    s->processQueue = newQueue();
    s->algorithm = algorithm;
    s->clockTimes=0;
    s->ended = 0;
    s->log = 0;

    return s;
}
