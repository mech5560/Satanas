/*******************************************
 * Author: Michail Georgiou
 *  Last Modified: Time-stamp: <2014-07-31 11:36:02 mike_georgiou>
 *
 *
Flux.cpp -- This programs computes the fluxes, with fourth order
accurate precision, in the X direction. The formula that is used to compute
these fluxes can be found at the Lessani-Papalexandris paper eq.63
*
* Written on Thursday, 17 April 2014.
********************************************/

#include "Flux_Evaluation.h"

void Flux_Evaluation_X(double*** flux_x, double*** velocity_x,
                       double*** rho, double*** pressure,
                       double dx, double dt,
                       int ldx, int ldy, int ldz)
{


  // I modified that manually BE CAREFULL
  for (int  k=0; k<ldz;   k++){
    for ( int  j=0; j<ldy;  j++){
      for (int   i=-1; i<ldx+1;  i++){


        flux_x[k][j][i] =

          9./8.*Interpolation(rho[k][j][i], velocity_x[k][j][i],
                              rho[k][j][i-1], velocity_x[k][j][i-1]) -
          1./8.*Interpolation(rho[k][j][i+1], velocity_x[k][j][i+1],
                              rho[k][j][i-2], velocity_x[k][j][i-2])

          -dt*(9./8.*Derivative(pressure[k][j][i],pressure[k][j][i-1], dx, 1) 
               -1./8.*Derivative(pressure[k][j][i+1],pressure[k][j][i-2], dx, 3));

      }
    }
  }

}
