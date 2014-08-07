/*******************************************
 * Author: Michail Georgiou
 *  Last Modified: Time-stamp: <2014-07-31 14:45:28 mike_georgiou>
 *
 *
Viscous_Component_YY.cpp -- This function computes
the viscous component of the
Y momentum equation
*
* Written on Thursday, 24 April 2014.
********************************************/

#include"Residuals-inl.h"


double Viscous_Component_YY(double*** velocity_x, double*** velocity_y,
                            double*** velocity_z,
                            double*** temperature,
                            double*** eddy_viscosity,
                            double Reynolds,
                            double dx, double* dy, double dz,
                            int i, int j, int k)
{

  double derivative_yx[3][2],derivative_yz[3][2],derivative_yy[2],
    viscous_terms[2], viscosity[2], dy_total;



  //Calculation of the d/dy(dv/dy)
  //j-1/2
  dy_total= dy[j]+dy[j-1];
  derivative_yy[0] =
    Derivative(velocity_y[k][j][i],velocity_y[k][j-1][i],
               dy_total,1);

  //j+1/2
  dy_total= dy[j+1]+dy[j];
  derivative_yy[1] =
    Derivative(velocity_y[k][j+1][i], velocity_y[k][j][i],
               dy_total,1);


  //Calculation of the d/dy(du/dx)
  double sum[3];
  for (int vi=0; vi<3; vi++)
    {

      derivative_yx[vi][0]=4./3.*Derivative(velocity_x[k][j+vi-1][i+1],
                                            velocity_x[k][j+vi-1][i-1],
                                            dx,2);

      derivative_yx[vi][1]=-1./3.*Derivative(velocity_x[k][j+vi-1][i+2],
                                             velocity_x[k][j+vi-1][i-2],
                                             dx,4);
      sum[vi]=0.;
      for (int vj=0; vj<2; vj++)
        {
          sum[vi] += derivative_yx[vi][vj];
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

  for (int vi=0; vi<3; vi++)
    {
      derivative_yz[vi][0]=4./3.*Derivative(velocity_z[k+1][j+vi-1][i],
                                            velocity_z[k-1][j+vi-1][i],
                                            dz,2);

      derivative_yz[vi][1]=-1./3.*Derivative(velocity_z[k+2][j+vi-1][i],
                                             velocity_z[k-2][j+vi-1][i],
                                             dz,4);

      sum[vi]=0.;
      for (int vj=0; vj<2; vj++)
        {
          sum[vi] += derivative_yz[vi][vj];
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
  for (int vi=-1, vj=0; vi<1; vi++, vj++)
    {
      viscosity[vj]=
        Viscosity_Calculator(Interpolation(temperature[k][j+vi][i],
                                           temperature[k][j+vi+1][i]))

        +Interpolation_Y(eddy_viscosity[k][j+vi][i],dy[j+vi],
                         eddy_viscosity[k][j+vi+1][i],dy[j+vi+1]);
    }



  //computing the viscous tensors
  for (int vi=0; vi<2; vi++)
    {
      viscous_terms[vi] =viscosity[vi]*(4./3*derivative_yy[vi]
                                        -2./3.*(total_derivative_x[vi]+
                                                total_derivative_z[vi]) );
    }


  // cout<<"yy"<<endl;
  //     cout<<total_derivative_x[1]-total_derivative_x[0]<<endl;
  //     cout<<total_derivative_z[1]-total_derivative_z[0]<<endl;


  /* Summing the X-component of the Viscous Term of the Y-Momentum equation*/

  dy_total=2.*dy[j];
  double viscous_term =
    1./Reynolds*(Derivative(viscous_terms[1],
                            viscous_terms[0],
                            dy_total,1));

  return viscous_term;
}
