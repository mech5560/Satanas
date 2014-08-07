/*******************************************
 * Author: Michail Georgiou
 *  Last Modified: Time-stamp: <2014-06-17 11:19:14 mike_georgiou>
 *
 *
Print_2D_Non_Uniform.cpp -- This program will save the output of my code
for the case of a non-uniform grid.
*
* Written on Tuesday,  3 June 2014.
********************************************/

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <cstring>
#include <sstream>

using namespace std;
void Print_2D_Non_Uniform(double*** data,
                          double dx, double* dy, double dz,
                          int ldx, int ldy, int ldz,
                          int time_index, int index,
                          const char* mike )


{
  stringstream ss;
  string out = "";

  string format = ".dat";
  string finalName;



      ss<<out<<mike<<time_index<<1<<format;
      finalName = ss.str();

      
      ofstream outfile;
      outfile.open(finalName);
      ss.str("");



      double y_local = 0.;
      for (int j = 0; j < ldy; j++){
        double x_local =0.;
        y_local+= dy[j];
        for (int i = 0; i < ldx; i++){

          x_local += dx/2.;
          outfile<<x_local<<" "<<y_local<<" "<<data[ldz/2][j][i]<<endl;
          x_local+=dx/2.;


        }
        outfile<<endl;
        y_local+= dy[j];
      }
      outfile.close();

      // XZ plane

      ss<<out<<mike<<time_index<<2<<format;
      finalName = ss.str();

  

      outfile.open(finalName);
      ss.str("");

      double z_local = 0.;
      for (int j = 0; j < ldz; j++){
        double x_local =0.;
        z_local+= dz/2.;
        for (int i = 0; i < ldx; i++){

          x_local += dx/2.;
          outfile<<x_local<<" "<<z_local<<" "<<data[j][ldy/2][i]<<endl;
          x_local+=dx/2.;


        }
        outfile<<endl;
        z_local+= dz/2.;
      }
      outfile.close();



      ss<<out<<mike<<time_index<<3<<format;
      finalName = ss.str();

  

      outfile.open(finalName);
      ss.str("");


      z_local = 0.;
      for (int j = 0; j < ldz; j++){
        double y_local =0.;
        z_local+= dz/2.;
        for (int i = 0; i < ldx; i++){

          y_local += dy[i];
          outfile<<y_local<<" "<<z_local<<" "<<data[j][i][ldx/2]<<endl;
          y_local+=dy[i];


        }
        outfile<<endl;
        z_local+= dz/2.;
      }

      outfile.close();
    


}
