/*******************************************
 * Author: Michail Georgiou
 *  Last Modified: Time-stamp: <2014-06-06 16:36:34 mike_georgiou>
 *
 *
Maximum_Velocities.cpp -- This program computes the maximum velocity in
each component of the velocity field
*
* Written on Friday,  6 June 2014.
********************************************/

void Maximum_Velocities(double*** velocity_x, double*** velocity_y,
                        double*** velocity_z,
			double* u_max, double* v_max, double* w_max,
                        int ldx, int ldy, int ldz)
{
  //Initialization of the velocities
  *u_max=0.;   *v_max=0.;   *w_max=0.;

  for (int k = 0; k < ldz; k++){
    for (int j = 0; j < ldy; j++){
      for (int i = 0; i < ldx; i++){


	*u_max= 
	  *u_max>=velocity_x[k][j][i] ? *u_max:velocity_x[k][j][i];
	*v_max=
	  *v_max>=velocity_y[k][j][i] ? *v_max:velocity_y[k][j][i];

	*w_max=
	  *w_max>=velocity_z[k][j][i] ? *w_max:velocity_z[k][j][i];


      }
    }
  }


}
