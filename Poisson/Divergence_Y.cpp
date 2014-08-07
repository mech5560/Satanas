/*******************************************
 * Author: Michail Georgiou
 *  Last Modified: Time-stamp: <2014-07-31 16:18:45 mike_georgiou>
 *
 *
Divergence_Y.cpp -- This function computes the y component of the
divergence that gonna be used in the Right_Hand_Side_Poisson function.
Because I am having non-uniform grid in this direction I ll use second  order
accurate scheme.

* Written on Friday, 25 April 2014.
********************************************/

#include "Right_Hand_Side_Poisson.h"

double Divergence_Y(double*** velocity_y, double*** rho,
                    double* dy,
                    int i, int j, int k)
{
  double dy_total, interpolated_y[2], derivative_y;

  for (int vi=0; vi<2; vi++)
    {
      //Computing the interpolated quantities that will be used to
      //compute the derivative
      interpolated_y[vi]=
        Interpolation_Y(rho[k][j+vi][i]*velocity_y[k][j+vi][i],
                        dy[j+vi],
                        rho[k][j-1+vi][i]*velocity_y[k][j-1+vi][i],
                        dy[j+vi-1]);
    }
  //Computing the derivative
  dy_total=2.*dy[j];
  derivative_y=Derivative(interpolated_y[1],interpolated_y[0],
                          dy_total,1);

  return derivative_y;
}
