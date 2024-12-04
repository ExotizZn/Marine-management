#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

typedef struct Texture {
    int initial_width;
    int initial_height;
    int resized_width;
    int resized_height;
    unsigned char * orininalImage;
    unsigned char * resizedImage;
} Texture;

Texture * initTexture(char * src);
void resizeTexture(Texture * texture, int new_width, int new_height);

#endif