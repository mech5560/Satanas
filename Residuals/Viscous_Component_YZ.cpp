/*******************************************
 * Author: Michail Georgiou
 *  Last Modified: Time-stamp: <2014-06-26 11:27:24 mike_georgiou>
 *
 *
Viscous_Component_YZ.cpp -- This function computes the Z component of
the of the  velocity residual of the Y momentum equation
*
* Written on Thursday, 24 April 2014.
********************************************/

#include"Residuals-inl.h"


double Viscous_Component_YZ(double*** velocity_y, double*** velocity_z,
                            double*** temperature, 
			    double*** eddy_viscosity,
			    double Reynolds,
                            double* dy, double dz,
                            int i, int j, int k)
{

  double derivative_zy[4][2], derivative_zz[4][2],
    viscous_terms[4], viscosity[4], dy_total;

  //Calculation of the d/dz(dv/dz) component
  double total_derivative_z[4];
  for (int vi=0; vi<4; vi++)
    {
      derivative_zz[vi][0]= 9./8.*Derivative(velocity_y[k+vi-1][j][i],
                                             velocity_y[k+vi-2][j][i],
                                             dz,1);

      derivative_zz[vi][1]= -1./8.*Derivative(velocity_y[k+vi][j][i],
                                              velocity_y[k+vi-3][j][i],
                                              dz,3);

      //computing the total derivative
      total_derivative_z[vi]=0.;
      for (int vj=0; vj<2; vj++)
        total_derivative_z[vi]+=derivative_zz[vi][vj];

    }

  //Calculation of the d/dz(dw/dy) component

  //k-3/2
  //k-3
  dy_total=dy[j-1]+2.*dy[j]+dy[j+1];
  derivative_zy[0][0] = Derivative(velocity_z[k-3][j+1][i],
                                   velocity_z[k-3][j-1][i],
                                   dy_total,1);

  //k
  dy_total=dy[j-1]+2.*dy[j]+dy[j+1];
  derivative_zy[0][1] = Derivative(velocity_z[k][j+1][i],
                                   velocity_z[k][j-1][i],
                                   dy_total,1);

  //k-1/2

  //k-1
  //k
  dy_total=dy[j-1] +2.*dy[j] +dy[j+1];
  derivative_zy[1][0] = Derivative(velocity_z[k-1][j+1][i],
                                   velocity_z[k-1][j-1][i],
                                   dy_total,1);

  //k
  derivative_zy[1][1] = derivative_zy[0][1];


  //k+1/2

  //k
  derivative_zy[2][0] = derivative_zy[0][1];


  //k+1
  dy_total=dy[j-1] +2.*dy[j] +dy[j+1];
  derivative_zy[2][1] = Derivative(velocity_z[k+1][j+1][i],
                                   velocity_z[k+1][j-1][i],
                                   dy_total,1);

  // k+3/2
  //k
  derivative_zy[3][0] = derivative_zy[0][1];
  //k+3
  dy_total=dy[j-1]+2.*dy[j]+dy[j+1];
  derivative_zy[3][1] = Derivative(velocity_z[k+3][j+1][i],
                                   velocity_z[k+3][j-1][i],
                                   dy_total,1);

  //computing the total derivative in the y-direction
  double total_derivative_y[4];
  for(int vi=0; vi<4; vi++)
    {
      total_derivative_y[vi]=Interpolation(derivative_zy[vi][0],
                                           derivative_zy[vi][1]);
    }


  //Computing the viscosities.
  for (int vi=-2, vj=0; vj<2; vi++, vj++)
    {
      viscosity[vj]=
        Viscosity_Calculator(Interpolation(temperature[k+vi][j][i],
                                           temperature[k+vi+1][j][i]))

	+Interpolation(eddy_viscosity[k+vi][j][i],
		       eddy_viscosity[k+vi+1][j][i]);
    }



  //computing the viscous tensors
  for (int vi=0; vi<4; vi++)
    {
      viscous_terms[vi] =viscosity[vi]*(total_derivative_y[vi]+
                                        total_derivative_z[vi]);
    }



  // cout<<"yz"<<endl;
  // cout<<-1./24.*(total_derivative_y[3]-total_derivative_y[0])
  //   +9./8*(total_derivative_y[2]-total_derivative_y[1])<<endl;


  double viscous_component =
    1./Reynolds*(9./8.*Derivative(viscous_terms[2],
                                  viscous_terms[1],
                                  dz,1)-
                 1./8.*Derivative(viscous_terms[3],
                                  viscous_terms[0],
                                  dz,3));


  return viscous_component;

}
