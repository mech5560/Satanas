/*******************************************
 * Author: Michail Georgiou
 * Last Modified: Time-stamp: <2014-07-31 16:05:31 mike_georgiou>
 *
 * BC_Flux.cpp -- In this program I will define  the boundary
 * conditions for my problem.
 * Firstly, I ll start with the easy ones (Periodic) and then I ll define the
 * BC.
 * at the wall
 *
 * The velocity BC at the wall is defined by the non-slip condition.
 * For the density I can define either Dirichlet=0 or obtain the Rho_{wall-1} by
 * the constitutive equatiion.
 * As for the intermediate velocities i ll follow christos suggestions
 *
 * Written on Thursday, 20 March 2014.
 ********************************************/


void BC_Tilda(double*** velocity_x_tilda,
              double*** velocity_y_tilda,
              double*** velocity_z_tilda,
              int ldx, int ldy, int ldz,
              int lx, int rx,
              int ly, int ry,
              int lz, int rz)
{



  /* X- Direction BC */
  for (int k = 0; k < ldz; k++){
    for (int j = 0; j < ldy; j++) {

      for (int i=1; i<=lx; i++)
        {
          velocity_x_tilda[k][j][-i] =  velocity_x_tilda[k][j][ldx-i];
        }

      for (int i=0; i<rx; i++)
        {
          velocity_x_tilda[k][j][ldx+i] =  velocity_x_tilda[k][j][i];
        }
    }
  }


  /* Z-Direction BC*/
  for (int j = 0; j < ldy; j++){
    for (int i = 0; i< ldx; i++){

      for (int k=1; k<=lz; k++)
        {
          velocity_z_tilda[-k][j][i] =  velocity_z_tilda[ldz-k][j][i];
        }

      for (int k=0; k<rz; k++)
        {
          velocity_z_tilda[ldz+k][j][i] =  velocity_z_tilda[k][j][i];
        }

    }
  }


  for (int k=0; k<ldz; k++){
    for (int i=0; i<ldx; i++){

      velocity_y_tilda[k][-ly][i]= -velocity_y_tilda[k][0][i];
      velocity_y_tilda[k][ldy-1+ry][i]= -velocity_y_tilda[k][ldy-1][i];
    }
  }


}
