#include <stdio.h>
#include <stdlib.h>
#include "ComplexNumber.h"
#include "Mandelbrot.h"
#include <sys/types.h>
#include <math.h>

/*
This function returns the number of iterations before the initial point >= the threshold.
If the threshold is not exceeded after maxiters, the function returns 0.
*/
u_int64_t MandelbrotIterations(u_int64_t maxiters, ComplexNumber * c, double threshold)
{
  ComplexNumber *z = newComplexNumber(0,0);
  u_int64_t iterations = 0;
  while((iterations < maxiters) && (ComplexAbs(z) < threshold)){
  ComplexNumber *z2 = ComplexProduct(z,z);
  ComplexNumber *nextz = ComplexSum(z2,c);

  if(ComplexAbs(z) > threshold){
    freeComplexNumber(z2);
    freeComplexNumber(nextz);
    freeComplexNumber(z);
    return iterations + 1;
  }
  freeComplexNumber(z);
  z = nextz;
  freeComplexNumber(z2);
  iterations++;
}

freeComplexNumber(z);

if (iterations < maxiters){
  return iterations;
}
else{
  return 0;
}

//NEED TO INPUT MEMORY STUFF
}



/*
This function calculates the Mandelbrot plot and stores the result in output.
The number of pixels in the image is resolution * 2 + 1 in one row/column. It's a square image.
Scale is the the distance between center and the top pixel in one dimension.
*/
void Mandelbrot(double threshold, u_int64_t max_iterations, ComplexNumber* center, double scale, u_int64_t resolution, u_int64_t * output){
    int arraySize = 2 * resolution + 1;
    for(int i = 0; i < arraySize; i ++){
      for(int k = 0; k < arraySize; k++){
        ComplexNumber* c = newComplexNumber(-scale + k * (scale/resolution), scale - i * (scale/resolution));
        ComplexNumber* c2 = ComplexSum(center, c);
        output[i+arraySize+k] = MandelbrotIterations(max_iterations, c, threshold);
        freeComplexNumber(c2);
        freeComplexNumber(c);

      }
    }
}
