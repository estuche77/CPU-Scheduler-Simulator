//
// Created by estuche on 03/04/18.
//

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "PQueue.h"
#include "Simulation.h"
#include "JobScheduler.h"
#define PORT 8080

Simulation *newSimulation(enum pAlgorithm algorithm) {
    Simulation *s = (Simulation*) malloc(sizeof(Simulation));

    s->processQueue = newQueue();
    s->algorithm = algorithm;
    s->clockTimes = 0;
    s->idleTime = 0;
    s->burstTime = 1;
    s->quantum = 0;
    s->ended = 0;
    s->log = 0;
    s->port=PORT;
    return s;
}

void activatedLog(Simulation *simulation)
{
    simulation->log = !simulation->log;
}

void increaseIdleTime(Simulation *simulation)
{
    simulation->idleTime++;
}

void increaseClockTimes(Simulation *simulation)
{
    simulation->clockTimes++;
}

void types_of_Algorithms(Simulation *simulation)
{
    int option = 0;
    do {
        printf("\n************Algorithms************\n");
        printf("*                                *\n");
        printf("* 1) FIFO                        *\n");
        printf("* 2) SJF                         *\n");
        printf("* 3) HPF                         *\n");
        printf("* 4) RR                          *\n");
        printf("*                                *\n");
        printf("**********************************\n");
        printf("*                                *\n");
        printf("* --> Type your option: ");
        scanf("%d", &(option));
        while(getchar() != '\n');
        switch (option) {
            case 1:
                simulation->algorithm = FIFO;
                return;
            case 2:
                simulation->algorithm = SJF;
                return;
            case 3:
                simulation->algorithm = HPF;
                return;
            case 4:
                simulation->algorithm = RR;
                int q = 0;
                printf("* --> Type quantum value: ");
                scanf("%d", &(q));
                while(getchar() != '\n');
                simulation->quantum = q;
                return;
            default:
                printf("*           Invalid option       *\n");
                break;
        }
    } while(1);

}

void generate_summary(Simulation *simulation) {
    printf("*-------> Generating summary <-------\n");

    int executed_Processes = 0;
    float TAT_Average = 0;
    float WT_Average = 0;
    Node *temp = simulation->processQueue->first;
    while(temp != NULL){
        if(isProcessEnded(temp->pcb)){

            executed_Processes++;

            calculate_TAT(temp->pcb);
            calculate_WT(temp->pcb);

            TAT_Average += temp->pcb->tat;
            WT_Average += temp->pcb->wt;

            printFinalPCB(temp->pcb);
        }
        temp = temp->next;
    }
    if(executed_Processes){
        TAT_Average = TAT_Average/executed_Processes;
        WT_Average = WT_Average/executed_Processes;
    }

    printf("\n* 1) Number of processes executed: %d\n", executed_Processes);
    printf("* 2) Idle CPU Time:                  %d\n", simulation->idleTime);
    printf("* 3) Average Turn Around Time:       %f\n", TAT_Average);
    printf("* 4) Average Waiting Time:           %f\n", WT_Average);
}

void simulationMenu(Simulation *simulation) {
    int option = 0;
    do {
        printf("\n************ SUB MENU ************\n");
        printf("*                                *\n");
        printf("* 1) See log                     *\n");
        printf("* 2) Print ready process         *\n");
        printf("* 3) Finish simulation           *\n");
        printf("*                                *\n");
        printf("**********************************\n");
        printf("*                                *\n");
        printf("*--> Type your option: ");
        scanf("%d", &(option));
        while(getchar() != '\n');
        switch (option) {
            case 1:
                printf("* Press any key to stop the log... \n");
                activatedLog(simulation); // Activate log
                getchar();
                activatedLog(simulation); // Disable log
                break;
            case 2:
                print_Queued_Processes(simulation->processQueue);
                break;
            case 3:
                simulation->ended = 1;
                break;

            default:
                printf("\n*-------> Invalid option <-------*\n");
                break;
        }
    } while(!simulation->ended);

    generate_summary(simulation);
}