#include <stdio.h>
#include <stdlib.h>
#include "Simulation.h"
#include "JobScheduler.h"

#define PORT 8080

int main() {

    Simulation *simulation = newSimulation(FIFO);

    JobScheduling(simulation, PORT);

    return 0;
}