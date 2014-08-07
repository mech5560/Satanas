/*******************************************
 * Author: Michail Georgiou 
*  Last Modified: Time-stamp: <2014-08-04 12:55:00 mike_georgiou>   
*
*
Next_Step.cpp -- This function is switcing the arrays in order to
proceed into the next time step
*
* Written on Tuesday,  6 May 2014.
********************************************/
#include "../Struct.h"

void Next_Step(Ar* Arr)
{
  double*** Temp;

      /*Passing the data to proceed  to the next time step*/
      Temp=Arr->velocity_x;
      Arr->velocity_x= Arr->velocity_x_new;
      Arr->velocity_x_new = Temp;

      Temp=Arr->velocity_y;
      Arr->velocity_y= Arr->velocity_y_new;
      Arr->velocity_y_new = Temp;

      Temp=Arr->velocity_z;
      Arr->velocity_z= Arr->velocity_z_new;
      Arr->velocity_z_new = Temp;

      Temp=Arr->temperature;
      Arr->temperature = Arr->temperature_new;
      Arr->temperature_new = Temp;

      Temp = Arr->rho_old;
      Arr->rho_old = Arr->rho;
      Arr->rho = Temp;

      Temp = Arr->rho;
      Arr->rho = Arr->rho_new;
      Arr->rho_new = Temp;

      Temp = Arr->residual_x_old;
      Arr->residual_x_old = Arr->residual_x;
      Arr->residual_x = Temp;

      Temp = Arr->residual_y_old;
      Arr->residual_y_old = Arr->residual_y;
      Arr->residual_y = Temp;

      Temp = Arr->residual_z_old;
      Arr->residual_z_old = Arr->residual_z;
      Arr->residual_z = Temp;

      // // Introducing q which in fact is pressure^{n-1}
      // Temp = Arr->pressure_old;
      // Arr->pressure_old = Arr->pressure;
      // Arr->pressure = Temp;

}
