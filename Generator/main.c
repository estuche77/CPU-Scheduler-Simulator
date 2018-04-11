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

void setAddress(Message *m);
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
        while(getchar() != '\n');
        switch (option) {
            case 1:
                setAddress(m);
                break;
            case 2:
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
    } while(m->active);

    pthread_exit(NULL);
}

void setAddress(Message *m) {
    printf("* --> IP: ");
    fgets(m->host, 16, stdin);
    printf("* --> Port: ");
    scanf("%hu",&(m->port));
    while(getchar()!='\n');
}

void setDataMessages(Message *m) {
    printf("* --> Type the creation range:\n* --> Lower: ");
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
}