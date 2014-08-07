#ifndef ENERGY_EQUATION_H
#define ENERGY_EQUATION_H

double Energy_Convection(double*** temperature,
                         double*** velocity_x, double*** velocity_y,
                         double*** velocity_z,
                         double dx, double* dy, double dz,
                         int i, int j, int k);

double Energy_Viscous(double*** temperature,
											double*** velocity_x, double*** velocity_y,
											double*** velocity_z,
											double dx, double* dy, double dz,
											int i, int j, int k);
#endif
