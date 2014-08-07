#ifndef RHS_H
#define RHS_H


double Divergence_X(double*** velocity_x, double*** rho_new,
		    double dx,
                    int i, int j, int k);

double Divergence_Y(double*** velocity_y, double*** rho_new,
		    double* dy,
                    int i, int j, int k);
double Divergence_Z(double*** velocity_z, double*** rho_new,
		    double dz,
                    int i, int j, int k);


#endif
