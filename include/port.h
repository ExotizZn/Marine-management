#ifndef PORT_H
#define PORT_H

#include "navire.h"
#include "quai.h"

typedef struct Port {
    int id;
    char * name;
    Quai * docks;
    int max_ships_waiting_zone;
    Navire * waiting_zone;
} Port;

Port * createNewPort(int id, char * name, int max_waiting_zone);
void addDock(Port * port, Quai * dock);
void addShipToWaitingZone(Port * port, Navire* ship);
void afficherZoneMouillage(Port * port);
Quai * getDockById(Port * port, int id);

#endif