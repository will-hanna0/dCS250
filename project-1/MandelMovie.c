#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "ComplexNumber.h"
#include "Mandelbrot.h"
#include "ColorMapInput.h"
#include "ColorOut.h"
#include <sys/types.h>
#include <string.h>

void printUsage(char* argv[])
{
    printf("Usage: %s <threshold> <maxiterations> <center_real> <center_imaginary> <initialscale> <finalscale> <framecount> <resolution> <output_folder> <colorfile>\n", argv[0]);
    printf("    This program simulates the Mandelbrot Fractal, and creates an iteration map of the given center, scale, and resolution, then saves it in output_file\n");
}


/*
This function calculates the threshold values of every spot on a sequence of frames. The center stays the same throughout the zoom. First frame is at initialscale, and last frame is at finalscale scale.
The remaining frames form a geometric sequence of scales, so
if initialscale=1024, finalscale=1, framecount=11, then your frames will have scales of 1024, 512, 256, 128, 64, 32, 16, 8, 4, 2, 1.
As another example, if initialscale=10, finalscale=0.01, framecount=5, then your frames will have scale 10, 10 * (0.01/10)^(1/4), 10 * (0.01/10)^(2/4), 10 * (0.01/10)^(3/4), 0.01 .
*/
void MandelMovie(double threshold, u_int64_t max_iterations, ComplexNumber* center, double initialscale, double finalscale, int framecount, u_int64_t resolution, u_int64_t ** output){
    double mul = pow((finalscale/initialscale), 1.0/(framecount-1));
    double scale = initialscale;
    for(int i = 0; i < framecount; i++){
    	Mandelbrot(threshold, max_iterations, center, scale, resolution, output[i]);
    	scale *= mul;

    }
}

/**************
**This main function converts command line inputs into the format needed to run MandelMovie.
**It then uses the color array from FileToColorMap to create PPM images for each frame, and stores it in output_folder
***************/
int main(int argc, char* argv[])
{
    //Tips on how to get started on main function:
    //MandelFrame also follows a similar sequence of steps; it may be useful to reference that.
    //Make sure you complete the steps below in order.

    //STEP 1: Convert command line inputs to local variables, and ensure that inputs are valid.
    /*
    Check the spec for examples of invalid inputs.
    Remember to process the colorfile.
    */

    /*int goodComplex = test_complex_number(); //Testing
    if(!goodComplex){
      return 1;
    }
    */

    if (argc != 11) {
        printf("Main Error\n");
    	return 1;
    }

    double threshold, initialscale, finalscale,  imaginary, real;
    int framecount;
    u_int64_t max_iterations, resolution;
    char* output_folder;
    char* colorfile;
    threshold = atof(argv[1]);
    max_iterations = (u_int64_t)atoi(argv[2]);
    real = atof(argv[3]);
    imaginary = atof(argv[4]);
    initialscale = atof(argv[5]);
    finalscale = atof(argv[6]);
    framecount = atoi(argv[7]);
    resolution = (u_int64_t)atoi(argv[8]);
    output_folder = argv[9];//pointer check
    colorfile = argv[10];

    if (threshold <= 0 ||initialscale <= 0 || finalscale <= 0 || max_iterations <= 0 || framecount <= 0 || framecount > 10000 || resolution < 0) {
    	printf("Main Error\n");
    	//didn't check these checks
    	return 1;
    }
    ComplexNumber * center = newComplexNumber(real, imaginary);
    if(center == NULL){
      printf("Main Error\n");
      return 1;
    }

/*
    if (framecount == 1 && initialscale != finalscale ) {
    	printf("Main Error\n");
    	printUsage(argv);
    	return 1;
    }
    */

    u_int64_t size = 2 * resolution + 1;
    int nColors;
    uint8_t ** cMap = FileToColorMap(colorfile, &nColors);
    if(cMap == NULL){
      freeComplexNumber(center);
      return 1;
    }



    //STEP 2: Run MandelMovie on the correct arguments.
    /*
    MandelMovie requires an output array, so make sure you allocate the proper amount of space.
    If allocation fails, free all the space you have already allocated (including colormap), then return with exit code 1.
    */

    u_int64_t **out;
    out = (u_int64_t **)malloc(framecount *  sizeof(u_int64_t*));

    if (out == NULL) {
      freeComplexNumber(center);
      for(int i = 0; i < nColors; i ++){
        free(cMap[i]);
      }
      free(cMap);
      //EDIT BELOW
     //printf("Unable to allocate %llu bytes\n", size * size * sizeof(u_int64_t));
     return 1;
    }


     for(int i = 0; i < framecount; i++){
       u_int64_t * space = (u_int64_t *) malloc((size*size) * sizeof(u_int64_t));
       if(space == NULL){
         for(int j = 0; j < i; j++){
           free(out[j]);
         }
         freeComplexNumber(center);
         free(out);
         for(int i = 0; i < nColors; i ++){
           free(cMap[i]);
         }
         free(cMap);
         return 1;
       }
     	out[i] = space;
     }



     MandelMovie(threshold, max_iterations, center, initialscale, finalscale, framecount, resolution, out);



//woop woop
    //STEP 3: Output the results of MandelMovie to .ppm files.
    /*
    Convert from iteration count to colors, and output the results into output files.
    Use what we showed you in Part B.1.2, create a seqeunce of ppm files in the output folder.
    Feel free to create your own helper function to complete this step.
    As a reminder, we are using P6 format, not P3.
    */

    //int colorcount;
  //uint8_t** colorMap = FileToColorMap(argv[10], &colorcount);

  for (int i = 0; i < framecount;i++) {
       char buffer[16 + strlen(output_folder)];
       sprintf(buffer, "%s/frame%05d.ppm", output_folder, i);
       FILE* outfile = fopen(buffer, "w+");
       if(outfile == NULL){
         for (int k = 0; k < framecount; k++) {
           free(out[k]);
         }
         freeComplexNumber(center);
         free(out);
         for(int i = 0; i < nColors; i ++){
           free(cMap[i]);
         }
         free(cMap);
         return 1;
       }
       uint8_t blac[] = {0,0,0};
       fprintf(outfile, "P6 %llu %llu 255\n", size, size);
       u_int64_t * b = out[i];
       for (int j = 0; j < framecount; j++) {
         u_int64_t iters = b[j];
         if(iters == 0){
           fwrite(blac, sizeof(char), 3, outfile);
         }
         else{
           uint8_t * colour;
           colour = cMap[(iters -1) % nColors];
           fwrite(colour, sizeof(char), 3, outfile);
         }
       }
       fclose(outfile);
  }





    //STEP 4: Free all allocated memory
    /*
    Make sure there's no memory leak.
    */
    for (int i = 0; i < framecount;i++) {
      free(out[i]);
    }
    free(out);
    for (int i = 0; i < nColors;i++) {
      free(cMap[i]);
    }
    free(cMap);
    freeComplexNumber(center);


    return 0;
}
