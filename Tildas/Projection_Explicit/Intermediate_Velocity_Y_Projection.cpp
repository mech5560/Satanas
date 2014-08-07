/*******************************************
 * Author: Michail Georgiou
 *  Last Modified: Time-stamp: <2014-05-28 17:57:30 mike_georgiou>
 *
 *
Intermediate_Velocity_Y_Press.cpp -- This function computes the v_tilda of my
code. Firstly  the velocity residual is computed. An extra term, in
order to introduce the pressure is introduced.
*
* Written on Tuesday, 29 April 2014.
********************************************/

#include"Intermediate_Velocity.h"

void Intermediate_Velocity_Y_Projection(double*** velocity_y_tilda,
                                        double*** residual_y,
                                        double*** residual_y_old,
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

  Velocity_Residual_Y( residual_y,
                       velocity_x,  velocity_y, velocity_z,
                       flux_x, flux_y,  flux_z,
                       temperature, Reynolds,source,
                       dx, dy,  dz,
                       time_total,
                       ldx, ldy, ldz);


  /* After the calculation of the Velocity_Residual I will compute the Intermediate Velocity
     at the Grid*/


  for (int k=0; k<ldz; k++){
    for (int j=0; j<ldy; j++){
      for (int i=0; i<ldx; i++){



        double residual_sum=
          1.5*residual_y[k][j][i] - 0.5*residual_y_old[k][j][i];


        // Introducing this term in order to fix the issue with the
        // pressure gradient in the tangential direction of the wall
        double interpolation_y[2];
        for(int vj=0; vj<2; vj++)
          {
            interpolation_y[vj] =
              Interpolation_Y(pressure[k][j+vj][i],dy[j+vj],
                              pressure[k][j+vj-1][i],dy[j+vj-1]);
          }


        double pressure_gradient = Derivative(interpolation_y[1],
                                              interpolation_y[0],
                                              2.*dy[j],1);




        velocity_y_tilda[k][j][i] =
          (rho[k][j][i]*velocity_y[k][j][i] +
           dt*(residual_sum - pressure_gradient))
          /rho_new[k][j][i];



      }
    }
  }
}
