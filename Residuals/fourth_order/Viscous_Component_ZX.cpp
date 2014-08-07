/*******************************************
 * Author: Michail Georgiou
 *  Last Modified: Time-stamp: <2014-07-30 17:58:33 mike_georgiou>
 *
 *
Viscous_Component_ZX.cpp -- This function computes the X component of
 the velocity
residuals of the Z momentum equation
*
* Written on Thursday, 24 April 2014.
********************************************/


#include"Residuals-inl.h"
#include <iostream>

using namespace std;



double Viscous_Component_ZX(double*** velocity_x, double*** velocity_z,
                            double*** temperature,
                            double*** eddy_viscosity,
                            double Reynolds,
                            double dx, double dz,
                            int i, int j, int k)
{

  double derivative_xx[4][2], derivative_xz[4][4],
    total_derivative_x[4], total_derivative_z[4],
    viscosity[4], viscous_terms[4];


  //Calculation of the d/dx(dw/dx) component

  for (int vi=0; vi<4; vi++)
    {

      derivative_xx[vi][0]=9./8.*Derivative(velocity_z[k][j][i+vi-1],
                                            velocity_z[k][j][i+vi-2],
                                            dx,1);

      derivative_xx[vi][1]=-1./8.*Derivative(velocity_z[k][j][i+vi],
                                             velocity_z[k][j][i+vi-3],
                                             dx,3);

      //computing the total derivative
      total_derivative_x[vi]=derivative_xx[vi][0]+derivative_xx[vi][1];

    }

  //Calculation of the d/dx(du/dz) component

  // i-3/2
  // i-3
  //\delta_1
  derivative_xz[0][0] = 4./3.*Derivative(velocity_x[k+1][j][i-3],
                                         velocity_x[k-1][j][i-3],
                                         dz,2);

  //\delta_2
  derivative_xz[0][1] = -1./3.*Derivative(velocity_x[k+2][j][i-3],
                                          velocity_x[k-2][j][i-3],
                                          dz,4);

  //i
  //\delta_1
  derivative_xz[0][2] = 4./3.*Derivative(velocity_x[k+1][j][i],
                                         velocity_x[k-1][j][i],
                                         dz,2);

  //\delta_2
  derivative_xz[0][3] = -1./3.*Derivative(velocity_x[k+2][j][i],
                                          velocity_x[k-2][j][i],
                                          dz,4);


  //i-1/2/

  //i-1
  derivative_xz[1][0] = 4./3.*Derivative(velocity_x[k+1][j][i-1],
                                         velocity_x[k-1][j][i-1],
                                         dz,2);

  //delta_2
  derivative_xz[1][1] = -1./3.*Derivative(velocity_x[k+2][j][i-1],
                                          velocity_x[k-2][j][i-1],
                                          dz,4);

  //i
  //\delta_1
  derivative_xz[1][2]=derivative_xz[0][2];
  //\delta_2
  derivative_xz[1][3]=derivative_xz[0][3];



  // i+1/2
  //i
  //\delta_1
  derivative_xz[2][0] = derivative_xz[0][2];
  //\delta_2
  derivative_xz[2][1] = derivative_xz[0][3];

  //i+1
  //delta_1
  derivative_xz[2][2] = 4./3.*Derivative(velocity_x[k+1][j][i+1],
                                         velocity_x[k-1][j][i+1],
                                         dz,2);

  //delta_2
  derivative_xz[2][3] = -1./3.*Derivative(velocity_x[k+2][j][i+1],
                                          velocity_x[k-2][j][i+1],
                                          dz,4);

  //i+3/2

  //i
  //\delta_1
  derivative_xz[3][0] = derivative_xz[0][2];
  /*\delta_2*/
  derivative_xz[3][1] = derivative_xz[0][3];


  //i+3
  derivative_xz[3][2] = 4./3.*Derivative(velocity_x[k+1][j][i+3],
                                         velocity_x[k-1][j][i+3],
                                         dz,2);

  //delta_2
  derivative_xz[3][3] = -1./3.*Derivative(velocity_x[k+2][j][i+3],
                                          velocity_x[k-2][j][i+3],
                                          dz,4);



  //summing up the components
  for (int vi=0; vi<4; vi++)
    {

      total_derivative_z[vi]=0.;
      for (int vj=0; vj<4; vj++)
        {
          total_derivative_z[vi]+=derivative_xz[vi][vj];
        }
    }


  // Calculating the components of the total residular Res_Visc_Total[2]//

  for (int vi=-2, vj=0; vi<2; vi++, vj++)
    {
      viscosity[vj]=
        Viscosity_Calculator(Interpolation(temperature[k][j][i+vi+1],
                                           temperature[k][j][i+vi]))

        +Interpolation(eddy_viscosity[k][j][i+vi+1],
                       eddy_viscosity[k][j][i+vi]);

      // I added the eddy viscosity in order to simulate turbulence
    }


  for (int vi=0; vi<4; vi++)
    {
      viscous_terms[vi]=viscosity[vi]*(total_derivative_x[vi]
                                       +total_derivative_z[vi]/2.);

    }



  // cout<<"zx"<<endl;
  // cout<<total_derivative_z[3]-total_derivative_z[0]<<endl;
  // cout<<total_derivative_z[2]-total_derivative_z[1]<<endl;



  double   viscous_component =
    1./Reynolds*( 9./8.*Derivative(viscous_terms[2],
                                   viscous_terms[1],
                                   dx,1)-
                  1./8.*Derivative(viscous_terms[3],
                                   viscous_terms[0],
                                   dx,3));

  return viscous_component;

}
