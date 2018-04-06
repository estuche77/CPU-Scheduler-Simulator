#include <sys/socket.h>
#include <arpa/inet.h>
#include <printf.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "Socket.h"
#include "Utils.h"
#include "Simulation.h"
#include "PBC.h"

Socket* newSocket(Simulation *simulation, int id){
    Socket *new_socket =(Socket*) malloc(sizeof(Socket));
    new_socket->socketID = id;
    new_socket->simulation = simulation;
    return new_socket;
}

int configureSocket(unsigned short port) {

    int sock = 0;
    int opt = 1;

    struct sockaddr_in server_addr;

    // Obtain a socketID descriptor by setting up the connection
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Socket creation error\n");
        return -1;
    }

    // Forcefully attaching socketID to the port 8080
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        perror("Setsockopt failed");
        return -1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    // Forcefully attaching socketID to the port 8080
    if (bind(sock, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0)
    {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    return sock;
}

void *startListening(void *v) {
    Socket *server_socket = (Socket *)v;

    struct sockaddr server_address;
    int addressLength = sizeof(server_address);

    // Forever
    while (1) {
        if (listen(server_socket->socketID, 3) < 0)
        {
            perror("listen");
            exit(EXIT_FAILURE);
        }

        // New struct with socketID id and process queue
        Socket *new_socket = newSocket(server_socket->simulation,0);
        new_socket->socketID = accept(server_socket->socketID, &server_address, (socklen_t*)&addressLength);
        // Keeps waiting for an incoming connection
        if (new_socket->socketID < 0)
        {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        threadComunication(new_socket);
    }

}

void threadComunication(Socket *new_socket){
    pthread_t communication;
    int result;

    // A communication thread is created
    result = pthread_create(&communication, NULL, startCommunication, (void *)new_socket);

    if (result) {
        printf("ERROR; return code from pthread_create() is %d\n", result);
        exit(-1);
    }
}

void *startCommunication(void *v) {
    Socket *socket = (Socket *)v;

    // The data is fetched
    char buffer[40] = {0};
    read(socket->socketID, buffer, 40);
    printf("%s\n", buffer);

    // Here the data should be analyzed and inserted
    int pid=insertNewPCB(buffer,socket->simulation);
    // And pid is converted to string
    char *str_pid = intToString(pid);

    // After inserting the new process, the assigned pid is sent
    send(socket->socketID, str_pid, sizeof(str_pid), 0);
    printf("Assigned PID: %s\n", str_pid);

    // Close the socketID and exits the thread
    close(socket->socketID);
    pthread_exit(NULL);
}

int insertNewPCB(char *message,Simulation *simulation){

    int values[2];
    char *token=strtok(message,DIVIDER);
    for(int i=0;token!=NULL;i++){
        values[i]=atoi(token);
        token = strtok(NULL, DIVIDER);
    }
    return addPCBToQueue(simulation->processQueue,
                         values[0],values[1],simulation->clockTimes);
}