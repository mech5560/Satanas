/*******************************************
 * Author: Michail Georgiou
 *  Last Modified: Time-stamp: <2014-05-16 14:13:53 mike_georgiou>
 *
 *
Energy_Viscous.cpp -- This function computes the viscous term of the
energy
equation. In the streamwise and spanwise directions I am using fourth
order
accurate schemes and in the vertical second order accurate.

To interpolate the conductivity i am using second order accurate
interpolation
in all the directions. I could easily change that at a later stage.
*
* Written on Thursday, 24 April 2014.
********************************************/


#include"Energy_Equation-inl.h"

double Energy_Viscous(double*** temperature,
                      double*** velocity_x, double*** velocity_y,
                      double*** velocity_z,
                      double dx, double* dy, double dz,
                      int i, int j, int k)
{
  double conductivity[4];
  double derivative[4], sum[4];
  double dy_total, viscous_components[3];

  // X- Direction
  for (int vi=0; vi<4; vi++)
    {
      derivative[vi]=
        9./8.*Derivative(temperature[k][j][i+vi-1],
                         temperature[k][j][i+vi-2],
                         dx,1)-
        1./8.*Derivative(temperature[k][j][i+vi],
                         temperature[k][j][i+vi-3],
                         dx,3);
    }


  //Interpolating the Conductivity
  for(int vi=0; vi<4; vi++)
    {
      conductivity[vi]= Conductivity(Interpolation(temperature[k][j][i+vi-1],
                                                   temperature[k][j][i+vi-2]));
    }

  //computing the sums
  for(int vi=0; vi<4; vi++)
    {
      sum[vi]=conductivity[vi]*derivative[vi];
    }


  viscous_components[0] =
    9./(8.)*Derivative(sum[2],sum[1],dx,1)-
    1./(8.)*Derivative(sum[3],sum[0],dx,3);


  //Y-Direction
  //computing the derivative costituents
  for(int vi=0; vi<2; vi++)
    {
      dy_total=dy[j+vi]+dy[j+vi-1];
      derivative[vi]= Derivative(temperature[k][j+vi][i],
                                 temperature[k][j+vi-1][i],
                                 dy_total,1);
    }
  //computing the conductivity
  for(int vi=0; vi<2; vi++)
    {

      conductivity[vi]= Conductivity(Interpolation_Y(temperature[k][j+vi][i],
                                                     dy[j+vi],
                                                     temperature[k][j+vi-1][i],
                                                     dy[j]));

      conductivity[vi]= Conductivity(Interpolation(temperature[k][j+vi][i],
                                                   temperature[k][j+vi-1][i]));

    }

  for(int vi=0; vi<2; vi++)
    {
      sum[vi]=conductivity[vi]*derivative[vi];
    }


  dy_total=2.*dy[j];
  viscous_components[1]=Derivative(sum[1],sum[0],
                                   dy_total,1);

  //Z-Direction
  for (int vi=0; vi<4; vi++)
    {
      derivative[vi]=
        9./8.*Derivative(temperature[k+vi-1][j][i],
                         temperature[k+vi-2][j][i],
                         dz,1)-
        1./8.*Derivative(temperature[k+vi][j][i],
                         temperature[k+vi-3][j][i],
                         dz,3);
    }

  for(int vi=0; vi<4; vi++)
    {
      conductivity[vi]= Conductivity(Interpolation(temperature[k+vi-1][j][i],
                                                   temperature[k+vi-2][j][i]));
    }

  //computing the sums
  for(int vi=0; vi<4; vi++)
    {
      sum[vi]=conductivity[vi]*derivative[vi];
    }


  viscous_components[2] =
    9./(8.)*Derivative(sum[2],sum[1],dz,1)-
    1./(8.)*Derivative(sum[3],sum[0],dz,3);

  double viscous_term=0.;
  for(int vi=0; vi<3; vi++)
    viscous_term+=viscous_components[vi];



  return viscous_term;
}
