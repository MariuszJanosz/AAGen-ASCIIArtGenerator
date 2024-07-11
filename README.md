# AAGen-ASCIIArtGenerator
A simple ASCII art generator which converts bmp files to text files.

This is my first C program larger than Hello world! or Fibbonaci sequence generator.
Its purpose was to let me train my C skills, so don't expect it to be bug-free or optimized.
Morover I was testing some wild code, so it uses some undefined behaviors like fflush(stdin). Therefore I cannot guarantee it will work on your platform.

Its output is supposed to be displayd with Consolas font (standard font of Windows' notepad). I hardcoded font height/width ratio, extracted form .ttf file, and Consolas font characters' density.
A day may come when I will add font selection oprion and automatic extraction of font's dimensions and density, but it is not this day.
