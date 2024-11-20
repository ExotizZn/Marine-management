#include <stdio.h>
#include <stdlib.h>

#include "../GfxLib/GfxLib.h"

#include "../include/navire.h"

#define LargeurFenetre 1366
#define HauteurFenetre 768

int main(int argc, char **argv) {
    AllExistingShips * list = malloc(sizeof(AllExistingShips));
    Navire * bateau1 = createNewShip(list, 1, 0, 10986.5657);
    Navire * bateau2 = createNewShip(list, 2, 1, 124765.5342);
    Navire * bateau3 = createNewShip(list, 3, 3, 1231233.7863);
    Navire * bateau4 = createNewShip(list, 4, 3, 2174632.6432);

    printf("Nombre de navires existant : %d\n", list->number_of_ships);
    showAllExistingShips(list);

	initialiseGfx(argc, argv);
	prepareFenetreGraphique("Marine Management", LargeurFenetre, HauteurFenetre);
	lanceBoucleEvenements();
	return 0;
}

void gestionEvenement(EvenementGfx evenement) {
	switch (evenement) {
        case Initialisation:
            break;
        case Temporisation:
            break;
        case Affichage:
            break;
        case Clavier:
            break;
        case ClavierSpecial:
            break;
        case BoutonSouris:
            break;
        case Souris:
            break;
        case Inactivite:
            break;
        case Redimensionnement:
            break;
    }
}