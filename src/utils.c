#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "../GfxLib/GfxLib.h"
#include "../GfxLib/BmpLib.h"
#include "../include/utils.h"

void cercle(float centreX, float centreY, float rayon) {
	const int Pas = 20;
	const double PasAngulaire = 2.*M_PI/Pas;
	
	for (int i = 0; i < Pas; ++i) {
		const double angle = 2.*M_PI*i/Pas;
		triangle(centreX, centreY,
				 centreX+rayon*cos(angle), centreY+rayon*sin(angle),
				 centreX+rayon*cos(angle+PasAngulaire), centreY+rayon*sin(angle+PasAngulaire));
	}
}

void quartCercle(float centreX, float centreY, float rayon, int orientation) {
	const int Pas = 20;
	const double PasAngulaire = 2.*M_PI/Pas;
	
	for (int i = 0; i < Pas/4; ++i) {
		const double angle = 2.*M_PI*(i+orientation)/Pas;
		triangle(centreX, centreY,
				 centreX+rayon*cos(angle), centreY+rayon*sin(angle),
				 centreX+rayon*cos(angle+PasAngulaire), centreY+rayon*sin(angle+PasAngulaire));
	}
}

void roundRect(int x, int y, int w, int h, int radius) {
	rectangle(x, y+radius, x+w, y+h-radius);
	rectangle(x+radius, y, x+w-radius, y+h);
	quartCercle(x+w-radius-1, y+h-radius-1, radius, 0);
	quartCercle(x+1+radius, y+h-radius-1, radius, 5);
	quartCercle(x+radius+1, y+radius+1, radius, 10);
	quartCercle(x+w-radius-1, y+radius+1, radius, 15);
}     