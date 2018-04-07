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
    Simulation *s =(Simulation*) malloc(sizeof(Simulation));

    s->processQueue = newQueue();
    s->algorithm = algorithm;
    s->clockTimes=0;
    s->idleTime=0;
    s->quantum=0;
    s->ended = 0;
    s->log = 0;
    return s;
}

void activetedLog(Simulation *simulation)
{
    simulation->log= !simulation->log;
}

void increaseIdleTime(Simulation *simulation)
{
    simulation->idleTime++;
}

void increaseClockTimes(Simulation *simulation)
{
    simulation->clockTimes++;
}

enum pAlgorithm types_of_Algorithms()
{
    int option=0;
    do{
        printf("\n************Algorithms************\n");
        printf("*                                *\n");
        printf("* 1) FIFO                        *\n");
        printf("* 2) SJF                         *\n");
        printf("* 3) HPF                         *\n");
        printf("* 4) RR                          *\n");
        printf("*                                *\n");
        printf("**********************************\n");
        printf("*                                *\n");
        printf("*--> Type your option: ");
        scanf("%d",&(option));
        while(getchar()!='\n');
        switch (option) {
            case 1:
                return FIFO;
            case 2:
                return SJF;
            case 3:
                return HPF;
            case 4:
                return RR;
            default:
                printf("*           Invalid option       *\n");
                break;
        }
    }while(1);

}

void printSummary(Simulation *simulation)
{

    int executed_Processes=0;
    int TAT_Average=0;
    int WT_Average=0;
    Node *temp=simulation->processQueue->first;
    while(temp!=NULL){
        if(isProcessEnded(temp->pcb)){

            executed_Processes++;

            calculate_TAT(temp->pcb);
            calculate_WT(temp->pcb);

            TAT_Average+=temp->pcb->tat;
            WT_Average+=temp->pcb->wt;

            printFinalPCB(temp->pcb);
        }
        temp=temp->next;
    }
    TAT_Average=TAT_Average/executed_Processes;
    WT_Average= WT_Average/executed_Processes;

    printf("\n* 1) Number of processes executed: %d\n",executed_Processes);
    printf("* 2) Seconds with idle CPU:        %d\n",simulation->idleTime);
    printf("* 3) Average Turn Around Time:     %d\n",TAT_Average);
    printf("* 4) Average Waiting Time:         %d\n",WT_Average);


}

void generate_summary(Simulation *simulation)
{
    printf("*-------> generating summary <-------\n");

    printSummary(simulation);
}

void closing_menu(Simulation *simulation)
{
    int option=0;
    do{
        printf("\n************ SUB MENU ************\n");
        printf("*                                *\n");
        printf("* 1) Print ready process         *\n");
        printf("* 2) Finish simulation           *\n");
        printf("*                                *\n");
        printf("**********************************\n");
        printf("*                                *\n");
        printf("*--> Type your option: ");
        scanf("%d",&(option));
        while(getchar()!='\n');
        switch (option){
            case 1:
                activetedLog(simulation);//active
                print_Queued_Processes(simulation->processQueue);
                activetedLog(simulation);//disable
                break;

            case 2:
                simulation->ended=1;
                break;

            default:
                printf("*           Invalid option       *\n");
                break;
        }
    }while(!simulation->ended);

    generate_summary(simulation);
}

