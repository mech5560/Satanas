/*******************************************
 * Author: Michail Georgiou 
*  Last Modified: Time-stamp: <2014-07-04 16:39:39 mike_georgiou>   
*
*
Dynamic_Smagorinsky.cpp -- This code implements the dynamic Smagorinsky
mode in order to compute the eddy viscosity based on that model. In
simple words, this model dynamically tests the smallest resolved
scales and based on their behaviour the Smagarinsky constant is
computed which is later used by the LES_Modelling function to compute
the eddy viscosity
*
* Written on Friday,  4 July 2014.
********************************************/

#include "LES_Modelling.h"

void Dynamic_Smagorinsky(double*** smagorinsky_constant,
			 double*** velocity_x,
			 double*** velocity_y, double*** velocity_z,
			 double*** rho,
			 double dx, double* dy, double dz,
			 int ldx, int ldy, int ldz,
			 int left_x, int right_x,
			 int left_y, int right_y,
			 int left_z, int right_z)
{

double
    ***u_over_x, ***u_over_y, ***u_over_z,
    ***v_over_x, ***v_over_y, ***v_over_z,
    ***w_over_x, ***w_over_y, ***w_over_z,

    ***u_over_x_filtered, ***u_over_y_filtered, ***u_over_z_filtered,
    ***v_over_x_filtered, ***v_over_y_filtered, ***v_over_z_filtered,
    ***w_over_x_filtered, ***w_over_y_filtered, ***w_over_z_filtered;




  //Allocating memory for the derivatives of the velocity_x
  u_over_x = Matrix_Allocator(ldx, ldy, ldz, left_x, right_x,
			      left_y, right_y, left_z, right_z);

  u_over_y = Matrix_Allocator(ldx, ldy, ldz, left_x, right_x,
			      left_y, right_y, left_z, right_z);

  u_over_z = Matrix_Allocator(ldx, ldy, ldz, left_x, right_x,
			      left_y, right_y, left_z, right_z);

  //Allocating memory for the derivatives of the velocity_y
  v_over_x = Matrix_Allocator(ldx, ldy, ldz, left_x, right_x,
			      left_y, right_y, left_z, right_z);

  v_over_y = Matrix_Allocator(ldx, ldy, ldz, left_x, right_x,
			      left_y, right_y, left_z, right_z);

  v_over_z = Matrix_Allocator(ldx, ldy, ldz, left_x, right_x,
			      left_y, right_y, left_z, right_z);

  //Allocating memory for the derivatives of the velocity_z
  w_over_x = Matrix_Allocator(ldx, ldy, ldz, left_x, right_x,
			      left_y, right_y, left_z, right_z);

  w_over_y = Matrix_Allocator(ldx, ldy, ldz, left_x, right_x,
			      left_y, right_y, left_z, right_z);

  w_over_z = Matrix_Allocator(ldx, ldy, ldz, left_x, right_x,
			      left_y, right_y, left_z, right_z);








}
