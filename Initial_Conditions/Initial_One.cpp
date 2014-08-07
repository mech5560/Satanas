/*  Last Modified Time-stamp: <2014-05-01 16:10:33 mike_georgiou> */
/*
  This Function gives to all the elements of the
  array the value 0
*/


void Initial_One( double ***data,
                   int ldx, int ldy, int ldz,
                   int lx, int rx,
                   int ly, int ry,
                   int lz, int rz)
{

  for (int k=0; k<ldz; k++){
    for (int j=0; j<ldy; j++){
      for (int i=0; i<ldx; i++){

        data[k][j][i] =1.0;


      }
    }
  }

}
