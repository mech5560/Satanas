/*  Last Modified Time-stamp: <2014-06-02 12:02:19 mike_georgiou> */
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <cstring>
#include <sstream>

using namespace std;

void Print_2D_Matrix_Ghost(double ***A,
			   int ldx, int ldy, int ldz,
			   int left_x, int right_x,
			   int left_y, int right_y,
			   int left_z, int right_z,
			   int time_index,const char *mike)
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


 

       for (int j=-left_y; j<ldy+right_y; j++){
	 for (int i=-left_x; i<ldx+right_x; i++){

	   outfile<<A[0][j][i]<<" ";
	 }
	 
	 outfile<<endl;
       }
       //   outfile.close();
       // ss.str("");
       // }


}
