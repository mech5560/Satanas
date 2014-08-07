/*******************************************
 * Author: Michail Georgiou
 *  Last Modified: Time-stamp: <2014-07-30 16:31:40 mike_georgiou>
 *
 *
Viscous_Component_XY_Implicit.cpp -- This function computes the
d/dy(\sigma_{ij}) of the X momentum equation. The difference
with the already existing version is that the velocity_x_tilda will be
computed implicitly fact  that modifies the computation of the
d/dy(du/dy) term
*
* Written on Wednesday, 28 May 2014.
********************************************/

#include"Residuals-inl.h"

double Viscous_Component_XY_Implicit(double*** velocity_x,
                                     double*** velocity_y,
                                     double*** temperature,
                                     double*** eddy_viscosity,
                                     double Reynolds,
                                     double dx, double* dy,
                                     int i, int j, int k,
                                     double* explicit_term)
{

  double  derivative_y[2],  dy_total;

  //calculation of the (du/dy)
  // j-1/2
  dy_total= dy[j]+dy[j-1];
  derivative_y[0] =Derivative(velocity_x[k][j][i],
                              velocity_x[k][j-1][i],
                              dy_total, 1);

  // j+1/2
  dy_total= dy[j]+dy[j+1];
  derivative_y[1] =Derivative(velocity_x[k][j+1][i],
                              velocity_x[k][j][i],
                              dy_total,1);


  //Calculation of the (dv/dx)
  double derivative_x[2][4];
  //j-1/2

  // j-1
  derivative_x[0][0] = 4./(3.)*Derivative(velocity_y[k][j-1][i+1],
                                          velocity_y[k][j-1][i-1],
                                          dx,2);

  derivative_x[0][1] = -1./(3.)*Derivative(velocity_y[k][j-1][i+2],
                                           velocity_y[k][j-1][i-2],
                                           dx,4);

  // j
  derivative_x[0][2] = 4./(3.)*Derivative(velocity_y[k][j][i+1],
                                          velocity_y[k][j][i-1],
                                          dx,2);

  derivative_x[0][3] = -1./(3.)*Derivative(velocity_y[k][j][i+2],
                                           velocity_y[k][j][i-2],
                                           dx,4);

  //j+1/2
  // j
  derivative_x[1][0] =derivative_x[0][2];
  derivative_x[1][1] =derivative_x[0][3];

  // j+1
  derivative_x[1][2] = 4./(3.)*Derivative(velocity_y[k][j+1][i+1],
                                          velocity_y[k][j+1][i-1],
                                          dx,2);

  derivative_x[1][3] = -1./(3.)*Derivative(velocity_y[k][j+1][i+2],
                                           velocity_y[k][j+1][i-2],
                                           dx,4);

  //computing the interpolated derivative d/dy(dv/dx)
  double sum[2];
  double total_derivative_x[2];

  for (int vi=0; vi<2; vi++)
    {
      sum[0] = derivative_x[vi][0]+derivative_x[vi][1];
      sum[1] = derivative_x[vi][2]+derivative_x[vi][3];


      total_derivative_x[vi]= Interpolation_Y(sum[1], dy[j],
                                              sum[0], dy[j]);
    }


  // Computing the Viscosity
  double viscosity[2];
  for (int vi=0; vi<2; vi++)
    {
      viscosity[vi]=
        Viscosity_Calculator(Interpolation_Y(temperature[k][j+vi][i],
                                             dy[j+1],
                                             temperature[k][j+vi-1][i],
                                             dy[j]))
        +Interpolation_Y(eddy_viscosity[k][j+vi][i],
                         dy[j+1],
                         eddy_viscosity[k][j+vi-1][i],
                         dy[j]);
    }

  double viscous_terms[2];
  for (int vi=0; vi<2; vi++)
    {
      viscous_terms[vi]=viscosity[vi]*(total_derivative_x[vi]);


    }


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
