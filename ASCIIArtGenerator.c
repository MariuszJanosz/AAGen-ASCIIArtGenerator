#include "ASCIIArtGenerator.h"
#include "Image.h"
#include <stdlib.h>
#include <math.h>

//Returns character corresponding to given brightness.
char select_character(long double brightness)
{
    //"Character density found for Consolas font by calculating what portion of space is taken by the given character.
    if(brightness<255.0L/24.0L*1)
        return ' ';
    else if(brightness<255.0L/24.0L*2)
        return '-';
    else if(brightness<255.0L/24.0L*3)
        return '"';
    else if(brightness<255.0L/24.0L*4)
        return ';';
    else if(brightness<255.0L/24.0L*5)
        return '/';
    else if(brightness<255.0L/24.0L*6)
        return 'r';
    else if(brightness<255.0L/24.0L*7)
        return 'c';
    else if(brightness<255.0L/24.0L*8)
        return ')';
    else if(brightness<255.0L/24.0L*9)
        return 'l';
    else if(brightness<255.0L/24.0L*10)
        return 's';
    else if(brightness<255.0L/24.0L*11)
        return '}';
    else if(brightness<255.0L/24.0L*12)
        return 'f';
    else if(brightness<255.0L/24.0L*13)
        return 'C';
    else if(brightness<255.0L/24.0L*14)
        return '5';
    else if(brightness<255.0L/24.0L*15)
        return 'E';
    else if(brightness<255.0L/24.0L*16)
        return 'k';
    else if(brightness<255.0L/24.0L*17)
        return 'w';
    else if(brightness<255.0L/24.0L*18)
        return 'X';
    else if(brightness<255.0L/24.0L*19)
        return 'm';
    else if(brightness<255.0L/24.0L*20)
        return 'q';
    else if(brightness<255.0L/24.0L*21)
        return 'R';
    else if(brightness<255.0L/24.0L*22)
        return '8';
    else if(brightness<255.0L/24.0L*23)
        return 'M';
    else
        return '@';
}

//Arithmetic average.
long double arithmetic_average(unsigned char a,unsigned char b,unsigned char c)
{
    long double arithmetic_average=(a+b+c)/3.0L;
    return arithmetic_average;
}

//Midpoint midpoint=(min+max)/2.0L.
long double midpoint(unsigned char a,unsigned char b,unsigned char c)
{
    unsigned char max=a;
    if(b>max)
        max=b;
    if(c>max)
    max=c;
    unsigned char min=a;
    if(b<min)
        min=b;
    if(c<min)
        min=c;
    long double midpoint=(min+max)/2.0L;
    return midpoint;
}

//Median.
long double median(unsigned char a,unsigned char b,unsigned char c)
{
    unsigned char helper;
    if((a<=b&&b<=c)||(c<=b&&b<=a))
    {
        helper=b;
    }
    else if((b<=a&&a<=c)||(c<=a&&a<=b))
    {
        helper=a;
    }
    else
    {
        helper=c;
    }
    long double median=(long double)helper;
    return median;
}

//Max.
long double max(unsigned char a,unsigned char b,unsigned char c)
{
    unsigned char helper=a;
    if(b>helper)
        helper=b;
    if(c>helper)
        helper=c;
    long double max=(long double)helper;
    return max;
}

//Min.
long double min(unsigned char a,unsigned char b,unsigned char c)
{
    unsigned char helper=a;
    if(b<helper)
        helper=b;
    if(c<helper)
        helper=c;
    long double min=(long double)helper;
    return min;
}

//Geometric average.
long double geometric_average(unsigned char a,unsigned char b,unsigned char c)
{
    long double geometric_average=powl((long double)(a*b*c),1.0L/3.0L);
    return geometric_average;
}

//Harmonic average.
long double harmonic_average(unsigned char a,unsigned char b,unsigned char c)
{
    long double harmonic_average=3.0L/((1.0L/(long double)a)+(1.0L/(long double)b)+(1.0L/(long double)c));
    return harmonic_average;
}

