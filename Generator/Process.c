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
    // String initialized in 37 bytes since
    // "BURST:" & "PRIORITY:" are 15 bytes
    // plus 1 new line plus the maximum integer
    // value are 10 digits each
    char *string = malloc(37);

    strcat(string, "BURST:");
    strcat(string, intToString(process->burst));
    strcat(string, "\n");
    strcat(string, "PRIORITY:");
    strcat(string, intToString(process->priority));

    return string;
}