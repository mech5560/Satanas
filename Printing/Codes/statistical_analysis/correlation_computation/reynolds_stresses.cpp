/*******************************************
 * Author: Michail Georgiou
 *  Last Modified: Time-stamp: <2014-07-29 10:50:35 mike_georgiou>
 *
 *
reynolds_stresses.cpp -- This function will compute the reynolds
    stresses for the turbulent channel flow. In order to compute the
    reynolds stresses I will give as an input two fluctuating
    components of the velocity, multiply them and then compute the
    mean which in my case, because the flow is statistically
    homogeneous i ll average over the streamwise(X) and the
    spanwise(Z) direction.
    *
    * Written on Tuesday, 29 July 2014.
    ********************************************/

#include "fluctuation_computation.h"
#include "fluctuation_structures.h"

void reynolds_stresses(double ***quantity_1, double ***quantity_2,
                       int time_step, const char* name,
                       grid_info grid)
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

  //Allocating memory to save the product of the reynold's stresses
  //which they will be averaged afterwards
  double ***product = Matrix_Allocator(grid);


  //computing the product of the reynolds stresses
  for (int k = 0; k < grid.ldz; k++){
    for (int j = 0; j < grid.ldy; j++){
      for (int i = 0; i < grid.ldx; i++){

       product[k][j][i] = quantity_1[k][j][i]*quantity_2[k][j][i];

      }
    }
  }

  //Averaging the product
  for (int j = 0; j < grid.ldy; j++){

    double sum=0.;
    for (int k = 0; k < grid.ldz; k++){
      for (int i = 0; i < grid.ldx; i++){

        //computing u_mean
        sum += product[k][j][i];

      }
    }

    sum/=(grid.ldx*grid.ldz);
    outfile.write( (char*)&sum,sizeof(double));
  }


  Free_Matrix(product, grid.left_x, grid.left_y, grid.left_z);
}
