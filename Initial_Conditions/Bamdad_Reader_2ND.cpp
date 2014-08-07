/*******************************************
 * Author: Michail Georgiou
 *  Last Modified: Time-stamp: <2014-08-07 16:37:52 mike_georgiou>
 *
 *
Initial_Reader.cpp -- This program reads the initial velocity
profiles from a number of data files that will be introduced by the
user in this folder.
*
* Written on Thursday, 15 May 2014.
********************************************/

#include "Initial_Reader.h"

using namespace std;

void Bamdad_Reader_2ND(double*** velocity_x, double*** velocity_y,
                       double*** velocity_z, double *pressure,
                       int left_x, int right_x,
                       int left_y, int right_y,
                       int left_z, int right_z,
                       int ldx, int ldy, int ldz)
{



  // Opening the .dat file to read the necessary information
  ifstream input_x("out_sol_pc.dat");
  //X
  if(input_x.is_open())
    {
      double temp;
      for (int k = -left_z; k < ldz+right_z; k++){
        for (int j = -left_y; j < ldy+right_y; j++){
          for (int i = -left_x; i < ldx+right_x; i++){

            input_x>>temp;
            input_x >> velocity_x[k][j][i];
            input_x >> velocity_y[k][j][i];
            input_x >> velocity_z[k][j][i];
            input_x >> pressure[k*ldy*ldx + j*ldx +1 +i];
            input_x>>temp;

          }
        }
      }
    }
  else {cout << "Unable to open file X\n";}


  //Subtracting the mean of the pressure from the pressure field
      for (int k = -left_z; k < ldz+right_z; k++){
        for (int j = -left_y; j < ldy+right_y; j++){
          for (int i = -left_x; i < ldx+right_x; i++){


        pressure[k*ldy*ldx + j*ldx +i +1]=
          pressure[k*ldy*ldx + j*ldx +i +1]+3.219836036253870e+05;

          }
        }
      }
    




  input_x.close();
}