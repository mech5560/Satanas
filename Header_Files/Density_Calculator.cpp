/*******************************************
 * Author: Michail Georgiou
 *  Last Modified: Time-stamp: <2014-05-20 09:18:01 mike_georgiou>
 *
 *
Density_Calculator.cpp -- This function will compute the density based on
interpolated data that i found on the net.
*
* Written on Thursday, 10 April 2014.
********************************************/


void Density_Calculator(double*** rho,
                        double*** T,
                        int ldx, int ldy, int ldz)

{
  for (int k=0; k<ldz; k++) {
    for(int j=0; j<ldy; j++){
      for (int i=0; i<ldx; i++){

        rho[k][j][i]= 1.;
          // 1.034615 -0.155/988.*(T[k][j][i]) - 0.0026580/988. *
          // (T[k][j][i])*(T[k][j][i]);
      }
    }
  }


}
