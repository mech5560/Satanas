/*******************************************
 * Author: Michail Georgiou 
*  Last Modified: Time-stamp: <2014-07-29 17:04:56 mike_georgiou>   
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

  //Defining the number of ghost cells in each direction.
  //They are constant and for this reason i am declaring theme here.
  grid.left_x=0; grid.right_x=0;
  grid.left_y=0; grid.right_y=0;
  grid.left_z=0; grid.right_z=0;

  //structure that contains the inputs of the files.
  data inputs;

 
  //these two variables are used to specify the time that the
  //statistical quantities will be computed.
  int time_step=0, final_time;

  grid_reader( &grid.ldx, &grid.ldy, &grid.ldz,
               &time_step, &final_time);


  //Allocating memory for the arrays that will read the inputs.
  inputs.fluct_x=Matrix_Allocator(grid);
  inputs.fluct_y=Matrix_Allocator(grid);
  inputs.fluct_z=Matrix_Allocator(grid);

  inputs.mean_x = new double[grid.ldy];
  inputs.mean_y = new double[grid.ldy];
  inputs.mean_z = new double[grid.ldy];

  inputs.x = new double[grid.ldx];
  inputs.y = new double[grid.ldy];
  inputs.z = new double[grid.ldz];


  //Reading the fluctuations from an external file.
  data_reader(inputs.fluct_x, "Ufluctuation", time_step,grid);
  data_reader(inputs.fluct_y, "Vfluctuation", time_step,grid);
  data_reader(inputs.fluct_z, "Wfluctuation", time_step,grid);

  data_reader_1D( inputs.mean_x,"Umean",  time_step,1,  grid.ldy);
  data_reader_1D( inputs.mean_y,"Vmean",  time_step,1,  grid.ldy);
  data_reader_1D( inputs.mean_z,"Wmean",  time_step,1,  grid.ldy);

  data_reader_1D( inputs.x,"x",  time_step, 2,  grid.ldx);
  data_reader_1D( inputs.y,"y",  time_step, 2,  grid.ldy);
  data_reader_1D( inputs.z,"z",  time_step, 2,  grid.ldz);


  int i=100;
  while ( i!=0)
    {
      cout<<"Please define what data you want to be produced.\n\n";

      cout<<"If you want to compute the rms quantities press 1\n";

      cout<<"If you want to compute the Reynolds stresses";
      cout<<" press 2\n";

      cout<<"If you want to compute  two points correlations press 3\n";

      cout<<"If you want to exit the program press 0\n";
      cin>>i;
        
  switch (i)
    {
    case 0: 
      cout<<"Exiting program. Goodbye!\n";
      break;


    case 1:
      rms_computation(inputs.fluct_x,time_step, "Urms",
                      grid.ldx, grid.ldy, grid.ldz);

      rms_computation(inputs.fluct_y,time_step, "Vrms",
                      grid.ldx, grid.ldy, grid.ldz);

      rms_computation(inputs.fluct_z,time_step, "Wrms",
                      grid.ldx, grid.ldy, grid.ldz);

      break;

    case 2:
      stresses_computation(inputs.fluct_x, inputs.fluct_y,
                           inputs.fluct_z, time_step, grid);

      break;

    case 3:
      int y_index;
      cout<<"Please define the vertical position that you want the";
      cout<<"correlation to be computed\n";
      cin>>y_index;

       two_point_correlation_computation(inputs.fluct_x, inputs.fluct_y,
                                    inputs.fluct_z, inputs.x, 
                                         inputs.z,  y_index,
                                         time_step,  grid);
      break;




    }


    }
  Free_Matrix(inputs.fluct_x, grid.left_x, grid.left_y, grid.left_z);
  Free_Matrix(inputs.fluct_y, grid.left_x, grid.left_y, grid.left_z);
  Free_Matrix(inputs.fluct_z, grid.left_x, grid.left_y, grid.left_z);

}
