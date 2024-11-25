#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../GfxLib/GfxLib.h"

#include "../include/navire.h"
#include "../include/quai.h"
#include "../include/port.h"
#include "../include/utils.h"

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
	switch (evenement) {
        case Initialisation:
            port1 = createNewPort(1, "Toulon", 20);
            quai1 = createNewDock(1, 30, 50, types_autorises, 3);
            demandeTemporisation(0);
            break;
        case Temporisation:
            rafraichisFenetre();
            break;
        case Affichage:
            effaceFenetre(0, 152, 182);

            couleurCourante(0, 0, 255);
            roundRect(10, 10, 300, 300, 5);

            couleurCourante(128, 128, 128);
            rectangle(0, hauteurFenetre(), largeurFenetre(), hauteurFenetre()-60);
            rectangle(largeurFenetre(), 0, largeurFenetre()-60, hauteurFenetre());
            roundRect(350, 0, largeurFenetre(), 60, 5);

            couleurCourante(255, 255, 255);

            for(int i = 0; i < 4; i++) {
                roundRect(20+(i*40), 20, 30, 30, 2);
            }

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