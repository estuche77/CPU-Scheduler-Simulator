#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "Simulation.h"
#include "JobScheduler.h"
#include "CpuScheduler.h"

int main() {

    Simulation *simulation = newSimulation(FIFO);

    int option = 0;

    do {
        printf("\n**************MENU****************\n");
        printf("*                                *\n");
        printf("* 1) Setup port                  *\n");
        printf("* 2) Select algorithm            *\n");
        printf("* 3) Start simulation            *\n");
        printf("* 4) Finish simulation           *\n");
        printf("*                                *\n");
        printf("**********************************\n");
        printf("*                                *\n");
        printf("* --> Type your option: ");
        scanf("%d", &(option));
        while(getchar() != '\n');
        switch (option) {
            case 1:
                printf("* --> Type an available port: ");
                scanf("%hu",&(simulation->port));
                while(getchar()!='\n');
                break;
            case 2:
                types_of_Algorithms(simulation);
                break;
            case 3:
                JobScheduling(simulation);
                CpuScheduling(simulation);
                simulationMenu(simulation);
                break;
            case 4:
                printf("\n*-----> Closing simulation <-----*\n");
                break;
            default:
                printf("\n*-------> Invalid option <-------*\n");
                break;
        }
    } while (option != 4);

    exit(0);
}

