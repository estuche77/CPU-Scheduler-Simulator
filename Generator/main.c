#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include "Process.h"
#include "Socket.h"
#include "Utils.h"
#include "MessageControl.h"
#include <unistd.h>
#include <pthread.h>

void subMenu(Message *m);

void subMenu(Message *m){
    char option='n';
    do{
        scanf("%c",&(option));
        while(getchar()!='\n');
        switch (option){
            case 's':
                m->active=0;
                break;
        }
    }while(option!='s');
}

int main() {
    Message *m=newMessage();
    int option=0;
    do {
        printf("\n**************MENU****************\n");
        printf("*                                *\n");
        printf("* 1) Configuration               *\n");
        printf("* 2) Manual control              *\n");
        printf("* 3) Automatic control           *\n");
        printf("* 4) Finish                      *\n");
        printf("*                                *\n");
        printf("**********************************\n");
        printf("*                                *\n");
        printf("* --> Type your option: ");
        scanf("%d",&(option));
        while(getchar()!='\n');
        switch (option){
            case 1:
                break;
            case 2:
                manualControl(m);
                break;
            case 3:
                automaticControl(m);
                subMenu(m);
                break;
            case 4:
                m->active=0;
                printf("\n*-----> closing simulation <-----*\n");
                break;
            default:
                printf("\n*-------> Invalid option <-------*\n");
                break;
        }
    }while(m->active);
    pthread_exit(NULL);

}