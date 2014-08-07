#ifndef SOLVER_RESIDUALS_INL_H
#define SOLVER_RESIDUALS_INL_H

#include <iostream>
using namespace std;

//i is the index of the first component of the interpolation and
//differentiation 
//j is the index of the second   ''                   ''          '' 
 
// Common Interpolation and Derivative operators for the uniform
// directions 
inline double Interpolation(double value_right, double value_left)
{
  return   0.5*( value_right+value_left);
}

inline double Derivative( double value_right, double value_left,
                          double dx, int order)
{
  return (1./(dx*order))*( value_right-value_left);
}


//Interpolating and differentiating in the non-uniform direction.
inline double Interpolation_Y(double value_right, double dy_right,
                              double value_left, double dy_left)
{
  double coefficient[2];
  coefficient[0] = dy_left/(dy_left+dy_right); // Right coeff
  coefficient[1] = dy_right/(dy_left+dy_right); // left coeff

  return coefficient[0]*value_right+coefficient[1]*value_left;
}

inline double Viscosity_Calculator(double Temperature)
{

  return 1.;
  /* return  pow(10, (-2.75 - 0.0141*(T) +91.9*1e-6*(T)*(T) -311*1e-9*
  */ 
  /*(T)*(T)*(T))/(0.547e-3) ); */ 
}





#endif
