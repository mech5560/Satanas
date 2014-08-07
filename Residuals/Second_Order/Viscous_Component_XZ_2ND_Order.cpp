/*******************************************
 * Author: Michail Georgiou
 *  Last Modified: Time-stamp: <2014-05-19 14:59:52 mike_georgiou>
 *
 *
Viscous_Component_XZ_2ND_Order.cpp -- This function computes the d/dz
 component 
 of the X-Momentum equation with second order accurate schemes.
 *
 * Written on Wednesday, 23 April 2014.
 ********************************************/

#include"Residuals.h"
#include"Residuals-inl.h"

double Viscous_Component_XZ_2ND_Order(double*** velocity_x,
                                      double*** velocity_z,
				      double*** temperature, 
                                      double Reynolds,
                                      double dx, double dz,
                                      int i, int j, int k)
{

  double derivative_z[2];
  //Calculation of the du/dy component
  for (int vi=0; vi<2; vi++)
    {
      derivative_z[vi] = Derivative(velocity_x[k+vi][j][i],
				    velocity_x[k+vi-1][j][i],
				    dz, 1);
    }


  // Calculation of the dw/dx component
  // interpolating the velocities at i\pm 1/2 (k-1,k,k+1)
  double interpolation_x[3][2];
  for(int vi=0; vi<2; vi++){
    for(int vj=0; vj<3; vj++){
  
      interpolation_x[vj][vi] = Interpolation(velocity_z[k+vj-1][j][i+vi], 
					      velocity_z[k+vj-1][j][i+vi-1]);
					
    }
  }

  //computing the derivative dv/dx at k-1,k,k+1
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
        Viscosity_Calculator(Interpolation(temperature[k+vi][j][i],
                                           temperature[k+vi-1][j][i]));
    }

  //Summing the X-component of the Viscous Term of the X-Momentum
  //equation
  double viscous_terms[2];
  for (int vi=0; vi<2; vi++)
    {
      viscous_terms[vi] =viscosity[vi]*(derivative_z[vi]                   
					+final_derivative_x[vi]);
    }

   double result =
    1./Reynolds*(1.*Derivative(viscous_terms[1],
			       viscous_terms[0],
			       dz,1));
  
  return result;
}
