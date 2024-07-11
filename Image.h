#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED

#include <stdio.h>

//Structures to store image in memory.
typedef struct Pixel
{
unsigned char r;
unsigned char g;
unsigned char b;
} Pixel;

typedef struct Image
{
    int width;
    int height;
    Pixel *data;
} Image;

//Reading an image from a file and saving it in the Image data type variable.
void copy_image(Image *Image,FILE *fp);

#endif // IMAGE_H_INCLUDED
