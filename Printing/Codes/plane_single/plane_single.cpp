/*******************************************
 * Author: Michail Georgiou
 *  Last Modified: Time-stamp: <2014-08-07 16:37:00 mike_georgiou>
 *
 *
This program creates the necessary file from gnuplot to produce
surface plots

* Written on Friday,  6 June 2014.
********************************************/

#include"plane_data_creator.h"

int main(int argc, char** argv)
{

  int ldx, ldy, ldz;
  int level_x, level_y, level_z, ghost,
    left_x, right_x,
    left_y, right_y,
    left_z, right_z;


  File_Reader(&level_x, &level_y, &level_z, &ghost);
  read_grid(&ldx, &ldy, &ldz);


  ghost_reader( &left_x, &right_x,
                &left_y, &right_y,
                &left_z, &right_z);


  cout<<level_x<<" "<<level_y<<" "<<level_z<<endl;
  cout<<ldx<<" "<<ldy<<" "<<ldz<<endl;

  int time_index;
  string name1;
  cout<<"Please define the time you want to be printed \n";
  cin>>time_index;

  cout<<"Please the value that you want to be printed \n";
  cin>>name1;

  stringstream ss;

  ss<<name1<<time_index;

  //Allocating the necessary memory for the process
  double*** temp, *d2, *d1, *d3;

  temp=Matrix_Allocator(ldx, ldy, ldz,
                        left_x,right_x,
                        left_y,right_y,
                        left_z,right_z);


  d1=new double[ldx+left_x + right_x]; d1+=left_x;
  d2=new double[ldy+left_y + right_y]; d2+=left_y;
  d3=new double[ldz+left_z + right_z]; d3+=left_z;


  data_reader_1D(d1, "x",ldx,left_x,right_x);
  data_reader_1D(d2, "y",ldy,left_y,right_y);
  data_reader_1D(d3, "z",ldz,left_z,right_z);


  string name = ss.str();
  data_reader( temp, name, ldx,  ldy,  ldz,
               left_x,right_x,
               left_y,right_y,
               left_z,right_z);



  //Saving the output array of data xy plane
  ss.str("");
  ss<<name1<<time_index;
  name = ss.str();

  output_data(temp, d1, d2,
              name,  ldx,  ldy,
              left_x,right_x,
              left_y,right_y,level_z,
              ghost, 1);

  //Saving the output array of data xz plane
  output_data(temp, d1, d3,
              name,  ldx,  ldz,
              left_x,right_x,
              left_z,right_z,
              level_y,
              ghost, 2);

  //Saving the output array of data yz plane

  output_data(temp, d3, d2,
              name,  ldz,  ldy,
              left_z,right_z,
              left_y,right_y,
              level_x,
              ghost, 3);

  d1-=left_x;
  d2-=left_y;
  d3-=left_z;

  delete []d1;
  delete []d2;
  delete []d3;


  Free_Matrix(temp,left_x,left_y,left_z);
}
