/*******************************************
 * Author: Michail Georgiou
 *  Last Modified: Time-stamp: <2014-05-26 15:07:31 mike_georgiou>
 *
 *
Velocity_Update_X.cpp -- This function updates the velocity based on eq.64 of
the lessani-papalexandris paper
*
* Written on Tuesday, 29 April 2014.
********************************************/


#include "Velocity_Update.h"

void Velocity_Update_X(double*** velocity_x, double*** velocity_x_tilda,
                       double*** rho, double*** pressure,
                       double dx, double dt,
                       int ldx, int ldy, int ldz)
{
  for (int k=0; k<ldz; k++){
    for (int j=0; j<ldy; j++){
      for (int i=0; i<ldx; i++){


        velocity_x[k][j][i] = velocity_x_tilda[k][j][i]
          -dt/rho[k][j][i]*
          ( (4./3.)*Derivative(pressure[k][j][i+1],pressure[k][j][i-1],
                               dx,2)
            -(1./3.)*Derivative(pressure[k][j][i+2],pressure[k][j][i-2],
                                dx,4));


      }
    }
  }
}
