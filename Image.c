#include "Image.h"
#include <stdio.h>
#include <stdlib.h>

//Reading an image from a file and saving it in the Image data type variable.
void copy_image(Image *p_Image,FILE* fp)
{
    //Reading image's dimensions.
    fseek(fp,0x12,SEEK_SET);
    fread(&p_Image->width,4,1,fp);
    fread(&p_Image->height,4,1,fp);

    //Setting offset of FILE* fp to point to the beginning of pixel data.
    {
        fseek(fp,0xA,SEEK_SET);
        long int data_offset;
        fread(&data_offset,4,1,fp);
        fseek(fp,data_offset,SEEK_SET);
    }

    //Creating an array of pixels to store data.
    p_Image->data=malloc(p_Image->width*p_Image->height*sizeof(Pixel));
    if(p_Image->data==NULL)
    {
        printf("Allocation failed!");
        exit(1);
    }

    //Copying pixel data from file to memory in such order that first Image.width elements represent uppermost row of pixels in the image and last Image.width of elements represents the bottom row of pixels in the image.
    for(int i=0;i<p_Image->height;i++)
    {
        for(int j=0;j<p_Image->width;j++)
        {
            p_Image->data[(p_Image->height-i-1)*p_Image->width+j].b=fgetc(fp);
            p_Image->data[(p_Image->height-i-1)*p_Image->width+j].g=fgetc(fp);
            p_Image->data[(p_Image->height-i-1)*p_Image->width+j].r=fgetc(fp);
        }

        //Skipping padding if needed.
        switch ((3*p_Image->width)%4)
        {
        case 1:
            fgetc(fp);
        case 2:
            fgetc(fp);
        case 3:
            fgetc(fp);
        default:
            break;
        }
    }
}

