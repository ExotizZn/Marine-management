#ifndef UTILS_H
#define UTILS_H

void cercle(float centreX, float centreY, float rayon);
void quartCercle(float centreX, float centreY, float rayon, int orientation);
void roundRect(int x, int y, int w, int h, int radius);
void intToString(int number, char * dest);
unsigned char * rescaleImage(unsigned char * orininalImage, int width, int height, int new_width, int new_height);

#endif