/*******************************************
 * Author: Michail Georgiou
 *  Last Modified: Time-stamp: <2014-08-06 11:29:33 mike_georgiou>
 *
 *
Initialize_Conditions_Turbulence.cpp -- This function initializes the problem for the
turbulent pipe flow. Specifically, the streamwise velocity "w" is
being initialized by using the log law profile. Also, in all
directions, pertubations of order ??? will be introduced.

The pressure gradient will be kept constant in the streamwise direction.
*
* Written on Monday,  5 May 2014.
********************************************/
#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <ctime>

#include"Initial_Conditions_Turbulence.h"

#define PI 4.*atan(1.)

void Initial_Conditions_Turbulence(double*** velocity_x,
                                   double*** velocity_y,
                                   double*** velocity_z,
                                   double Reynolds, double dt,
                                   double dx, double* dy, double dz,
                                   int ldx, int ldy, int ldz)
{
  // Reading data for the initialization of the turbulent flow


  // Computing the friction velocity and the viscosity which is
  // necessary for the implementation of the law of the wall
  double friction_velocity=1.;
  double viscosity = friction_velocity/Reynolds;

  double y_local=0.;
  for (int j=1; j<(ldy)/2+1; j++ ){

    y_local+= dy[j-1];
    double condition=y_local*friction_velocity/viscosity;
    if (condition<10.)
      {
        velocity_x[0][j-1][0]= condition;
      }
    else
      {
        velocity_x[0][j-1][0]=2.5*log (y_local*friction_velocity/viscosity)+5.;
      }
    y_local+=dy[j-1];

  }

  for(int j=0; j<(ldy)/2+1; j++)
    {
      velocity_x[0][ldy-1-j][0] = velocity_x[0][j][0];
    }

  for (int k = 0; k < ldz; k++){
    for (int j = 0; j < ldy; j++){
      for (int i = 0; i < ldx; i++){
        velocity_x[k][j][i]=velocity_x[0][j][0];
      }
    }
  }


  //Seeding the rand() function
  srand(time(NULL));

  //Exactly the bandads case.
  double relaxation_x = 0.5;
  double relaxation_yz=0.05;


  for (int k = 0; k < ldz; k++){
    for (int j = 0; j < ldy; j++){
      for (int i = 0; i < ldx; i++){

        velocity_x[k][j][i]=  (velocity_x[k][j][i]+
                               relaxation_x*velocity_x[k][j][i]*(drand()));

        velocity_y[k][j][i]=  velocity_y[k][j][i] +
          (velocity_y[k][j][i]+(drand()*relaxation_yz))*relaxation_x*drand();


        velocity_z[k][j][i]=  velocity_z[k][j][i] +
          (velocity_z[k][j][i]+(drand()*relaxation_yz))*relaxation_x*drand();
      }
    }
  }


}
