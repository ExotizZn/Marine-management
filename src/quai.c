#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../include/quai.h"
#include "../include/navire.h"

Quai * createNewDock(int dock_number, int dock_size, float dock_depth, TYPE_NAVIRE * authorized_ships, int max_ships) {
    Quai * new = malloc(sizeof(Quai));

    if(!new){
        puts("Erreur lors de la création du quai.");
        return NULL;
    }

    new->dock_number = dock_number;
    new->dock_size = dock_size;
    new->dock_depth = dock_depth;
    memcpy(new->authorized_ships, authorized_ships, 4 * sizeof(TYPE_NAVIRE));
    new->max_ships = max_ships;
    new->docked = NULL;
    new->waiting = NULL;

    return new;
}

void addShip(Navire ** list, Navire * ship) {
    if (*list == NULL) {
        *list = ship;
    } else {
        Navire* temp = *list;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = ship;
    }
}

bool shipCompatibility(Quai * dock, Navire * ship) {
    for (int i = 0; i < 4; i++) {
        if (dock->authorized_ships[i] == ship->type) {
            return true;
        }
    }
    return false;
}

void dockingAShip(Quai * dock, Navire * ship) {
    if(!ship) return;

    if(!shipCompatibility(dock, ship)) {
        printf("Navire incompatible.\n");
        return;
    }

    int nb_docked = 0;
    Navire * current = dock->docked;
    while(current) {
        nb_docked++;
        current = current->next;
    }

    if(nb_docked < dock->max_ships) {
        ship->status = ACCOSTE;
        ship->next = NULL;
        addShip(&(dock->docked), ship);
    } else {
        ship->status = EN_ATTENTE;
        ship->next = NULL;
        addShip(&(dock->waiting), ship);
    }
}

void removeDockedShip(Quai * dock, int id) {
    Navire * current = dock->docked;

    if(current->id == id) {
        Navire * temp = current->next;
        current->status = EN_MER;
        dock->docked = current->next;
        temp->next = NULL;

        if(dock->waiting) {
            Navire * temp = dock->waiting;
            dock->waiting = dock->waiting->next;
            dockingAShip(dock, temp);
        }

        return;
    }

    while(current->next && current->next->id != id) {
        current = current->next;
    }

    if(current->next) {
        Navire * temp = current->next;
        current->next->status = EN_MER;
        current->next = current->next->next;
        temp->next = NULL;

        if(dock->waiting) {
            Navire * temp = dock->waiting;
            dock->waiting = dock->waiting->next;
            dockingAShip(dock, temp);
        }
    }
}

void showAllDockedShips(Quai * dock) {
    Navire * current = dock->docked;
    while(current) {
        printf("Id : %d | Type : %d | Status : %d | Capacity : %.2f\n", current->id, current->type, current->status, current->capacity);
        current = current->next;
    }
}

void showAllWaitingShips(Quai * dock) {
    Navire * current = dock->waiting;
    while(current) {
        printf("Id : %d | Type : %d | Status : %d | Capacity : %.2f\n", current->id, current->type, current->status, current->capacity);
        current = current->next;
    }
}