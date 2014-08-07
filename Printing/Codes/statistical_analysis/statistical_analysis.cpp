/*******************************************
 * Author: Michail Georgiou
 *  Last Modified: Time-stamp: <2014-07-25 11:56:15 mike_georgiou>
 *
 *
fluctuation_computation.cpp -- This program computes the statistical
    quantities that are necessary to describe a turbulent field
    *
    * Written on Thursday, 24 July 2014.
    ********************************************/


#include "fluctuation_computation.h"
#include "fluctuation_structures.h"

int main(int argc, char** argv)
{

  // Defining the quantities that will be computed.
  int final_time, time_step=0;
  grid_info grid;
  quantities field;

  //Defining the number of ghost cells in each direction.
  //They are constant and for this reason i am declaring theme here.
  grid.left_x=3; grid.right_x=3;
  grid.left_y=1; grid.right_y=1;
  grid.left_z=3; grid.right_z=3;

  // Reading information about the domain and the time steps that will
  // be used for averaging
  grid_reader( &grid.ldx, &grid.ldy, &grid.ldz,
               &time_step, &final_time);


  //Allocating memory in order to read the velocity components
  field.velocity_x = Matrix_Allocator(grid);
  field.velocity_y = Matrix_Allocator(grid);
  field.velocity_z = Matrix_Allocator(grid);

  data_reader(field.velocity_x, "X", time_step,grid);
  data_reader(field.velocity_y, "Y", time_step,grid);
  data_reader(field.velocity_z, "Z", time_step,grid);

  // These quantities will be used in order to average throught the
  // x and the z direction

  double u_mean[grid.ldy], v_mean[grid.ldy], w_mean[grid.ldy];

  // computing and saving the means
  mean_computation( u_mean, field.velocity_x,
                    time_step,"U",
                    grid.ldx,  grid.ldy, grid.ldz);

  mean_computation( v_mean, field.velocity_y,
                    time_step,"V",
                    grid.ldx,  grid.ldy, grid.ldz);

  mean_computation( w_mean, field.velocity_z,
                    time_step,"W",
                    grid.ldx,  grid.ldy, grid.ldz);


  //computing and saving the fluctuations
  fluctuation_computation( u_mean, field.velocity_x,
                           time_step, "U",
                           grid.ldx, grid.ldy, grid.ldz);

  fluctuation_computation( v_mean, field.velocity_y,
                           time_step, "V",
                           grid.ldx, grid.ldy, grid.ldz);

  fluctuation_computation( w_mean, field.velocity_z,
                           time_step, "W",
                           grid.ldx, grid.ldy, grid.ldz);


  Free_Matrix(field.velocity_x,grid.left_x,grid.left_y,grid.left_z);
  Free_Matrix(field.velocity_y,grid.left_x,grid.left_y,grid.left_z);
  Free_Matrix(field.velocity_z,grid.left_x,grid.left_y,grid.left_z);

}
