#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../GfxLib/GfxLib.h" 
#include "../GfxLib/BmpLib.h"
#include "../include/textureLoader.h"
#include "../include/utils.h"

Texture * initTexture(char * src) {
    Texture * t = NULL;
    DonneesImageRGB * image = NULL;
    image = lisBMPRGB(src);

    t = (Texture*)calloc(1, sizeof(Texture));
    t->initial_width  = image->largeurImage;
    t->initial_height = image->hauteurImage;
    t->resized_width  = image->largeurImage;
    t->resized_height = image->hauteurImage;
    t->orininalImage  = image->donneesRGB;
    t->resizedImage   = image->donneesRGB;
    
    free(image);
    return t;
}

void resizeTexture(Texture * texture, int new_width, int new_height) {
    texture->resized_width = new_width;
    texture->resized_height = new_height;
    texture->resizedImage = rescaleImage(texture->orininalImage, texture->initial_width, texture->initial_height, new_width, new_height);
}
