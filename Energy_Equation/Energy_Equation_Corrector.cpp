/*******************************************
 * Author: Michail Georgiou
 *  Last Modified: Time-stamp: <2014-05-01 13:09:08 mike_georgiou>
 *
 *
Energy_Equation.cpp -- This function solves the energy equation of my
problem. Since I am dealing with a liquid water flow inside a pipe the equation
that I am solving is eq.17 from the Lessani-Papalexandris paper without the time
derivative of the pressure. The scheme I am using is fourth order accurate in
the streamwise and spanwise direction(Z) and second order accurate in the
vertical directiion(Y). The stensils I am using can be found at the
Lessani-Papalexandris paper.
*
* Written on Thursday, 24 April 2014.
********************************************/

#include"Energy_Equation.h"
#include"Energy_Equation-inl.h"

void Energy_Equation_Corrector(double*** temperature_new,
                               double*** temperature_avg, double*** temperature,
                               double*** velocity_x, double*** velocity_y,
                               double*** velocity_z,
															 double*** rho, double Reynolds, double Prandtl,
															 double dx, double* dy, double dz, double dt,
                               int ldx, int ldy,  int ldz)
{

  double convection;
  double viscous_term;

  for (int k=0; k<ldz; k++){
    for (int j=0; j<ldy; j++){
      for (int i=0; i<ldx; i++){


        // Convective Terms
        convection=Energy_Convection(temperature_avg,
                                     velocity_x,velocity_y,velocity_z,
                                     dx,dy,dz,
                                     i,j,k);


        //Viscous_Terms
        viscous_term=Energy_Viscous(temperature_avg,
                                    velocity_x,velocity_y,velocity_z,
                                    dx,dy,dz,
                                    i,j,k);



        double denominator= 1./(Reynolds*Prandtl*rho[k][j][i]
                                *Heat_Capacity(temperature[k][j][i]));

        temperature_new[k][j][i] =
          temperature[k][j][i]
          + dt*( -convection +(viscous_term/denominator));


      }
    }
  }



}
