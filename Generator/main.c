#include <stdio.h>
#include <stdlib.h>
#include "Process.h"

int main() {

    Process *p = newProcess(20, 12);

    char *str = toString(p);

    printf("%s", str);
    return 0;
}