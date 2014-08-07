/*******************************************
 * Author: Michail Georgiou
 *  Last Modified: Time-stamp: <2014-07-31 15:27:47 mike_georgiou>
 *
 *
Viscous_Component_ZZ.cpp -- This function computes the Z component of the velocity
residual of the Z momentum equation
*
* Written on Thursday, 24 April 2014.
********************************************/

#include"Residuals-inl.h"



double Viscous_Component_ZZ(double*** velocity_x, double*** velocity_y,
                            double*** velocity_z,
                            double*** temperature,
                            double*** eddy_viscosity,
                            double Reynolds,
                            double dx, double* dy, double dz,
                            int i, int j, int k)
{

  double derivative_zz[4][2],derivative_zx[4][4],derivative_zy[4][2],
    viscous_terms[4], viscosity[4], dy_total;


  //Calculation of the d/dz(dw/dz) component
  double total_derivative_z[4];
  for (int vi=0; vi<4; vi++)
    {

      derivative_zz[vi][0]=9./8.*Derivative(velocity_z[k+vi-1][j][i],
                                            velocity_z[k+vi-2][j][i],
                                            dz,1);

      derivative_zz[vi][1]=-1./8.*Derivative(velocity_z[k+vi][j][i],
                                             velocity_z[k+vi-3][j][i],
                                             dz,3);

      total_derivative_z[vi]=derivative_zz[vi][0]+derivative_zz[vi][1];

    }
  // Calculation of the d/dz(dv/dy) component

  //k-3/2
  dy_total=dy[j-1]+2.*dy[j]+dy[j+1];
  derivative_zy[0][0] =Derivative(velocity_y[k-3][j+1][i],
                                  velocity_y[k-3][j-1][i],
                                  dy_total, 1);

  dy_total=dy[j-1]+2.*dy[j]+dy[j+1];
  derivative_zy[0][1] =Derivative(velocity_y[k][j+1][i],
                                   velocity_y[k][j-1][i],
                                   dy_total, 1);

  //k-1/2
  dy_total=dy[j-1]+2.*dy[j]+dy[j+1];
  derivative_zy[1][0] = Derivative(velocity_y[k-1][j+1][i],
                                   velocity_y[k-1][j-1][i],
                                   dy_total, 1);
  derivative_zy[1][1] = derivative_zy[0][1];

  //k+1/2
  derivative_zy[2][0] = derivative_zy[0][1];
  dy_total=dy[j-1]+2.*dy[j]+dy[j+1];
  derivative_zy[2][1] = Derivative(velocity_y[k+1][j+1][i],
                                   velocity_y[k+1][j-1][i],
                                   dy_total, 1);

  //k+3/2
  derivative_zy[3][0] = derivative_zy[0][1];
  dy_total=dy[j-1]+2.*dy[j]+dy[j+1];
  derivative_zy[3][1] = Derivative(velocity_y[k+3][j+1][i],
                                   velocity_y[k+3][j-1][i],
                                   dy_total, 1);

  double total_derivative_y[4];
  for (int vi=0; vi<4; vi++)
    {
      //intializing the vector
      total_derivative_y[vi]=0.;
      for (int vj=0; vj<2; vj++)
        {
          total_derivative_y[vi]+=derivative_zy[vi][vj];
        }
    }


  // Calculation of the d/dz(du/dx) component

  //k-3/2
  //k-3
  //delta_1
  derivative_zx[0][0] = 4./(3.)*Derivative(velocity_x[k-3][j][i+1],
                                           velocity_x[k-3][j][i-1],
                                           dx,2);
  //delta_2
  derivative_zx[0][1] = -1./(3.)*Derivative(velocity_x[k-3][j][i+2],
                                            velocity_x[k-3][j][i-2],
                                            dx,4);
  //k
  //delta_1
  derivative_zx[0][2] = 4./(3.)*Derivative(velocity_x[k][j][i+1],
                                           velocity_x[k][j][i-1],
                                           dx,2);
  //delta_2
  derivative_zx[0][3] = -1./(3.)*Derivative(velocity_x[k][j][i+2],
                                            velocity_x[k][j][i-2],
                                            dx,4);
  //k-1/2//
  //k-1
  //\delta_1
  derivative_zx[1][0] = 4./(3.)*Derivative(velocity_x[k-1][j][i+1],
                                           velocity_x[k-1][j][i-1],
                                           dx,2);
  //\delta_2
  derivative_zx[1][1] = -1./(3.)*Derivative(velocity_x[k-1][j][i+2],
                                            velocity_x[k-1][j][i-2],
                                            dx,4);
  //k
  //\delta_1
  derivative_zx[1][2]=derivative_zx[0][2];
  //\delta_2
  derivative_zx[1][3]=derivative_zx[0][3];


  /// k+1/2//
  //k
  //\delta_1
  derivative_zx[2][0] = derivative_zx[0][2];
  //delta_2
  derivative_zx[2][1] = derivative_zx[0][3];

  //k+1
  //delta_1
  derivative_zx[2][2] = 4./(3.)*Derivative(velocity_x[k+1][j][i+1],
                                           velocity_x[k+1][j][i-1],
                                           dx,2);
  //\delta_2
  derivative_zx[2][3] = -1./(3.)*Derivative(velocity_x[k+1][j][i+2],
                                            velocity_x[k+1][j][i-2],
                                            dx,4);

  //k+3/2//
  //k
  //delta_1
  derivative_zx[3][0] = derivative_zx[0][2];
  //delta_2
  derivative_zx[3][1] = derivative_zx[0][3];
  //i+3
  //delta_1
  derivative_zx[3][2] = 4./(3.)*Derivative(velocity_x[k+3][j][i+1],
                                           velocity_x[k+3][j][i-1],
                                           dx,2);
  //delta_2
  derivative_zx[3][3] = -1./(3.)*Derivative(velocity_x[k+3][j][i+2],
                                            velocity_x[k+3][j][i-2],
                                            dx,4);

  double total_derivative_x[4];
  for (int vi=0; vi<4; vi++)
    {
      total_derivative_x[vi]=0.;
      for (int vj=0; vj<4; vj++)
        {
          total_derivative_x[vi]+=derivative_zx[vi][vj];
        }
    }



  //Computing the viscosities.
  for (int vi=-2, vj=0; vi<2; vi++, vj++)
    {
      viscosity[vj]=
        Viscosity_Calculator(Interpolation(temperature[k+vi+1][j][i],
                                           temperature[k+vi][j][i]))
        +Interpolation(eddy_viscosity[k+vi+1][j][i],
                       eddy_viscosity[k+vi][j][i]);
    }

  //Summing the X-component of the Viscous Term of the X-Momentum
  //equation
  for (int vi=0; vi<4; vi++)
    {
      viscous_terms[vi] =
        viscosity[vi]*(4./3.*total_derivative_z[vi]
                       -2./6.*(total_derivative_y[vi]+
                               total_derivative_x[vi]));
    }

  double viscous_term =
    1./Reynolds*(9./8.*Derivative(viscous_terms[2],
                                  viscous_terms[1],
                                  dz,1)-
                 1./8.*Derivative(viscous_terms[3],
                                  viscous_terms[0],
                                  dz,3));

  return viscous_term;
}
