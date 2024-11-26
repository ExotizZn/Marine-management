#include "../GfxLib/GfxLib.h"
#include <string.h>

// Dimensions des rectangles
#define RECT_WIDTH 20
#define RECT_HEIGHT 60



// Fonction pour dessiner une lettre ou un chiffre avec des rectangles
void dessineLettre(char lettre, float x, float y, float taille) {
    // Dimensions ajustées en fonction de la taille
    float largeur = RECT_WIDTH * taille;
    float hauteur = RECT_HEIGHT * taille;


    switch (lettre) {
        case 'A':
            // Barre gauche
            ligne(x, y, x , y + hauteur);
            // Barre droite
            ligne(x +largeur , y, x + largeur, y + hauteur);
            // Barre horizontale centrale
            ligne(x, y + hauteur / 2, x + largeur, y + hauteur / 2);
            // Barre horizontale supérieure
            ligne(x, y + hauteur, x + largeur, y + hauteur);
            break;

        case 'B':
            ligne(x, y, x, y + hauteur);
            ligne(x,y+hauteur,x+2*largeur/3,y+hauteur);
            ligne(x+2*largeur/3,y+hauteur,x+largeur,y+5*hauteur/6);
            ligne(x+largeur,y+5*hauteur/6,x+largeur,y+4*hauteur/6);
            ligne(x+largeur,y+4*hauteur/6,x+2*largeur/3,y+hauteur/2);
            ligne(x+2*largeur/3,y+hauteur/2,x+largeur,y+2*hauteur/6);
            ligne(x+largeur,y+2*hauteur/6,x+largeur,y+1*hauteur/6);
            ligne(x+largeur,y+1*hauteur/6,x+2*largeur/3,y);
            ligne(x+2*largeur/3,y,x,y);
            ligne(x+2*largeur/3,y+hauteur/2,x,y+hauteur/2);
            break;

        case 'C':
            // Barre gauche
            ligne(x, y, x, y + hauteur);
            // Barre supérieure
            ligne(x, y + hauteur, x + largeur, y + hauteur);
            // Barre inférieure
            ligne(x, y, x + largeur, y);
            break;

        case 'D':
            // Barre gauche
            ligne(x, y, x, y + hauteur);
            // Barre supérieure
            ligne(x, y + hauteur, x + largeur, y + hauteur);
            // Barre inférieure
            ligne(x, y, x + largeur, y);
            // Courbe droite (approximée par une ligne droite)
            ligne(x + largeur, y, x + largeur, y + hauteur);
            break;

        case 'E':
            // Barre gauche
            ligne(x, y, x, y + hauteur);
            // Barre supérieure
            ligne(x, y + hauteur, x + largeur, y + hauteur);
            // Barre centrale
            ligne(x, y + hauteur / 2, x + largeur, y + hauteur / 2);
            // Barre inférieure
            ligne(x, y, x + largeur, y);
            break;

        case 'F':
            // Barre gauche
            ligne(x, y, x, y + hauteur);
            // Barre supérieure
            ligne(x, y + hauteur, x + largeur, y + hauteur);
            // Barre centrale
            ligne(x, y + hauteur / 2, x + largeur, y + hauteur / 2);
            break;

        case 'G':
            // Barre gauche
            ligne(x, y, x, y + hauteur);
            // Barre supérieure
            ligne(x, y + hauteur, x + largeur, y + hauteur);
            // Barre inférieure
            ligne(x, y, x + largeur, y);
            // Barre intérieure droite
            ligne(x + largeur/2, y + hauteur / 2, x + largeur, y + hauteur / 2);
            // Barre droite
            ligne(x + largeur, y, x + largeur , y + hauteur/2);
            break;

        case 'H':
            // Barre gauche
            ligne(x, y, x, y + hauteur);
            // Barre droite
            ligne(x + largeur, y, x + largeur, y + hauteur);
            // Barre centrale
            ligne(x, y + hauteur / 2, x + largeur, y + hauteur / 2);
            break;

        case 'I':
            // Barre centrale
            ligne(x + largeur / 3, y, x + largeur / 3, y + hauteur);
            break;

        case 'J':
            // Barre verticale droite
            ligne(x + largeur * 2 / 3, y, x + largeur * 2 / 3, y + hauteur);
            // Barre inférieure
            ligne(x, y, x + largeur, y);
            break;

        case 'K':
            // Barre gauche
            ligne(x, y, x, y + hauteur);
            // Diagonale supérieure droite
            ligne(x, y + hauteur / 2, x + largeur, y + hauteur);
            // Diagonale inférieure droite
            ligne(x, y + hauteur / 2, x + largeur, y);
            break;

        case 'L':
            // Barre gauche
            ligne(x, y, x, y + hauteur);
            // Barre inférieure
            ligne(x, y, x + largeur, y);
            break;

        case 'M':
            // Barre gauche
            ligne(x, y, x, y + hauteur);
            // Barre droite
            ligne(x + largeur, y, x + largeur, y + hauteur);
            // Diagonale gauche
            ligne(x, y + hauteur, x + largeur / 2, y);
            // Diagonale droite
            ligne(x + largeur / 2, y, x + largeur, y + hauteur);
            break;

        case 'N':
        
            // Barre verticale gauche
            ligne(x, y, x, y + hauteur);
            // Diagonale
            ligne(x, y+ hauteur, x + largeur, y);
            // Barre verticale droite
            ligne(x + largeur, y, x + largeur, y + hauteur);
            break;

        case 'O':
            // Cercle approximé avec un rectangle
            ligne(x, y, x, y + hauteur);
            ligne(x, y + hauteur, x + largeur, y + hauteur);
            ligne(x + largeur, y + hauteur, x + largeur, y);
            ligne(x + largeur, y, x, y);
            break;

        case 'P':
            // Barre gauche
            ligne(x, y, x, y + hauteur);
            // Partie supérieure droite
            ligne(x, y + hauteur, x + largeur, y + hauteur);
            // Partie inférieure droite
            ligne(x + largeur, y + hauteur, x + largeur, y + hauteur / 2);

            ligne(x, y + hauteur /2 , x + largeur, y + hauteur/2 );
            break;

        case 'Q':
            // Rectangle plein pour le cercle
            ligne(x, y, x, y + hauteur);
            ligne(x, y + hauteur, x + largeur, y + hauteur);
            ligne(x + largeur, y + hauteur, x + largeur, y);
            ligne(x + largeur, y, x, y);
            // Queue de Q
            ligne(x + largeur / 2, y + hauteur / 2, x + largeur, y);
            break;

        case 'R':
            // Barre gauche
            ligne(x, y, x, y + hauteur);
            // Partie supérieure droite
            ligne(x, y + hauteur, x + largeur, y + hauteur);
            // Partie inférieure droite
            ligne(x + largeur, y + hauteur, x + largeur, y + hauteur /2);

            ligne(x, y + hauteur /2 , x + largeur, y + hauteur/2 );

            ligne(x+ largeur/3, y + hauteur /2, x + largeur, y);
            break;

        case 'S':
            // Barre horizontale supérieure
            ligne(x, y + hauteur, x + largeur, y + hauteur);
            // Barre horizontale centrale
            ligne(x, y + hauteur / 2, x + largeur, y + hauteur / 2);
            // Barre horizontale inférieure
            ligne(x, y, x + largeur, y);
            // Barre verticale gauche
            ligne(x, y + hauteur / 2, x, y + hauteur);
            // Barre verticale droite
            ligne(x + largeur, y, x + largeur, y + hauteur / 2);
            break;

        case 'T':
            // Barre verticale centrale
            ligne(x + largeur / 2, y, x + largeur / 2, y + hauteur);
            // Barre horizontale supérieure
            ligne(x, y + hauteur, x + largeur, y + hauteur);
            break;

        case 'U':
            // Barre gauche
            ligne(x, y, x, y + hauteur);
            // Barre droite
            ligne(x + largeur, y, x + largeur, y + hauteur);
            // Barre inférieure
            ligne(x, y, x + largeur, y);
            break;

        case 'V':
            // Diagonale gauche
            ligne(x, y + hauteur, x + largeur / 2, y);
            // Diagonale droite
            ligne(x + largeur / 2, y, x + largeur, y + hauteur);
            break;

        case 'W':
            // Barre gauche
            ligne(x, y, x, y + hauteur);
            // Barre droite
            ligne(x + largeur, y, x + largeur, y + hauteur);
            // Diagonale centrale gauche
            ligne(x, y, x + largeur / 2, y + hauteur / 2);
            // Diagonale centrale droite
            ligne(x + largeur / 2, y + hauteur / 2, x + largeur, y);
            break;

        case 'X':
            // Diagonale gauche
            ligne(x, y, x + largeur, y + hauteur);
            // Diagonale droite
            ligne(x, y + hauteur, x + largeur, y);
            break;

        case 'Y':
            // Diagonale gauche
            ligne(x, y + hauteur, x + largeur / 2, y + hauteur / 2);
            // Diagonale droite
            ligne(x + largeur / 2, y + hauteur / 2, x + largeur, y + hauteur);
            // Barre verticale inférieure
            ligne(x + largeur / 2, y, x + largeur / 2, y + hauteur / 2);
            break;

        case 'Z':
            // Barre horizontale supérieure
            ligne(x, y + hauteur, x + largeur, y + hauteur);
            // Diagonale
            ligne(x, y, x + largeur, y + hauteur);
            // Barre horizontale inférieure
            ligne(x, y, x + largeur, y);
            break;

        default:
            // Si un caractère n'est pas pris en charge, ne rien dessiner
            break;
    }
}


void dessineTexte(const char *texte, float x, float y, float taille) {
    for (size_t i = 0; i < strlen(texte); ++i) {
        dessineLettre(texte[i], x + i * (RECT_WIDTH + 10) * taille, y, taille);
    }
}


