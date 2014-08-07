/*******************************************
 * Author: Michail Georgiou
 *  Last Modified: Time-stamp: <2014-07-30 17:58:28 mike_georgiou>
 *
 *
Viscous_Component_ZY.cpp -- This function computes the Y component of
the velosity
residuals in the Z momentum equation
*
* Written on Thursday, 24 April 2014.
********************************************/

#include"Residuals-inl.h"


double Viscous_Component_ZY_Implicit(double*** velocity_y,
                                     double*** velocity_z,
                                     double*** temperature,
                                     double*** eddy_viscosity,
                                     double Reynolds,
                                     double* dy, double dz,
                                     int i, int j, int k,
                                     double* explicit_term)
{


  //calculation of the (dw/dy)
  double derivative_y[2];

  // j-1/2
  double  dy_total= dy[j]+dy[j-1];
  derivative_y[0] =Derivative(velocity_z[k][j][i],
                              velocity_z[k][j-1][i],
                              dy_total, 1);

  // j+1/2
  dy_total= dy[j]+dy[j+1];
  derivative_y[1] =Derivative(velocity_z[k][j+1][i],
                              velocity_z[k][j][i],
                              dy_total,1);


  // Calculation of the (dv/dz)
  double derivative_z[2][4];
  //j-1/2
  // j-1
  derivative_z[0][0] = 4./(3.)*Derivative(velocity_y[k+1][j-1][i],
                                          velocity_y[k-1][j-1][i],
                                          dz,2);

  derivative_z[0][1] = -1./(3.)*Derivative(velocity_y[k+2][j-1][i],
                                           velocity_y[k-2][j-1][i],
                                           dz,4);

  // j
  derivative_z[0][2] = 4./(3.)*Derivative(velocity_y[k+1][j][i],
                                          velocity_y[k-1][j][i],
                                          dz,2);

  derivative_z[0][3] = -1./(3.)*Derivative(velocity_y[k+2][j][i],
                                           velocity_y[k-2][j][i],
                                           dz,4);

  //j+1/2
  // j
  derivative_z[1][0] =derivative_z[0][2];
  derivative_z[1][1] =derivative_z[0][3];

  // j+1
  derivative_z[1][2] = 4./(3.)*Derivative(velocity_y[k+1][j+1][i],
                                          velocity_y[k-1][j+1][i],
                                          dz,2);

  derivative_z[1][3] = -1./(3.)*Derivative(velocity_y[k+2][j+1][i],
                                           velocity_y[k-2][j+1][i],
                                           dz,4);

  //computing the interpolated derivative d/dy(dv/dz)
  double sum[2], total_derivative_z[2];
  for (int vi=0; vi<2; vi++)
    {
      sum[0] = derivative_z[vi][0]+derivative_z[vi][1];
      sum[1] = derivative_z[vi][2]+derivative_z[vi][3];


      total_derivative_z[vi]= Interpolation_Y(sum[1], dy[j],
                                              sum[0], dy[j]);
    }


  // Computing the Viscosity
  double viscosity[2];
  for (int vi=0; vi<2; vi++)
    {
      viscosity[vi]=
        Viscosity_Calculator(Interpolation(temperature[k][j+vi][i],
                                           temperature[k][j+vi-1][i]))
        +Interpolation(eddy_viscosity[k][j+vi][i],
                       eddy_viscosity[k][j+vi-1][i]);
    }

  double viscous_terms[2];
  for (int vi=0; vi<2; vi++)
    viscous_terms[vi]=viscosity[vi]*(total_derivative_z[vi]);



  //computing the viscous component in the y-direction
  dy_total=2.*dy[j];
  double viscous_component= 1./(Reynolds*dy_total)*(viscous_terms[1]-
                                                    viscous_terms[0]);



  //Computing the explicit term that will be returned by the function

  //Firstly i multiply those terms with viscosoty
  for(int vi=0; vi<2; vi++)
    derivative_y[vi]*=viscosity[vi];

  //Computing the derivative
  *explicit_term= 1./(Reynolds)*Derivative(derivative_y[1],
                                           derivative_y[0],
                                           dy_total,1) ;


  return viscous_component;
}
