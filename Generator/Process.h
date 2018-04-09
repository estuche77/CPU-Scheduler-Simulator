//
// Created by estuche on 01/04/18.
//

#ifndef GENERATOR_PROCESS_H
#define GENERATOR_PROCESS_H
#define DIVIDER "\t"
typedef struct Process {
    int burst;
    int priority;
} Process;

Process *newProcess(int, int);
char *toString(Process*);

#endif //GENERATOR_PROCESS_H
