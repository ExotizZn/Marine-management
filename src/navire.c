#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../include/navire.h"

Navire * initializeShip(int id, int ship_type, float capacity) {
    Navire * new = malloc(sizeof(Navire));

    if (!new) return NULL;

    new->id = id;
    new->ship_type = ship_type;
    new->status = EN_ATTENTE;
    new->capacity = capacity;
    new->next = NULL;
    new->prev = NULL;

    return new;
}

Navire * createNewShip(AllExistingShips * allShips, int id, int ship_type, float capacity) {
    if(ship_type < 0 || ship_type > 3) {
        return NULL;
    }

    if(allShips->number_of_ships == 0 && allShips->list == NULL) {
        Navire * new = initializeShip(id, ship_type, capacity);

        if(!new) return NULL;

        allShips->number_of_ships ++;
        allShips->list = new;

        return new;
    } else {
        Navire * current = allShips->list;

        if(current->id == id) return NULL;

        while(current->next) {
            if (current->next->id == id) {
                return NULL;  // Navire déjà existant
            }
            current = current->next;
        }
            
        Navire * new = initializeShip(id, ship_type, capacity);

        if(!new) return NULL;

        allShips->number_of_ships ++;
        current->next = new;

        return new;
    }
}

void showAllExistingShips(AllExistingShips * list) {
    Navire * current = list->list;
    while(current) {
        printf("Id : %d | Type : %d | Status : %d | Capacity : %.2f\n", current->id, current->ship_type, current->status, current->capacity);
        current = current->next;
    }
}