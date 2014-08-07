/*******************************************
 * Author: Michail Georgiou
 *  Last Modified: Time-stamp: <2014-07-30 18:01:20 mike_georgiou>
 *
 *
Velocity_Residual_X_Implicit.cpp -- This program will compute the
velocity  residuals of the X-momentum equation. These residuals will
be used for the implicit calculation of velocity_tilda.
*
* Written on Wednesday, 28 May 2014.
********************************************/

#include"Residuals.h"
#include"Residuals-inl.h"

void Velocity_Residual_Z_Implicit( double*** residual_z,
                                   double*** velocity_x,
                                   double*** velocity_y,
                                   double*** velocity_z,
                                   double*** flux_x, double*** flux_y,
                                   double*** flux_z,
                                   double*** temperature,
                                   double*** eddy_viscosity,
                                   double Reynolds,
                                   double source,
                                   double dx, double* dy, double dz,
                                   double time_total,
                                   int i, int j, int k,
                                   double* explicit_term)
{

  //Computing the convection term of the residuals by calling the
  double convection= Convection_Term(velocity_z,
                                     flux_x, flux_y,flux_z,
                                     dx, dy, dz,
                                     i, j, k);

  //Viscous_Term_ZX
  double viscous_components[3];
  viscous_components[0]=
    Viscous_Component_ZX(velocity_x, velocity_z,
                         temperature,
                         eddy_viscosity,
                         Reynolds,
                         dx, dz,
                         i, j, k);

  //Viscous Term ZY
  viscous_components[1]=
    Viscous_Component_ZY_Implicit(velocity_y, velocity_z,
                                  temperature,
                                  eddy_viscosity,
                                  Reynolds,
                                  dy,dz,
                                  i, j, k,
                                  explicit_term);


  //Viscous Term ZZ
  viscous_components[2]=
    Viscous_Component_ZZ(velocity_x, velocity_y,
                         velocity_z,
                         temperature,
                         eddy_viscosity,
                         Reynolds,
                         dx, dy, dz,
                         i, j, k);


  double viscous_total=0.;
  for(int index=0; index<3; index++)
    viscous_total += viscous_components[index];



  residual_z[k][j][i] = -convection + viscous_total + source;

}
