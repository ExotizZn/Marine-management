#ifndef NAVIRE_H
#define NAVIRE_H

typedef enum {
    NAVIRE_PASSAGERS,       // 0 
    NAVIRE_MARCHANDISE,     // 1
    PETROLIER,              // 2
    YATCH                   // 3
} TYPE_NAVIRE;

typedef enum {
    EN_MER,                 // 0
    ACCOSTE,                // 1
    EN_ATTENTE              // 2
} ETAT;

typedef struct Navire Navire;
typedef struct Navire {
    int id;                 // Identifiant
    TYPE_NAVIRE type;       // Type de navire (navire de passagers, navire de marchandise, pétrolier et yacht)
    ETAT status;            // Etat (en mer, accosté, en attente)
    float capacity;         // Capacité de chargement (en tonnes)
    Navire * next;
} Navire;

Navire * initializeShip(int id, TYPE_NAVIRE type, float capacity);
void showShipInfo(Navire * ship);

#endif