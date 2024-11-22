#ifndef PORT_H
#define PORT_H

#include "navire.h"
#include "quai.h"

typedef struct ZoneDeMouillage {
    int max_ships;
    Navire * waiting;
} ZoneDeMouillage;

typedef struct Port {
    int id;
    char * name;
    Quai * docks;
    ZoneDeMouillage * waiting_zone;
} Port;

Port * createNewPort(int id, char * name, int max_waiting_zone);
void addDock(Port * port, Quai * dock);
void addShipToWaitingZone(Port * port, Navire* ship);

#endif