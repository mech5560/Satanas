/*******************************************
 * Author: Michail Georgiou
 *  Last Modified: Time-stamp: <2014-07-29 17:48:13 mike_georgiou>
 *
 *
two_point_correlation.cpp -- This function computes the two-point
    correlations between  fluctuating components of the velocity
    along the given direction which is defined by the index variable.
    *
    * Written on Tuesday, 29 July 2014.
    ********************************************/

#include "fluctuation_computation.h"
#include "fluctuation_structures.h"

void two_point_correlation(double ***quantity_1, double ***quantity_2,
                           double *x, double *z,
                           int y_position, int index,
                           int time_index, const char*name,
                           grid_info grid)
{


  stringstream ss;
  // Creating the output files
  string format = ".bin";
  string output;
  ss<<name<<time_index<<format;
  output = ss.str();

  string finalName;
  ofstream  outfile;
  outfile.open(output,ios::out | ios::binary);

  //Computing the normalizing quantity first.
  double *mean= new double [grid.ldy];

  for (int j = 0; j < grid.ldy; j++){

    double sum=0.;
    for (int k = 0; k < grid.ldz; k++){
      for (int i = 0; i < grid.ldx; i++){

        //computing u_mean
        sum += quantity_1[k][j][i]*quantity_2[k][j][i];
      }
    }
    mean[j] = sum/(grid.ldx*grid.ldz);
  }


  if (index==1) // computing along the x
    {

      for (int i=0; i<grid.ldx; i++){
        double sum =0.;
        for (int k = 0; k < grid.ldz; k++){

           sum += quantity_1[k][y_position][0]*quantity_2[k][y_position][i];


        }
        double temp = (sum/grid.ldz)/mean[y_position];
        outfile<<x[i]<<" "<<temp<<endl;
      }

    }
  else if(index==2)
    {
      for (int k=0; k<grid.ldz; k++){
        double sum =0.;
        for (int i = 0; i < grid.ldx; i++){

           sum += quantity_1[0][y_position][i]*quantity_2[k][y_position][i];


        }
        double temp = (sum/grid.ldx)/mean[y_position];
        outfile<<z[k]<<" "<<temp<<endl;
      }

      
    }

  delete [] mean;
}
