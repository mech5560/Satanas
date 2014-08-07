/*******************************************
 * Author: Michail Georgiou
 *  Last Modified: Time-stamp: <2014-05-21 14:04:09 mike_georgiou>
 *
 *
Forcing_Term_Christos.cpp -- This function introduces a forcing term in
the Velocity Residuals. This case is adapted from the "Accurate
Projection  Methods for the Incompressible Navier Stokes Equations" by
D. L. Brown et al. The problem that is studied is 2D and the expected
solution is presented in that specific paper
*
* Written on Tuesday, 20 May 2014.
********************************************/

#include "Forcing_Term_Christos.h"

double Forcing_Term_Christos_Y(double x_local, double y_local,
                               double time)
{

  //definition of omega
  double omega = 0.;//1 +sin(2.*pi*time*time);
  double omega_t = 0.;// 4.*pi*time*cos(2.*pi*time*time);

  //Definition of the y components of the forcing term
  double y_component_1 = 3.*y_local*y_local-2.*y_local;
  double y_component_2 = y_local*y_local*(y_local-1);


  //velocity_x components
  double velocity_x= cos(2.*pi*(x_local-omega))*y_component_1;
  double velocity_y = 2.*pi*sin(2.*pi*(x_local-omega))*y_component_2;


  double y_component_2_y = 3.*y_local*y_local-2.*y_local;
  double y_component_2_yy = 6.*y_local-2.;


  // derivatives of "v" with respect to t
  double velocity_y_t =
    -4.*pi*pi*omega_t*cos(2.*pi*(x_local-omega))*y_component_2;

  // derivatives of "v" with respect to x
  double velocity_y_x =
    4.*pi*pi*(cos(2.*pi*(x_local-omega)))*y_component_2;

  double velocity_y_xx =
    -8.*pi*pi*pi* (sin(2.*pi*(x_local-omega)))*y_component_2;


  // derivatives of "v" with respect to y
  double velocity_y_y =
    2.*pi*sin(2.*pi*(x_local-omega))*y_component_2_y;

  double velocity_y_yy =
    2.*pi*sin(2.*pi*(x_local-omega))*y_component_2_yy;

  double pressure_y =
    -omega_t/(2.*pi)*sin(2.*pi*(x_local-omega))
    *(2.*pi*cos(2.*pi*y_local) -2.*pi) 
    -nu*cos(2.*pi*(x_local-omega))
    *(-4.*pi*cos(2.*pi*y_local) +2.*pi);

  double left_side =
    velocity_y_t + velocity_x*velocity_y_x + velocity_y*velocity_y_y;


  double right_side=
    -pressure_y +nu*(velocity_y_yy +velocity_y_xx );

  return right_side-left_side;

}
