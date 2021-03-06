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


void File_Reader_Curve(int* level_x, int* level_y, int* level_z,
                       int* curve_xxy, int* curve_yxy,
                       int* curve_xxz, int* curve_zxz,
                       int* curve_yyz, int* curve_zyz, int*);

void ghost_reader( int *left_x, int *right_x,
                   int *left_y, int *right_y,
                   int *left_z, int *right_z);

#endif
