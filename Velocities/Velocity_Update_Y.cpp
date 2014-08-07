/*******************************************
 * Author: Michail Georgiou
 *  Last Modified: Time-stamp: <2014-05-26 15:07:37 mike_georgiou>
 *
 *
Velocity_Update_Y.cpp -- This function updates the velocity based on eq.64 of
the lessani-papalexandris paper
*
* Written on Tuesday, 29 April 2014.
********************************************/

#include "Velocity_Update.h"


void Velocity_Update_Y(double*** velocity_y, double*** velocity_y_tilda,
                       double*** rho, double*** pressure,
                       double* dy, double dt,
                       int ldx, int ldy, int ldz)
{

  for (int k=0; k<ldz; k++){
    for (int j=0; j<ldy; j++){
      for (int i=0; i<ldx; i++){

        double dy_total=dy[j+1] +2.*dy[j]+ dy[j-1];

        velocity_y[k][j][i] = velocity_y_tilda[k][j][i]
          -dt/rho[k][j][i]*Derivative(pressure[k][j+1][i],
                                      pressure[k][j-1][i],
                                      dy_total,1);



      }
    }
  }
}
