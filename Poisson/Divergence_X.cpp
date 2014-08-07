/*******************************************
 * Author: Michail Georgiou
 *  Last Modified: Time-stamp: <2014-07-31 16:09:54 mike_georgiou>
 *
 *
Divergence_X.cpp -- This program computes the X-component of the divergence
that is used in the Right_Hand_Side_Poisson.cpp program
*
* Written on Friday, 25 April 2014.
********************************************/

#include "Right_Hand_Side_Poisson.h"

double Divergence_X(double*** velocity_x, double*** rho,
                    double dx,
                    int i, int j, int k)
{
  double derivative_x[4][2], interpolated_x[4];


  //calculation of the interpolated quantities that will be used for the
  //calculation of the derivatives in the x-direction
  for(int vi=0, vj=0; vi<2; vi++, vj+=3)
    {
      //\delta_1
      //i\pm 3
      derivative_x[0][vi]=
        9./8.*Derivative(rho[k][j][i-1+vj]*velocity_x[k][j][i-1+vj],
                         rho[k][j][i-2+vj]*velocity_x[k][j][i-2+vj],
                         dx,1);
      //\delta_3
      //i\pm 3
      derivative_x[1][vi]=
        -1./8.*Derivative(rho[k][j][i+vj]*velocity_x[k][j][i+vj],
                          rho[k][j][i+vj-3]*velocity_x[k][j][i+vj-3],
                          dx,3);

      //i\pm 1
      derivative_x[2][vi]=
        9./8.*Derivative(rho[k][j][i+vi]*velocity_x[k][j][i+vi],
                         rho[k][j][i-1+vi]*velocity_x[k][j][i-1+vi],
                         dx,1);

      //i\pm 1
      derivative_x[3][vi]=
        -1./8.*Derivative(rho[k][j][i+1+vi]*velocity_x[k][j][i+1+vi],
                          rho[k][j][i-2+vi]*velocity_x[k][j][i-2+vi],
                          dx,3);
    }
  //computing the interpolated  derivative constituents in the x-direction
  for(int vi=0; vi<2; vi++)
    {
      interpolated_x[vi]= -1./8.*Interpolation(derivative_x[vi][0],
                                               derivative_x[vi][1]);

      interpolated_x[vi+2]= 9./8.*Interpolation(derivative_x[vi+2][0],
                                                derivative_x[vi+2][1]);
    }

  //summing the total derivative
  double  total_derivative=0.;
  for (int vi=0; vi<4; vi++)
    total_derivative +=interpolated_x[vi];


  return total_derivative;
}
