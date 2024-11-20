#include <stdio.h>
#include <stdlib.h>

#include "../include/quai.h"


Quai * createQuai(int dock_number, int dock_size, float dock_depth, int authorized_ships, int max_ships) {
    Quai * new = malloc(sizeof(Quai));

    if(!new){
        puts("Erreur lors de la création du quai.");
        return NULL;
    }

    new->dock_number = dock_number;
    new->dock_size = dock_size;
    new->dock_depth = dock_depth;
    new->authorized_ships = authorized_ships;
    new->max_ships = max_ships;
    new->list = NULL;

    return new;
}
