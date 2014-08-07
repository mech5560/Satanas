/*******************************************
 * Author: Michail Georgiou
 *  Last Modified: Time-stamp: <2014-05-20 12:19:13 mike_georgiou>
 *
 *
Intermediate_Velocity_Y.cpp -- This function computes the v_tilda of my
code. Firstly  the velocity residual is computed.
*
* Written on Tuesday, 29 April 2014.
********************************************/

#include"Intermediate_Velocity.h"

void Intermediate_Velocity_Y(double*** velocity_y_tilda,
                             double*** residual_y,
			     double*** residual_y_old,
                             double*** velocity_x, 
			     double*** velocity_y,
                             double*** velocity_z,
                             double*** flux_x, double***flux_y, 
			     double***flux_z,
                             double*** rho_new, double*** rho,
			     double*** temperature,
                             double Reynolds,double source,
                             double dx, double* dy,  double dz,
			     double dt, double time_total,
                             int ldx, int ldy, int ldz)
{

  Velocity_Residual_Y( residual_y,
                       velocity_x,  velocity_y, velocity_z,
                       flux_x, flux_y,  flux_z,
                       temperature, Reynolds,source,
                       dx, dy,  dz,
		       time_total,
                       ldx, ldy, ldz);


  /* After the calculation of the Velocity_Residual I will compute the Intermediate Velocity
     at the Grid*/


  for (int k=0; k<ldz; k++){
    for (int j=0; j<ldy; j++){
      for (int i=0; i<ldx; i++){


        velocity_y_tilda[k][j][i] = 
	  (rho[k][j][i]*velocity_y[k][j][i] +
	   dt*(1.5*residual_y[k][j][i] -
	       0.5*residual_y_old[k][j][i]) )
          /rho_new[k][j][i];



      }
    }
  }
}
