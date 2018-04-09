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

typedef struct message{
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

void startMessageControl(Message * m, enum generationType type);
void *manualControl(void *v);
void *automaticControl(void *v);
void sendMessage(char *str, Message *m);
Process *generateRandomProcess(Message *m);

#endif //GENERATOR_FILECONTROL_H
