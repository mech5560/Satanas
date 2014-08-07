/*******************************************
 * Author: Michail Georgiou
 *  Last Modified: Time-stamp: <2014-08-04 14:33:25 mike_georgiou>
 *
 *
Viscous_Component_XX_2ND_Order.cpp -- This function computes the d/dx
 component
 of the X-Momentum equation with second order accurate schemes.
 *
 * Written on Wednesday, 23 April 2014.
 ********************************************/

#include"Residuals.h"
#include"Residuals-inl.h"

double Viscous_Component_XX_2ND_Order(double*** velocity_x,
                                      double*** velocity_y,
                                      double*** velocity_z,
                                      double*** temperature,
                                      double Reynolds,
                                      double dx, double* dy, double dz,
                                      int i, int j, int k)
{

  double derivative_x[2];

  //Calculation of the du/dx component
  for (int vi=0; vi<2; vi++)
    {
      derivative_x[vi] = Derivative(velocity_x[k][j][i+vi],
                                    velocity_x[k][j][i+vi-1],
                                    dx, 1);
    }


  // Calculation of the dv/dy component
  double interpolation_y[3][2];

  for(int vi=0; vi<3; vi++){
    for(int vj=0; vj<2; vj++){

      interpolation_y[vi][vj] = Interpolation_Y(velocity_y[k][j+vj][i+vi-1],
                                                dy[j+vj],
                                                velocity_y[k][j+vj-1][i+vi-1],
                                                dy[j+vj-1]);
    }
  }

  double derivative_xy[3];
  for(int vi=0; vi<3; vi++){

    double dy_total=2.*dy[j-1+vi];
    derivative_xy[vi]= Derivative(interpolation_y[vi][1],
                                  interpolation_y[vi][0],
                                  dy_total, 1);
  }

  //interpolation in the x direction
  double final_derivative_y[2];
  for(int vi=0, vj=1; vi<2; vi++, vj++){

    final_derivative_y[vi]=  Interpolation(derivative_xy[vj],
                                           derivative_xy[vj-1]);
  }


  double interpolation_z[3][2];

  for(int vi=0; vi<3; vi++){
    for(int vk=0; vk<2; vk++){

      interpolation_z[vi][vk] = Interpolation(velocity_z[k+vk][j][i+vi-1],
                                              velocity_z[k+vk-1][j][i+vi-1]);

    }
  }

  double derivative_xz[3];
  for(int vi=0; vi<3; vi++){

    derivative_xz[vi]= Derivative(interpolation_z[vi][1],
                                  interpolation_z[vi][0],
                                  dz,1);
  }


  double final_derivative_z[2];
  for(int vi=0, vj=1; vi<2; vi++, vj++){

    final_derivative_z[vi]=  Interpolation(derivative_xz[vj],
                                           derivative_xz[vj-1]);
  }

  //Computing the viscosities.
  double viscosity[2];
  for (int vi=0; vi<2; vi++)
    {
      viscosity[vi]=
        Viscosity_Calculator(Interpolation(temperature[k][j][i+vi],
                                           temperature[k][j][i+vi-1]));
    }

  //Summing the X-component of the Viscous Term of the X-Momentum
  //equation
  double viscous_terms[2];
  for (int vi=0; vi<2; vi++)
    {
      viscous_terms[vi] =viscosity[vi]*(4./3.*derivative_x[vi]
                                        -2./3.*(final_derivative_y[vi]+
                                                final_derivative_z[vi]));
    }


  double result =
    1./Reynolds*(1.*Derivative(viscous_terms[1],
                               viscous_terms[0],
                               dx,1));

  return result;
}
