/*******************************************
 * Author: Michail Georgiou
 *  Last Modified: Time-stamp: <2014-05-26 09:17:58 mike_georgiou>
 *
 *
Viscous_Component_XY_2ND_Order.cpp -- This function computes the d/dy
 component 
 of the X-Momentum equation with second order accurate schemes.
 *
 * Written on Wednesday, 23 April 2014.
 ********************************************/

#include"Residuals.h"
#include"Residuals-inl.h"

double Viscous_Component_YX_2ND_Order(double*** velocity_x,
                                      double*** velocity_y,
				      double*** temperature, 
                                      double Reynolds,
                                      double dx, double* dy,
                                      int i, int j, int k)
{

  double derivative_x[2];

  //Calculation of the du/dy component
  for (int vi=0; vi<2; vi++)
    {
      derivative_x[vi] = Derivative(velocity_y[k][j][i+vi],
				    velocity_y[k][j][i+vi-1],
				    dx, 1);
    }


  // Calculation of the du/dy component
  // interpolating the velocities at j\pm 1/2 (i-1,i,i+1)
  double interpolation_y[3][2];
  for(int vi=0; vi<3; vi++){
    for(int vj=0; vj<2; vj++){
  
      interpolation_y[vj][vi] = Interpolation(velocity_x[k][j+vj][i+vi-1], 
					      velocity_x[k][j+vj-1][i+vi-1]);
					
    }
  }

  //computing the derivative dv/dx at j-1,j,j+1
  double derivative_y[3];
  for(int vi=0; vi<3; vi++){
      
    derivative_y[vi]= Derivative(interpolation_y[1][vi],
				 interpolation_y[0][vi],
				 dx, 1);
  }

  //interpolation in the x direction
  double final_derivative_y[2];
  for(int vi=0, vj=1; vi<2; vi++, vj++){
    
    final_derivative_y[vi]=  Interpolation(derivative_y[vj],
					   derivative_y[vj-1]);
  }
  


  //Computing the viscosities.
  double viscosity[2];
  for (int vi=0; vi<2; vi++)
    {
      viscosity[vi]=
        Viscosity_Calculator(Interpolation(temperature[k][j][i+vi],
                                           temperature[k][j][i+vi-1]));
    }

  //Summing the X-component of the Viscous Term of the X-Momentum
  //equation
  double viscous_terms[2];
  for (int vi=0; vi<2; vi++)
    {
      viscous_terms[vi] =viscosity[vi]*(derivative_x[vi]                   
					+final_derivative_y[vi]);
    }

  double result =
    1./Reynolds*(1.*Derivative(viscous_terms[1],
			       viscous_terms[0],
			       dx,1));
  
  return result;
}
