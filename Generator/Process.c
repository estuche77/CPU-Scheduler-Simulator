//
// Created by estuche on 01/04/18.
//

#include <wchar.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Process.h"
#include "Utils.h"

Process *newProcess(int burst, int priority) {
    Process *p = malloc(sizeof(Process));

    p->burst = burst;
    p->priority = priority;

    return p;
}

char *toString(Process *process) {
    // String initialized in 38 bytes since
    // "BURST: " & "PRIORITY: " are 18 bytes plus
    // maximum integer value are 10 digits each
    char *string = malloc(40);

    strcat(string, "BURST:");
    strcat(string, intToString(process->burst));
    strcat(string, "\n");
    strcat(string, "PRIORITY:");
    strcat(string, intToString(process->priority));

    return string;
}