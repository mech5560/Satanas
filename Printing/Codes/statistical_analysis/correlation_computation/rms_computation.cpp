/*******************************************
 * Author: Michail Georgiou 
*  Last Modified: Time-stamp: <2014-07-28 16:19:27 mike_georgiou>   
*
*
rms_computation.cpp -- This function computes the rms of the
    inputted quantity 
*
* Written on Monday, 28 July 2014.
********************************************/

#include "fluctuation_computation.h"

void rms_computation(double ***quantity,
                     int time_step, const char* name,
                     int ldx, int ldy, int ldz)
{

  stringstream ss;
  // Creating the output files
  string format = ".bin";
  string output;
  ss<<name<<time_step<<format;
  output = ss.str();

  string finalName;
  ofstream  outfile;
  outfile.open(output,ios::out | ios::binary);



for (int k = 0; k < ldz; k++){
  for (int j = 0; j < ldy; j++){
    for (int i = 0; i < ldx; i++){
      
      // Computing and storing the rms. 
      double temp = sqrt(quantity[k][j][i]*quantity[k][j][i]);
      outfile.write( (char*)&temp,sizeof(double));

    }
  }	    
 }   
 outfile.close(); 
}
