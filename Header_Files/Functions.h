/*  Last Modified Time-stamp: <2014-08-06 13:16:01 mike_georgiou> */

#ifndef Functions
#define Functions

/* Allocating Functions*/
void Allocator( int ldx, int ldy, int ldz,
                int lx, int rx,
                int ly, int ry,
                int lz, int rz,
                Ar *Arr);

void DeAllocator( Ar *Arr,
                  int ldz, int ldy, int ldx,
                  int lx, int rx,
                  int ly, int ry,
                  int lz, int rz);

void Next_Step(Ar* Arr);
void Predictor_To_Corrector(Ar* Arr);


void Density_Calculator(double*** rho,
                        double*** T,
                        int ldx, int ldy, int ldz);

void BC_Single(double ***data,
               int ldx, int ldy, int ldz,
               int lx, int rx,
               int ly, int ry,
               int lz, int rz,
               int index,
               double bc_top, double bc_bottom,
               double *dy);



void BC_Tilda(double*** velocity_x_tilda, double*** velocity_y_tilda,
              double*** velocity_z_tilda,
              int ldx, int ldy, int ldz,
              int lx, int rx,
              int ly, int ry,
              int lz, int rz);

void BC_Velocities(double*** velocity_x,
                   double*** velocity_y,
                   double*** velocity_z,
                   int ldx, int ldy, int ldz,
                   int lx, int rx,
                   int ly, int ry,
                   int lz, int rz,
                   int index,
                   double bc_x_top, double bc_x_bottom,
                   double bc_y_top, double bc_y_bottom,
                   double bc_z_top, double bc_z_bottom,
                   double *dy,double dx, double time);

/* Energy Equation Functions */
void Energy_Equation(double*** temperature_new, double*** temperature,
                     double*** velocity_x, double*** velocity_y, double***
                     velocity_z,
                     double*** rho, double Reynolds, double Prandtl,
                     double  dx, double* dy,double dz, double dt,
                     int ldx, int ldy,  int ldz);

void Energy_Equation_Corrector(double*** temperature_new,
                               double*** temperature_avg, double*** temperature,
                               double*** velocity_x, double*** velocity_y,
                               double*** velocity_z,
                               double*** rho, double Reynolds, double Prandtl,
                               double dx, double* dy, double dz, double dt,
                               int ldx, int ldy,  int ldz);

void Cubic_Mesh( double *dy,double *y,
                 double length_y,
                 int ldy,
                 int yl, int yr,
		 double* y_min);

void Hyperbolic_Mesh( double *dy, double *y,
                      double length_y,
                      int ldy,
                      int yl, int yr,
		      double* y_min);



void Initial_Zero( double ***Speed_X,
                   int ldz, int ldy, int ldx,
                   int lz, int rz,
                   int ly, int ry,
                   int lx, int rx);

void Initial_One( double ***Speed_X,
                  int ldz, int ldy, int ldx,
                  int lz, int rz,
                  int ly, int ry,
                  int lx, int rx);

void Initial_Reader(double*** velocity_x, double*** velocity_y,
                    double*** velocity_z,double*** pressure,
		    int left_x, int right_x,
		    int left_y, int right_y,
		    int left_z, int right_z,
                    int ldx, int ldy, int ldz);

void Initial_Christos(double*** velocity_x, double*** velocity_y,
                      double*** velocity_z,
                      double dx,
                      int ldx, int ldy, int ldz);

void Initial_Brown_2(double*** velocity_x, double*** velocity_y,
                     double*** velocity_z,
                     double dx, double* dy,
                     int ldx, int ldy, int ldz);

void Pertubation_Introducer(double*** velocity_x, double***velocity_y,
                            double*** velocity_z,
                            double length_x, double length_y,
                            double length_z,
                            double dx, double *dy, double dz,
                            int ldx, int ldy, int ldz);

void Initial_Conditions_Turbulence(double*** velocity_x,
                                   double*** velocity_y,
                                   double*** velocity_z,
                                   double Reynolds, double dt,
                                   double dx, double* dy, double dz,
                                   int ldx, int ldy, int ldz);


void Print_Domain(double dx, double* dy, double dz,
                  int ldx, int ldy, int ldz);


void Print_Data( double ***velocity_x, double ***velocity_y,
                 double ***velocity_z, double ***pressure,
                 int ldx, int ldy, int ldz,
                 int left_x,int right_x,
                 int left_y, int right_y,
                 int left_z, int right_z, int time_index);

void Print_Binary(double ***A,
		  int ldx, int ldy, int ldz,
		  int left_x,int right_x,
		  int left_y, int right_y, 
		  int left_z, int right_z,
		  int time_index,const char *mike);

