#ifndef NAVIRE_H
#define NAVIRE_H

enum TYPE_NAVIRE {
    NAVIRE_PASSAGERS,       // 0 
    NAVIRE_MARCHANDISE,     // 1
    PETROLIER,              // 2
    YATCH                   // 3
};

enum ETAT {
    EN_MER,                 // 0
    ACCOSTE,                // 1
    EN_ATTENTE              // 2
};

typedef struct Navire Navire;
typedef struct Navire {
    int id;                 // Identifiant
    int ship_type;          // Type de navire (navire de passagers, navire de marchandise, pétrolier et yacht)
    int status;             // Etat (en mer, accosté, en attente)
    float capacity;         // Capacité de chargement (en tonnes)
    Navire * next;
    Navire * prev;
} Navire;

typedef struct AllExistingShips {
    int number_of_ships;
    Navire * list;
} AllExistingShips;

Navire * initializeShip(int id, int ship_type, float capacity);
Navire * createNewShip(AllExistingShips * allShips, int id, int ship_type, float capacity);
void showAllExistingShips(AllExistingShips * list);

#endif