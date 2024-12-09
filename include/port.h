#ifndef PORT_H
#define PORT_H
#include <stdbool.h>
#include "navire.h"
#include "quai.h"

typedef struct Port {
    int id;
    char * name;
    Quai * docks;
    int max_ships_waiting_zone;
    Navire * waiting_zone;
    Navire *selected_ship;
} Port;

Port * createNewPort(int id, char * name, int max_waiting_zone);
void addDock(Port * port, Quai * dock);
void addShipToWaitingZone(Port * port, Navire* ship);
void afficherZoneMouillage(Port * port);
Quai * getDockById(Port * port, int id);
void verifierClicSurBateau(Port *port, int px, int py);
void afficherInfosBateau(Port *port);
bool isPointInTriangle(float px, float py, float x1, float y1, float x2, float y2, float x3, float y3);
const char* obtenirNomTypeNavire(int type);


#endif