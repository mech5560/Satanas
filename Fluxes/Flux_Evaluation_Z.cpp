/*******************************************
 * Author: Michail Georgiou
 *  Last Modified: Time-stamp: <2014-05-19 16:20:54 mike_georgiou>
 *
 *
Flux.cpp -- This programs computes the fluxes, with fourth order
accurate precision, in the Z direction. The formula that is used to compute
these fluxes can be found at the Lessani-Papalexandris paper eq.63
*
* Written on Thursday, 17 April 2014.
********************************************/

#include "Flux_Evaluation.h"


void Flux_Evaluation_Z(double*** flux_z, double*** velocity_z,
                       double*** rho, double*** pressure,
                       double dz, double dt,
                       int ldx, int ldy, int ldz)
{

  for (int  k=-1; k<ldz+1; k++){
    for (int  j=0; j<ldy; j++){
      for (int  i=0; i<ldx; i++){

        flux_z[k][j][i] =

          9./8.*Interpolation(rho[k][j][i], velocity_z[k][j][i],
                              rho[k-1][j][i], velocity_z[k-1][j][i]) -
          1./8.*Interpolation(rho[k+1][j][i], velocity_z[k+1][j][i],
                              rho[k-2][j][i], velocity_z[k-2][j][i])
          -
          dt*(9./8.*Derivative(pressure[k][j][i],pressure[k-1][j][i], dz, 1) -
              1./8.*Derivative(pressure[k+1][j][i],pressure[k-2][j][i], dz, 3));


      }
    }
  }

}
