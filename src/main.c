#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../GfxLib/GfxLib.h"

#include "../include/navire.h"
#include "../include/quai.h"
#include "../include/port.h"
#include "../include/utils.h"
#include "../include/lettre.h"

#define LargeurFenetre 1366
#define HauteurFenetre 768

int main(int argc, char **argv) {
	initialiseGfx(argc, argv);
	prepareFenetreGraphique("Marine Management", LargeurFenetre, HauteurFenetre);
	lanceBoucleEvenements();
	return 0;
}

void gestionEvenement(EvenementGfx evenement) {
    static TYPE_NAVIRE types_autorises[] = {NAVIRE_PASSAGERS, NAVIRE_MARCHANDISE, PETROLIER};
    static Port * port1 = NULL;
    static Quai * quai1 = NULL;
    static bool isMouillageOpen = false;

	switch (evenement) {
        case Initialisation:
            port1 = createNewPort(1, "Toulon", 20);
            quai1 = createNewDock(1, 30, 50, types_autorises, 3);
            addShipToWaitingZone(port1, initializeShip(1, NAVIRE_PASSAGERS, 200));
            addShipToWaitingZone(port1, initializeShip(2, NAVIRE_MARCHANDISE, 200));
            addShipToWaitingZone(port1, initializeShip(3, PETROLIER, 200));
            addShipToWaitingZone(port1, initializeShip(4, YATCH, 200));
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

            for(int i=0; i<3; i++){
                rectangle(500+(i*300),hauteurFenetre()-60,510+(i*300),hauteurFenetre()-350);
                rectangle(400+(i*300),hauteurFenetre()-340,610+(i*300),hauteurFenetre()-350);
                rectangle(400+(i*300),hauteurFenetre()-240,610+(i*300),hauteurFenetre()-250);
                rectangle(400+(i*300),hauteurFenetre()-140,610+(i*300),hauteurFenetre()-150);
            }

            for(int i=0; i<3; i++){
                rectangle(500+(i*300),60,510+(i*300),350);
                rectangle(400+(i*300),340,610+(i*300),350);
                rectangle(400+(i*300),240,610+(i*300),250);
                rectangle(400+(i*300),140,610+(i*300),150);
            }

            couleurCourante(255,0,0);
            dessineTexte("ABCDEFGHIJKLMNOPQRSTUVWXYZ",100,100,1);

            afficherZoneMouillage(port1);

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