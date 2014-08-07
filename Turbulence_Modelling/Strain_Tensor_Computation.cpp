/*******************************************
 * Author: Michail Georgiou 
*  Last Modified: Time-stamp: <2014-06-19 16:03:15 mike_georgiou>   
*
*
Strain_Tensor_Computation.cpp -- This Function will compute the Strain Tensor
which is necessary for the implementation of the Smagarinsky model.
*
* Written on Thursday, 19 June 2014.
********************************************/

#include "LES_Modelling.h"

void Strain_Tensor_Computation(double*** strain_tensor,
			       double*** velocity_x, 
			       double*** velocity_y,
			       double*** velocity_z,
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

	// In this array, the necessary quantities
        // for the computation of the mean  strain tensor will be
        //stored 
	double result[3]; 
	
        result[0]= u_over_x + u_over_y + u_over_z;


        //Computing the Gradients of the y component of the velocity
        Gradients(velocity_y,
                  &v_over_x, &v_over_y, &v_over_z,
                  i, j, k,
                  dx, dy, dz);

        result[1]= v_over_x + v_over_y + v_over_z;



        //Computing the Gradients of the z component of the velocity
        Gradients(velocity_z,
                  &w_over_x, &w_over_y, &w_over_z,
                  i, j, k,
                  dx, dy, dz);

        result[2]=  w_over_x +w_over_y + w_over_z;

	strain_tensor[k][j][i]=0.;
	for(int vi=0; vi<4; vi++)
	  {
	    strain_tensor[k][j][i] +=result[vi];
	  }

      }
    }
  }


}
