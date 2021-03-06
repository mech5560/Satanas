#ifndef VORTICITY_COMPUTATION_H
#define VORTICITY_COMPUTATION_H

#include <cstdlib>
#include "../../Residuals/Residuals-inl.h"
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


#endif
