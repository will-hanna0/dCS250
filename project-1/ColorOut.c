#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include "ColorOut.h"

/**************
**Translate pixel value given in MandelOut array into a color that can be found in the colorMap array
**Length of the MandelOut array = size * size
**Output should be written to outputfile with P3 format
***************/
int P3colorpalette(u_int64_t size, uint8_t** colorMap, int colorcount, u_int64_t * MandelOut, char* outputfile)
{
  FILE *ofile = fopen(outputfile, "w");
      if (ofile == NULL)
      {
          printf("File not opening/working"); //Checker
          return 1;
      }
      fprintf(ofile, "%s %llu %llu %d\n", "P3", size, size, 255);
      for (int i =0; i < (size*size);i++) {
          if (MandelOut[i] == 0) { //black
              if (fprintf(ofile, "%d %d %d\n", 0,0,0) == 1) {
                  free(outputfile);
                  free(ofile);
                  return 1;
              }
          } else if (MandelOut[i] > colorcount) { //MandelOut[i] returns higher number than colorcount holds, loop to beginning
              int x = (MandelOut[i] % colorcount) - 1;
              int rgb[3];

              for (int j = 0;j < 3;j++) { // assigns rgb array with correct rgb value
                  rgb[j] = colorMap[x][j];
              }
                  if (fprintf(ofile, "%d %d %d\n", rgb[0],rgb[1],rgb[2]) == 1) { //works
                    free(outputfile);
                    free(ofile);
                    return 1;
                  }

          } else {
              int rgb[3];
              int x = MandelOut[i]-1;
              for (int j = 0;j < 3;j++) {// assigns rgb array with correct rgb value
                  rgb[j] = colorMap[x][j];
              }


              if (fprintf(ofile, "%d %d %d\n", rgb[0],rgb[1],rgb[2]) == 1) { //works
                  free(outputfile);
                  free(ofile);
                  return 1;
              }

          }
      }
return 0;
}

/**************
**Same as above, but with P6 format
***************/
int P6colorpalette(u_int64_t size, uint8_t** colorMap, int colorcount, u_int64_t * MandelOut, char* outputfile)
{
  FILE *ofile = fopen(outputfile, "w");
 if (ofile == NULL)
 {
     printf("File not opening/working");//Checker
     return 1;
 }
 fprintf(ofile, "%s %llu %llu %d\n", "P6", size, size, 255);

 for (int i =0; i < (size*size);i++) {
     if (MandelOut[i] == 0) { //black
         uint8_t rgb[3];
         for (int j = 0;j < 3;j++) {
             rgb[j] = 0;
         }
         if (fwrite(rgb, sizeof(uint8_t), 3, ofile) < 0) {
             free(outputfile);
             free(ofile);
             return 1;
         }
     }
      else if (MandelOut[i] > colorcount) { //MandelOut[i] returns higher number than colorcount holds, loop to beginning
         int x = (MandelOut[i] % colorcount) - 1;
         uint8_t rgb[3];
         for (int j = 0;j < 3;j++) { // assigns rgb array with correct rgb value
             rgb[j] = colorMap[x][j];
         }
         if (fwrite(rgb, sizeof(uint8_t), 3, ofile) < 0) {
             free(outputfile);
             free(ofile);
             return 1;
         }
     }
     else {
         int x = MandelOut[i]-1;
         uint8_t rgb[3];
         for (int j=0;j<3;j++) { // assigns rgb array with correct rgb value
             rgb[j] = colorMap[x][j];
         }
         if (fwrite(rgb, sizeof(uint8_t), 3, ofile) < 0 ) {
             free(outputfile);
             free(ofile);
             return 1;
         }
     }
 }
    return 0;
}
