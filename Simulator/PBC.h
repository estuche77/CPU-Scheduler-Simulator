//
// Created by estuche on 02/04/18.
//

#ifndef SIMULATOR_PBC_H
#define SIMULATOR_PBC_H

typedef struct PCB {
    int pid;
    int burst;
    int priority;
    enum pState state;
    int tat;
    int wt;
};

#endif //SIMULATOR_PBC_H
