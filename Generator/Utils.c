//
// Created by estuche on 03/04/18.
//

#include <stdlib.h>
#include <stdio.h>
#include "Utils.h"

double randomDouble() {
    return (double)rand() / (double)RAND_MAX;
}

int randIntBetween(int a, int b) {
    b = b + 1;
    return (int)((randomDouble() * (b - a)) + a);
}

char *intToString(int value)
{
    char str[10] = {10};
    sprintf(str, "%d", value);
    char *strValor = str;

    return strValor;
}
