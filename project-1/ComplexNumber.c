/*********************
**  Complex Numbers
**  This file contains a few functions that will be useful when performing computations with complex numbers
**  It is advised that you work on this part first.
**********************/

#include "ComplexNumber.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct ComplexNumber
{
    double real;
    double imaginary;
}ComplexNumber;

//Returns a pointer to a new Complex Number with the given real and imaginary components
ComplexNumber* newComplexNumber(double real_component, double imaginary_component)
{
  struct ComplexNumber* newComplexNumber;
  newComplexNumber = (ComplexNumber*)malloc(sizeof(ComplexNumber));
  newComplexNumber->real =  real_component;
  newComplexNumber->imaginary =  imaginary_component;
    return newComplexNumber;
}

//Returns a pointer to a new Complex Number equal to a*b
ComplexNumber* ComplexProduct(ComplexNumber* a, ComplexNumber* b)
{
    //YOUR CODE HERE
    struct ComplexNumber* newComplexNumber = malloc(sizeof(ComplexNumber));
    double c1 = b->real * (a->real + a->imaginary);
    double c2= a->real * (b->imaginary - b->real);
    double c3= a->imaginary * (b->real + b->imaginary);
    newComplexNumber->real = c1-c3;
    newComplexNumber->imaginary = c1+c2;
    return newComplexNumber;
}

//Returns a pointer to a new Complex Number equal to a+b
ComplexNumber* ComplexSum(ComplexNumber* a, ComplexNumber* b)
{
    struct ComplexNumber* newComplexNumber = malloc(sizeof(ComplexNumber));
    double c1 = a->real + b->real;
    double c2 = a->imaginary + b->imaginary;
    newComplexNumber->real = c1;
    newComplexNumber->imaginary = c2;
    //YOUR CODE HERE
    return newComplexNumber;
}

//Returns the absolute value of Complex Number a
double ComplexAbs(ComplexNumber* a)
{

    double abso = sqrt(pow(a->real, 2) + pow(a->imaginary,2));
    //YOUR CODE HERE
    return abso;
}

void freeComplexNumber(ComplexNumber* a)
{
free(a);
    //YOUR CODE HERE
}

double Re(ComplexNumber* a)
{
    return a->real;
}
double Im(ComplexNumber* a)
{
    return a->imaginary;
}


//Contains a few tests.
int test_complex_number()
{
    int fail = 0;
    ComplexNumber* a = newComplexNumber(2.0, 1.0);
    if (a == NULL)
    {
    	fprintf(stderr, "Creation of complex numbers not implemented\n");
    	return 0;
    }
    ComplexNumber* b = ComplexProduct(a, a);
    if (b == NULL)
    {
    	fprintf(stderr, "Multiplication of complex numbers not implemented\n");
    	free(a);
    	return 0;
    }
    ComplexNumber* c = ComplexSum(b, b);
    if (c == NULL)
    {
    	fprintf(stderr, "Addition of complex numbers not implemented\n");
    	free(a);
    	free(b);
    	return 0;
    }
    float d = ComplexAbs(c);
    if (d == 0)
    {
    	fprintf(stderr, "Absolute Value of complex numbers not implemented\n");
    	free(a);
    	free(b);
    	free(c);
    	return 0;
    }
    else if (fabsf(d - 10) < 0.0001)
    {
    	//passes
    	free(a);
    	free(b);
    	free(c);
    	return 1;
    }
    else
    {
    	fprintf(stderr, "At least one of your functions is incorrect\n");
    	free(a);
    	free(b);
    	free(c);
    	return 0;
    }
    free(a);
    free(b);
    free(c);
    return 0;
}
