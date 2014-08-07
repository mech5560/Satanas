/*******************************************
 * Author: Michail Georgiou 
*  Last Modified: Time-stamp: <2014-07-28 09:48:07 mike_georgiou>   
*
*
fluctuation_computation.cpp -- This function will compute the fluctuating
    component of the quantity that will be given as an input
*
* Written on Friday, 25 July 2014.
********************************************/

#include"fluctuation_computation.h"

void fluctuation_computation(double* mean, double ***quantity,
                             int time_step, const char* name,
                             int ldx, int ldy, int ldz)
{

  stringstream ss;
  // Creating the output files
  string output;
  string format = ".bin";
  ss<<name<<"fluctuation"<<time_step<<format;
  output = ss.str();


  string finalName;
  ofstream  outfile;
  outfile.open(output,ios::out | ios::binary);
  ss.str("");


  for (int k = 0; k < ldz; k++){
    for (int j = 0; j < ldy; j++){
      for (int i = 0; i < ldx; i++){


        double fluctuation=(quantity[k][j][i]-mean[j]);
        outfile.write( (char*)&fluctuation,sizeof(double));
      }
    }
  }


}
