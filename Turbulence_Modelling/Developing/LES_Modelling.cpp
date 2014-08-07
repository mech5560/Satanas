/*******************************************
 * Author: Michail Georgiou
 *  Last Modified: Time-stamp: <2014-07-04 09:31:33 mike_georgiou>
 *
 *
LES_Modeling.cpp -- This code will generate  the desired
infomation in order to perform LES modelling to the turbulent channel
flow.
*
* Written on Thursday, 19 June 2014.
********************************************/

#include "LES_Modelling.h"

void LES_Modelling(double*** eddy_viscosity,
		   double*** velocity_x,
		   double*** velocity_y, double*** velocity_z,
		   double*** rho,
		   double dx, double* dy, double dz,
		   int ldx, int ldy, int ldz)
{

  for (int k = 0; k < ldz; k++){
    for (int j = 0; j < ldy; j++){
      for (int i = 0; i < ldx; i++){

        // These are the variables that the derivatives will be saved in
        //  order to  compute the filtered rate of strain which is necessary
        //  to compute the eddy viscosity based on the Smagorinsky model

        double u_over_x=0., u_over_y=0., u_over_z=0.,
          v_over_x=0., v_over_y=0., v_over_z=0.,
          w_over_x=0., w_over_y=0., w_over_z=0.;


        //Computing the Gradients of the x component of the velocity
        Gradients(velocity_x,
                  &u_over_x, &u_over_y, &u_over_z,
                  i, j, k,
                  dx, dy, dz);

        //Computing the Gradients of the y component of the velocity
        Gradients(velocity_y,
                  &v_over_x, &v_over_y, &v_over_z,
                  i, j, k,
                  dx, dy, dz);

        //Computing the Gradients of the z component of the velocity
        Gradients(velocity_z,
                  &w_over_x, &w_over_y, &w_over_z,
                  i, j, k,
                  dx, dy, dz);


	// Characteristic filtered rate of strain	
	double char_filtered_strain=
	  2.*(u_over_x*u_over_x + v_over_y*v_over_y 
	      +w_over_z*w_over_z + u_over_y*v_over_x + u_over_z*w_over_x
	      +v_over_z*w_over_y);
	
	char_filtered_strain+=
	  u_over_y*u_over_y + v_over_x*v_over_x + u_over_z*u_over_z 
	  +w_over_x*w_over_x + v_over_z*v_over_z + w_over_y*w_over_y;
	

	char_filtered_strain = sqrt(char_filtered_strain);
	

	// Computing the (Smagarinsky length)^2
	double C_s =0.12;
	double width_square =dx*dx + dy[j]*dy[j] + dz*dz; 
	double length_square = C_s*C_s * width_square;


	//Computing the eddy viscosity	
	eddy_viscosity[k][j][i] =  length_square * char_filtered_strain*rho[k][j][i]; 

      }
    }
  }

}
