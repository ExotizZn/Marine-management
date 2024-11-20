#ifndef QUAI_H
#define QUAI_H

#include "./navire.h"

typedef struct Quai {
    int dock_number;        // Numéro de quai
    int dock_size;          // Taille du quai
    float dock_depth;       // Profondeur
    int authorized_ships;   // Type de navires autorisés
    int max_ships;          // Nombre maximum de navires pouvant être accostés
    Navire * list;          // Liste chaînée des navires en attente d'accostage
} Quai;

#endif