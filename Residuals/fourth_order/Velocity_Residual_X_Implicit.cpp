/*******************************************
 * Author: Michail Georgiou
 *  Last Modified: Time-stamp: <2014-07-30 16:40:26 mike_georgiou>
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


void Velocity_Residual_X_Implicit( double*** residual_x,
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
  //Convection Term
  double  convection= Convection_Term(velocity_x,
                                      flux_x, flux_y,flux_z,
                                      dx, dy, dz,
                                      i, j, k);


  //Viscous Term XX
  double viscous_components[3];
  viscous_components[0] =
    Viscous_Component_XX(velocity_x,velocity_y,
                         velocity_z,
                         temperature,
                         eddy_viscosity,
                         Reynolds,
                         dx, dy, dz,
                         i, j, k);


  //Viscous Term XY
  viscous_components[1] =
    Viscous_Component_XY_Implicit(velocity_x,velocity_y,
                                  temperature,
                                  eddy_viscosity,
                                  Reynolds,
                                  dx, dy,
                                  i, j, k,
                                  explicit_term);

  //Viscous Term XY
  viscous_components[2] =
    Viscous_Component_XZ(velocity_x,velocity_z,
                         temperature,
                         eddy_viscosity,
                         Reynolds,
                         dx, dz,
                         i, j, k);


  double viscous_total=0.;
  for(int index=0; index<3; index++)
    viscous_total += viscous_components[index];


  residual_x[k][j][i] = -convection + viscous_total + source;



}
