/*******************************************
 * Author: Michail Georgiou
 *  Last Modified: Time-stamp: <2014-07-29 11:07:52 mike_georgiou>
 *
 *
stresses_computation.cpp -- this function will just call the reynolds stresses
    function
    *
    * Written on Tuesday, 29 July 2014.
    ********************************************/

#include "fluctuation_computation.h"
#include "fluctuation_structures.h"

void stresses_computation(double ***fluct_x, double ***fluct_y,
                          double ***fluct_z, int time_step,
                          grid_info grid)
{

  //Rxx
  reynolds_stresses(fluct_x, fluct_x,
                    time_step,"Rxx",grid);
  //Rxy
  reynolds_stresses(fluct_x, fluct_y,
                    time_step,"Rxy",grid);
  //Rxz
  reynolds_stresses(fluct_x, fluct_z,
                    time_step,"Rxz",grid);


  //Ryy
  reynolds_stresses(fluct_y, fluct_y,
                    time_step,"Ryy",grid);
  //Ryz
  reynolds_stresses(fluct_y, fluct_z,
                    time_step,"Ryz",grid);

  //Rzz
  reynolds_stresses(fluct_z, fluct_z,
                    time_step,"Rzz",grid);



}
