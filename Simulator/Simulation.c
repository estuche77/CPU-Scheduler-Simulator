//
// Created by estuche on 03/04/18.
//

#include <stdlib.h>
#include "Simulation.h"

Simulation *newSimulation(enum pAlgorithm algorithm) {
    Simulation *s = malloc(sizeof(Simulation));

    s->processQueue = newQueue();
    s->algorithm = algorithm;
    s->ended = 0;
    s->log = 0;

    return s;
}
