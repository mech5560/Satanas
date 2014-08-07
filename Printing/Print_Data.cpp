/*******************************************
 * Author: Michail Georgiou
 *  Last Modified: Time-stamp: <2014-08-04 11:15:24 mike_georgiou>
 *
 *
Print_Data.cpp -- This functio will save the problems data in binary format
*
* Written on Monday,  4 August 2014.
********************************************/
#include "Print_Data.h"

void Print_Data( double ***velocity_x, double ***velocity_y,
                 double ***velocity_z, double ***pressure,
                 int ldx, int ldy, int ldz,
                 int left_x,int right_x,
                 int left_y, int right_y,
                 int left_z, int right_z, int time_index)

{
        Print_Binary(velocity_x,
                     ldx,  ldy,  ldz,
                     left_x, right_x,
                     left_y, right_y,
                     left_z, right_z,
                     time_index,"X");

        Print_Binary(velocity_y,
                     ldx,  ldy,  ldz,
                     left_x, right_x,
                     left_y, right_y,
                     left_z, right_z,
                     time_index,"Y");

        Print_Binary(velocity_z,
                     ldx,  ldy,  ldz,
                     left_x, right_x,
                     left_y, right_y,
                     left_z, right_z,
                     time_index,"Z");

        Print_Binary(pressure,
                     ldx,  ldy,  ldz,
                     left_x, right_x,
                     left_y, right_y,
                     left_z, right_z,
                     time_index,"P");

}
