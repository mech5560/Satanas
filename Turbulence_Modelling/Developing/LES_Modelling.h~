#ifndef LES_MODELLING_H
#define LES_MODELLING_H

#include"../Residuals/Residuals-inl.h"
#include<cstdlib>
#include<math.h>

using namespace std;

void Gradients(double*** velocity,
               double* velocity_over_x,  double* velocity_over_y,
               double* velocity_over_z,
               int i, int j, int k,
               double dx, double* dy, double dz);


void Strain_Tensor_Computation(double*** strain_tensor,
			       double*** velocity_x, 
			       double*** velocity_y,
			       double*** velocity_z,
			       double dx, double* dy, double dz,
			       int ldx, int ldy, int ldz);


double *** Matrix_Allocator(int ldx, int ldy, int ldz,
                            int x_left,int x_right,
                            int y_left,int y_right,
                            int z_left,int z_right);

void Free_Matrix(double***, int, int, int);



void LES_Modelling(double*** eddy_viscosity,
		   double*** velocity_x,
		   double*** velocity_y, double*** velocity_z,
		   double*** rho,
		   double dx, double* dy, double dz,
		   int ldx, int ldy, int ldz);


#endif
