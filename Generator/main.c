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
    char option = 'n';
    do{
        scanf("%c", &(option));
        while(getchar() != '\n');
        switch (option) {
            case 's':
                m->active = 0;
                break;

            default:
                break;
        }
    } while(option != 's');
}

int main() {
    Message *m = newMessage();
    int option = 0;
    do {
        printf("\n**************MENU****************\n");
        printf("*                                *\n");
        printf("* 1) Manual control              *\n");
        printf("* 2) Automatic control           *\n");
        printf("* 3) Finish                      *\n");
        printf("*                                *\n");
        printf("**********************************\n");
        printf("*                                *\n");
        printf("* --> Type your option: ");
        scanf("%d", &(option));
        while(getchar() != '\n');
        switch (option) {
            case 1:
                manualControl(m);
                break;
            case 2:
                automaticControl(m);
                subMenu(m);
                break;
            case 3:
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