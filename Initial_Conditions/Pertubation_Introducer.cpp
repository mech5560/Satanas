/*******************************************
 * Author: Michail Georgiou
 *  Last Modified: Time-stamp: <2014-05-20 09:35:48 mike_georgiou>
 *
 *
Pertubation_Introducer.cpp -- This program introduces pertubations to my
initial conditions
*
* Written on Friday, 16 May 2014.
********************************************/

#include"Pertubation_Introducer.h"

void Pertubation_Introducer(double*** velocity_x, double*** velocity_y,
                            double*** velocity_z,
                            double length_x, double length_y,
                            double length_z,
			    double dx, double *y, double dz,  
                            int ldx, int ldy, int ldz)
{


  double epsilon=1e-3;
  double dy_single=length_y/(2*ldy);

  double pi = 4.0*atan(1.);

  for (int k = 0; k < ldz; k++){

    double y_local=0.;
    for (int j = 0; j < ldy; j++){

	 y_local+=dy_single;

      double x_local=0.;
      for (int i = 0; i < ldx; i++){

  	 x_local += dx/2.;
	 velocity_x[k][j][i] = velocity_x[k][j][i]*

	   (1+ epsilon*sin(2.*pi*x_local/length_x)
	    *exp(-4*y[j]*y[j]));

	 x_local+=dx/2.;
	 

	 velocity_y[k][j][i]  = epsilon * exp(-4*y[j]*y[j]);
	   // *sin(2.*pi*y_local);



      }
      	 y_local+=dy_single;
    }
  }


}
