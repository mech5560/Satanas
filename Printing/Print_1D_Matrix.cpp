/*  Last Modified Time-stamp: <2014-05-22 17:43:24 mike_georgiou> */
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <cstring>
#include <sstream>

using namespace std;

void Print_1D_Matrix(double *A,
                   int ldx, int ldy, int ldz,
                   int time_index, char *mike)
{
  stringstream ss;
  string out = "";

  string format = ".dat";
  string finalName;

  ss<<out<<mike<<time_index<<format;
  finalName = ss.str();
 

  ofstream outfile;
  outfile.open(finalName);


 // for (int k=0; k<ldz; k++){

 //   ss<<out<<mike<<time_index<<k<<format;
 //  finalName = ss.str();
 //  outfile.open(finalName);


 

       for (int j=0; j<ldy; j++){
	 for (int i=0; i<ldx; i++){

       outfile<<A[ldx*j+i+1]<<" ";
     }
     
    outfile<<endl;
   }
 //   outfile.close();
 // ss.str("");
 // }


}
