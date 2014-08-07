/*******************************************
 * Author: Michail Georgiou
 *  Last Modified: Time-stamp: <2014-07-25 10:55:37 mike_georgiou>
 *
 *
Matrix_Allocator.cpp -- This function allocates contiguous memory for my 3D
matrice. In addition, it introduces a number of ghost cells, which is given as
an input in all the edges of my domain
*
* Written on Tuesday, 29 April 2014.
********************************************/

#include<cstdlib>
#include "fluctuation_structures.h"

double *** Matrix_Allocator(grid_info grid)
{

  int ldx=grid.ldx; int x_left=grid.left_x; int x_right=grid.right_x;
  int ldy=grid.ldy; int y_left=grid.left_y; int y_right=grid.right_y;
  int ldz=grid.ldz; int z_left=grid.left_z; int z_right=grid.right_z;


  int z_total=ldz+z_left+z_right;
  int y_total=ldy+y_left+y_right;
  int x_total=ldx+x_left+x_right;

  double ***pA;

  pA= new double**[z_total]; pA+=z_left;
  pA[-z_left]= new double* [z_total*y_total] ; pA[-z_left]+=y_left;
  pA[-z_left][-y_left]= new double [z_total*y_total*x_total];
  pA[-z_left][-y_left] +=x_left;



  // Pointer Assignment
  for (int j = -z_left; j < ldz+z_right; j++)
    {
      if (j !=-z_left)
        {
          pA[j] = pA[j-1] + y_total;
          pA[j][-y_left] = pA[j-1][-y_left] + y_total*x_total;
        }
      for (int i=-y_left+1; i<ldy+y_right; i++)
        {
          pA[j][i] = pA[j][i-1] + x_total;
        }

    }

  return pA;

}
