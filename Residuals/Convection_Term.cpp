/*******************************************
 * Author: Michail Georgiou
 *  Last Modified: Time-stamp: <2014-07-30 15:26:51 mike_georgiou>
 *
 *
Convection_Term.cpp -- This function will compute the convection term of the
velocity residuals
*
* Written on Thursday, 17 April 2014.
********************************************/
#include "Residuals-inl.h"

double Convection_Term( double*** velocity,
                        double*** flux_x, double*** flux_y,
                        double*** flux_z,
                        double dx, double* dy, double dz,
                        int i, int j, int k)
{

  double interpolated_velocity[2];
  double derivatives[2];
  double convection_terms[3];

  //X-Direction - 4th order accurate - Uniform Grid

  //Interpolated velocities necessary for the computation of the
  //derivative
  for (int vi=0; vi<2; vi++)
    {
      interpolated_velocity[vi]=
        Interpolation(velocity[k][j][i+vi],
                      velocity[k][j][i-1+vi]);
    }


  double product[2];
  for (int vi=0; vi<2; vi++)
    {
      product[vi] = interpolated_velocity[vi]*flux_x[k][j][i+vi];
    }

  //First term of derivative (eq 67)
  derivatives[0] =9./8.*Derivative( product[1],product[0],
                                    dx,1);

  //Interpolated velocities necessary for the computation of the derivative
  for (int vi=0; vi<2; vi++)
    {
      interpolated_velocity[vi] =
        Interpolation( velocity[k][j][i+vi*3],
                       velocity[k][j][i-3+vi*3]);
    }

  for (int vi=0, vj=-1; vi<2; vi++, vj+=3)
    {
      product[vi] = interpolated_velocity[vi]*flux_x[k][j][i+vj];
    }

  derivatives[1] =-1./8.*Derivative( product[1],product[0],
                                     dx,3);

  //Summing the componnets of this relation
  convection_terms[0]=0.;
  for (int vi=0; vi<2; vi++)
    convection_terms[0]+=derivatives[vi];



  //Y-Direction - Non Uniform Grid - Second order accurate (e1 60)
  for (int vi=0; vi<2; vi++)
    {
      interpolated_velocity[0] =
        Interpolation_Y( velocity[k][j+vi][i], dy[j+vi],
                         velocity[k][j-1+vi][i], dy[j-1+vi]);
    }

  for (int vi=0; vi<2; vi++)
    product[vi] = interpolated_velocity[vi]*flux_y[k][j+vi][i];


  convection_terms[1]= Derivative(product[1],product[0],
                                  2.*dy[j], 1);


  //Z- Direction 4rth order accurate.
  //Interpolated velocities necessary for the computation of the
  //derivative
  for (int vi=0; vi<2; vi++)
    {
      interpolated_velocity[vi] =
        Interpolation( velocity[k+vi][j][i],
                       velocity[k-1+vi][j][i]);
    }


  for (int vi=0; vi<2; vi++)
    product[vi] = interpolated_velocity[vi]*flux_z[k+vi][j][i];


  //First term of derivative (eq 67)
  derivatives[0] =9./8.*Derivative( product[1],product[0],
                                    dz,1);

  //Interpolated velocities necessary for the computation of the
  //derivative
  for (int vi=0; vi<2; vi++)
    {
      interpolated_velocity[vi] =
        Interpolation( velocity[k+vi*3][j][i],
                       velocity[k-3+vi*3][j][i]);
    }


  for (int vi=0, vj=-1; vi<2; vi++, vj+=3)
    {
      product[vi] = interpolated_velocity[vi]*flux_z[k+vj][j][i];
    }

  derivatives[1] =-1./8.*Derivative( product[1],product[0],
                                     dz,3);

  //Summing the componnets of this relation
  convection_terms[2]=0.;
  for (int vi=0; vi<2; vi++)
    convection_terms[2]+=derivatives[vi];


  //Summing the Components of the Convective fluxes
  double convection_total=0.;
  for (int index=0; index<3; index++)
    convection_total += convection_terms[index];

  return convection_total;

}
