/*******************************************
 * Author: Michail Georgiou
 *  Last Modified: Time-stamp: <2014-06-04 10:35:44 mike_georgiou>
 *
 *
Intermediate_Velocity_Z_Projection_Implicit.cpp -- This function computes
the velocity_z_tilda implicitly over the y-direction. More
specifically, it solves  d/dy(dw/dy) = rhs, where rhs is given from
eq.30 of the Lessani-Papalexandris paper. Of course, the d/dy(dw/dy)
term of the Residual at time n is treated differently depending on
the implicit schemes that is used

It must be stressed that the Projection is refering to the projection
method that is used to correct the velocity_z_tilda. Specifically the
Bell et. al method is used.
*
* Written on Wednesday, 28 May 2014.
********************************************/

#include"Intermediate_Velocity.h"


void
Intermediate_Velocity_Z_Projection_Implicit(double***velocity_z_tilda,
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
                                            double Reynolds,double source,
                                            double dx, double* dy,  double dz,
                                            double dt, double time_total,
                                            int ldx, int ldy, int ldz)
{
  //Allocating memory for the three vectors that will be used by the
  //tridiagonal solver
  double *lower_diagonal, *central_diagonal, *upper_diagonal, *rhs,
  *result, *auxiliary;

  lower_diagonal = new double [ldy+1];
  central_diagonal = new double [ldy+1];
  upper_diagonal = new double [ldy+1];
  rhs = new double [ldy+1];
  result = new double [ldy+1];
  auxiliary = new double [ldy+1];


  for (int k=0; k<ldz; k++){
    for (int i=0; i<ldx; i++){


      for (int j=0; j<ldy; j++){


        double explicit_term=0.;
        Velocity_Residual_Z_Implicit(residual_z,
                                     velocity_x, velocity_y, velocity_z,
                                     flux_x, flux_y,  flux_z,
                                     temperature, Reynolds,
                                     source,
                                     dx, dy, dz,
                                     time_total,
                                     i, j, k,
                                     &explicit_term);

        double residual_sum=
          1.5*residual_z[k][j][i] - 0.5*residual_z_old[k][j][i];



        // Introducing this term in order to fix the issue with the
        // pressure gradient in the tangential direction of the wall
        double pressure_gradient =
          ((4./3.)*Derivative(pressure[k+1][j][i],pressure[k-1][j][i],
                              dz,2)
           -(1./3.)*Derivative(pressure[k+2][j][i],pressure[k-2][j][i],
                               dz,4));


	////////////Define the implicit methodology that I will use
	double implicit_scheme=0.5;
	explicit_term *=(1.-implicit_scheme); 

	// computing the inputs of the vectors that the tridiagonal
	//solver will get
	double coefficients[3];
	Coefficient_Calculator(temperature, Reynolds,
			       coefficients,
			       dy, dt, 
			       implicit_scheme,
			       i, j, k);



        // Filling the vectors. Be cautious in the introduction of
        //the boundary conditions
        if (j==0)
          {

            lower_diagonal[j+1] = 0.;
            central_diagonal[j+1] = coefficients[1]+ rho_new[k][j][i]
	      -coefficients[0];
            
	    upper_diagonal[j+1] = coefficients[2];

            rhs[j+1] = ((rho[k][j][i]*velocity_z[k][j][i]+
			 dt*(residual_sum+explicit_term
			     -2.*pressure_gradient)));

              
          }
        else if (j==ldy-1)
          {

            lower_diagonal[j+1] = coefficients[0];
            
	    central_diagonal[j+1] = coefficients[1]+ rho_new[k][j][i]
	      -coefficients[2];
            
	    upper_diagonal[j+1] = 0.;

            rhs[j+1] = ((rho[k][j][i]*velocity_z[k][j][i]+
			 dt*(residual_sum+explicit_term
			     -2.*pressure_gradient)));


          }
        else
          {
            lower_diagonal[j+1] = coefficients[0];
            central_diagonal[j+1] = coefficients[1]+ rho_new[k][j][i];
            upper_diagonal[j+1] = coefficients[2];

            rhs[j+1] = ((rho[k][j][i]*velocity_z[k][j][i]+
			 dt*(residual_sum +explicit_term
			     -pressure_gradient)));


          }
      }

      // Solving the tridiagonal system
      int flag=0;
      tridag(lower_diagonal,central_diagonal,upper_diagonal,
	     rhs, result, ldy, auxiliary, flag, i, k);


      for (int vj = 0; vj < ldy; vj++)
	{
	  velocity_z_tilda[k][vj][i] = result[vj+1];
	}


    }
  }


  //deallocating the memory for the  vectors that will be used by the
  //tridiagonal solver

  delete[] lower_diagonal;
  delete[] central_diagonal;
  delete[] upper_diagonal;
  delete[] rhs ;
  delete[] result;
  delete [] auxiliary;





}
