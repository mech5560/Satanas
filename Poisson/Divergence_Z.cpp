/*******************************************
 * Author: Michail Georgiou
 *  Last Modified: Time-stamp: <2014-07-31 16:20:43 mike_georgiou>
 *
 *
Divergence_X.cpp -- This program computes the X-component of the divergence
that is used in the Right_Hand_Side_Poisson.cpp program
*
* Written on Friday, 25 April 2014.
********************************************/


#include "Right_Hand_Side_Poisson.h"
double Divergence_Z(double*** velocity_z, double*** rho,
                    double dz,
                    int i, int j, int k)
{

  double derivative_z[4][2], interpolated_z[4];


  //calculation of the interpolated quantities that will be used for the
  //calculation of the derivatives in the x-direction
  for(int vi=0, vj=0; vi<2; vi++, vj+=3)
    {
      //\delta_1
      //i\pm 3
      derivative_z[0][vi]=
        9./8.*Derivative(rho[k-1+vj][j][i]*velocity_z[k-1+vj][j][i],
                         rho[k-2+vj][j][i]*velocity_z[k-2+vj][j][i],
                         dz,1);
      //\delta_3
      //i\pm 3
      derivative_z[1][vi]=
        -1./8.*Derivative(rho[k+vj][j][i]*velocity_z[k+vj][j][i],
                          rho[k+vj-3][j][i]*velocity_z[k+vj-3][j][i],
                          dz,3);

      //i\pm 1
      derivative_z[2][vi]=
        9./8.*Derivative(rho[k+vi][j][i]*velocity_z[k+vi][j][i],
                         rho[k-1+vi][j][i]*velocity_z[k-1+vi][j][i],
                         dz,1);

      //i\pm 1
      derivative_z[3][vi]=
        -1./8.*Derivative(rho[k+1+vi][j][i]*velocity_z[k+1+vi][j][i],
                          rho[k-2+vi][j][i]*velocity_z[k-2+vi][j][i],
                          dz,3);
    }
  //computing the interpolated  derivative constituents in the x-direction
  for(int vi=0; vi<2; vi++)
    {
      interpolated_z[vi]= -1./8.*Interpolation(derivative_z[vi][0],
                                               derivative_z[vi][1]);

      interpolated_z[vi+2]= 9./8.*Interpolation(derivative_z[vi+2][0],
                                                derivative_z[vi+2][1]);
    }

  //summing the total derivative
  double  total_derivative=0.;
  for (int vi=0; vi<4; vi++)
    total_derivative +=interpolated_z[vi];


  return total_derivative;
}
