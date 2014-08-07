/*******************************************
 * Author: Michail Georgiou
 *  Last Modified: Time-stamp: <2014-08-07 13:47:07 mike_georgiou>
 *
 *
Right_Hand_Side_Poisson.cpp -- This program computes the rhs of the poisson equation
of my code. The scheme that  I am using is presented in the
lessani-papalexandris paper, more specifically eq.66. In the vertical direction,
where the scheme is non-uniform i am using second order accurate scheme
*
* Written on Friday, 25 April 2014.
********************************************/
#include "Right_Hand_Side_Poisson.h"
#include "RHS.h"
#include <iostream>
#include <stdio.h>

using namespace std;
void Right_Hand_Side_Poisson(double* rhs, double*** velocity_x,
                             double*** velocity_y, double*** velocity_z,
                             double*** rho_new, double*** rho,double*** rho_old,
                             double dx, double* dy, double dz,
                             double dt,
                             int ldx, int ldy, int ldz)
{
  double density_derivative, derivative[3], divergence;


  for (int k=0; k<ldz; k++){
    for (int j=0; j<ldy; j++){
      for (int i=0; i<ldx; i++){

        //Calculation of the time derivative of the Density

        // density_derivative =(3.0*rho_new[k][j][i]-4.0*rho[k][j][i]
        //                     +1.0*rho_old[k][j][i])/(2.*dt);

        //First Order, Just for Checking
        density_derivative = (rho_new[k][j][i]-rho[k][j][i])/(dt);

        //Divergence X-Component
        derivative[0]=Divergence_X(velocity_x,rho_new,
                                   dx,
                                   i, j, k);


        derivative[1]=Divergence_Y(velocity_y,rho_new,
                                   dy,
                                   i,j,k);


        derivative[2]=Divergence_Z(velocity_z,rho_new,
                                   dz,
                                   i, j, k);

        divergence=0.;
        for (int vi=0; vi<3; vi++)
          divergence+=derivative[vi];


        int index= A(i,ldx,
                     j, ldy,
                     k,ldz);

        double result=(density_derivative+divergence)/dt;

        rhs[index+1] = result;


      }
    }
  }
}
