/*******************************************
 * Author: Michail Georgiou 
*  Last Modified: Time-stamp: <2014-07-28 12:12:34 mike_georgiou>   
*
*
correlation_computation.cpp -- This function will compute two point
    correlations and reynold stresses. It will have an interface in
    order to define the desired output from terminal
*
* Written on Monday, 28 July 2014.
********************************************/
#include "fluctuation_computation.h"
#include "fluctuation_structures.h"

int main(int argc, char** argv)
{
  //structure that contains information about the grid
  grid_info grid;

  //structure that contains the inputs of the files.
  data inputs;

 
  //these two variables are used to specify the time that the
  //statistical quantities will be computed.
  int time_step, final_time;

  grid_reader( &grid.ldx, &grid.ldy, &grid.ldz,
               &time_step, &final_time);


  //Allocating memory for the arrays that will read the inputs.
  inputs.fluct_x=Matrix_Allocator(grid);
  inputs.fluct_y=Matrix_Allocator(grid);
  inputs.fluct_z=Matrix_Allocator(grid);

  inputs.mean_x = new double[grid.ldy];
  inputs.mean_y = new double[grid.ldy];
  inputs.mean_z = new double[grid.ldy];




}
