//
// Created by shake on 07/04/18.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <pthread.h>
#include <zconf.h>
#include "MessageControl.h"
#include "Utils.h"
#include "Process.h"
#include "Socket.h"

Message *newMessage() {
    Message *m = (Message*)malloc(sizeof(Message));

    m->lowerPriority = LOWER_PRIORITY;
    m->highPriority = HIGH_PRIORITY;
    m->lowerCreate = LOWER_CREATE;
    m->highCreate = HIGH_CREATE;
    m->lowerBurst = LOWER_BURST;
    m->highBurst = HIGH_BURST;
    m->active = 1;
    m->port = PORT;
    m->host = HOST;
    m->directory = "data.txt";
    return m;
}

// This functions decides which thread is going to be executed
void startMessageControl(Message * m, enum generationType type) {
    pthread_t messageControl;
    int result = 0;

    if (type == AUTOMATIC) {
        result = pthread_create(&messageControl, NULL, automaticControl, (void *)m);
    }
    else if (type == MANUAL) {
        result = pthread_create(&messageControl, NULL, manualControl, (void *)m);
    }

    if (result) {
        printf("Error creating message control thread; return code from pthread_create() is %d\n", result);
        exit(-1);
    }
}

void *manualControl(void *v) {
    Message *m = (Message *)v;

    // Opening file
    FILE *file;
    file = fopen(m->directory, "r");

    // If was not able to open it
    if (file == NULL) {
        printf("Error opening file: %s\n", m->directory);
        return NULL;
    }

    char line[20];
    unsigned int interval;

    // Until end of file or generation not active
    while (!feof(file) && m->active) {

        // Get the current line
        fgets(line, 20, file);

        // Prepares the string and sent it
        strcpy(line, strtok(line, "\n"));
        sendMessage(line, m);

        // Calculates a random interval to continue
        interval = (unsigned int) randIntBetween(m->lowerCreate, m->highCreate);
        printf("\nWaiting interval: %d\n", interval);

        // And waits
        sleep(interval);
    }

    // If the End Of File
    if (feof(file)) {
        printf("File read completed\n");
    }

    // Safety close the file
    fclose(file);

    pthread_exit(NULL);
}

void *automaticControl(void *v) {
    Message *m = (Message *)v;

    unsigned int interval;
    Process *process;

    while (m->active) {

        // Generate a random process
        process = generateRandomProcess(m);

        // Converts the process to string & sent it
        char *str = toString(process);
        sendMessage(str, m);

        // Calculates a random interval to continue
        interval = (unsigned int) randIntBetween(m->lowerCreate, m->highCreate);
        printf("\nWaiting interval: %d\n", interval);

        // And waits
        sleep(interval);
    }

    pthread_exit(NULL);
}

void sendMessage(char *str, Message *m) {
    // Creates a new connection and starts the communication
    int socket = connectSocket(m->host, m->port);
    startCommunication(socket, str);
}

Process *generateRandomProcess(Message *m) {
    // Random values
    int randomBurst = randIntBetween(m->lowerBurst, m->highBurst);
    int randomPriority = randIntBetween(m->highPriority, m->lowerPriority);
    // Process creation
    return newProcess(randomBurst, randomPriority);
}
