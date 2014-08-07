/*******************************************
 * Author: Michail Georgiou
 *  Last Modified: Time-stamp: <2014-07-31 14:43:02 mike_georgiou>
 *
 *
Viscous_Component_YX.cpp -- This function computes the x component of the viscous
term of the momentoum equation
*
* Written on Wednesday, 23 April 2014.
********************************************/
#include"Residuals-inl.h"

double Viscous_Component_YX(double*** velocity_x, double*** velocity_y,
                            double*** temperature,
                            double*** eddy_viscosity,
                            double Reynolds,
                            double dx, double* dy,
                            int i, int j, int k)
{

  double  derivative_xx[4][2], derivative_xy[4][2];
  double dy_total,  viscous_terms[4];

  // Calculation of the (dv/dx) component
  double total_derivative_x[4];
  for (int vi=0; vi<4; vi++)
    {

      derivative_xx[vi][0] = 9./(8.)*Derivative(velocity_y[k][j][i+vi-1],
                                                velocity_y[k][j][i+vi-2],
                                                dx,1);

      derivative_xx[vi][1] = -1./(8.)*Derivative(velocity_y[k][j][i+vi],
                                                 velocity_y[k][j][i+vi-3],
                                                 dx,3);

      //initalizing the vector
      total_derivative_x[vi]=0.;
      for (int vj=0; vj<2; vj++)
        total_derivative_x[vi]+=derivative_xx[vi][vj];

    }

  // Calculation of the (du/dy) component
  //i-3/2
  //i-3
  dy_total=dy[j-1]+2.*dy[j]+dy[j+1];
  derivative_xy[0][0] = Derivative(velocity_x[k][j+1][i-3],
                                   velocity_x[k][j-1][i-3],
                                   dy_total,1);

  //i
  dy_total=dy[j-1]+2.*dy[j]+dy[j+1];
  derivative_xy[0][1] = Derivative(velocity_x[k][j+1][i],
                                   velocity_x[k][j-1][i],
                                   dy_total,1);

  //i-1/2
  //i-1
  dy_total=dy[j-1]+2.*dy[j]+dy[j+1];
  derivative_xy[1][0] = Derivative(velocity_x[k][j+1][i-1],
                                   velocity_x[k][j-1][i-1],
                                   dy_total,1);

  //i/
  derivative_xy[1][1] = derivative_xy[0][1];

  //i+1/2
  //i
  derivative_xy[2][0] = derivative_xy[0][1];
  //i+1
  dy_total=dy[j-1]+2.*dy[j]+dy[j+1];
  derivative_xy[2][1] = Derivative(velocity_x[k][j+1][i+1],
                                   velocity_x[k][j-1][i+1],
                                   dy_total,1);

  //i+3/2
  //i
  derivative_xy[3][0] = derivative_xy[0][1];
  //i+3
  dy_total=dy[j-1]+2.*dy[j]+dy[j+1];
  derivative_xy[3][1] = Derivative(velocity_x[k][j+1][i+3],
                                   velocity_x[k][j-1][i+3],
                                   dy_total,1);


  //summing the derivatives in the y direction
  double total_derivative_y[4];
  for(int vi=0; vi<4; vi++)
    {
      total_derivative_y[vi]=Interpolation(derivative_xy[vi][0],
                                           derivative_xy[vi][1]);
    }

  //Computing the viscosities.
  double viscosity[4];
  for (int vi=-2, vj=0; vi<2; vi++, vj++)
    {
      viscosity[vj]=
        Viscosity_Calculator(Interpolation(temperature[k][j][i+vi+1],
                                           temperature[k][j][i+vi]))
        +Interpolation(eddy_viscosity[k][j][i+vi+1],
                       eddy_viscosity[k][j][i+vi]);
    }


  //computing the viscous tensors
  for (int vi=0; vi<4; vi++)
    {
      viscous_terms[vi] =viscosity[vi]*(total_derivative_x[vi]
                                        +total_derivative_y[vi]);
    }


  // cout<<"yx"<<endl;
  // cout<<-1./24.*(total_derivative_y[3]-total_derivative_y[0])
  //   +9./8.*(total_derivative_y[2]-total_derivative_y[1])<<endl;



  /* Summing the X-component of the Viscous Term of the Y-Momentum equation*/
  double viscous_component =
    1./Reynolds*(9./8.*Derivative(viscous_terms[2],
                                  viscous_terms[1],
                                  dx,1)-
                 1./8.*Derivative(viscous_terms[3],
                                  viscous_terms[0],
                                  dx,3));

  return viscous_component;


}
