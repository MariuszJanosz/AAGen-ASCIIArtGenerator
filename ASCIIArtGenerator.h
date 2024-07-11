#ifndef ASCIIARTGENERATOR_H_INCLUDED
#define ASCIIARTGENERATOR_H_INCLUDED

#include "Image.h"

//Returns character corresponding to given brightness.
char select_character(long double brightness);

//Arithmetic average.
long double arithmetic_average(unsigned char a,unsigned char b,unsigned char c);

//Midpoint midpoint=(min+max)/2.0L.
long double midpoint(unsigned char a,unsigned char b,unsigned char c);

//Median.
long double median(unsigned char a,unsigned char b,unsigned char c);

//Max.
long double max(unsigned char a,unsigned char b,unsigned char c);

//Min.
long double min(unsigned char a,unsigned char b,unsigned char c);

//Geometric average.
long double geometric_average(unsigned char a,unsigned char b,unsigned char c);

//Harmonic average.
long double harmonic_average(unsigned char a,unsigned char b,unsigned char c);

//Generates brightness_data array for picture of size described by width and height from Image *p_Image with average brightness calculated by *averaging_method.
void generate_brightness_data(long double **brightness_data,int width,int height,Image *p_Image,long double (*averaging_method)(unsigned char,unsigned char,unsigned char));

#endif // ASCIIARTGENERATOR_H_INCLUDED
