/*******************************************
 * Author: Michail Georgiou
 *  Last Modified: Time-stamp: <2014-05-26 09:12:04 mike_georgiou>
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

double Viscous_Component_XY_2ND_Order(double*** velocity_x,
                                      double*** velocity_y,
				      double*** temperature, 
                                      double Reynolds,
                                      double dx, double* dy,
                                      int i, int j, int k)
{

  double derivative_y[2], dy_total=0.;

  //Calculation of the du/dy component
  for (int vi=0; vi<2; vi++)
    {
      dy_total=dy[j+vi]+dy[j+vi-1];
      derivative_y[vi] = Derivative(velocity_x[k][j+vi][i],
				    velocity_x[k][j+vi-1][i],
				    dy_total, 1);
    }


  // Calculation of the dv/dx component
  // interpolating the velocities at i\pm 1/2 (j-1,j,j+1)
  double interpolation_x[3][2];
  for(int vi=0; vi<2; vi++){
    for(int vj=0; vj<3; vj++){
  
      interpolation_x[vj][vi] = 
	Interpolation(velocity_y[k][j+vj-1][i+vi], 
		      velocity_y[k][j+vj-1][i+vi-1]); 
					
    }
  }

  //computing the derivative dv/dx at j-1,j,j+1
  double derivative_x[3];
  for(int vi=0; vi<3; vi++){
      
    derivative_x[vi]= Derivative(interpolation_x[vi][1],
				 interpolation_x[vi][0],
				 dx, 1);
  }

  //interpolation in the x direction
  double final_derivative_x[2];
  for(int vi=0, vj=1; vi<2; vi++, vj++){
    
    final_derivative_x[vi]=  Interpolation(derivative_x[vj],
					   derivative_x[vj-1]);
  }
  


  //Computing the viscosities.
  double viscosity[2];
  for (int vi=0; vi<2; vi++)
    {
      viscosity[vi]=
        Viscosity_Calculator(Interpolation(temperature[k][j+vi][i],
                                           temperature[k][j+vi-1][i]));
    }

  //Summing the X-component of the Viscous Term of the X-Momentum
  //equation
  double viscous_terms[2];
  for (int vi=0; vi<2; vi++)
    {
      viscous_terms[vi] =viscosity[vi]*(derivative_y[vi]                   
					+final_derivative_x[vi]);
    }

  dy_total=2.*dy[j];
  double result =
    1./Reynolds*(1.*Derivative(viscous_terms[1],
			       viscous_terms[0],
			       dy_total,1));
  
  return result;
}
