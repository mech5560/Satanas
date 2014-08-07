/*******************************************
 * Author: Michail Georgiou
 *  Last Modified: Time-stamp: <2014-07-31 14:19:25 mike_georgiou>
 *
 *
Viscous_Component_XX.cpp -- This function computes the d/dx component of the
X-Momentum equation.
*
* Written on Wednesday, 23 April 2014.
********************************************/
#include"Residuals-inl.h"

double Viscous_Component_XX(double*** velocity_x, double*** velocity_y,
                            double*** velocity_z,
                            double*** temperature,
                            double*** eddy_viscosity,
                            double Reynolds,
                            double dx, double* dy, double dz,
                            int i, int j, int k)
{

  double derivative_xx[4][2],derivative_xz[4][4],derivative_xy[4][2],
    viscous_terms[4], viscosity[4], dy_total=0.;

  //Calculation of the du/dx component
  for (int vi=0; vi<4; vi++)
    {
      derivative_xx[vi][0] = 9./(8.)*Derivative(velocity_x[k][j][i+vi-1],
                                                velocity_x[k][j][i+vi-2],
                                                dx, 1);

      derivative_xx[vi][1] =-1./(8.)*Derivative(velocity_x[k][j][i+vi],
                                                velocity_x[k][j][i+vi-3],
                                                dx, 3);
    }


  double total_derivative_x[4];
  for (int vi=0; vi<4; vi++)
    {
      //initializing the vector
      total_derivative_x[vi]=0.;
      for (int vj=0; vj<2; vj++)
        {
          total_derivative_x[vi]+=derivative_xx[vi][vj];
        }
    }

  // Calculation of the dv/dy component
  // i-3/2
  dy_total=dy[j-1]+2.*dy[j]+dy[j+1];
  derivative_xy[0][0] =Derivative(velocity_y[k][j+1][i-3],
                                  velocity_y[k][j-1][i-3],
                                  dy_total, 1);

  dy_total=dy[j-1]+2.*dy[j]+dy[j+1];
  derivative_xy[0][1] =Derivative(velocity_y[k][j+1][i],
                                  velocity_y[k][j-1][i],
                                  dy_total, 1);

  //i-1/2
  dy_total=dy[j-1]+2.*dy[j]+dy[j+1];
  derivative_xy[1][0] = Derivative(velocity_y[k][j+1][i-1],
                                   velocity_y[k][j-1][i-1],
                                   dy_total, 1);
  derivative_xy[1][1] = derivative_xy[0][1];

  //i+1/2
  derivative_xy[2][0] = derivative_xy[0][1];

  dy_total=dy[j-1]+2.*dy[j]+dy[j+1];
  derivative_xy[2][1] = Derivative(velocity_y[k][j+1][i+1],
                                   velocity_y[k][j-1][i+1],
                                   dy_total, 1);

  //i+3/2
  derivative_xy[3][0] = derivative_xy[0][1];

  dy_total=dy[j-1]+2.*dy[j]+dy[j+1];
  derivative_xy[3][1] = Derivative(velocity_y[k][j+1][i+3],
                                   velocity_y[k][j-1][i+3],
                                   dy_total, 1);

  double total_derivative_y[4];
  for (int vi=0; vi<4; vi++)
    {
      //intializing the vector
      total_derivative_y[vi]=0.;
      for (int vj=0; vj<2; vj++)
        {
          total_derivative_y[vi]+=derivative_xy[vi][vj];
        }
    }

  // Calculation of the dw/dz component

  //delta_1
  derivative_xz[0][0] = 4./(3.)*Derivative(velocity_z[k+1][j][i-3],
                                           velocity_z[k-1][j][i-3],
                                           dz,2);
  //delta_2
  derivative_xz[0][1] = -1./(3.)*Derivative(velocity_z[k+2][j][i-3],
                                            velocity_z[k-2][j][i-3],
                                            dz,4);
  //delta_1
  derivative_xz[0][2] = 4./(3.)*Derivative(velocity_z[k+1][j][i],
                                           velocity_z[k-1][j][i],
                                           dz,2);
  //delta_2
  derivative_xz[0][3] = -1./(3.)*Derivative(velocity_z[k+2][j][i],
                                            velocity_z[k-2][j][i],
                                            dz,4);
  //i-1/2//
  //i-1
  //\delta_1
  derivative_xz[1][0] = 4./(3.)*Derivative(velocity_z[k+1][j][i-1],
                                           velocity_z[k-1][j][i-1],
                                           dz,2);
  //\delta_2
  derivative_xz[1][1] = -1./(3.)*Derivative(velocity_z[k+2][j][i-1],
                                            velocity_z[k-2][j][i-1],
                                            dz,4);
  //i
  //\delta_1
  derivative_xz[1][2]=derivative_xz[0][2];
  //\delta_2
  derivative_xz[1][3]=derivative_xz[0][3];


  /// i+1/2//
  //i//
  //\delta_1
  derivative_xz[2][0] = derivative_xz[0][2];
  //delta_2
  derivative_xz[2][1] = derivative_xz[0][3];
  //i+1
  //delta_1
  derivative_xz[2][2] = 4./(3.)*Derivative(velocity_z[k+1][j][i+1],
                                           velocity_z[k-1][j][i+1],
                                           dz,2);
  //\delta_2
  derivative_xz[2][3] = -1./(3.)*Derivative(velocity_z[k+2][j][i+1],
                                            velocity_z[k-2][j][i+1],
                                            dz,4);

  //i+3/2//
  //i
  //delta_1
  derivative_xz[3][0] = derivative_xz[0][2];
  //delta_2
  derivative_xz[3][1] = derivative_xz[0][3];
  //i+3
  //delta_1
  derivative_xz[3][2] = 4./(3.)*Derivative(velocity_z[k+1][j][i+3],
                                           velocity_z[k-1][j][i+3],
                                           dz,2);
  //delta_2
  derivative_xz[3][3] = -1./(3.)*Derivative(velocity_z[k+2][j][i+3],
                                            velocity_z[k-2][j][i+3],
                                            dz,4);

  double total_derivative_z[4];
  for (int vi=0; vi<4; vi++)
    {
      //initializing the vector
      total_derivative_z[vi]=0.;
      for (int vj=0; vj<4; vj++)
        {
          total_derivative_z[vi]+=derivative_xz[vi][vj];
        }
    }


  //Computing the viscosities.
  for (int vi=-2, vj=0; vi<2; vi++, vj++)
    {
      viscosity[vj]=
        Viscosity_Calculator(Interpolation(temperature[k][j][i+vi+1],
                                           temperature[k][j][i+vi]))

        +Interpolation(eddy_viscosity[k][j][i+vi+1],
                       eddy_viscosity[k][j][i+vi]);

      // I added the eddy viscosity in order to simulate turbulence
    }

  //Summing the X-component of the Viscous Term of the X-Momentum
  //equation
  for (int vi=0; vi<4; vi++)
    {
      viscous_terms[vi] =viscosity[vi]*(4./3.*total_derivative_x[vi]
                                        -2./6.*(total_derivative_y[vi]+
                                                total_derivative_z[vi]));
    }


  double viscous_term =
    1./Reynolds*(9./8.*Derivative(viscous_terms[2],
                                  viscous_terms[1],
                                  dx,1)
                 -1./8.*Derivative(viscous_terms[3],
                                   viscous_terms[0],
                                   dx,3));


  return viscous_term;
}
