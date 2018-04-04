//
// Created by estuche on 03/04/18.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Utils.h"

char *intToString(int value)
{
    char str[10] = {10};
    sprintf(str, "%d", value);
    char *strValor = malloc(10);
    strcpy(strValor, str);

    return strValor;
}
