#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "Simulation.h"
#include "JobScheduler.h"
#include "CpuScheduler.h"

#define PORT 8080

int main() {
    Simulation *simulation = newSimulation(FIFO);
    int option=0;
    do {
        printf("\n**************MENU****************\n");
        printf("*                                *\n");
        printf("* 1) Configure port              *\n");
        printf("* 2) Select algorithm            *\n");
        printf("* 3) Start simulation            *\n");
        printf("* 4) Finish simulation           *\n");
        printf("*                                *\n");
        printf("**********************************\n");
        printf("*                                *\n");
        printf("*--> Type your option: ");
        scanf("%d",&(option));
        while(getchar()!='\n');
        switch (option){
            case 1:
                break;
            case 2:
                simulation->algorithm=types_of_Algorithms();
                break;
            case 3:
                JobScheduling(simulation, PORT);
                CpuScheduling(simulation);
                closing_menu(simulation);
                break;
            case 4:
                printf("\n*-----> closing simulation <-----*\n");
                break;
            default:
                printf("\n*-------> Invalid option <-------*\n");
                break;
        }
    }while(option!=4);
    pthread_exit(NULL);
}

