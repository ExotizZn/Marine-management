#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/navire.h"
#include "../include/port.h"
#include "../GfxLib/GfxLib.h"

Port * createNewPort(int id, char * name, int max_waiting_zone) {
    Port * new = malloc(sizeof(Port));
    if(!new) return NULL;

    new->id = id;
    new->name = strdup(name);
    new->docks = NULL;
    new->max_ships_waiting_zone = max_waiting_zone;
    new->waiting_zone = NULL;

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

    if(port->waiting_zone == NULL) {
        ship->status = EN_ATTENTE;
        ship->next = NULL;
        port->waiting_zone = ship;
    } else {
        Navire * temp = port->waiting_zone;
        while(temp->next) {
            temp = temp->next;
        }
        ship->status = EN_ATTENTE;
        ship->next = NULL;
        temp->next = ship;
    }
}

void afficherZoneMouillage(Port * port) {
    int row = 0;
    int column = 0;

    Navire * current = port->waiting_zone;

    while(current) {
        switch(current->type) {
            case NAVIRE_PASSAGERS : 
                couleurCourante(255, 0, 0);
                break;
            case NAVIRE_MARCHANDISE :
                couleurCourante(0, 255, 0);
                break;
            case PETROLIER :
                couleurCourante(0, 255, 255);
                break;
            case YATCH :
                couleurCourante(255, 255, 0);
                break;
        }

        triangle(20+(column*30), 20+(row*30), 30+(column*30), 40+(row*30), 40+(column*30), 20+(row*30));
        if(column == 7) {
            row++;
            column = 0;
        } else {
            column++;
        }

        current = current->next;
    }
}