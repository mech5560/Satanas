/*******************************************
 * Author: Michail Georgiou 
*  Last Modified: Time-stamp: <2014-08-06 17:54:29 mike_georgiou>   
*
*
Print_Divergence.cpp -- In this code I will print each component of the
    divergence separately in order to trace where a possible bug might be
    situated.
*
* Written on Wednesday,  6 August 2014.
********************************************/

#include "../Poisson/Right_Hand_Side_Poisson.h"
#include "../Poisson/RHS.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sstream>

using namespace std;
void Print_Divergence(double*** velocity_x,
                      double*** velocity_y, double*** velocity_z,
                      double*** rho_new, double*** rho,double*** rho_old,
                      double dx, double* dy, double dz,
                      double dt, int time_index,const char *a,
                      int ldx, int ldy, int ldz)
{

  double density_derivative, derivative[3];


  stringstream ss;

  string directory = "./Printing/Postprocessing/";
  string name = "dudx";
  string format = ".bin";
  string finalName;
  ss<<directory<<name<<a<<time_index<<format;
  finalName = ss.str();


  ofstream  outfile1;
  outfile1.open(finalName,ios::out | ios::binary);

  name="dvdy";
  ss.str("");
  ss<<directory<<name<<a<<time_index<<format;
  finalName = ss.str();
  ofstream  outfile2;
  outfile2.open(finalName,ios::out | ios::binary);


  name="dwdz";
  ss.str("");
  ss<<directory<<name<<a<<time_index<<format;
  finalName = ss.str();
  ofstream  outfile3;
  outfile3.open(finalName,ios::out | ios::binary);

  name="drdt";
  ss.str("");
  ss<<directory<<name<<a<<time_index<<format;
  finalName = ss.str();
  ofstream  outfile4;
  outfile4.open(finalName,ios::out | ios::binary);


  for (int k=0; k<ldz; k++){
    for (int j=0; j<ldy; j++){
      for (int i=0; i<ldx; i++){

        //Calculation of the time derivative of the Density

        // density_derivative =(3.0*rho_new[k][j][i]-4.0*rho[k][j][i]
        //                     +1.0*rho_old[k][j][i])/(2.*dt);

        //First Order, Just for Checking
        density_derivative = (rho_new[k][j][i]-rho[k][j][i])/(dt);
        outfile4.write( (char*)&density_derivative,sizeof(double));


        //Divergence X-Component
        derivative[0]=Divergence_X(velocity_x,rho_new,
                                   dx,
                                   i, j, k);
        outfile1.write( (char*)&derivative[0],sizeof(double));


        derivative[1]=Divergence_Y(velocity_y,rho_new,
                                   dy,
                                   i,j,k);
        outfile2.write( (char*)&derivative[1],sizeof(double));

        derivative[2]=Divergence_Z(velocity_z,rho_new,
                                   dz,
                                   i, j, k);
        outfile3.write( (char*)&derivative[2],sizeof(double));



      }
    }
  }

}
