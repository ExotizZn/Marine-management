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
    TYPE_NAVIRE types_autorises[] = {NAVIRE_PASSAGERS, NAVIRE_MARCHANDISE, PETROLIER};
    Port * port1 = createNewPort(1, "Toulon", 20);
    Quai * quai1 = createNewDock(1, 30, 50, types_autorises, 3);

    addDock(port1, quai1);
    showAllDockedShips(port1->docks);

	initialiseGfx(argc, argv);
	prepareFenetreGraphique("Marine Management", LargeurFenetre, HauteurFenetre);
	lanceBoucleEvenements();
	return 0;
}

void gestionEvenement(EvenementGfx evenement) {
	switch (evenement) {
        case Initialisation:
            demandeTemporisation(0);
            break;
        case Temporisation:
            rafraichisFenetre();
            break;
        case Affichage:
            effaceFenetre(0, 152, 182);
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