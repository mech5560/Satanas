#ifndef PRINTING_FUNCTIONS_H
#define PRINTING_FUNCTIONS_H



void Printing_RHS(double *rhs, int time_index,
                  int ldx, int ldy, int ldz,
                  const char *a);

void Print_Divergence(double*** velocity_x,
                      double*** velocity_y, double*** velocity_z,
                      double*** rho_new, double*** rho,double*** rho_old,
                      double dx, double* dy, double dz,
                      double dt, int time_index,const char *a,
                      int ldx, int ldy, int ldz);


void Print_Divergence_2ND_Order(double*** velocity_x,
                                double*** velocity_y, double*** velocity_z,
                                double*** rho_new, double*** rho,double*** rho_old,
                                double dx, double* dy, double dz,
                                double dt, int time_index, const char *a,
                                int ldx, int ldy, int ldz);

void Print_Residuals(double*** velocity_x,
                     double*** velocity_y,
                     double*** velocity_z,
                     double*** flux_x, double*** flux_y,
                     double*** flux_z,
                     double*** temperature,
                     double*** eddy_viscosity,
                     double Reynolds,
                     double dx, double* dy, double dz,
                     int ldx, int ldy, int ldz,
                     double* explicit_term,
                     int time_index,
                     const char* a);

#endif
