#ifndef PRINT_DATA_H
#define PRINT_DATA_H

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <cstring>
#include <sstream>

using namespace std;

void Print_Binary(double ***A,
                  int ldx, int ldy, int ldz,
                  int left_x,int right_x,
                  int left_y, int right_y, 
                  int left_z, int right_z,
                  int time_index,const char *mike);


#endif
