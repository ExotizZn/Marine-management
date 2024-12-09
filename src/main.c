#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "../GfxLib/GfxLib.h"

#include "../include/navire.h"
#include "../include/quai.h"
#include "../include/port.h"
#include "../include/utils.h"

#define LargeurFenetre 1366
#define HauteurFenetre 768

int main(int argc, char **argv) {
    srand(time(NULL));
	initialiseGfx(argc, argv);
	prepareFenetreGraphique("Marine Management", LargeurFenetre, HauteurFenetre);
	lanceBoucleEvenements();
	return 0;
}

void gestionEvenement(EvenementGfx evenement) {
    static Port * port1 = NULL;

	switch (evenement) {
        case Initialisation:
            port1 = createNewPort(1, "Toulon", 20);
            addDock(port1, createNewDock(1, 30, 50, 0, 46));
            addDock(port1, createNewDock(2, 30, 50, 1, 46));
            addDock(port1, createNewDock(3, 30, 50, 2, 46));
            addDock(port1, createNewDock(4, 30, 50, 3, 46));  
            addDock(port1, createNewDock(5, 30, 50, 0, 46));
            addDock(port1, createNewDock(6, 30, 50, 1, 46));

            demandeTemporisation(100);
            break;
        case Temporisation:
            int random_type = rand()%4;
            
            Navire * current_ship = port1->waiting_zone;

            Quai * dock = port1->docks;

            while (dock) {
                int randType = rand()%4;
                dockingAShip(dock, initializeShip(1, randType, 1000));
                dock = dock->next;
            }

            rafraichisFenetre();
            break;
        case Affichage:
            effaceFenetre(0, 173, 181);

            couleurCourante(63, 114, 175);
            roundRect(10, 10, 250, 250, 5);

            couleurCourante(34, 40, 49);
            rectangle(0, hauteurFenetre(), largeurFenetre(), hauteurFenetre()-60);
            rectangle(largeurFenetre(), 0, largeurFenetre()-60, hauteurFenetre());
            roundRect(350, 0, largeurFenetre(), 60, 5);

            afficheQuai(getDockById(port1, 1), 500, 65);
            afficheQuai(getDockById(port1, 2), 800, 65);
            afficheQuai(getDockById(port1, 3), 1100, 65);

            afficheQuai(getDockById(port1, 4), 500, 425);
            afficheQuai(getDockById(port1, 5), 800, 425);
            afficheQuai(getDockById(port1, 6), 1100, 425);

            afficherZoneMouillage(port1);
            afficherInfosBateau(port1);

            break;
        case Clavier:
        	switch (caractereClavier()) {
				case 'Q':
				case 'q':
					termineBoucleEvenements();
					break;
                case 'S':
                case 's':
                    savePortState(port1, "port_state.data");
                    break;
                case 'R':
                case 'r':
                    free(port1->docks);
                    free(port1->waiting_zone);
                    free(port1->selected_ship);
                    port1->docks = NULL;
                    port1->waiting_zone = NULL;
                    port1->selected_ship = NULL;
                    break;
                case 'L':
                case 'l':
                    free(port1->docks);
                    free(port1->waiting_zone);
                    free(port1);
                    port1 = NULL;
                    port1 = loadPortState("port_state.data");
                    break;
                case 'D':
                case 'd':
                    break;
			}
            break;
        case ClavierSpecial:
            break;
        case BoutonSouris:
            switch (etatBoutonSouris()){
				case GaucheAppuye:
                    int px = abscisseSouris();
                    int py = ordonneeSouris();
                    verifierClicSurBateau(port1, px, py);
                    break;
            }
            break;
        case Souris:
            break;
        case Inactivite:
            break;
        case Redimensionnement:
            break;
    }
}