void Vorticity_Computation(double*** velocity_x,
                           double*** velocity_y,
                           double*** velocity_z,
			   double dx, double* dy, double dz,
                           int ldx, int ldy, int ldz,
                           int time_index);


void Fluctuation_Computation(double*** velocity_x,
			     double*** velocity_y,
			     double*** velocity_z,
			     int ldx, int ldy, int ldz,
			     int time_index);

void Velocity_Residual_X( double*** residual_x, double*** velocity_x,
                          double*** velocity_y, double*** velocity_z,
                          double*** flux_x, double*** flux_y, double*** flux_z,
                          double*** temperature,
			  double*** eddy_viscosity,
			  double Reynolds,
                          double source,
                          double dx, double* dy, double dz,
                          double time,
                          int ldx, int ldy, int ldz);

void Velocity_Residual_Y( double*** residual_y,double*** velocity_x,
                          double*** velocity_y,double*** velocity_z,
                          double*** flux_x,double*** flux_y, double***flux_z,
                          double*** temperature, 
			  double*** eddy_viscosity,
			  double Reynolds,
                          double source,
                          double dx, double* dy, double dz,
                          double time,
                          int ldx, int ldy, int ldz);


void Velocity_Residual_Z( double*** residual_z, double*** velocity_x,
                          double*** velocity_y, double*** velocity_z,
                          double*** flux_x, double*** flux_y,
                          double*** flux_z,
                          double*** temperature, 
			  double*** eddy_viscosity,
			  double Reynolds,
                          double source,
                          double dx, double* dy, double dz,
                          double time,
                          int ldx, int ldy, int ldz);


/* Poisson Solver*/
void Pressure_Update(double*** pressure, double*** pressure_old,
                     double*** potential,
                     int ldx, int ldy, int ldz,
                     int left_x, int right_x,
                     int left_y, int right_y,
                     int left_z, int right_z);



void BCSG(double *sL, int *ijL, double *X, double *D, double *Pre,
          double error, int L, int N, int& flag);

void BCSG_Printing(double *sL, int *ijL, double *X, double *D, double *Pre,
                   double error, int L, int N, int& flag);


void Vector_Constructor(double *s_A, double *Precond_A, int *ij_A,
                        double Coefficients_Z[4], double Coefficients_X[4], double *dy,
                        int ldz, int ldy, int ldx, int Nze);


void Right_Hand_Side_Poisson(double* rhs, double*** velocity_x,
                             double*** velocity_y, double*** velocity_z,
                             double*** rho_new, double*** rho,double*** rho_old,
                             double dx, double* dy, double dz,
                             double dt,
                             int ldx, int ldy, int ldz);



/* Velocity Update*/
void Velocity_Update_X(double*** velocity_x, double*** velocity_x_tilda,
                       double*** rho, double*** pressure,
                       double dx, double dt,
                       int ldx, int ldy, int ldz);


void Velocity_Update_Y(double*** velocity_y, double*** velocity_y_tilda,
                       double*** rho, double*** pressure,
                       double* dy, double dt,
                       int ldx, int ldy, int ldz);

void Velocity_Update_Z(double*** velocity_z, double*** velocity_z_tilda,
                       double*** rho, double*** pressure,
                       double dz, double dt,
                       int ldx, int ldy, int ldz);


/* Flux Evaluation */
void Flux_Evaluation_X(double*** flux_x, double*** velocity_x,
                       double*** rho, double*** pressure,
                       double dx, double dt,
                       int ldx, int ldy, int ldz);

void Flux_Evaluation_Y(double*** flux_y, double*** velocity_y,
                       double*** rho, double*** pressure,
                       double* dy, double dt,
                       int ldx, int ldy, int ldz);

void Flux_Evaluation_Z(double*** flux_z, double*** velocity_z,
                       double*** rho, double*** pressure,
                       double dz, double dt,
                       int ldx, int ldy, int ldz);


void
Intermediate_Velocity_Predictor_X(double***velocity_x_tilda,
				  double*** residual_x,
				  double*** residual_x_old,
				  double*** velocity_x,
				  double*** velocity_y,
				  double*** velocity_z,
				  double*** flux_x, double***flux_y,
				  double***flux_z,
				  double*** rho_new, double*** rho,
				  double*** temperature,
				  double*** pressure,
				  double*** eddy_viscosity,
				  double Reynolds,double source,
				  double implicit_scheme,
				  double dx, double* dy,  double dz,
				  double dt, double time_total,
				  int ldx, int ldy, int ldz);

