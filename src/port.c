#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "../include/utils.h"
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
    new->selected_ship = NULL;

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
}

void afficherInfosBateau(Port *port) {
    if (!port || !port->selected_ship) {
        return; 
    }

    float rect_x = 10;  
    float rect_y = 400;  
    float rect_width = 250; 
    float rect_height = 150; 
    int corner_radius = 10;  

    
    couleurCourante(255, 255, 255); 
    roundRect(rect_x, rect_y, rect_width, rect_height, corner_radius);

    
    couleurCourante(255, 255, 255); 
    epaisseurDeTrait(2);      
    roundRect(rect_x, rect_y, rect_width, rect_height, corner_radius);

    couleurCourante(0, 0, 0); 
    char buffer[128];


    sprintf(buffer, "Informations du bateau :");
    afficheChaine(buffer, 16, rect_x + 15, rect_y + rect_height - 25);

    sprintf(buffer, "ID : %d", port->selected_ship->id);
    afficheChaine(buffer, 14, rect_x + 15, rect_y + rect_height - 50);

    sprintf(buffer, "Type : %s", obtenirNomTypeNavire(port->selected_ship->type));
    afficheChaine(buffer, 14, rect_x + 15, rect_y + rect_height - 75);

    sprintf(buffer, "Capacité : %.2f", port->selected_ship->capacity);
    afficheChaine(buffer, 14, rect_x + 15, rect_y + rect_height - 100);

    sprintf(buffer, "Statut : %d", port->selected_ship->status);
    afficheChaine(buffer, 14, rect_x + 15, rect_y + rect_height - 125);
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

void savePortState(Port *port, const char *filename) {
    if (!port || !filename)
        return;

    FILE *file = fopen(filename, "wb");
    if (!file)
    {
        perror("Erreur d'ouverture du fichier pour sauvegarde");
        return;
    }

    fprintf(file, "%d %s %d\n", port->id, port->name, port->max_ships_waiting_zone);

    Quai *current_dock = port->docks;
    while (current_dock)
    {
        fprintf(file, "Q\n%d %d %f %d\n",
                current_dock->dock_number,
                current_dock->dock_size,
                current_dock->dock_depth,
                current_dock->max_ships);
        fwrite(current_dock->authorized_ships, sizeof(TYPE_NAVIRE), 4, file);      
        Navire *current = current_dock->docked;
        while (current)
        {
            fprintf(file, "N\n%d %d %d %f\n",
                    current->id,
                    current->type,
                    current->status,
                    current->capacity);
            current = current->next;
        }
        current_dock = current_dock->next;
    }

    Navire *current_ship = port->waiting_zone;
    while (current_ship)
    {
        fprintf(file, "M\n%d %d %f\n",
                current_ship->id,
                current_ship->type,
                current_ship->capacity);
        current_ship = current_ship->next;
    }

    fclose(file);
}

Port *loadPortState(const char *filename) {
    if (!filename)
        return NULL;

    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Erreur d'ouverture du fichier");
        return NULL;
    }

    char name_buffer[128];
    int id, max;
    if (fscanf(file, "%d %s %d", &id, name_buffer, &max) != 3) {
        fclose(file);
        fprintf(stderr, "Erreur : format incorrect en tête du fichier\n");
        return NULL;
    }

    Port *port = createNewPort(id, name_buffer, max);
    if (!port) {
        fclose(file);
        fprintf(stderr, "Erreur : allocation mémoire échouée pour le port\n");
        return NULL;
    }

    char type;
    int dock_number;
    while (fscanf(file, " %c", &type) != EOF){
        if (type == 'Q') {
            int dock_size, max_ships;
            float dock_depth;
            if (fscanf(file, "%d %d %f %d", &dock_number, &dock_size, &dock_depth, &max_ships) != 4){
                fprintf(stderr, "Erreur : format incorrect pour les quais\n");
                fclose(file);
                return NULL;
            }
            TYPE_NAVIRE types_autorises[] = { NAVIRE_PASSAGERS, NAVIRE_MARCHANDISE, PETROLIER, YATCH };
            Quai *dock = createNewDock(dock_number, dock_size, dock_depth, types_autorises, max_ships);
            addDock(port, dock);
        } else if (type == 'N'){
            int ship_id, ship_type, ship_status;
            float ship_capacity;
            if (fscanf(file, "%d %d %d %f", &ship_id, &ship_type, &ship_status, &ship_capacity) != 4){
                fprintf(stderr, "Erreur : format incorrect pour les navires\n");
                fclose(file);
                return NULL;
            }
            dockingAShip(getDockById(port, dock_number), initializeShip(ship_id, ship_type, ship_capacity));
        } else if (type == 'M') {
            int ship_id, ship_type;
            float ship_capacity;
            if (fscanf(file, "%d %d %f", &ship_id, &ship_type, &ship_capacity) != 3) {
                fprintf(stderr, "Erreur : format incorrect pour la zone de mouillage\n");
                fclose(file);
                return NULL;
            }
            Navire *ship = initializeShip(ship_id, ship_type, ship_capacity);
            addShipToWaitingZone(port, ship);
        }
    }

    fclose(file);
    return port;
}