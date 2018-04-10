#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "Simulation.h"
#include "JobScheduler.h"
#include "CpuScheduler.h"

#define PORT 8080

int main() {

    Simulation *simulation = newSimulation(FIFO);

    int option = 0;

    do {
        printf("\n**************MENU****************\n");
        printf("*                                *\n");
        printf("* 1) Select algorithm            *\n");
        printf("* 2) Start simulation            *\n");
        printf("* 3) Finish simulation           *\n");
        printf("*                                *\n");
        printf("**********************************\n");
        printf("*                                *\n");
        printf("* --> Type your option: ");
        scanf("%d", &(option));
        while(getchar() != '\n');
        switch (option) {
            case 1:
                types_of_Algorithms(simulation);
                break;
            case 2:
                JobScheduling(simulation, PORT);
                CpuScheduling(simulation);
                simulationMenu(simulation);
                break;
            case 3:
                printf("\n*-----> closing simulation <-----*\n");
                break;
            default:
                printf("\n*-------> Invalid option <-------*\n");
                break;
        }
    } while(option != 3);

    exit(0);
}

