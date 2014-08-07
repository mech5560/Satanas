/*******************************************
 * Author: Michail Georgiou
 *  Last Modified: Time-stamp: <2014-07-31 14:38:10 mike_georgiou>
 *
 *
Coefficient_Calculator.cpp -- This Function computes the coefficients that
are necessary used to fill the inputs of the tridag solver extracted
by the Numerical Recipes
*
* Written on Friday, 30 May 2014.
********************************************/

#include"../Residuals/Residuals-inl.h"
#include<iostream>

using namespace std;


void Coefficient_Calculator(double*** temperature,
                            double ***eddy_viscosity,
                            double Reynolds,
                            double* coefficients,
                            double* dy, double dt,
                            double implicit_scheme,
                            int i, int j, int k)

{
  //Computing the delta_y
  double   dy_local[3];
  for (int vi = 0; vi<3; vi++)
    {
      dy_local[vi] = dy[j]+ dy[j+vi-1];

    }

  //computing the viscosities at j \pm 1/2
  double viscosity[2];
  for (int vi=0; vi<2; vi++)
    {
      viscosity[vi]=
        Viscosity_Calculator
        (Interpolation_Y(temperature[k][j+vi][i],dy_local[vi+1],
                         temperature[k][j+vi-1][i],dy_local[vi]))
        
        +Interpolation(eddy_viscosity[k][j+vi][i],
                       eddy_viscosity[k][j+vi-1][i]);

    }


  //Computing the coefficients.
  coefficients[0] =-(dt/Reynolds*(1.-implicit_scheme)
                     *(1./(dy_local[0]*dy_local[1]))
                     *(viscosity[0]) );

  coefficients[1] = +( dt/Reynolds*(1.-implicit_scheme)*
                       (viscosity[1]*dy_local[0]
                        +viscosity[0]*dy_local[2])
                       /(dy_local[0]*dy_local[1]*dy_local[2]) );


  coefficients[2] = -( dt/Reynolds*(1.-implicit_scheme)*
                       (1./(dy_local[2]*dy_local[1]))
                       *(viscosity[1]) );





}
