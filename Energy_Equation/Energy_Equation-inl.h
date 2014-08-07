#ifndef ENERGY_EQUATION_INL_H
#define ENERGY_EQUATION_INL_H

//i is the index of the first component of the interpolation and differentiation
//j is the index of the second   ''                   ''          ''

// Common Interpolation and Derivative operators for the uniform directions
inline double Interpolation(double value_right, double value_left)
{
  return        0.5*( value_right+value_left);
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

  return         coefficient[0]*value_right+
    coefficient[1]*value_left;
}


//4 Calculation of Thermal Conductivity
inline double Conductivity(double T)
{
  return 1.;
  //  return 0.886025 + 0.001756/0.644*(T) - 0.00000646/0.644*(T)*(T);
}


//4 Calculation of Heat Capacity
inline double Heat_Capacity(double T)
{
  return 1.;
  //  return  1.005495 -1.31/4186.0*(T) +0.014/4186.*(T)*(T);
}





#endif
