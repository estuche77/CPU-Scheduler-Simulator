#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "Process.h"
#include "Socket.h"

#define PORT 8080
#define HOST "127.0.0.1"

int main() {

    Process *p = newProcess(20, 12);

    char *str = toString(p);

    printf("%s\n", str);

    int socket = configureSocket(HOST, PORT);
    startCommunication(socket, "HOLA!!");

    return 0;
}