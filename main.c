#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Image.h"
#include "ASCIIArtGenerator.h"

int main(int argc, char *argv[])
{
    //Program requires an additional argument, a path to a bmp file.
    if(argc!=2)
    {
        printf("Incorrect arguments, program failed!\n");
        return 1;
    }

    //Opening specified bmp file.
    FILE *fp;
    fp=fopen(argv[1],"rb");
    if(fp==NULL)
    {
        printf("Couldn\'t open file, program failde!\n");
        return 1;
    }

    //Checking file type. BMP file required.
    {
        char a=fgetc(fp);
        if(a!='B')
        {
            printf("Incorrect file. BMP file required!");
            return 1;
        }
        a=fgetc(fp);
        if(a!='M')
        {
            printf("Incorrect file. BMP file required!");
            return 1;
        }
    }

    //Creating an image in memory.
    Image Image;

    //Copying an image from a file to the Image variable.
    copy_image(&Image,fp);

    //File no longer needed, closing.
    fclose(fp);

    //Declaring dimensions of output image.
    int width,height;

    //Option menu.
    while(1)
    {
        printf("1. I want to select width only. Height will be automatically calculated to preserve original image proportions.\n");
        printf("2. I want to select both width and height.\n");
        printf("Enter your choice: ");

        //Reading choice.
        char buffer[64];
        char choice;
        fgets(buffer,sizeof(buffer),stdin);
        //Expected format char+\n.
        if(strlen(buffer)!=2)
        {
            choice=0;
        }
        else
        {
            choice=buffer[0];
        }

        switch (choice)
        {
        //Selecting width only.
        case '1':
            {
            //Values of font dimensions for Consolas font. I extracted them from consola.ttf file from OS/2 table. https://learn.microsoft.com/en-us/typography/opentype/spec/os2#tlg
            //font_width=xAvgCharWidth, font_height=sTypoAscender-sTypoDescender+sTypoLineGap.
            //This is platform specific. For other platforms it is necessary to use different tables in .ttf file to extract data from.
            long double font_width=1126.0L,font_height=2398.0L;
            printf("How many characters wide do you want your image to be? Enter number between 1 and %u: ",Image.width);
            scanf("%u", &width);
            //Formula to calculate height preserving original image proportions.
            height=(int)((long double)width*(font_width*(long double)Image.height)/(font_height*(long double)Image.width));
            printf("Your image would be %u characters wide and %u characters high.\n",width,height);
            }
            break;
        //Selecting both output dimensions.
        case '2':
            {
            printf("How many characters wide do you want your image to be? Enter number between 1 and %u: ",Image.width);
            scanf("%u", &width);
            printf("How many characters high do you want your image to be? Enter number between 1 and %u: ",Image.height);
            scanf("%u", &height);
            printf("Your image would be %u characters wide and %u characters high.\n",width,height);
            }
            break;
        default:
            printf("Invalid choice. Choose again.\n");
        }

        //Clear stdin.
        fflush(stdin);

        //Breaking loop if valid option selected.
        if(choice=='1'||choice=='2')
            break;
    }

    //Choose method of conversion to black and white image.
    long double (*method)(unsigned char,unsigned char,unsigned char);
    while(1)
    {
        printf("What method do you want to choose to generate black and white base for your ASCII art?\n");
        printf("1. Arithmetic average=(r+g+b)/3.\n");
        printf("2. Midpoint=(min+max)/2.\n");
        printf("3. Median.\n");
        printf("4. Max.\n");
        printf("5. Min.\n");
        printf("6. Geometric average=(r*g*b)^(1/3).\n");
        printf("7. Harmonic average=3*(1/(1/r)+(1/g)+(1/b)).\n");
        char choice;
        scanf("%c",&choice);
        fflush(stdin);
        if(choice=='1')
        {
            method=arithmetic_average;
            break;
        }
        else if(choice=='2')
        {
            method=midpoint;
            break;
        }
        else if(choice=='3')
        {
            method=median;
            break;
        }
        else if(choice=='4')
        {
            method=max;
            break;
        }
        else if(choice=='5')
        {
            method=min;
            break;
        }
        else if(choice=='6')
        {
            method=geometric_average;
            break;
        }
        else if(choice=='7')
        {
            method=harmonic_average;
            break;
        }
        else
        {
            printf("Invalid choice, choose again.\n");
        }
    }
    //Generates brightness_data array for picture of size described by width and height from Image *p_Image.
    long double *brightness_data=NULL;
    generate_brightness_data(&brightness_data,width,height,&Image,method);

    //Image.data no longer needed, freeing.
    free(Image.data);

    //Creating result file.
    printf("Select the name for your output file: ");
    char name[64];
    scanf("%s",name);
    fp=fopen(name,"w");

    //Writing characters to result file based on average brightness of corresponding regions.
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            fputc(select_character(brightness_data[width*i+j]),fp);
        }
        fputc('\n',fp);
    }

    //brightness_data no longer needed, freeing.
    free(brightness_data);

    //Closing file.
    fclose(fp);

    return 0;
}
