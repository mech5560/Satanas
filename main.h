#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <cstdlib>
#include <fstream>
#include <signal.h>
#include <sstream>

#include "Struct.h"
#include "./Printing/printing_functions.h"





static const double pi = 4.*atan(1.);


int 
  ldx,ldy,ldz,
/*Nze is defined in order to construct the vectors for the sparse solver*/
  nze, dim_a, flag;

int left_z,right_z,
  left_y,right_y,
  left_x,right_x;

/* Structure defined in the Struct.h file*/
Ar Arr;


double *s_a, *precond_a, *result, *rhs,Coefficients_X[4],Coefficients_Z[4];
int *ij_a;


double dx, dz, dt, length_x, length_y, length_z;
double cfl, tolerance, time_total;

int iterations, printing_variable;
#endif
