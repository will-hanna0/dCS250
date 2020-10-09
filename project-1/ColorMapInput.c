/*********************
**  Color Map generator
**********************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include "ColorMapInput.h"


/**************
**This function frees the memory allocated for colorMap.
**Length represents the number of elements in colorMap
***************/
void freeMap(int length, uint8_t** colorMap)
{
    for(int i = 0; i < length; i++){
      free(colorMap[i]);
    }
}

/**************
**This function reads in a file name colorfile.
**It then uses the information in colorfile to create a color array, with each color represented by an int[3].
***************/
uint8_t** FileToColorMap(char* colorfile, int* colorcount)
{
FILE * ptr = fopen(colorfile, "r");
        if (ptr == NULL) {
                return NULL;
        }
        int size;
        int byte = fscanf(ptr, "%d", &size);

        if (byte <= 0) {
                return NULL;
        }

        uint8_t ** ret = malloc(sizeof(uint8_t *) * size);
        *colorcount = size;
        int count = 0;

        while (count < size) {
                int r;
                int g;
                int b;


                uint8_t * color = malloc(sizeof(uint8_t) * 3);

                //scan red
                byte = fscanf(ptr, "%d", &r);
                if (byte <= 0) {
			               for (int j = 0; j < count; j++) {
				                   free(ret[j]);
			                      }
			               free(color);
			               free(ret);
                     return NULL;
                }
                uint8_t nR = r;
                //scan green
                byte = fscanf(ptr, "%d", &g);
                if (byte <= 0) {
			               for (int j = 0; j < count; j++) {
                                free(ret[j]);
                        }
                        free(color);
                        free(ret);
                        return NULL;
                }
                uint8_t nG = g;
                //scan blue
                byte = fscanf(ptr, "%d", &b);
                if (byte <= 0) {
			               for (int j = 0; j < count; j++) {
                                free(ret[j]);
                        }
                        free(color);
                        free(ret);
                        return NULL;
                }
                uint8_t nB = b;

                color[0] = nR;
                color[1] = nG;
                color[2] = nB;

                ret[count] = color;

                count ++;

        }
        fclose(ptr);
        return ret;

    //Make an array of pointers to size 3 arrays of the R, G, and B values

    //If a line is malformed then that line's pointer should be NULL, and free the data that was allocated to it
    //Exception to ^ is if the number at the top of the file is less than the actual amount of lines, then only that # of lines would be returned

    // use "int fscanf(FILE* ptr, const char *format, ...)," for scanning the file

    //colorcount should be set to the number of colors in the file
}
