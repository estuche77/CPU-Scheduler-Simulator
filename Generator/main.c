#include <stdio.h>
#include <stdlib.h>
#include "Process.h"

int main() {

    Process *p = newProcess(10, 20);

    char *str = toString(p);

    printf(str);
    return 0;
}