//Generates brightness_data array for picture of size described by width and height from Image *p_Image with average brightness calculated by *averaging_method.
void generate_brightness_data(long double **p_brightness_data,int width,int height,Image *p_Image,long double (*averaging_method)(unsigned char,unsigned char,unsigned char))
{
    //Allocating required space with calloc to set it to 0.
    (*p_brightness_data)=calloc(width*height,sizeof(long double));
    if((*p_brightness_data)==NULL)
    {
        printf("Allocation failed!");
        exit(1);
    }

    //This ratios describe how many columns and rows of pixels correspond to one character in height and width respectively.
    long double height_ratio=(long double)p_Image->height/(long double)height;
    long double width_ratio=(long double)p_Image->width/(long double)width;

    //Visiting every pixel and deciding where to add its brightness.
    for(int i=0;i<p_Image->height;i++)
    {
        for(int j=0;j<p_Image->width;j++)
        {
            //Finding coordinates k,l of first region containing part of pixel with coordinates i,j.
            int k=0;
            while((long double)(k+1)*height_ratio-(long double)i<0.000000001L)
                k++;
            int l=0;
            while((long double)(l+1)*width_ratio-(long double)j<0.000000001L)
                l++;

            //Adding brightness to regions containing part of pixel with coordinates i,j.
            if((long double)(i+1)-(long double)(k+1)*height_ratio<0.000000001L&&(long double)(j+1)-(long double)(l+1)*width_ratio<0.000000001L)
            {
                //Pixel i,j is inside region k,l.
                (*p_brightness_data)[k*width+l]+=averaging_method(p_Image->data[i*p_Image->width+j].r,p_Image->data[i*p_Image->width+j].g,p_Image->data[i*p_Image->width+j].b);
            }
            else if((long double)(i+1)-(long double)(k+1)*height_ratio<0.000000001L&&(long double)(l+1)*width_ratio-(long double)(j+1)<0.000000001L)
            {
                //Pixel i,j is split between regions k,l and k,l+1.
                (*p_brightness_data)[k*width+l]+=((l+1)*width_ratio-j)*averaging_method(p_Image->data[i*p_Image->width+j].r,p_Image->data[i*p_Image->width+j].g,p_Image->data[i*p_Image->width+j].b);
                (*p_brightness_data)[k*width+l+1]+=(1-((l+1)*width_ratio-j))*averaging_method(p_Image->data[i*p_Image->width+j].r,p_Image->data[i*p_Image->width+j].g,p_Image->data[i*p_Image->width+j].b);
            }
            else if((long double)(k+1)*height_ratio-(long double)(i+1)<0.000000001L&&(long double)(j+1)-(long double)(l+1)*width_ratio<0.000000001L)
            {
                //Pixel i,j is split between regions k,l and k+1,l.
                (*p_brightness_data)[k*width+l]+=((k+1)*height_ratio-i)*averaging_method(p_Image->data[i*p_Image->width+j].r,p_Image->data[i*p_Image->width+j].g,p_Image->data[i*p_Image->width+j].b);
                (*p_brightness_data)[(k+1)*width+l]+=(1-((k+1)*height_ratio-i))*averaging_method(p_Image->data[i*p_Image->width+j].r,p_Image->data[i*p_Image->width+j].g,p_Image->data[i*p_Image->width+j].b);
            }
            else
            {
                //Pixel i,j is split between regions k,l and k,l+1 and k+1,l and k+1,l+1.
                (*p_brightness_data)[k*width+l]+=(((l+1)*width_ratio-j)*((k+1)*height_ratio-i))*averaging_method(p_Image->data[i*p_Image->width+j].r,p_Image->data[i*p_Image->width+j].g,p_Image->data[i*p_Image->width+j].b);
                (*p_brightness_data)[k*width+l+1]+=((1-((l+1)*width_ratio-j))*((k+1)*height_ratio-i))*averaging_method(p_Image->data[i*p_Image->width+j].r,p_Image->data[i*p_Image->width+j].g,p_Image->data[i*p_Image->width+j].b);
                (*p_brightness_data)[(k+1)*width+l]+=(((l+1)*width_ratio-j)*(1-((k+1)*height_ratio-i)))*averaging_method(p_Image->data[i*p_Image->width+j].r,p_Image->data[i*p_Image->width+j].g,p_Image->data[i*p_Image->width+j].b);
                (*p_brightness_data)[(k+1)*width+l+1]+=((1-((l+1)*width_ratio-j))*(1-((k+1)*height_ratio-i)))*averaging_method(p_Image->data[i*p_Image->width+j].r,p_Image->data[i*p_Image->width+j].g,p_Image->data[i*p_Image->width+j].b);
            }
        }
    }

    //Normalizing (*p_brightness_data) by size of the region.
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            (*p_brightness_data)[i*width+j]/=height_ratio*width_ratio;
        }
    }
}
