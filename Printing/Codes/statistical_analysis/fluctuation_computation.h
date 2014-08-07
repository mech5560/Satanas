#ifndef VORTICITY_COMPUTATION_H
#define VORTICITY_COMPUTATION_H


#include "../../../Residuals/Residuals-inl.h"
#include "fluctuation_structures.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include<stdio.h>
#include <string>
#include <cstdlib>
using namespace std;


double *** Matrix_Allocator(grid_info grid);

void Free_Matrix(double ***pA,
                 int x_left, int y_left, int z_left);


void grid_reader(int *ldx, int *ldy, int *ldz,
                 int *time_step, int *final_time);

void data_reader( double ***velocity,
                  const char *name, int time_index, 
                  grid_info grid);

void mean_computation(double* mean, double ***quantity,
                      int time_step, const char* name,
                      int ldx, int ldy, int ldz);

void fluctuation_computation(double* mean, double ***quantity,
                             int time_step, const char* name,
                             int ldx, int ldy, int ldz);




#endif
