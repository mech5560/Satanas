/*******************************************
 * Author: Michail Georgiou
 * Last Modified: Time-stamp: <2014-06-02 10:52:38 mike_georgiou>
 *
 *
Intermediate_Velocity_X.cpp -- This function computes the u_tilda of
my
code. Firstly the velocity residual is computed.
*
* Written on Tuesday, 29 April 2014.
********************************************/


#include"Intermediate_Velocity.h"

void Intermediate_Velocity_X(double*** velocity_x_tilda,
                             double*** residual_x,
                             double*** residual_x_old,
                             double*** velocity_x,
                             double*** velocity_y,
                             double*** velocity_z,
                             double*** flux_x, double***flux_y,
                             double***flux_z,
                             double*** rho_new, double*** rho,
                             double*** temperature,
                             double Reynolds,double source,
                             double dx, double* dy, double dz,
                             double dt, double time_total,
                             int ldx, int ldy, int ldz)
{

  //At first I will calculate the Velocity Residual
  Velocity_Residual_X( residual_x,
                       velocity_x, velocity_y, velocity_z,
                       flux_x, flux_y, flux_z,
                       temperature, Reynolds,
                       source,
                       dx, dy, dz,
                       time_total,
                       ldx, ldy, ldz);


  //After the calculation of the Velocity_Residual I will compute the
  //Intermediate Velocity
  for (int k=0; k<ldz; k++){
    for (int j=0; j<ldy; j++){
      for (int i=0; i<ldx; i++){

        velocity_x_tilda[k][j][i] =

          ((rho[k][j][i]*velocity_x[k][j][i] +
            dt*(1.5*residual_x[k][j][i] -
                0.5*residual_x_old[k][j][i] ) )
           / rho_new[k][j][i]);

      }
    }
  }


}
