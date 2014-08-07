/*******************************************
 * Author: Michail Georgiou
 *  Last Modified: Time-stamp: <2014-07-30 17:37:01 mike_georgiou>
 *
 *
Velocity_Residual_Y_Implicit.cpp -- This program will compute the
velocity  residuals of the Y-momentum equation. These residuals will
be used for the implicit calculation of velocity_tilda.
*
* Written on Wednesday, 28 May 2014.
********************************************/

#include"Residuals.h"
#include"Residuals-inl.h"

void Velocity_Residual_Y_Implicit
( double*** residual_y,double*** velocity_x,
  double*** velocity_y,double*** velocity_z,
  double*** flux_x,double*** flux_y,
  double***flux_z,
  double*** temperature,
  double*** eddy_viscosity,
  double Reynolds,
  double source,
  double dx, double* dy, double dz,
  double time_total,
  int i, int j, int k,
  double* explicit_term)


{

  //Convection Term
  double convection= Convection_Term(velocity_y,
                                     flux_x, flux_y,flux_z,
                                     dx, dy, dz,
                                     i, j, k);


  //Viscous Term YX
  double viscous_components[3];
  viscous_components[0]=
    Viscous_Component_YX(velocity_x, velocity_y,
                         temperature,
                         eddy_viscosity,
                         Reynolds,
                         dx, dy,
                         i, j, k);

  //Viscous Term YY
  viscous_components[1]=
    Viscous_Component_YY_Implicit(velocity_x, velocity_y,
                                  velocity_z,
                                  temperature,
                                  eddy_viscosity,
                                  Reynolds,
                                  dx, dy,dz,
                                  i, j, k,
                                  explicit_term);


  //Viscous Term YZ
  viscous_components[2]=
    Viscous_Component_YZ(velocity_y, velocity_z,
                         temperature,
                         eddy_viscosity,
                         Reynolds,
                         dy,dz,
                         i, j, k);


  double viscous_total=0.;
  for(int index=0; index<3; index++)
    viscous_total += viscous_components[index];





  residual_y[k][j][i] =
    -convection + viscous_total +source;


}
