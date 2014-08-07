#ifndef SOLVER_RESIDUALS_H
#define SOLVER_RESIDUALS_H

#include <stdio.h>

// Function Declaration
double Convection_Term( double*** velocity_x,
                        double*** flux_x, double*** flux_y, double*** flux_z,
                        double dx, double* dy, double dz,
                        int i, int j, int k);


// X-Momentum
double Viscous_Component_XX(double*** velocity_x, double*** velocity_y,
                            double*** velocity_z,
                            double*** temperature, double Reynolds,
                            double dx, double* dy, double dz,
                            int i, int j, int k);


double Viscous_Component_XY(double*** velocity_x, double*** velocity_y,
                            double*** temperature,double Reynolds,
                            double dx, double* dy,
                            int i, int j, int k);


double Viscous_Component_XZ(double*** velocity_x, double*** velocity_z,
                            double*** temperature, double Reynolds,
                            double dx, double dz,
                            int i, int j, int k);

double Forcing_Term_Christos_X(double x_local, double y_local,
                               double time);

//Y-momentum
double Viscous_Component_YX(double*** velocity_x, double*** velocity_y,
                            double*** temperature, double Reynolds,
                            double dx, double* dy,
                            int i, int j, int k);

double Viscous_Component_YY(double*** velocity_x, double*** velocity_y,
                            double*** velocity_z,
                            double*** temperature, double Reynolds,
                            double dx, double* dy, double dz,
                            int i, int j, int k);


double Viscous_Component_YZ(double*** velocity_y, double*** velocity_z,
                            double*** temperature, double Reynolds,
                            double* dy, double dz,
                            int i, int j, int k);

double Forcing_Term_Christos_Y(double x_local, double y_local,
                               double time);


//Z-momentum
double Viscous_Component_ZX(double*** velocity_x, double*** velocity_z,
                            double*** temperature, double Reynolds,
                            double dx, double dz,
                            int i, int j, int k);

double Viscous_Component_ZY(double*** velocity_y, double*** velocity_z,
                            double*** temperature, double Reynolds,
                            double* dy, double dz,
                            int i, int j, int k);


double Viscous_Component_ZZ(double*** velocity_x, double*** velocity_y,
                            double*** velocity_z,
                            double*** temperature, double Reynolds,
                            double dx, double* dy, double dz,
                            int i, int j, int k);





#endif
