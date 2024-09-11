#ifndef IMAGE_CONVERSION_H
#define IMAGE_CONVERSION_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

// Function to convert image to binary format
bool ConvertToBin(char *filename, int * dimensions);

// Function to check binary file was created properly and print the values
bool CheckBin(char *filename, int * dimensions, bool print);

#endif // IMAGE_CONVERSION_H