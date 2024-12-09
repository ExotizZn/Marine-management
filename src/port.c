#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
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
    if(!port || !dock) return;

    if(port->docks == NULL) {
        port->docks = dock;
        return;
    }

    Quai * temp = port->docks;
    while(temp->next){
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

Quai * getDockById(Port * port, int id) {
    if(!port) return NULL;

    Quai * current = port->docks;

    while(current && current->dock_number != id) {
        current = current->next;
    }

    if(!current) return NULL;

    return current;
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

void verifierClicSurBateau(Port *port, int px, int py) {
    if (!port) {
        printf("Erreur : port invalide.\n");
        return;
    }

    // Vérifier les bateaux dans la zone de mouillage
    int row = 0, column = 0;
    Navire *currentNavire = port->waiting_zone;

    while (currentNavire) {
        // Coordonnées du triangle pour ce bateau
        float x1 = 20 + (column * 30);
        float y1 = 20 + (row * 30);
        float x2 = x1 + 10;
        float y2 = y1 + 20;
        float x3 = x1 + 20;
        float y3 = y1;

        if (isPointInTriangle(px, py, x1, y1, x2, y2, x3, y3)) {
            printf("Bateau sélectionné dans la zone de mouillage : ID=%d\n", currentNavire->id);
            port->selected_ship = currentNavire; // Met à jour le bateau sélectionné
            return;
        }

        if (column == 7) {
            row++;
            column = 0;
        } else {
            column++;
        }

        currentNavire = currentNavire->next;
    }

    // Vérifier les bateaux dans les quais
    Quai *currentQuai = port->docks;
    while (currentQuai) {
        row = 0; column = 0;
        currentNavire = currentQuai->docked;

        while (currentNavire) {
            // Coordonnées du triangle pour ce bateau
            float x1 = 200 + (column * 30); // Exemple : Décalage pour les quais
            float y1 = 400 - (row * 30);
            float x2 = x1 + 10;
            float y2 = y1 + 20;
            float x3 = x1 + 20;
            float y3 = y1;

            if (isPointInTriangle(px, py, x1, y1, x2, y2, x3, y3)) {
                printf("Bateau sélectionné dans le quai : ID=%d\n", currentNavire->id);
                port->selected_ship = currentNavire; // Met à jour le bateau sélectionné
                return;
            }

            if (column == 7) {
                row++;
                column = 0;
            } else {
                column++;
            }

            currentNavire = currentNavire->next;
        }

        currentQuai = currentQuai->next;
    }

    // Si aucun bateau n'est trouvé, désélectionne
    port->selected_ship = NULL;
    printf("Aucun bateau trouvé aux coordonnées (%d, %d).\n", px, py);
}

void afficherInfosBateau(Port *port) {
    if (!port || !port->selected_ship) {
        return; // Pas de bateau sélectionné, ne rien afficher
    }

    // Coordonnées et dimensions du rectangle
    float rect_x = 20;   // Aligné avec la zone de mouillage
    float rect_y = 450;  // Positionné au-dessus de la zone de mouillage
    float rect_width = 300;
    float rect_height = 120;

    // Dessiner le rectangle (fond clair)
    couleurCourante(230, 230, 255); // Couleur de fond (bleu pâle)
    rectangle(rect_x, rect_y, rect_x + rect_width, rect_y + rect_height);

    // Dessiner le contour
    couleurCourante(255, 255, 255); // Couleur du contour (bleu foncé)
    epaisseurDeTrait(2);        // Épaissir le trait pour le contour
    rectangle(rect_x, rect_y, rect_x + rect_width, rect_y + rect_height);

    // Texte formaté
    couleurCourante(0, 0, 0); // Texte noir
    char buffer[128];

    // Titre
    sprintf(buffer, "Informations du bateau :");
    afficheChaine(buffer, 16, rect_x + 10, rect_y + rect_height - 20);

    // ID
    sprintf(buffer, "ID: %d", port->selected_ship->id);
    afficheChaine(buffer, 14, rect_x + 10, rect_y + rect_height - 40);

    // Type
    sprintf(buffer, "Type: %s", obtenirNomTypeNavire(port->selected_ship->type));
    afficheChaine(buffer, 14, rect_x + 10, rect_y + rect_height - 60);

    // Capacité
    sprintf(buffer, "Capacité: %2.f", port->selected_ship->capacity);
    afficheChaine(buffer, 14, rect_x + 10, rect_y + rect_height - 80);
}


bool isPointInTriangle(float px, float py, float x1, float y1, float x2, float y2, float x3, float y3) {
    float aireOrig = fabs((x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1));
    float aire1 = fabs((x1 - px) * (y2 - py) - (x2 - px) * (y1 - py));
    float aire2 = fabs((x2 - px) * (y3 - py) - (x3 - px) * (y2 - py));
    float aire3 = fabs((x3 - px) * (y1 - py) - (x1 - px) * (y3 - py));

    return fabs(aireOrig - (aire1 + aire2 + aire3)) < 0.01f;
}

const char* obtenirNomTypeNavire(int type) {
    switch (type) {
        case 0:
            return "Navire de passagers";
        case 1:
            return "Navire marchand";
        case 2:
            return "Petrolier";
        case 3:
            return "Yacht";
        default:
            return "Type inconnu";
    }
}