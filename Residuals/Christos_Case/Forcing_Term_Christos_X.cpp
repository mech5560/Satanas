/*******************************************
 * Author: Michail Georgiou
 *  Last Modified: Time-stamp: <2014-05-22 11:43:32 mike_georgiou>
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

double Forcing_Term_Christos_X(double x_local, double y_local,
                               double time)
{

  //definition of omega
  double omega = 0.;//1 +sin(2.*pi*time*time);
  double omega_t =  0.;//4.*pi*time*cos(2.*pi*time*time);

  //Definition of the y components of the forcing term
  double y_component_1 = 3.*y_local*y_local-2.*y_local;
  double y_component_2 = y_local*y_local*(y_local-1.);


  //velocity_x components
  double velocity_x= cos(2.*pi*(x_local-omega))*y_component_1;
  double velocity_y = 2.*pi*sin(2.*pi*(x_local-omega))*y_component_2;

  //Definition of the y components of the forcing term
  double y_component_1_y = 6.*y_local-2.;
  double y_component_1_yy = 6.;


  //derivative with respect to t
  double velocity_x_t=
    2.*pi*omega_t *sin(2.*pi*(x_local-omega))*y_component_1;

  //derivative with respect to x
  double velocity_x_x=
    -2.*pi*sin(2.*pi*(x_local-omega))*y_component_1;

  //double derivative with respect to x
  double velocity_x_xx=
    -4.*pi*pi*cos(2.*pi*(x_local-omega))*y_component_1;

  //derivative with respect to y
  double velocity_x_y=
    cos(2.*pi*(x_local-omega))*y_component_1_y;

  //double derivative with respect to y
  double velocity_x_yy=
    cos(2.*pi*(x_local-omega))*y_component_1_yy;

  double pressure_x =
    -omega_t*cos(2.*pi*(x_local-omega))
    *(sin(2.*pi*y_local) -2.*pi*y_local + pi) 

    +nu*2.*pi*sin(2.*pi*(x_local-omega))
    *(-2.*sin(2.*pi*y_local) +2.*pi*y_local - pi);


  double left_side= velocity_x_t + velocity_x*velocity_x_x +
    velocity_y*velocity_x_y;

  double right_side= -pressure_x + nu*(velocity_x_xx + velocity_x_yy);

  return right_side-left_side;

}
