/*******************************************
 * Author: Michail Georgiou
 *  Last Modified: Time-stamp: <2014-06-19 14:04:46 mike_georgiou>
 *
 *
Gradients.cpp -- This function will compute the gradients  velocity
components
*
* Written on Thursday, 19 June 2014.
********************************************/
#include "LES_Modelling.h"

void Gradients(double*** velocity,
               double* velocity_over_x,  double* velocity_over_y,
               double* velocity_over_z,
               int i, int j, int k,
               double dx, double* dy, double dz)
{


  //Derivative in the X direction
  *velocity_over_x+=4./3.*Derivative(velocity[k][j][i+1],
                                     velocity[k][j][i-1],
                                     dx,2);

  *velocity_over_x+=-1./3.*Derivative(velocity[k][j][i+2],
                                      velocity[k][j][i-2],
                                      dx,4);


  //Derivative in the Y direction

  // I need to interpolate the velocities along the y direction in
  //order to compute the desired velocity
  double interpolated_velocity[2];
  for (int vj=0; vj<2; vj++)
    {
      interpolated_velocity[vj]=
	Interpolation_Y(velocity[k][j+vj][i],dy[j+vj],
			velocity[k][j+vj-1][i],dy[j+vj-1]);
    }

  *velocity_over_y+=Derivative(interpolated_velocity[1],
                               interpolated_velocity[0],
                               2.*dy[j],1);


  //Derivative in the Z direction
  *velocity_over_z+=4./3.*Derivative(velocity[k+1][j][i],
                                     velocity[k-1][j][i],
                                     dz,2);

  *velocity_over_z+=-1./3.*Derivative(velocity[k+2][j][i],
                                      velocity[k-2][j][i],
                                      dz,4);


}
