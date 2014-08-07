/*******************************************
 * Author: Michail Georgiou
 *  Last Modified: Time-stamp: <2014-07-30 17:51:12 mike_georgiou>
 *
 *
Viscous_Component_YY.cpp -- This function computes
the viscous component of the
Y momentum equation
*
* Written on Thursday, 24 April 2014.
********************************************/

#include"Residuals-inl.h"


double Viscous_Component_YY_Implicit(double*** velocity_x,
                                     double*** velocity_y,
                                     double*** velocity_z,
                                     double*** temperature,
                                     double*** eddy_viscosity,
                                     double Reynolds,
                                     double dx, double* dy, double dz,
                                     int i, int j, int k,
                                     double* explicit_term)
{

  //Calculation of the d/dy(dv/dy)
  //j-1/2
  double derivative_y[2];

  double  dy_total= dy[j]+dy[j-1];
  derivative_y[0] =
    Derivative(velocity_y[k][j][i],velocity_y[k][j-1][i],
               dy_total,1);

  //j+1/2
  dy_total= dy[j+1]+dy[j];
  derivative_y[1] =
    Derivative(velocity_y[k][j+1][i], velocity_y[k][j][i],
               dy_total,1);


  //Calculation of the d/dy(du/dx)

  double derivative_x[3][2], sum[3];
  for (int vi=0; vi<3; vi++)
    {

      derivative_x[vi][0]=4./3.*Derivative(velocity_x[k][j+vi-1][i+1],
                                           velocity_x[k][j+vi-1][i-1],
                                           dx,2);

      derivative_x[vi][1]=-1./3.*Derivative(velocity_x[k][j+vi-1][i+2],
                                            velocity_x[k][j+vi-1][i-2],
                                            dx,4);
      sum[vi]=0.;
      for (int vj=0; vj<2; vj++)
        {
          sum[vi] += derivative_x[vi][vj];
        }

    }

  double total_derivative_x[2];
  for (int vi=0; vi<2; vi++)
    {
      //interpolation to obtain the derivative at the desired point
      total_derivative_x[vi] = Interpolation_Y(sum[vi],dy[j-1+vi],
                                               sum[vi+1],dy[j+vi]);
    }



  // Calculation of the d/dy(dw/dz)
  double derivative_z[3][2];
  for (int vi=0; vi<3; vi++)
    {
      derivative_z[vi][0]=4./3.*Derivative(velocity_z[k+1][j+vi-1][i],
                                           velocity_z[k-1][j+vi-1][i],
                                           dz,2);

      derivative_z[vi][1]=-1./3.*Derivative(velocity_z[k+2][j+vi-1][i],
                                            velocity_z[k-2][j+vi-1][i],
                                            dz,4);

      sum[vi]=0.;
      for (int vj=0; vj<2; vj++)
        {
          sum[vi] += derivative_z[vi][vj];
        }
    }


  //interpolation to obtain the derivative at the desired point
  double total_derivative_z[2];
  for (int vi=0; vi<2; vi++)
    {

      total_derivative_z[vi] = Interpolation_Y(sum[vi],dy[j-1+vi],
                                               sum[vi+1],dy[j+vi]);
    }

  //Computing the viscosities.
  double viscosity[2];
  for (int vi=-1, vj=0; vi<1; vi++, vj++)
    {
      viscosity[vj]=
        Viscosity_Calculator(Interpolation(temperature[k][j+vi][i],
                                           temperature[k][j+vi+1][i]))+
        Interpolation(eddy_viscosity[k][j+vi][i],
                      eddy_viscosity[k][j+vi+1][i]);
    }



  //computing the viscous tensors
  double viscous_terms[2];
  for (int vi=0; vi<2; vi++)
    {
      viscous_terms[vi] =viscosity[vi]*(-2./3.*(total_derivative_x[vi]+
                                                total_derivative_z[vi]) );
    }

  dy_total=2.*dy[j];
  double viscous_term =
    1./Reynolds*(Derivative(viscous_terms[1],
                            viscous_terms[0],
                            dy_total,1));



  //Computing the explicit term that will be returned by the function

  //Firstly i multiply those terms with viscosoty
  for(int vi=0; vi<2; vi++)
    derivative_y[vi]*=viscosity[vi];

  //Computing the derivative
  *explicit_term= 1./(Reynolds)*Derivative(derivative_y[1],
                                           derivative_y[0],
                                           dy_total,1) ;


  return viscous_term;
}
