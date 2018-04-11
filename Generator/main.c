#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include "Process.h"
#include "Socket.h"
#include "Utils.h"
#include "MessageControl.h"
#include <string.h>
void setAddress(Message *m);
void setFilePath(Message *m);
void setDataMessages(Message *m);

int main() {

    // Instruction used to initialize a
    // random seed to the entire program
    // Executed one time only
    srand((unsigned int) time(NULL));

    Message *m = newMessage();
    m->directory = "data.txt";

    int option = 0;
    do {
        printf("\n**************MENU****************\n");
        printf("*                                *\n");
        printf("* 1) Configure IP                *\n");
        printf("* 2) Manual control              *\n");
        printf("* 3) Automatic control           *\n");
        printf("* 4) Finish                      *\n");
        printf("*                                *\n");
        printf("**********************************\n");
        printf("*                                *\n");
        printf("* --> Type your option: ");
        scanf("%d", &(option));
        while (getchar() != '\n');
        switch (option) {
            case 1:
                setAddress(m);
                break;
            case 2:
                setFilePath(m);
                startMessageControl(m, MANUAL);
                break;
            case 3:
                setDataMessages(m);
                startMessageControl(m, AUTOMATIC);
                break;
            case 4:
                m->active = 0;
                printf("\n*-----> Closing simulation <-----*\n");
                break;
            default:
                printf("\n*-------> Invalid option <-------*\n");
                break;
        }
    } while (m->active);

    pthread_exit(NULL);
}

void setAddress(Message *m) {
    char* ip=(char*)malloc(16);
    printf("* --> IP: ");
    fgets(ip, 16, stdin);
    strcpy(ip, strtok(ip, "\n"));
    m->host=ip;
    printf("* --> Port: ");
    scanf("%hu",&(m->port));
    while(getchar()!='\n');
}

void setFilePath(Message *m) {
    int option = 0;
    char* p=(char*)malloc(64);
    do {
        printf("\n************Manual****************\n");
        printf("*                                *\n");
        printf("* 1) Set up file path            *\n");
        printf("* 2) Start simulation            *\n");
        printf("*                                *\n");
        printf("**********************************\n");
        printf("*                                *\n");
        printf("* --> Type your option: ");
        scanf("%d", &(option));
        while (getchar() != '\n');
        switch (option) {
            case 1:

                printf("* --> File path: ");
                fgets(p, 64, stdin);
                strcpy(p, strtok(p, "\n"));
                m->directory=p;
                break;
            case 2:
                break;
            default:
                printf("\n*-------> Invalid option <-------*\n");
                break;
        }
    } while (option != 2);
}

void setDataMessages(Message *m) {

    int option = 0;
    do {
        printf("\n***********Automatic**************\n");
        printf("*                                *\n");
        printf("* 1) Set up ranges               *\n");
        printf("* 2) Start simulation            *\n");
        printf("*                                *\n");
        printf("**********************************\n");
        printf("*                                *\n");
        printf("* --> Type your option: ");
        scanf("%d", &(option));
        while (getchar() != '\n');
        switch (option) {
            case 1:
                printf("* --> Type the process creation range:\n* --> Lower: ");
                scanf("%d",&( m->lowerCreate));
                while(getchar()!='\n');
                printf("* --> High: ");
                scanf("%d",&(m->highCreate));
                while(getchar()!='\n');

                printf("* --> Type the burst range: \n* --> Lower: ");
                scanf("%d",&(m->lowerBurst));
                while(getchar()!='\n');
                printf("* --> High: ");
                scanf("%d",&(m->highBurst));
                while(getchar()!='\n');

                printf("* --> Type the priority range: \n* --> Lower: ");
                scanf("%d",&(m->lowerPriority));
                while(getchar()!='\n');
                printf("* --> High: ");
                scanf("%d",&(m->highPriority));
                while(getchar()!='\n');
                break;
            case 2:
                break;
            default:
                printf("\n*-------> Invalid option <-------*\n");
                break;
        }
    } while (option != 2);

}