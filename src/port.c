#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/navire.h"
#include "../include/port.h"

Port * createNewPort(int id, char * name, int max_waiting_zone) {
    Port * new = malloc(sizeof(Port));
    ZoneDeMouillage * new_waiting_zone = malloc(sizeof(ZoneDeMouillage));
    if(!new) return NULL;

    new->id = id;
    new->name = strdup(name);
    new->docks = NULL;
    new_waiting_zone->max_ships = max_waiting_zone;
    new_waiting_zone->waiting = NULL;
    new->waiting_zone = new_waiting_zone;

    return new;
}

void addDock(Port * port, Quai * dock) {
    if(!dock || !port) return;

    if(port->docks == NULL) {
        port->docks = dock;
        return;
    }

    Quai * temp = port->docks;
    while(temp){
        temp = temp->next;
    }

    temp->next = dock;
}

void addShipToWaitingZone(Port * port, Navire* ship) {
    if(!port || !ship) return;

    if(port->waiting_zone->waiting == NULL) {
        ship->status = EN_ATTENTE;
        ship->next = NULL;
        port->waiting_zone->waiting = ship;
    } else {
        Navire * temp = port->waiting_zone->waiting;
        while(temp->next) {
            temp = temp->next;
        }

        ship->status = EN_ATTENTE;
        ship->next = NULL;
        temp->next = ship;
    }
}
