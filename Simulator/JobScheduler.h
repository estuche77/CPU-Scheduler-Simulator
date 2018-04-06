//
// Created by estuche on 03/04/18.
//

#ifndef SIMULATOR_JOBSCHEDULER_H
#define SIMULATOR_JOBSCHEDULER_H

#include "Simulation.h"
#include "Socket.h"

void JobScheduling(Simulation *simulation, unsigned short port);
void activateListen(struct Socket *server_socket);

#endif //SIMULATOR_JOBSCHEDULER_H
