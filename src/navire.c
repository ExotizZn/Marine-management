#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../include/navire.h"

Navire * initializeShip(int id, TYPE_NAVIRE type, float capacity) {
    Navire * new = malloc(sizeof(Navire));

    if (!new) return NULL;

    new->id = id;
    new->type = type;
    new->status = EN_ATTENTE;
    new->capacity = capacity;
    new->next = NULL;

    return new;
}

void showShipInfo(Navire * ship) {
    if(!ship) return;
    printf("%d %d %d %.2f\n", ship->id, ship->type, ship->status, ship->capacity);
}