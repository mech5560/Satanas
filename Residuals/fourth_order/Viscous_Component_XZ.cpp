/*******************************************
 * Author: Michail Georgiou
 *  Last Modified: Time-stamp: <2014-07-30 16:40:15 mike_georgiou>
 *
 *
Viscous_Component_XY.cpp -- This function computes the viscous
component of the X-Momentum equation
*
* Written on Wednesday, 23 April 2014.
********************************************/

#include"Residuals-inl.h"


double Viscous_Component_XZ(double*** velocity_x, double*** velocity_z,
                            double*** temperature,
                            double*** eddy_viscosity,
                            double Reynolds,
                            double dx, double dz,
                            int i, int j, int k)
{

  double derivative_zz[4][2], derivative_zx[4][4],
    viscosity[4], viscous_terms[4];

  // Calculation of the (du/dz) component
  double total_derivative_z[4];
  for (int vi=0; vi<4; vi++)
    {

      derivative_zz[vi][0] = 9./(8.)*Derivative(velocity_x[k+vi-1][j][i],
                                                velocity_x[k+vi-2][j][i],
                                                dz,1);

      derivative_zz[vi][1] = -1./(8.)*Derivative(velocity_x[k+vi][j][i],
                                                 velocity_x[k+vi-3][j][i],
                                                 dz,3);

      //initalizing the vector
      total_derivative_z[vi]=0.;
      for (int vj=0; vj<2; vj++)
        total_derivative_z[vi]+=derivative_zz[vi][vj];

    }

  // Calculation of the (dw/dx) component
  // k-3/2//
  // k-3
  //\delta_1
  derivative_zx[0][0] = 4./(3.)*Derivative(velocity_z[k-3][j][i+1],
                                           velocity_z[k-3][j][i-1],
                                           dx,2);
  //\delta_2
  derivative_zx[0][1] = -1./(3.)*Derivative(velocity_z[k-3][j][i+2],
                                            velocity_z[k-3][j][i-2],
                                            dx,4);
  // k
  derivative_zx[0][2] = 4./(3.)*Derivative(velocity_z[k][j][i+1],
                                           velocity_z[k][j][i-1],
                                           dx,2);
  //\delta_2
  derivative_zx[0][3] = -1./(3.)*Derivative(velocity_z[k][j][i+2],
                                            velocity_z[k][j][i-2],
                                            dx,4);

  //k-1/2//
  //k-1
  //\delta_1
  derivative_zx[1][0] = 4./(3.)*Derivative(velocity_z[k-1][j][i+1],
                                           velocity_z[k-1][j][i-1],
                                           dx,2);
  //\delta_2
  derivative_zx[1][1] = -1./(3.)*Derivative(velocity_z[k-1][j][i+2],
                                            velocity_z[k-1][j][i-2],
                                            dx,4);
  //k
  //\delta_1
  derivative_zx[1][2]=derivative_zx[0][2];
  //\delta_2
  derivative_zx[1][3]=derivative_zx[0][3];


  // k+1/2
  //k
  //\delta_1
  derivative_zx[2][0] = derivative_zx[0][2];
  //\delta_2
  derivative_zx[2][1] = derivative_zx[0][3];

  //k+1
  //\delta_1
  derivative_zx[2][2] = 4./(3.)*Derivative(velocity_z[k+1][j][i+1],
                                           velocity_z[k+1][j][i-1],
                                           dx,2);
  //\delta_2
  derivative_zx[2][3] = -1./(3.)*Derivative(velocity_z[k+1][j][i+2],
                                            velocity_z[k+1][j][i-2],
                                            dx,4);

  //k+3/2
  //k
  //\delta_1
  derivative_zx[3][0] = derivative_zx[0][2];
  //\delta_2
  derivative_zx[3][1] = derivative_zx[0][3];
  //k+3
  //\delta_1
  derivative_zx[3][2] = 4./(3.)*Derivative(velocity_z[k+3][j][i+1],
                                           velocity_z[k+3][j][i-1],
                                           dx,2);
  //\delta_2
  derivative_zx[3][3] = -1./(3.)*Derivative(velocity_z[k+3][j][i+2],
                                            velocity_z[k+3][j][i-2],
                                            dx,4);

  //summing up the components
  double total_derivative_x[4];
  for (int vi=0; vi<4; vi++)
    {
      //initializing the vector
      total_derivative_x[vi]=0.;

      for (int vj=0; vj<4; vj++)
        {
          total_derivative_x[vi]+=derivative_zx[vi][vj];
        }
    }


  // Calculating the components of the total residular Res_Visc_Total[2]//
  for (int vi=-2, vj=0; vi<2; vi++, vj++)
    {
      viscosity[vj]=
        Viscosity_Calculator(Interpolation(temperature[k+vi+1][j][i],
                                           temperature[k+vi][j][i]))

        +Interpolation(eddy_viscosity[k+vi+1][j][i],
                       eddy_viscosity[k+vi][j][i]);

      // I added the eddy viscosity in order to simulate turbulence
    }




  for (int vi=0; vi<4; vi++)
    {
      viscous_terms[vi]=viscosity[vi]*(total_derivative_z[vi]
                                       +total_derivative_x[vi]/2.);

    }

  double   viscous_component =
    1./Reynolds*( 9./8.*Derivative(viscous_terms[2],
                                   viscous_terms[1],
                                   dz,1)-
                  1./8.*Derivative(viscous_terms[3],
                                   viscous_terms[0],
                                   dz,3));



  return viscous_component;
}
