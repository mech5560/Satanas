/*******************************************
 * Author: Michail Georgiou
 *  Last Modified: Time-stamp: <2014-08-07 16:17:34 mike_georgiou>
 *
 *
output_data.cpp -- this file will create the data that are
    necessary from the gnuplot script to create the contours
    *
    * Written on Wednesday, 30 July 2014.
    ********************************************/

#include "plane_data_creator.h"
#include <iomanip>
void output_data(double ***output, double *grid_1, double *grid_2,
                 string name, int ld1, int ld2,
                 int left_1, int right_1,
                 int left_2, int right_2,
                 int level,
                 int index, int plane_index)
{
  stringstream ss;
  if (plane_index==1)
    {
      ss<<name<<"xy.dat";
      string finalName=ss.str();
      ofstream output_file;
      output_file.open(finalName,ios::out | ios:: binary);

      if(index==1)
        {
          for (int j = 0; j < ld2; j++){
            for (int i = 0; i < ld1; i++){

              output_file<<setprecision(17)<<grid_1[i]<<" ";
              output_file<<setprecision(17)<<grid_2[j]<<" ";
              output_file<<setprecision(17)<<output[level][j][i]<<endl;
            }
            output_file<<endl;
          }
          output_file.close();

        }
      else if(index==2)
        {

          for (int j = -left_2; j < ld2+right_2; j++){
            for (int i = -left_1; i < ld1+right_1; i++){

              output_file<<setprecision(17)<<grid_1[i]<<" ";
              output_file<<setprecision(17)<<grid_2[j]<<" ";
              output_file<<setprecision(17)<<output[level][j][i]<<endl;

            }
            output_file<<endl;
          }
          output_file.close();
        }

    }
  else if(plane_index==2)
    {
      ss<<name<<"xz.dat";
      string finalName=ss.str();
      ofstream output_file;
      output_file.open(finalName,ios::out | ios:: binary);


      if(index==1)
        {
          for (int j = 0; j < ld2; j++){
            for (int i = 0; i < ld1; i++){


              output_file<<setprecision(17)<<grid_1[i]<<" ";
              output_file<<setprecision(17)<<grid_2[j]<<" ";
              output_file<<setprecision(17)<<output[j][level][i]<<endl;


            }
            output_file<<endl;
          }
          output_file.close();

        }
      else if(index==2)
        {

          for (int j = -left_2; j < ld2+right_2; j++){
            for (int i = -left_1; i < ld1+right_1; i++){

              output_file<<setprecision(17)<<grid_1[i]<<" ";
              output_file<<setprecision(17)<<grid_2[j]<<" ";
              output_file<<setprecision(17)<<output[j][level][i]<<endl;

            }
            output_file<<endl;
          }
          output_file.close();
        }


    }
  else if(plane_index==3)
    {
      ss<<name<<"yz.dat";
      string finalName=ss.str();
      ofstream output_file;
      output_file.open(finalName,ios::out | ios:: binary);

      if(index==1)
        {
          for (int j = 0; j < ld2; j++){
            for (int i = 0; i < ld1; i++){

              output_file<<setprecision(17)<<grid_1[i]<<" ";
              output_file<<setprecision(17)<<grid_2[j]<<" ";
              output_file<<setprecision(17)<<output[i][j][level]<<endl;



            }
            output_file<<endl;
          }
          output_file.close();

        }
      else if(index==2)
        {

          for (int j = -left_2; j < ld2+right_2; j++){
            for (int i = -left_1; i < ld1+right_1; i++){

              output_file<<setprecision(17)<<grid_1[i]<<" ";
              output_file<<setprecision(17)<<grid_2[j]<<" ";
              output_file<<setprecision(17)<<output[i][j][level]<<endl;

            }
            output_file<<endl;
          }
          output_file.close();
        }

    }




}
