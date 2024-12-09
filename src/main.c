#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../GfxLib/GfxLib.h"

#include "../include/navire.h"
#include "../include/quai.h"
#include "../include/port.h"
#include "../include/utils.h"
#include "../include/lettre.h"
#include "../include/textureLoader.h"

#define LargeurFenetre 1366
#define HauteurFenetre 768

int main(int argc, char **argv) {
	initialiseGfx(argc, argv);
	prepareFenetreGraphique("Marine Management", LargeurFenetre, HauteurFenetre);
	lanceBoucleEvenements();
	return 0;
}

void gestionEvenement(EvenementGfx evenement) {
    static TYPE_NAVIRE types_autorises[] = { NAVIRE_PASSAGERS, NAVIRE_MARCHANDISE, PETROLIER };
    static TYPE_NAVIRE types_autorises2[] = { NAVIRE_PASSAGERS, YATCH };
    static Port * port1 = NULL;

	switch (evenement) {
        case Initialisation:
            port1 = createNewPort(1, "Toulon", 20);
            addDock(port1, createNewDock(1, 30, 50, types_autorises, 42));
            addDock(port1, createNewDock(2, 30, 50, types_autorises2, 42));

            addShipToWaitingZone(port1, initializeShip(1, NAVIRE_PASSAGERS, 200));
            addShipToWaitingZone(port1, initializeShip(2, NAVIRE_MARCHANDISE, 200));
            addShipToWaitingZone(port1, initializeShip(3, PETROLIER, 200));
            addShipToWaitingZone(port1, initializeShip(4, YATCH, 200));

            dockingAShip(getDockById(port1, 1), initializeShip(5, NAVIRE_PASSAGERS, 200));
            dockingAShip(getDockById(port1, 1), initializeShip(6, PETROLIER, 200));
            dockingAShip(getDockById(port1, 1), initializeShip(7, NAVIRE_MARCHANDISE, 200));
            dockingAShip(getDockById(port1, 1), initializeShip(8, NAVIRE_PASSAGERS, 200));
            dockingAShip(getDockById(port1, 1), initializeShip(9, NAVIRE_PASSAGERS, 200));
            dockingAShip(getDockById(port1, 1), initializeShip(10, NAVIRE_PASSAGERS, 200));
            dockingAShip(getDockById(port1, 1), initializeShip(11, NAVIRE_MARCHANDISE, 200));

            dockingAShip(getDockById(port1, 2), initializeShip(14, YATCH, 200));
            dockingAShip(getDockById(port1, 2), initializeShip(15, NAVIRE_PASSAGERS, 200));
            dockingAShip(getDockById(port1, 2), initializeShip(16, YATCH, 200));
            dockingAShip(getDockById(port1, 2), initializeShip(17, NAVIRE_PASSAGERS, 200));
            dockingAShip(getDockById(port1, 2), initializeShip(14, YATCH, 200));
            dockingAShip(getDockById(port1, 2), initializeShip(15, NAVIRE_PASSAGERS, 200));
            dockingAShip(getDockById(port1, 2), initializeShip(16, YATCH, 200));

            demandeTemporisation(0);
            break;
        case Temporisation:
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
/*          afficheQuai(getDockById(port1, 3), 1100, 65);

            afficheQuai(getDockById(port1, 4), 500, 425);
            afficheQuai(getDockById(port1, 5), 800, 425);
            afficheQuai(getDockById(port1, 6), 1100, 425); */

            afficherZoneMouillage(port1);
            afficherInfosBateau(port1);

            break;
        case Clavier:
        	switch (caractereClavier()) {
				case 'Q':
				case 'q':
					termineBoucleEvenements();
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
                    printf("Clic détecté aux coordonnées : (%d, %d)\n", px, py);
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