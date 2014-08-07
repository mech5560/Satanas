#ifndef INITIAL_CONDITIONS_TURBULENCE_H
#define INITIAL_CONDITIONS_TURBULENCE_H
#include <stdlib.h>
#include <math.h>



void Turbulence_Reader(double* Reynolds_wall);


inline double drand()
{
  return (2.*((double) rand() / (RAND_MAX+1.0)) - 1.);
}


#endif
