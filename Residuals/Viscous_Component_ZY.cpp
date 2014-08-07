/*******************************************
 * Author: Michail Georgiou
 *  Last Modified: Time-stamp: <2014-07-31 14:57:55 mike_georgiou>
 *
 *
Viscous_Component_ZY.cpp -- This function computes the Y component of the velosity
residuals in the Z momentum equation
*
* Written on Thursday, 24 April 2014.
********************************************/

#include"Residuals-inl.h"

#include<iostream>
using namespace std;


double Viscous_Component_ZY(double*** velocity_y, double*** velocity_z,
                            double*** temperature,
                            double*** eddy_viscosity,
                            double Reynolds,
                            double* dy, double dz,
                            int i, int j, int k)
{


  double derivative_yz[2][4], derivative_yy[2],
    total_derivative_z[2],
    viscosity[2], viscous_terms[2], dy_total;


  //calculation of the (dw/dy)
  // j-1/2
  dy_total= dy[j]+dy[j-1];
  derivative_yy[0] =Derivative(velocity_z[k][j][i],
                               velocity_z[k][j-1][i],
                               dy_total, 1);

  // j+1/2
  dy_total= dy[j]+dy[j+1];
  derivative_yy[1] =Derivative(velocity_z[k][j+1][i],
                               velocity_z[k][j][i],
                               dy_total,1);


  // Calculation of the (dv/dz)
  //j-1/2
  // j-1
  derivative_yz[0][0] = 4./(3.)*Derivative(velocity_y[k+1][j-1][i],
                                           velocity_y[k-1][j-1][i],
                                           dz,2);

  derivative_yz[0][1] = -1./(3.)*Derivative(velocity_y[k+2][j-1][i],
                                            velocity_y[k-2][j-1][i],
                                            dz,4);

  // j
  derivative_yz[0][2] = 4./(3.)*Derivative(velocity_y[k+1][j][i],
                                           velocity_y[k-1][j][i],
                                           dz,2);

  derivative_yz[0][3] = -1./(3.)*Derivative(velocity_y[k+2][j][i],
                                            velocity_y[k-2][j][i],
                                            dz,4);

  //j+1/2
  // j
  derivative_yz[1][0] =derivative_yz[0][2];
  derivative_yz[1][1] =derivative_yz[0][3];

  // j+1
  derivative_yz[1][2] = 4./(3.)*Derivative(velocity_y[k+1][j+1][i],
                                           velocity_y[k-1][j+1][i],
                                           dz,2);

  derivative_yz[1][3] = -1./(3.)*Derivative(velocity_y[k+2][j+1][i],
                                            velocity_y[k-2][j+1][i],
                                            dz,4);

  //computing the interpolated derivative d/dy(dv/dz)
  double sum[2];
  for (int vi=0; vi<2; vi++)
    {
      sum[0] = derivative_yz[vi][0]+derivative_yz[vi][1];
      sum[1] = derivative_yz[vi][2]+derivative_yz[vi][3];


      total_derivative_z[vi]= Interpolation_Y(sum[1], dy[j],
                                              sum[0], dy[j]);
    }


  // Computing the Viscosity
  for (int vi=0; vi<2; vi++)
    {
      viscosity[vi]=
        Viscosity_Calculator(Interpolation(temperature[k][j+vi][i],
                                           temperature[k][j+vi-1][i]))

        +Interpolation_Y(eddy_viscosity[k][j+vi][i],dy[j+vi],
                         eddy_viscosity[k][j+vi-1][i],dy[j+vi-1]);
    }

  for (int vi=0; vi<2; vi++)
    {
      viscous_terms[vi]=viscosity[vi]*(derivative_yy[vi]
                                       +total_derivative_z[vi]);
    }


  // cout<<"zy"<<endl;
  // cout<<total_derivative_z[1]-total_derivative_z[0]<<endl;




  //computing the viscous component in the y-direction
  dy_total=2.*dy[j];
  double viscous_component= 1./(Reynolds)*Derivative(viscous_terms[1],
                                                     viscous_terms[0],
                                                     dy_total,1) ;


  return viscous_component;
}
