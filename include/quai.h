#ifndef QUAI_H
#define QUAI_H

#include "navire.h"

typedef struct Quai Quai;
typedef struct Quai {
    int dock_number;                   // Numéro de quai
    int dock_size;                     // Taille du quai
    float dock_depth;                  // Profondeur
    TYPE_NAVIRE authorized_ships[4];   // Type de navires autorisés
    int max_ships;                     // Nombre maximum de navires pouvant être accostés
    Navire * docked;
    Navire * waiting;                  // Liste chaînée des navires en attente d'accostage
    Quai * next;
} Quai;

Quai * createNewDock(int dock_number, int dock_size, float dock_depth, TYPE_NAVIRE * authorized_ships, int max_ships);
void dockingAShip(Quai * dock, Navire * ship);
void removeDockedShip(Quai * dock, int id);
void showAllDockedShips(Quai * dock);
void showAllWaitingShips(Quai * dock);

#endif