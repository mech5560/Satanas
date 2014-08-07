#ifndef VORTICITY_COMPUTATION_H
#define VORTICITY_COMPUTATION_H

#include <cstdlib>
#include "../../../Residuals/Residuals-inl.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include<stdio.h>
#include <string>


using namespace std;

double *** Matrix_Allocator(int ldx, int ldy, int ldz,
                            int x_left,int x_right,
                            int y_left,int y_right,
                            int z_left,int z_right);


void Free_Matrix(double ***pA,
                 int x_left, int y_left, int z_left);

void File_Reader(int* level_x, int* level_y, int* level_z, int* ghost);

void read_grid(int* ldx, int* ldy, int* ldz);


void data_reader_1D( double *velocity,const char *name ,int ldx,
                     int left, int right);


void data_reader( double ***velocity,
                  string name, 
                  int ldx, int ldy, int ldz,
                  int left_x, int right_x,
                  int left_y, int right_y,
                  int left_z, int right_z);


void output_data(double ***output, double *grid_1, double *grid_2,
                 string name, int ld1, int ld2,
                 int left_1, int right_1,
                 int left_2, int right_2,
                 int level,
                 int index, int plane_index);

#endif
