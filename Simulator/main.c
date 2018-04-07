#include <stdio.h>
#include <stdlib.h>
#include "Simulation.h"
#include "JobScheduler.h"

#define PORT 8080

enum pAlgorithm types_of_Algorithms();
void closing_menu(Simulation *simulation);

int main() {
    Simulation *simulation = newSimulation(FIFO);
    int option=0;
    do {
        printf("**************MENU****************\n");
        printf("*                                *\n");
        printf("*1) Configure port               *\n");
        printf("*2) Select algorithm             *\n");
        printf("*3) Start simulation             *\n");
        printf("*4) Finish simulation            *\n");
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
                closing_menu(simulation);
                break;
            case 4:
                printf("*        closing simulation      *\n");
                break;
            default:
                printf("*           Invalid option       *\n");
                break;
        }
    }while(option!=4);

    return 0;
}

enum pAlgorithm types_of_Algorithms()
{
    int option=0;
    do{
        printf("************Algorithms************\n");
        printf("*                                *\n");
        printf("*1) FIFO                         *\n");
        printf("*2) SJF                          *\n");
        printf("*3) HPF                          *\n");
        printf("*4) RR                           *\n");
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

void closing_menu(Simulation *simulation)
{
    int option=0;
    do{
        printf("************ SUB MENU ************\n");
        printf("*                                *\n");
        printf("*1) Print log                    *\n");
        printf("*2) Finish simulation            *\n");
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
                simulation->ended=1;
                break;

            default:
                printf("*           Invalid option       *\n");
                break;
        }
    }while(!simulation->ended);

}