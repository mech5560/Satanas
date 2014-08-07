/*******************************************
 * Author: Michail Georgiou
 *  Last Modified: Time-stamp: <2014-05-26 09:50:46 mike_georgiou>
 *
 *
Viscous_Component_YY_2ND_Order.cpp -- This function computes the d/dy
 component
 of the Y-Momentum equation with second order accurate schemes.
 *
 * Written on Wednesday, 23 April 2014.
 ********************************************/

#include"Residuals.h"
#include"Residuals-inl.h"

double Viscous_Component_YY_2ND_Order(double*** velocity_x,
                                      double*** velocity_y,
                                      double*** velocity_z,
                                      double*** temperature,
                                      double Reynolds,
                                      double dx, double* dy, double dz,
                                      int i, int j, int k)
{

  double derivative_y[2], dy_total;

  //Calculation of the du/dy component
  for (int vi=0; vi<2; vi++)
    {
      dy_total= dy[j+vi]+dy[j+vi-1];
      derivative_y[vi] = Derivative(velocity_y[k][j+vi][i],
                                    velocity_y[k][j+vi-1][i],
                                    dy_total, 1);
    }


  // Calculation of the du/dx component
  // interpolating the velocities at j\pm 1/2 (i-1,i,i+1)
  double interpolation_x[3][2];

  for(int vj=0; vj<3; vj++){
    for(int vi=0; vi<2; vi++){

      interpolation_x[vj][vi] = Interpolation(velocity_x[k][j+vj-1][i+vi],
                                              velocity_x[k][j+vj-1][i+vi-1]);

    }
  }

  //computing the derivative du/dx at j-1,j,j+1
  double derivative_x[3];
  for(int vi=0; vi<3; vi++){

    derivative_x[vi]= Derivative(interpolation_x[vi][1],
                                 interpolation_x[vi][0],
                                 dx, 1);
  }

  //interpolation in the x direction
  double final_derivative_x[2];
  for(int vi=0, vj=1; vi<2; vi++, vj++){

    final_derivative_x[vi]=  Interpolation_Y(derivative_x[vj],dy[j]
					     derivative_x[vj-1],dy[j]);
  }



  // Calculation of the dw/dz component
  // interpolating the velocities at j\pm 1/2 (k-1,k,k+1)
  double interpolation_z[3][2];

  for(int vj=0; vj<3; vj++){
    for(int vk=0; vk<2; vk++){

      interpolation_z[vj][vk] = Interpolation(velocity_z[k+vk][i+vj-1][j],
                                              velocity_z[k+vk-1][j+vj-1][i]);

    }
  }

  //computing the derivative dw/dz at j-1,j,j+1
  double derivative_z[3];
  for(int vk=0; vk<3; vk++){

    derivative_z[vk]= Derivative(interpolation_z[vk][1],
                                 interpolation_z[vk][0],
                                 dz, 1);
  }

  //interpolation in the x direction
  double final_derivative_z[2];
  for(int vi=0, vj=1; vi<2; vi++, vj++){

    final_derivative_z[vi]=  Interpolation_Y(derivative_z[vj],dy[j],
					     derivative_z[vj-1], dy[j]);
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
