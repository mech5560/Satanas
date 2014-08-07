/*******************************************
 * Author: Michail Georgiou
 *  Last Modified: Time-stamp: <2014-07-28 09:48:22 mike_georgiou>
 *
 *
mean_computation.cpp -- this function will compute the mean of the
    inputted quantity ONLY for the case where the flow is
    statistically homogeneous in the streamwise (X) and spanwise (Z)
    direction.
    *
    * Written on Friday, 25 July 2014.
    ********************************************/


#include"fluctuation_computation.h"

void mean_computation(double* mean, double ***quantity,
                      int time_step, const char* name,
                      int ldx, int ldy, int ldz)
{

  stringstream ss;
  // Creating the output files
  string format = ".bin";
  string output;
  ss<<name<<"mean"<<time_step<<format;
  output = ss.str();


  string finalName;
  ofstream  outfile;
  outfile.open(output,ios::out | ios::binary);


  for (int j = 0; j < ldy; j++){

    double sum=0.;
    for (int k = 0; k < ldz; k++){
      for (int i = 0; i < ldx; i++){

        //computing u_mean
        sum += quantity[k][j][i];

      }
    }

    mean[j] = sum/(ldx*ldz);
    outfile.write( (char*)&mean[j],sizeof(double));
  }





}
