/*******************************************
 * Author: Michail Georgiou
 *  Last Modified: Time-stamp: <2014-05-15 12:45:56 mike_georgiou>
 *
 *
Energy_Convection.cpp -- This function computes the convection term of the
energy equation. For the fourth order accurate scheme eq. 68 from the
Lessani-Papalexandris paper is used. For the non-uniform direction.
*
* Written on Thursday, 24 April 2014.
********************************************/

#include "Energy_Equation-inl.h"

double Energy_Convection(double*** temperature,
                         double*** velocity_x, double*** velocity_y,
                         double*** velocity_z,
                         double dx, double* dy, double dz,
                         int i, int j, int k)
{

  double convective_terms[3];
  double interpolated[4], derivative[2],total_interpolated[2];


  //X-Direction
  for (int vi=0; vi<2; vi++)
    {
      interpolated[vi]=Interpolation(velocity_x[k][j][i+vi],
                                     velocity_x[k][j][i+vi-1]);

      interpolated[vi+2]=Interpolation(velocity_x[k][j][i+2*vi],
                                       velocity_x[k][j][i+2*vi-2]);
    }

  total_interpolated[0]=interpolated[0]+interpolated[1];
  total_interpolated[1]=interpolated[2]+interpolated[3];


  derivative[0]=4./3.*Derivative(temperature[k][j][i+1],
                                 temperature[k][j][i-1],
                                 dx, 2);

  derivative[1]=-1./3.*Derivative(temperature[k][j][i+2],
                                  temperature[k][j][i-2],
                                  dx, 4);

  convective_terms[0]=0.;
  for(int vi=0; vi<2; vi++)
    convective_terms[0]+=derivative[vi]*total_interpolated[vi];



  //Y-direction. This quantity I computed it by just implementing vdT/dy. At the
  // paper it says that the v has also to be interpolated so this source can
  // cause errors

  double dy_total=dy[j+1]+2.*dy[j]+dy[j-1];
  derivative[0]=Derivative(velocity_y[k][j+1][i],
                           velocity_y[k][j-1][i],
                           dy_total,1);

  convective_terms[1] =velocity_y[k][j][i]*derivative[0];


  //Z-Component
  for (int vi=0; vi<2; vi++)
    {
      interpolated[vi]=Interpolation( velocity_z[k+vi][j][i],
                                      velocity_z[k+vi-1][j][i]);

      interpolated[vi+2]=Interpolation(velocity_z[k+2*vi][j][i],
                                       velocity_x[k+2*vi-2][j][i]);

    }

  total_interpolated[0]=interpolated[0]+interpolated[1];
  total_interpolated[1]=interpolated[2]+interpolated[3];


  derivative[0]=4./3.*Derivative(temperature[k+1][j][i],
                                 temperature[k-1][j][i],
                                 dz, 2);

  derivative[1]=-1./3.*Derivative(temperature[k+2][j][i],
                                  temperature[k-2][j][i],
                                  dz, 4);

  convective_terms[2]=0.;
  for(int vi=0; vi<2; vi++)
    convective_terms[2]+=derivative[vi]*total_interpolated[vi];


  double convection=0.;
  for (int vi=0; vi<3; vi++)
    convection+=convective_terms[vi];

  return convection;
}