void 
Intermediate_Velocity_Predictor_Y(double***velocity_y_tilda,
				  double*** residual_y,
				  double*** residual_y_old,
				  double*** velocity_x,
				  double*** velocity_y,
				  double*** velocity_z,
				  double*** flux_x, double***flux_y,
				  double*** flux_z,
				  double*** rho_new, double*** rho,
				  double*** temperature,
				  double*** pressure,
				  double*** eddy_viscosity,
				  double Reynolds,double source,
				  double implicit_scheme,
				  double dx, double* dy,  double dz,
				  double dt, double time_total,
				  int ldx, int ldy, int ldz);



void
Intermediate_Velocity_Predictor_Z(double***velocity_z_tilda,
				  double*** residual_z,
				  double*** residual_z_old,
				  double*** velocity_x,
				  double*** velocity_y,
				  double*** velocity_z,
				  double*** flux_x, double***flux_y,
				  double***flux_z,
				  double*** rho_new, double*** rho,
				  double*** temperature,
				  double*** pressure,
				  double*** eddy_viscosity,
				  double Reynolds,double source,
				  double implicit_scheme,
				  double dx, double* dy,  double dz,
				  double dt, double time_total,
				  int ldx, int ldy, int ldz);




void Intermediate_Velocity_Corrector_X(double***velocity_x_tilda,
                                       double*** residual_x,
                                       double*** residual_x_old,
                                       double*** velocity_x_old,
                                       double*** velocity_x,
                                       double*** velocity_y,
                                       double*** velocity_z,
                                       double*** flux_x,
                                       double*** flux_y,
                                       double*** flux_z,
                                       double*** rho_new,
                                       double*** rho,
                                       double*** temperature,
                                       double*** pressure,
				       double*** eddy_viscosity,
                                       double Reynolds,double source,
				       double implicit_scheme,
                                       double dx, double* dy,
                                       double dz,
                                       double dt, double time_total,
                                       int ldx, int ldy, int ldz);


void 
Intermediate_Velocity_Corrector_Y(double***velocity_y_tilda,
				  double*** residual_y,
				  double*** residual_y_old,
				  double*** velocity_y_old,
				  double*** velocity_x,
				  double*** velocity_y,
				  double*** velocity_z,
				  double*** flux_x, double***flux_y,
				  double*** flux_z,
				  double*** rho_new, double*** rho,
				  double*** temperature,
				  double*** pressure,
				  double*** eddy_viscosity,
				  double Reynolds,double source,
				  double implicit_scheme,
				  double dx, double* dy,  double dz,
				  double dt, double time_total,
				  int ldx, int ldy, int ldz);

void
Intermediate_Velocity_Corrector_Z(double***velocity_z_tilda,
				  double*** residual_z,
				  double*** residual_z_old,
				  double*** velocity_z_old,
				  double*** velocity_x,
				  double*** velocity_y,
				  double*** velocity_z,
				  double*** flux_x, double***flux_y,
				  double***flux_z,
				  double*** rho_new, double*** rho,
				  double*** temperature,
				  double*** pressure,
				  double*** eddy_viscosity,
				  double Reynolds,double source,
				  double implicit_scheme,
				  double dx, double* dy,  double dz,
				  double dt, double time_total,
				  int ldx, int ldy, int ldz);

void Continuity_Printer_Y(double*** velocity_y, double* dy,
                          int ldx, int ldy, int ldz,
                          int time_index, char *mike);



void Maximum_Velocities(double*** velocity_x, double*** velocity_y,
                        double*** velocity_z,
			double* u_max, double* v_max, double* w_max,
                        int ldx, int ldy, int ldz);


void LES_Modelling(double*** eddy_viscosity,
		   double*** velocity_x,
		   double*** velocity_y, double*** velocity_z,
		   double*** rho,
		   double dx, double* dy, double dz,
		   int ldx, int ldy, int ldz);


void Information_Reader(int *ldx,int *ldy, int *ldz,
                        double *cfl, double *tolerance, int* iterations,double*,
                        int *printing_variable);

void Bamdad_Reader(double*** velocity_x, double*** velocity_y,
                   double*** velocity_z,double ***pressure,
                   int left_x, int right_x,
                   int left_y, int right_y,
                   int left_z, int right_z,
                   int ldx, int ldy, int ldz);

void Bamdad_Reader_2ND(double*** velocity_x, double*** velocity_y,
                       double*** velocity_z,double *pressure,
                       int left_x, int right_x,
                       int left_y, int right_y,
                       int left_z, int right_z,
                       int ldx, int ldy, int ldz);
#endif
