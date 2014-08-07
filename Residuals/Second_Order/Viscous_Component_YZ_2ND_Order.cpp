/*******************************************
 * Author: Michail Georgiou
 *  Last Modified: Time-stamp: <2014-05-26 10:06:03 mike_georgiou>
 *
 *
Viscous_Component_YZ_2ND_Order.cpp -- This function computes the d/dy
 component
 of the Y-Momentum equation with second order accurate schemes.
 *
 * Written on Wednesday, 23 April 2014.
 ********************************************/

#include"Residuals.h"
#include"Residuals-inl.h"

double Viscous_Component_YZ_2ND_Order(double*** velocity_y,
                                      double*** velocity_z,
                                      double*** temperature,
                                      double Reynolds,
				      double* dy, double dz,
                                      int i, int j, int k)
{

  double derivative_z[2];
  //Calculation of the dv/dz component
  for (int vi=0; vi<2; vi++)
    {

      derivative_z[vi] = Derivative(velocity_y[k+vi][j][i],
                                    velocity_y[k+vi-1][j][i],
                                    dz, 1);
    }


  // Calculation of the dw/dy component
  // interpolating the velocities at k\pm 1/2 (j-1,j,j+1)
  double interpolation_y[3][2];

  for(int vk=0; vk<3; vk++){
    for(int vj=0; vj<2; vj++){

      interpolation_y[vk][vj] = 
	Interpolation_Y(velocity_y[k+vk-1][j+vj][i],dy[j+vj],
			velocity_y[k+vk-1][j+vj-1][i],dy[j+vj-1]);

    }
  }

  //computing the derivative du/dx at k-1,k,k+1
  double derivative_y[3], dy_total;
  for(int vi=0; vi<2; vi++){
    dy_total=dy[j+vi]+dy[j+vi-1];
    derivative_y[vi]= Derivative(interpolation_y[vi][1],
                                 interpolation_y[vi][0],
                                 dy_total, 1);
  }

  //interpolation in the x direction
  double final_derivative_y[2];
  for(int vi=0, vj=1; vi<2; vi++, vj++){

    final_derivative_y[vi]=  Interpolation(derivative_y[vj],
                                           derivative_y[vj-1]);
  }



  //Computing the viscosities.
  double viscosity[2];
  for (int vi=0; vi<2; vi++)
    {
      viscosity[vi]=
        Viscosity_Calculator(Interpolation(temperature[k][j+vi][i],
                                           temperature[k][j+vi-1][i]));
    }

  //Summing the X-component of the Viscous Term of the X-Momentum
  //equation
  double viscous_terms[2];
  for (int vi=0; vi<2; vi++)
    {
      viscous_terms[vi] =
        viscosity[vi]*
        (4./3.*derivative_y[vi]
         -2./3.*(final_derivative_x[vi]+final_derivative_z[vi]));
    }

  dy_total=2.*dy[j]
    double result =
    1./Reynolds*(1.*Derivative(viscous_terms[1],
                               viscous_terms[0],
                               dy_total,1));

  return result;
}
