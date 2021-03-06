/*******************************************
 *   Author: Michail Georgiou
 * main.cpp -- This project solves the 3D navier stokes equations for a
  non-isothermal problem. Fourth order accurate conservative schemes are used in
  the spanwise(x) and streamwise(z) directions. These schemes are being adopted by
  the Lessani-Papalexandris paper. On the vertical direction(y) a non-uniform grid
  is used.
  *
  * Written on Wednesday, 30 April 2014.
  ********************************************/

//Definition of the libraries that this program will use
#include "main.h"
#include "main-inl.h"

#include "./Header_Files/Functions.h"
#include "./Header_Files/Data.h"

int ibroke =0;
void termination_handler (int signum)
{
  cout<<"Terminating the program, Please wait"<<endl;
  ibroke = 1;
}

int main (int argc, char *argv[])
{

  //Opening a file to print dts
  ofstream output_file;
  output_file.open("dt.txt",ios::out);
  if(!output_file)
    {
      cout << "Cannot open file for output.\n";
      exit(1);
    }

  //Defining the number of solution points in each direction
  length_x = 4.*pi; length_y =2.; length_z=4./3.*pi;

  Information_Reader( &ldx, &ldy, &ldz, &cfl, &tolerance,
                      &iterations, &time_total, &printing_variable);

  cout<<"The length of my domain is following, from x to z"<<endl;
  cout<< length_x<<" "<<length_y<<" "<<length_z<<" "<<endl<<endl;
  cout<<"The number of solution points follows from x to z"<<endl;
  cout<< ldx<<" "<<ldy<<" "<<ldz<<" "<<endl<<endl;
  cout<< "The simulation starts from time "<< time_total;
  cout<<" and the cfl number is "<<cfl<<endl<<endl;

  cout<<"The tolerance of the bcstab solver is "<<tolerance;
  cout<<" and the maximum no. of iterations that it can do is "<<iterations<<endl<<endl;
  cout<<"The code saves data  every "<<printing_variable<<" steps"<<endl;


  //calculating dx and dz
  dx= length_x/(ldx*1.0);
  dz= length_z/(ldz*1.0);

  //Defining the extra points on each direction depending on the BC
  left_x=3; right_x=3;
  left_y=1; right_y=1;
  left_z=3; right_z=3;

  Allocator(ldx,ldy,ldz,
            left_x,right_x,
            left_y,right_y,
            left_z,right_z,
            &Arr);

  //Calculation of the Dy's
  double dy_min=100.;
  Hyperbolic_Mesh(Arr.dy, Arr.y,
                  length_y,
                  ldy,
                  left_y,right_y,
                  &dy_min);

  Print_Domain( dx, Arr.dy,  dz,
                ldx,  ldy,  ldz);


  //Defining the Non-Zero Elements for the Poisson solver
  nze = 15*ldz*(ldy-2)*ldx + 14*ldz*ldx*2;

  //Dimension of the A matrix of the Poisson Equation
  dim_a=ldz*ldy*ldx;

  //Vectors for the Poisson Solver
  s_a = new double [nze  +2];
  ij_a = new int [nze  +2];
  rhs = new double [dim_a +1];
  precond_a = new double [dim_a +1];
  result = new double [dim_a +1];

  // Defining the Second derivative coefficients  that will be use by the
  // Vector_Constructor Function
  Coefficients_X[0] = 1./(576.*dx*dx);
  Coefficients_X[1] = -9./(96.*dx*dx);
  Coefficients_X[2] = ( 81./(64.*dx*dx) + 9./(96.*dx*dx) );
  Coefficients_X[3] = (- 81./(32.*dx*dx) - 1./(288.*dx*dx) );

  Coefficients_Z[0] = 1./(576.*dz*dz);
  Coefficients_Z[1] = -9./(96.*dz*dz);
  Coefficients_Z[2] = ( 81./(64.*dz*dz) + 9./(96.*dz*dz) );
  Coefficients_Z[3] = (- 81./(32.*dz*dz) - 1./(288.*dz*dz) );


  /////////////////////////////////////////////////////////////
  //////////////////Initial Conditions/////////////////////////

   // Initial_Conditions_Turbulence(Arr.velocity_x,
   //                              Arr.velocity_y,
   //                              Arr.velocity_z,
   //                              Reynolds,  dt,
   //                              dx, Arr.dy,  dz,
   //                              ldx,  ldy,  ldz);

  //Changed that sos
  Bamdad_Reader_2ND(Arr.velocity_x, Arr.velocity_y,
                    Arr.velocity_z, result,
                    0,  0,
                    0,  0,
                    0,  0,
                    ldx,  ldy,  ldz);

  ////Passing the Poisson solution to the Arr.pressure Array
  for (int k=0; k<ldz; k++){
    for (int j=0; j<ldy; j++){
      for (int i=0; i<ldx; i++){

        Arr.pressure[k][j][i] = result[A(i,ldx,j,ldy,k,ldz) +1];

      }
    }
  }


  BC_Velocities( Arr.velocity_x,
                 Arr.velocity_y,
                 Arr.velocity_z,
                 ldx, ldy, ldz,
                 left_x, right_x,
                 left_y, right_y,
                 left_z, right_z,
                 1,
                 velocity_x_top, velocity_x_bottom,
                 velocity_y_top, velocity_y_bottom,
                 velocity_z_top, velocity_z_bottom,
                 Arr.dy, dx, 0.);

  BC_Single(Arr.pressure,
            ldx,ldy,ldz,
            left_x,right_x,
            left_y,right_y,
            left_z,right_z,
            2,
            pressure_gradient_top, pressure_gradient_bottom,
            Arr.dy);

  Print_Data( Arr.velocity_x, Arr.velocity_y,
              Arr.velocity_z, Arr.pressure,
              ldx, ldy, ldz,
              left_x,right_x,
              left_y, right_y,
              left_z, right_z, 12);


  double u_max=0.,v_max=0.,w_max=0.;
  Maximum_Velocities(Arr.velocity_x, Arr.velocity_y,
                     Arr.velocity_z,
                     &u_max, &v_max, &w_max,
                     ldx,  ldy,  ldz);

  double max_velocity = fmax(u_max,v_max);
  max_velocity = fmax(max_velocity, w_max);

  double min_dxi = fmin(dx,dz);
  min_dxi = fmin(min_dxi,dy_min);

  cout<<"The maximum velocity is "<<max_velocity<< " and the minimum dx is "<<min_dxi<<endl;

  //Getting the smallest dt
  dt = cfl * min_dxi / max_velocity;
  cout<<dt<<endl;

  //Initializing the Arr.temperature
  Initial_One(Arr.temperature,
              ldx, ldy, ldz,
              left_x,right_x,
              left_y,right_y,
              left_z,right_z);

  BC_Single(Arr.temperature,
            ldx, ldy, ldz,
            left_x,right_x,
            left_y,right_y,
            left_z,right_z,
            1,
            temperature_top, temperature_bottom,
            Arr.dy);

  // Eliminating the projection method with this way.
  Initial_Zero(Arr.pressure_old,
               ldx, ldy, ldz,
               left_x,right_x,
               left_y,right_y,
               left_z,right_z);

  BC_Single(Arr.pressure_old,
            ldx, ldy, ldz,
            left_x,right_x,
            left_y,right_y,
            left_z,right_z,
            1,
            pressure_gradient_top, pressure_gradient_bottom,
            Arr.dy);

  //////////////////////////////////////////////////////
  /////////////////////////////////////////////////////

  //Only for the test case, this thing will be applied
  Initial_One(Arr.temperature_new,
              ldx, ldy, ldz,
              left_x,right_x,
              left_y,right_y,
              left_z,right_z);

  BC_Single(Arr.temperature_new,
            ldx, ldy, ldz,
            left_x,right_x,
            left_y,right_y,
            left_z,right_z,
            1,
            temperature_top, temperature_bottom,
            Arr.dy);


  //Initializing  the Density for each Point
  Density_Calculator(Arr.rho_old,
                     Arr.temperature,
                     ldx, ldy, ldz);
  BC_Single(Arr.rho_old,
            ldx, ldy, ldz,
            left_x,right_x,
            left_y,right_y,
            left_z,right_z,
            2,
            rho_gradient_top, rho_gradient_bottom,
            Arr.dy);


  Density_Calculator(Arr.rho,
                     Arr.temperature,
                     ldx, ldy, ldz);
  BC_Single(Arr.rho,
            ldx, ldy, ldz,
            left_x,right_x,
            left_y,right_y,
            left_z,right_z,
            2,
            rho_gradient_top, rho_gradient_bottom,
            Arr.dy);


  Density_Calculator(Arr.rho_new,
                     Arr.temperature,
                     ldx, ldy, ldz);
  BC_Single(Arr.rho_new,
            ldx, ldy, ldz,
            left_x,right_x,
            left_y,right_y,
            left_z,right_z,
            2,
            rho_gradient_top, rho_gradient_bottom,
            Arr.dy);

  //Initializing the Arr.Fluxes.
  //In order to do that I will use the Arr.Flux_Evaluation function.
  //But with the initial values as an input
  Flux_Evaluation_X(Arr.flux_x, Arr.velocity_x,
                    Arr.rho_old, Arr.pressure,
                    dx, dt,
                    ldx+1,  ldy,  ldz);

  Flux_Evaluation_Y(Arr.flux_y, Arr.velocity_y,
                    Arr.rho_old, Arr.pressure,
                    Arr.dy, dt,
                    ldx,  ldy+1, ldz);

  Flux_Evaluation_Z(Arr.flux_z, Arr.velocity_z,
                    Arr.rho_old,  Arr.pressure,
                    dz, dt,
                    ldx,  ldy,  ldz+1);


  //initializing the Arr.Residuals at the n-1 time
  //In order to do that I will use the Velosity Residual Functions.
  //but with the initial values velocities as an inpu
  Velocity_Residual_X( Arr.residual_x_old,
                       Arr.velocity_x, Arr.velocity_y, Arr.velocity_z,
                       Arr.flux_x, Arr.flux_y,  Arr.flux_z,
                       Arr.temperature,
                       Arr.eddy_viscosity,
                       Reynolds,
                       -Pressure_Gradient,
                       dx, Arr.dy,  dz,
                       time_total,
                       ldx,  ldy,  ldz);


  Velocity_Residual_Y( Arr.residual_y_old,
                       Arr.velocity_x,  Arr.velocity_y, Arr.velocity_z,
                       Arr.flux_x, Arr.flux_y,  Arr.flux_z,
                       Arr.temperature,
                       Arr.eddy_viscosity,
                       Reynolds,
                       0.,
                       dx, Arr.dy,  dz,
                       time_total,
                       ldx,  ldy,  ldz);

  Velocity_Residual_Z( Arr.residual_z_old,
                       Arr.velocity_x,  Arr.velocity_y, Arr.velocity_z,
                       Arr.flux_x, Arr.flux_y,  Arr.flux_z,
                       Arr.temperature,
                       Arr.eddy_viscosity,
                       Reynolds,
                       0.,
                       dx, Arr.dy, dz,
                       time_total,
                       ldx,  ldy, ldz);

  // Before Entering the time integration loop
  // i will define the constant vectors for the poisson solver
  Vector_Constructor(s_a, precond_a, ij_a,
                     Coefficients_Z,  Coefficients_X, Arr.dy,
                     ldx,  ldy,  ldz,  nze);

  //////////////////////////////////////////////////////////////////////
  //////////////////////Time Integration Loop///////////////////////////
  //////////////////////////////////////////////////////////////////////
  int  time_index=0;
  while(time_total<20.)
    {
      time_total += dt;

      //////////////////////////////////////////////////////////////////////
      ///////////////////////////// Predictor Stage ////////////////////////
      //////////////////////////////////////////////////////////////////////
      LES_Modelling( Arr.eddy_viscosity,
                     Arr.velocity_x,
                     Arr.velocity_y,  Arr.velocity_z,
                     Arr.rho_new,
                     dx, Arr.dy,  dz,
                     ldx,  ldy,  ldz);

      BC_Single(Arr.eddy_viscosity,
                ldx, ldy, ldz,
                left_x,right_x,
                left_y,right_y,
                left_z,right_z,
                2,
                0., 0.,
                Arr.dy);

      ////Calculating the Intermediate Velocity at the Predictor Stage
      Intermediate_Velocity_Predictor_X(Arr.velocity_x_tilda,
                                        Arr.residual_x,
                                        Arr.residual_x_old,
                                        Arr.velocity_x,
                                        Arr.velocity_y,
                                        Arr.velocity_z,
                                        Arr.flux_x, Arr.flux_y,
                                        Arr.flux_z,
                                        Arr.rho_new, Arr.rho,
                                        Arr.temperature_new,
                                        Arr.pressure_old,
                                        Arr.eddy_viscosity,
                                        Reynolds,
                                        -Pressure_Gradient,
                                        implicit_scheme,
                                        dx, Arr.dy, dz, dt,
                                        time_total,
                                        ldx,  ldy,  ldz);

      Intermediate_Velocity_Predictor_Y(Arr.velocity_y_tilda,
                                        Arr.residual_y,
                                        Arr.residual_y_old,
                                        Arr.velocity_x,
                                        Arr.velocity_y,
                                        Arr.velocity_z,
                                        Arr.flux_x, Arr.flux_y,
                                        Arr.flux_z,
                                        Arr.rho_new, Arr.rho,
                                        Arr.temperature_new,
                                        Arr.pressure_old,
                                        Arr.eddy_viscosity,
                                        Reynolds,
                                        0.,
                                        implicit_scheme,
                                        dx, Arr.dy, dz, dt,
                                        time_total,
                                        ldx,  ldy,  ldz);

      Intermediate_Velocity_Predictor_Z(Arr.velocity_z_tilda,
                                        Arr.residual_z,
                                        Arr.residual_z_old,
                                        Arr.velocity_x,
                                        Arr.velocity_y,
                                        Arr.velocity_z,
                                        Arr.flux_x, Arr.flux_y,
                                        Arr.flux_z,
                                        Arr.rho_new, Arr.rho,
                                        Arr.temperature_new,
                                        Arr.pressure_old,
                                        Arr.eddy_viscosity,
                                        Reynolds,
                                        0.,
                                        implicit_scheme,
                                        dx, Arr.dy, dz, dt,
                                        time_total,
                                        ldx,  ldy,  ldz);

      BC_Tilda(Arr.velocity_x_tilda,
               Arr.velocity_y_tilda,
               Arr.velocity_z_tilda,
               ldx, ldy, ldz,
               left_x, right_x,
               left_y, right_y,
               left_z, right_z);

      double useless_variable;
      if(time_index %printing_variable==0)
        {
          Print_Binary(Arr.velocity_x_tilda,
                       ldx, ldy, ldz,
                       left_x, right_x,
                       0, 0, 0, 0,
                       time_index, "utilda");

          Print_Binary(Arr.velocity_y_tilda,
                       ldx, ldy, ldz,
                       0, 0,
                       left_y, right_y, 0, 0,
                       time_index, "vtilda");

          Print_Binary(Arr.velocity_z_tilda,
                       ldx, ldy, ldz,
                       0, 0,
                       0, 0, left_z, right_z,
                       time_index, "wtilda");

          Print_Residuals(Arr.velocity_x,
                          Arr.velocity_y,
                          Arr.velocity_z,
                          Arr.flux_x, Arr.flux_y,
                          Arr.flux_z,
                          Arr.temperature,
                          Arr.eddy_viscosity,
                           Reynolds,
                          dx, Arr.dy,  dz,
                          ldx,  ldy,  ldz,
                          &useless_variable,
                          time_index,
                          "");
            

        }

      // //Solving the Poisson Equation
      // //To do that, I will use the bcgs-solver of Christos.
      // //The s_A ij_A and Precond_A vectors will be constructed once and
      // //they will be defined outside the iterating part of the code

      //Determining the RHS of the Poisson Equation
      Right_Hand_Side_Poisson(rhs,
                              Arr.velocity_x_tilda,
                              Arr.velocity_y_tilda,
                              Arr.velocity_z_tilda,
                              Arr.rho_new,
                              Arr.rho,
                              Arr.rho_old,
                              dx, Arr.dy, dz,
                              dt,
                              ldx, ldy,  ldz);

      if(time_index%printing_variable==0)
        {
          Printing_RHS(rhs, time_index, ldx, ldy, ldz,"");

          Print_Divergence(Arr.velocity_x_tilda,
                           Arr.velocity_y_tilda, Arr.velocity_z_tilda,
                           Arr.rho_new, Arr.rho, Arr.rho_old,
                           dx, Arr.dy, dz,
                           dt,  time_index,"", 
                           ldx,  ldy, ldz);


        }

      ////Solving the Poisson Equation
      BCSG(s_a, ij_a, result, rhs, precond_a,
           tolerance, iterations, dim_a, flag);
      if(flag==1)
        {

          Print_Data( Arr.velocity_x, Arr.velocity_y,
                      Arr.velocity_z, Arr.pressure,
                      ldx, ldy, ldz,
                      left_x,right_x,
                      left_y, right_y,
                      left_z, right_z, time_index);

          cout<<time_index<<endl;
          break;
        }

      ////Passing the Poisson solution to the Arr.pressure Array
      for (int k=0; k<ldz; k++){
        for (int j=0; j<ldy; j++){
          for (int i=0; i<ldx; i++){

            Arr.pressure[k][j][i] = result[A(i,ldx,j,ldy,k,ldz) +1];

          }
        }
      }

      BC_Single(Arr.pressure,
                ldx,ldy,ldz,
                left_x,right_x,
                left_y,right_y,
                left_z,right_z,
                2,
                pressure_gradient_top, pressure_gradient_bottom,
                Arr.dy);


      ///computing the Updated Velocity
      Velocity_Update_X(Arr.velocity_x_new, Arr.velocity_x_tilda,
                        Arr.rho_new, Arr.pressure,
                        dx, dt,
                        ldx,  ldy,  ldz);

      Velocity_Update_Y(Arr.velocity_y_new,  Arr.velocity_y_tilda,
                        Arr.rho_new, Arr.pressure,
                        Arr.dy, dt,
                        ldx,  ldy,  ldz);

      Velocity_Update_Z(Arr.velocity_z_new,  Arr.velocity_z_tilda,
                        Arr.rho_new, Arr.pressure,
                        dz, dt,
                        ldx,  ldy,  ldz);

      BC_Velocities( Arr.velocity_x_new,
                     Arr.velocity_y_new,
                     Arr.velocity_z_new,
                     ldx, ldy, ldz,
                     left_x, right_x,
                     left_y, right_y,
                     left_z, right_z,
                     1,
                     velocity_x_top, velocity_x_bottom,
                     velocity_y_top, velocity_y_bottom,
                     velocity_z_top, velocity_z_bottom,
                     Arr.dy, dx, time_total);


      //Updating the Auxiliary Arr.Fluxes in order to proceed at
      //the Corrector Stage
      Flux_Evaluation_X(Arr.flux_x, Arr.velocity_x_tilda,
                        Arr.rho_new, Arr.pressure,
                        dx, dt,
                        ldx+1,  ldy,  ldz);

      Flux_Evaluation_Y(Arr.flux_y, Arr.velocity_y_tilda,
                        Arr.rho_new, Arr.pressure,
                        Arr.dy, dt,
                        ldx,  ldy+1,  ldz);

      Flux_Evaluation_Z(Arr.flux_z, Arr.velocity_z_tilda,
                        Arr.rho_new,  Arr.pressure,
                        dx, dt,
                        ldx,  ldy,  ldz+1);

      if(time_index % printing_variable==0)
        {
          Print_Binary(Arr.flux_x,
                       ldx+1, ldy, ldz,
                       1, 1,
                       0, 0, 0, 0,
                       time_index, "fluxx");

          Print_Binary(Arr.flux_y,
                       ldx, ldy+1, ldz,
                       0, 0,
                       0, 0, 0, 0,
                       time_index, "fluxy");

          Print_Binary(Arr.flux_z,
                       ldx, ldy, ldz+1,
                       0, 0,
                       0, 0, 1, 1,
                       time_index, "fluxz");
        }


      /////////////////////////////////////////////////////////////
      ////////////////// end of the Predictor Stage ///////////////
      /////////////////////////////////////////////////////////////

      Predictor_To_Corrector(&Arr);
      // /////////////////////////////////////////////////////////////
      // ////////////////// Corrector Stage //////////////////////////
      // /////////////////////////////////////////////////////////////

      LES_Modelling( Arr.eddy_viscosity,
                     Arr.velocity_x_new,
                     Arr.velocity_y_new,  Arr.velocity_z_new,
                     Arr.rho_new,
                     dx, Arr.dy,  dz,
                     ldx,  ldy,  ldz);

      BC_Single(Arr.eddy_viscosity,
                ldx, ldy, ldz,
                left_x,right_x,
                left_y,right_y,
                left_z,right_z,
                2,
                0., 0.,
                Arr.dy);



      ////Calculating the Intermediate Velocity at the Corrector stage
      Intermediate_Velocity_Corrector_X(Arr.velocity_x_tilda,
                                        Arr.residual_x,
                                        Arr.residual_x_old,
                                        Arr.velocity_x,
                                        Arr.velocity_x_new,
                                        Arr.velocity_y_new,
                                        Arr.velocity_z_new,
                                        Arr.flux_x,
                                        Arr.flux_y,
                                        Arr.flux_z,
                                        Arr.rho_new,
                                        Arr.rho,
                                        Arr.temperature_new,
                                        Arr.pressure_old,
                                        Arr.eddy_viscosity,
                                        Reynolds,
                                        -Pressure_Gradient,
                                        implicit_scheme,
                                        dx, Arr.dy,  dz,
                                        dt,  time_total,
                                        ldx,  ldy,  ldz);

      Intermediate_Velocity_Corrector_Y(Arr.velocity_y_tilda,
                                        Arr.residual_y,
                                        Arr.residual_y_old,
                                        Arr.velocity_y,
                                        Arr.velocity_x_new,
                                        Arr.velocity_y_new,
                                        Arr.velocity_z_new,
                                        Arr.flux_x,
                                        Arr.flux_y,
                                        Arr.flux_z,
                                        Arr.rho_new, Arr.rho,
                                        Arr.temperature_new,
                                        Arr.pressure_old,
                                        Arr.eddy_viscosity,
                                        Reynolds, 0.,
                                        implicit_scheme,
                                        dx, Arr.dy, dz,
                                        dt,  time_total,
                                        ldx,  ldy,  ldz);


      Intermediate_Velocity_Corrector_Z(Arr.velocity_z_tilda,
                                        Arr.residual_z,
                                        Arr.residual_z_old,
                                        Arr.velocity_z,
                                        Arr.velocity_x_new,
                                        Arr.velocity_y_new,
                                        Arr.velocity_z_new,
                                        Arr.flux_x,
                                        Arr.flux_y,
                                        Arr.flux_z,
                                        Arr.rho_new, Arr.rho,
                                        Arr.temperature,
                                        Arr.pressure_old,
                                        Arr.eddy_viscosity,
                                        Reynolds,
                                        0.,
                                        implicit_scheme,
                                        dx, Arr.dy, dz,
                                        dt,  time_total,
                                        ldx,  ldy,  ldz);

      BC_Tilda(Arr.velocity_x_tilda,
               Arr.velocity_y_tilda,
               Arr.velocity_z_tilda,
               ldx, ldy, ldz,
               left_x, right_x,
               left_y, right_y,
               left_z, right_z);


      if(time_index % printing_variable==0)
        {
          Print_Binary(Arr.velocity_x_tilda,
                       ldx, ldy, ldz,
                       left_x, right_x,
                       0, 0, 0, 0,
                       time_index, "utildac");

          Print_Binary(Arr.velocity_y_tilda,
                       ldx, ldy, ldz,
                       0, 0,
                       left_y, right_y, 0, 0,
                       time_index, "vtildac");

          Print_Binary(Arr.velocity_z_tilda,
                       ldx, ldy, ldz,
                       0, 0,
                       0, 0, left_z, right_z,
                       time_index, "wtildac");

          Print_Residuals(Arr.velocity_x,
                          Arr.velocity_y,
                          Arr.velocity_z,
                          Arr.flux_x, Arr.flux_y,
                          Arr.flux_z,
                          Arr.temperature,
                          Arr.eddy_viscosity,
                          Reynolds,
                          dx, Arr.dy,  dz,
                          ldx,  ldy,  ldz,
                          &useless_variable,
                          time_index,
                          "c");
        }


      ///Determining the RHS of the Poisson Equation
      Right_Hand_Side_Poisson(rhs,
                              Arr.velocity_x_tilda,
                              Arr.velocity_y_tilda,
                              Arr.velocity_z_tilda,
                              Arr.rho_new,Arr.rho, Arr.rho_old,
                              dx, Arr.dy, dz,
                              dt,
                              ldx,  ldy,  ldz);


      if(time_index%printing_variable==0)
        {
          Printing_RHS(rhs, time_index, ldx, ldy, ldz,"c");

          Print_Divergence(Arr.velocity_x_tilda,
                           Arr.velocity_y_tilda, Arr.velocity_z_tilda,
                           Arr.rho_new, Arr.rho, Arr.rho_old,
                           dx, Arr.dy, dz,
                           dt,  time_index,"c",
                           ldx,  ldy, ldz);

        }


      ///Solving the Poisson Equation
      BCSG(s_a, ij_a, result, rhs, precond_a,
           tolerance, iterations, dim_a,flag);
      if(flag==1)
        {

          Print_Data( Arr.velocity_x_new, Arr.velocity_y_new,
                      Arr.velocity_z_new, Arr.pressure,
                      ldx, ldy, ldz,
                      left_x,right_x,
                      left_y, right_y,
                      left_z, right_z, time_index);

          cout<<time_index<<endl;
          break;
        }

      //Passing the Poisson solution to the Arr.pressure Array
      for (int k=0; k<ldz; k++){
        for (int j=0; j<ldy; j++){
          for (int i=0; i<ldx; i++){

            Arr.pressure[k][j][i] = result[A(i,ldx,j,ldy,k,ldz) +1];

          }
        }
      }

      BC_Single(Arr.pressure,
                ldx,ldy,ldz,
                left_x,right_x,
                left_y,right_y,
                left_z,right_z,
                2,
                pressure_gradient_top, pressure_gradient_bottom,
                Arr.dy);


      //computing the Updated Velocity
      Velocity_Update_X(Arr.velocity_x_new, Arr.velocity_x_tilda,
                        Arr.rho_new, Arr.pressure,
                        dx, dt,
                        ldx,  ldy,  ldz);

      Velocity_Update_Y(Arr.velocity_y_new,  Arr.velocity_y_tilda,
                        Arr.rho_new, Arr.pressure,
                        Arr.dy, dt,
                        ldx,  ldy,  ldz);


      Velocity_Update_Z(Arr.velocity_z_new,  Arr.velocity_z_tilda,
                        Arr.rho_new, Arr.pressure,
                        dz, dt,
                        ldx,  ldy,  ldz);

      ///Implementing the Velocity  boundary conditions for the next step
      BC_Velocities( Arr.velocity_x_new,
                     Arr.velocity_y_new,
                     Arr.velocity_z_new,
                     ldx, ldy, ldz,
                     left_x, right_x,
                     left_y, right_y,
                     left_z, right_z,
                     1,
                     velocity_x_top, velocity_x_bottom,
                     velocity_y_top, velocity_y_bottom,
                     velocity_z_top, velocity_z_bottom,
                     Arr.dy, dx, time_total);


      ///Updating the Auxiliary Arr.Fluxes in order to proceed
      //  the next timestep
      Flux_Evaluation_X(Arr.flux_x, Arr.velocity_x_tilda,
                        Arr.rho_new, Arr.pressure,
                        dx,dt,
                        ldx+1,  ldy,  ldz);


      Flux_Evaluation_Y(Arr.flux_y, Arr.velocity_y_tilda,
                        Arr.rho_new, Arr.pressure,
                        Arr.dy, dt,
                        ldx,  ldy+1,  ldz);


      Flux_Evaluation_Z(Arr.flux_z, Arr.velocity_z_tilda,
                        Arr.rho_new,  Arr.pressure,
                        dx, dt,
                        ldx,  ldy,  ldz+1);

      if(time_index % printing_variable==0)
        {
          Print_Binary(Arr.flux_x,
                       ldx+1, ldy, ldz,
                       1, 1,
                       0, 0, 0, 0,
                       time_index, "fluxxc");

          Print_Binary(Arr.flux_y,
                       ldx, ldy+1, ldz,
                       0, 0,
                       0, 0, 0, 0,
                       time_index, "fluxyc");

          Print_Binary(Arr.flux_z,
                       ldx, ldy, ldz+1,
                       0, 0,
                       0, 0, 1, 1,
                       time_index, "fluxzc");
        }

      ////////////////////////////////////////////////////////////////
      ////////////////End of the Corrector Stage /////////////////////
      ///////////////////////////////////////////////////////////////
      if (time_index%printing_variable==0)
        {
          Print_Data( Arr.velocity_x_new, Arr.velocity_y_new,
                      Arr.velocity_z_new, Arr.pressure,
                      ldx, ldy, ldz,
                      left_x,right_x,
                      left_y, right_y,
                      left_z, right_z, time_index);

          cout<<time_index<<endl;

        }


      //Computing the timestep for the next iteration
      Maximum_Velocities(Arr.velocity_x, Arr.velocity_y,
                         Arr.velocity_z,
                         &u_max, &v_max, &w_max,
                         ldx,  ldy,  ldz);


      //Computing the smallest dt for the next iteration
      max_velocity = fmax(u_max,v_max);
      max_velocity = fmax(max_velocity, w_max);


      //Getting the smallest dt for the next iteratio
      dt = cfl * min_dxi / max_velocity;
      output_file<<time_index<<" "<<dt<<" "<<time_total<<endl;


      signal (SIGINT, termination_handler);
      if (ibroke){
        Print_Data( Arr.velocity_x_new, Arr.velocity_y_new,
                    Arr.velocity_z_new, Arr.pressure,
                    ldx, ldy, ldz,
                    left_x,right_x,
                    left_y, right_y,
                    left_z, right_z, time_index);

        cout<<time_index<<endl;
        break;
      }


      time_index++;
      Next_Step(&Arr);
    }

  // Releasing the allocated memory
  DeAllocator(  &Arr,
                ldx,  ldy,  ldz,
                left_x,right_x,
                left_y,right_y,
                left_z,right_z);

  delete[] s_a;
  delete[] ij_a;
  delete[] precond_a;
  delete[] rhs;
  delete[] result;
}
