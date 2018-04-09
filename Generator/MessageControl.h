//
// Created by shake on 07/04/18.
//

#ifndef GENERATOR_FILECONTROL_H
#define GENERATOR_FILECONTROL_H

#include "Process.h"

#define LOWERCREATE 3
#define HIGHCREATE 8

#define LOWERBURST 3
#define HIGHBURST 8
#define LOWERPRIORITY 5
#define HIGHPRIORITY 1
#define PORT 8080
#define HOST "127.0.0.1"

enum generationType {AUTOMATIC, MANUAL};

typedef struct Message{
    int lowerPriority;
    int highPriority;
    int lowerCreate;
    int highCreate;
    int lowerBurst;
    int highBurst;
    int active;
    unsigned short port;
    char *host;
    char *directory;
} Message;

Message *newMessage();

// Main function where Message Control starts to work
void startMessageControl(Message * m, enum generationType type);

// Used as a thread for Manual process of the Generation
void *manualControl(void *v);

// Used as as thread for Automatic process Generation
void *automaticControl(void *v);

// To send over a socket connection
void sendMessage(char *str, Message *m);

// Generate a random process
Process *generateRandomProcess(Message *m);

#endif //GENERATOR_FILECONTROL_H
