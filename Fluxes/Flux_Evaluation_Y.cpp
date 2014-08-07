/*******************************************
 * Author: Michail Georgiou
 *  Last Modified: Time-stamp: <2014-07-31 11:41:01 mike_georgiou>
 *
 *
Flux.cpp -- This programs computes the fluxes, with second order
accurate precision, in the Y direction. The formula that is used to compute
these fluxes can be found at the Lessani-Papalexandris paper eq.51.

In this case, second order accurate scheme is chosen because I have a
non-uniform grid in this direction.
*
* Written on Thursday, 17 April 2014.
********************************************/


#include "Flux_Evaluation_Y.h"
#include "../Header_Files/Data.h"

void Flux_Evaluation_Y(double*** flux_y, double*** velocity_y,
                       double*** rho, double*** pressure,
                       double* dy, double dt,
                       int ldx, int ldy, int ldz)
{
  for (int k=0; k<ldz;  k++){
    for (int j=0; j<ldy; j++){
      for (int i=0; i<ldx; i++){

        flux_y[k][j][i] =
          Interpolation_Y(rho[k][j][i], velocity_y[k][j][i],dy[j],
                          rho[k][j-1][i], velocity_y[k][j-1][i],dy[j-1])
          -
          dt* Derivative_Y(pressure[k][j][i], dy[j],
                           pressure[k][j-1][i], dy[j-1]);


      }
    }
  }

}
