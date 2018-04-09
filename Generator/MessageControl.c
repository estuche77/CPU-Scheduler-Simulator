//
// Created by shake on 07/04/18.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <pthread.h>
#include "MessageControl.h"
#include "Utils.h"
#include "Process.h"
#include "unistd.h"
#include "Socket.h"

Message *newMessage(){
    Message *m = (Message*)malloc(sizeof(Message));
    m->lowerCreate = LOWERCREATE;
    m->highCreate = HIGHCREATE;
    m->highBurst = HIGHBURST;
    m->lowerBurst = LOWERBURST;
    m->port = PORT;
    m->host = HOST;
    m->active = 1;
    return m;
}
void manualMessage(Message *m, char *dir){
    FILE *file;
    int interval;
    char line[20];
    file = fopen(dir, "r");

    if(file == NULL){
        puts("there is no file /home/.../Documentos/scheduler_Files/data.txt");
        return;
    }

    // Instruction used to initialize the random seed
    srand((unsigned int) time(NULL));

    for(int i = 0; !feof(file); i++){
        fgets(line, 20, file);
        if(i > 0){
            strcpy(line, strtok(line, "\n"));
            sendMessage(line, m);
            interval = randIntBetween(m->lowerCreate, m->highCreate);
            sleep(interval);
        }
    }

    fclose(file);
}

void manualControl(Message *m){
    char *dir="/home/shake/Documentos/scheduler_Files/data.txt";
    manualMessage(m, dir);
}

void setDataMessages(Message *m){
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
void automaticControl(Message *m){
    setDataMessages(m);
    pthread_t listeningThread;
    int result;

    // Thread used for listen incoming connections
    result = pthread_create(&listeningThread, NULL, automaticMessage, (void *) m);

    if (result) {
        printf("ERROR; return code from pthread_create() is %d\n", result);
        exit(-1);
    }
}

void *automaticMessage(void *m){
    Message *message=(Message*)m;
    int interval;
    // Instruction used to initialize the random seed
    srand((unsigned int) time(NULL));
    for(int i=0;i<5 && message->active;i++){
        char *str= generateMessage();
        sendMessage(str, message);
        interval= randIntBetween(message->lowerCreate, message->highCreate);
        sleep(interval);
    }
    pthread_exit(NULL);
}

void sendMessage(char *str, Message *m) {
    // Connection and communication
    int socket = connectSocket(m->host, m->port);
    startCommunication(socket, str);
}

char* generateMessage() {
    // Random values
    int randomBurst = randIntBetween(LOWERBURST, HIGHBURST);
    int randomPriority = randIntBetween(HIGHPRIORITY, LOWERPRIORITY);
    // Process creation
    Process *process = newProcess(randomBurst, randomPriority);
    char *str = toString(process);
    return str;
}

