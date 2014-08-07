/*******************************************
 * Author: Michail Georgiou
 *  Last Modified: Time-stamp: <2014-08-07 12:04:24 mike_georgiou>
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
  int level_x, level_y, level_z, ghost;

  File_Reader(&level_x, &level_y, &level_z, &ghost);
  read_grid(&ldx, &ldy, &ldz);

  cout<<level_x<<" "<<level_y<<" "<<level_z<<endl;
  cout<<ldx<<" "<<ldy<<" "<<ldz<<endl;

  int time_index;
  cout<<"Please define the time you want to be printed \n";
  cin>>time_index;


  //Allocating the necessary memory for the process
  double*** temp, *d2, *d1, *d3, ***temp2, ***temp3, ***press;

  temp=Matrix_Allocator(ldx, ldy, ldz,
                        3,3,1,1,3,3);

  temp2=Matrix_Allocator(ldx, ldy, ldz,
                         3,3,1,1,3,3);

  temp3=Matrix_Allocator(ldx, ldy, ldz,
                         3,3,1,1,3,3);

  press=Matrix_Allocator(ldx, ldy, ldz,
                         3,3,1,1,3,3);

  d1=new double[ldx+6]; d1+=3;
  d2=new double[ldy+2]; d2+=1;
  d3=new double[ldz+6]; d3+=3;


  data_reader_1D(d1, "x",ldx,3,3);
  data_reader_1D(d2, "y",ldy,1,1);
  data_reader_1D(d3, "z",ldz,3,3);


  stringstream ss;
  ss<<"X"<<time_index;
  string name = ss.str();
  data_reader( temp, name, ldx,  ldy,  ldz,
               3,  3, 1, 1, 3,  3);

  ss.str("");
  ss<<"Y"<<time_index;
  name = ss.str();
  data_reader( temp2, name, ldx,  ldy,  ldz,
               3,  3, 1, 1, 3,  3);

  ss.str("");
  ss<<"Z"<<time_index;
  name = ss.str();
  data_reader( temp3, name, ldx,  ldy,  ldz,
               3,  3, 1, 1, 3,  3);

  ss.str("");
  ss<<"P"<<time_index;
  name = ss.str();
  data_reader( press, name, ldx,  ldy,  ldz,
               3,  3, 1, 1, 3,  3);



  //Saving the output array of data xy plane
  ss.str("");
  ss<<"X"<<time_index;
  name = ss.str();
  output_data(temp, d1, d2,
              name,  ldx,  ldy,
              3,  3, 1,  1,level_z,
              ghost, 1);

  ss.str("");
  ss<<"Y"<<time_index;
  name = ss.str();
  output_data(temp2, d1, d2,
              name,  ldx,  ldy,
              3,  3, 1,  1,level_z,
              ghost, 1);

  ss.str("");
  ss<<"Z"<<time_index;
  name = ss.str();
  output_data(temp3, d1, d2,
              name,  ldx,  ldy,
              3,  3, 1,  1,level_z,
              ghost, 1);

  ss.str("");
  ss<<"P"<<time_index;
  name = ss.str();
  output_data(press, d1, d2,
              name,  ldx,  ldy,
              3,  3, 1,  1,level_z,
              ghost, 1);


  //Saving the output array of data xz plane
  ss.str("");
  ss<<"X"<<time_index;
  name = ss.str();
  output_data(temp, d1, d3,
              name,  ldx,  ldz,
              3,  3, 3,  3,level_y,
              ghost, 2);

  ss.str("");
  ss<<"Y"<<time_index;
  name = ss.str();
  output_data(temp2, d1, d3,
              name,  ldx,  ldz,
              3,  3, 3,  3,level_y,
              ghost, 2);

  ss.str("");
  ss<<"Z"<<time_index;
  name = ss.str();
  output_data(temp3, d1, d3,
              name,  ldx,  ldz,
              3,  3, 3,  3,level_y,
              ghost, 2);

  ss.str("");
  ss<<"P"<<time_index;
  name = ss.str();
  output_data(press, d1, d3,
              name,  ldx,  ldz,
              3,  3, 3,  3,level_y,
              ghost, 2);

  //Saving the output array of data yz plane
  ss.str("");
  ss<<"X"<<time_index;
  name = ss.str();
  output_data(temp, d3, d2,
              name,  ldz,  ldy,
              3,  3, 1,  1,level_x,
              ghost, 3);

  ss.str("");
  ss<<"Y"<<time_index;
  name = ss.str();
  output_data(temp2, d3, d2,
              name,  ldz,  ldy,
              3,  3, 1,  1,level_x,
              ghost, 3);

  ss.str("");
  ss<<"Z"<<time_index;
  name = ss.str();
  output_data(temp3, d3, d2,
              name,  ldz,  ldy,
              3,  3, 1,  1,level_x,
              ghost, 3);

  ss.str("");
  ss<<"P"<<time_index;
  name = ss.str();
  output_data(press, d3, d2,
              name,  ldz,  ldy,
              3,  3, 1,  1,level_x,
              ghost, 3);




d1-=3;
d2-=1;
d3-=3;

delete []d1;
delete []d2;
delete []d3;


Free_Matrix(temp,3,1,3);
Free_Matrix(temp2,3,1,3);
Free_Matrix(temp3,3,1,3);
Free_Matrix(press,3,1,3);
}
