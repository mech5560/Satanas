/*  Last Modified Time-stamp: <2014-04-30 18:02:23 mike_georgiou> */
/*
  This Function gives to all the elements of the
  array the value 0
*/


void Initial_Zero( double ***data,
                   int ldx, int ldy, int ldz,
                   int lx, int rx,
                   int ly, int ry,
                   int lz, int rz)
{

  for (int k=0; k<ldz; k++){
    for (int j=0; j<ldy; j++){
      for (int i=0; i<ldx; i++){

        data[k][j][i] =0.0;


      }
    }
  }

}
