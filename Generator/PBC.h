//
// Created by estuche on 02/04/18.
//

#ifndef GENERATOR_PBC_H
#define GENERATOR_PBC_H

enum pState{Ready, Active, Ended};

typedef struct PCB {
    int pid;
    int burst;
    int priority;
    enum pState state;
    int tat;
    int wt;
};

#endif //GENERATOR_PBC_H
