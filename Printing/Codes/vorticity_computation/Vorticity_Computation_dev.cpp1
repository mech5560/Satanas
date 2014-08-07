/*******************************************
 * Author: Michail Georgiou
 *  Last Modified: Time-stamp: <2014-06-17 13:16:47 mike_georgiou>
 *
 *
Vorticity_Computation.cpp -- This function will compute the three
components of the vorticity in the domain and it will store them into
output binary files
*
* Written on Wednesday, 11 June 2014.
********************************************/

#include "../Residuals/Residuals-inl.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;
void Vorticity_Computation(double*** velocity_x,
                           double*** velocity_y,
                           double*** velocity_z,
			   double dx, double* dy, double dz,
                           int ldx, int ldy, int ldz,
                           int time_index)
{

  // Creating the output files
  string name[3];
  name[0]="omega_x";
  name[1]="omega_y";
  name[2]="omega_z";

  stringstream ss;

  string directory = "./Printing/Postprocessing/";
  string format = ".bin";
  string finalName[3];
  ofstream  outfile[3];


  for(int vi=0; vi<3; vi++)
    {
      ss<<directory<<name[vi]<<time_index<<format;
      finalName[vi]= ss.str();
      outfile[vi].open(finalName[vi],ios::out | ios::binary);
      ss.str("");
    }


  //Computing the vorticities.
  double   u_over_y, u_over_z, v_over_x, v_over_z, w_over_x, w_over_y;

  double dy_total=0.;
  double derivative_components[2];
  for (int k = 0; k < ldz; k++){
    for (int j = 0; j < ldy; j++){
      for (int i = 0; i < ldx; i++){

	//computing dy
	dy_total=dy[j-1]+2.*dy[j]+dy[j+1];

	//computing the du/dy
	u_over_y = Derivative(velocity_x[k][j+1][i],
				      velocity_x[k][j-1][i],
				      dy_total,1);

	//computing the du/dz
	derivative_components[0]= 4./3.*Derivative(velocity_x[k+1][j][i],
						   velocity_x[k-1][j][i],
						   dz,2);
	derivative_components[1]= -1./3.*Derivative(velocity_x[k+2][j][i],
						    velocity_x[k-2][j][i],
						   dz,4);

	//Initializing the quantity to be filled
	u_over_z = 0.;
	for(int vi=0; vi<2; vi++)
	  u_over_z+= derivative_components[vi];


	//Computing the dv/dx
	derivative_components[0]= 4./3.*Derivative(velocity_y[k][j][i+1],
						   velocity_y[k][j][i-1],
						   dx,2);
	derivative_components[1]= -1./3.*Derivative(velocity_y[k][j][i+2],
						    velocity_y[k][j][i-2],
						    dx,4);

	//Initializing the quantity to be filled
	v_over_x = 0.;
	for(int vi=0; vi<2; vi++)
	  v_over_x+= derivative_components[vi];


	//computing the dv/dz
	derivative_components[0]= 4./3.*Derivative(velocity_y[k+1][j][i],
						   velocity_y[k-1][j][i],
						   dz,2);
	derivative_components[1]= -1./3.*Derivative(velocity_y[k+2][j][i],
						    velocity_y[k-2][j][i],
						   dz,4);

	//Initializing the quantity to be filled
	v_over_z = 0.;
	for(int vi=0; vi<2; vi++)
	  v_over_z+= derivative_components[vi];


	//Computing the dw/dx
	derivative_components[0]= 4./3.*Derivative(velocity_z[k][j][i+1],
						   velocity_z[k][j][i-1],
						   dx,2);
	derivative_components[1]= -1./3.*Derivative(velocity_z[k][j][i+2],
						    velocity_z[k][j][i-2],
						    dx,4);

	w_over_x = 0.;
	for(int vi=0; vi<2; vi++)
	  w_over_x+= derivative_components[vi];

	//computing dw/dy
	//computing the du/dy
	w_over_y = Derivative(velocity_z[k][j+1][i],
			      velocity_z[k][j-1][i],
			      dy_total,1);

	double omega[3]; 
	
	//omega_x
	omega[0] = w_over_y-v_over_z;
	//omega_y
	omega[1] = u_over_z-w_over_x;
	//omega_z
	omega[2] = v_over_x-u_over_y;


	//Writing  the vorticities 
	for (int vi=0; vi<3; vi++)
	  outfile[vi].write( (char*)&omega[vi],sizeof(double));
      
      }
    }
  }


}
