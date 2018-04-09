//
// Created by shake on 07/04/18.
//

#ifndef GENERATOR_FILECONTROL_H
#define GENERATOR_FILECONTROL_H

#include <bits/types/FILE.h>

#define LOWERCREATE 3
#define HIGHCREATE 8

#define LOWERBURST 3
#define HIGHBURST 8
#define LOWERPRIORITY 5
#define HIGHPRIORITY 1
#define PORT 8080
#define HOST "127.0.0.1"

typedef struct message{
    int lowerCreate;
    int highCreate;
    int lowerBurst;
    int highBurst;
    int active;
    int port;
    char * host;
}Message;

Message *newMessage();
void  manualMessage(Message *m, char *di);


void automaticControl(Message *m);
void manualControl(Message *m);
void *automaticalMessage(void *m);
void sendMEssage(char * str, Message *m);
char* generateMessage();
#endif //GENERATOR_FILECONTROL_H
