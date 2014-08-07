/*  Last Modified Time-stamp: <2014-06-17 16:28:40 mike_georgiou> */ 
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <cstring>
#include <sstream>

using namespace std;

void Print_Binary(double ***A,
		  int ldx, int ldy, int ldz,
		  int left_x,int right_x,
		  int left_y, int right_y, 
		  int left_z, int right_z,
		  int time_index,const char *mike)
{

  stringstream ss;

  string directory = "./Printing/Postprocessing/";
  string format = ".bin";
  string finalName;

  ss<<directory<<mike<<time_index<<format;
  finalName = ss.str();

   ofstream  outfile;
   outfile.open(finalName,ios::out | ios::binary);



for (int k = -left_z; k < ldz+right_z; k++){
  for (int j = -left_y; j < ldy+right_y; j++){
    for (int i = -left_x; i < ldx+right_x; i++){
      
      outfile.write( (char*)&A[k][j][i],sizeof(double));
    }
  }	    
 }   

 
}

