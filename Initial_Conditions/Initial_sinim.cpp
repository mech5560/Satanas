/*  Last Modified Time-stamp: <2014-04-15 16:36:40 mike_georgiou> */
/*
  This Function gives to all the elements of the
  array the value 0
*/
#define PI 4.*atan(1.)

#include<cmath>
void Initial_Cos( double ***Speed_X, int ldz, int ldy, int ldx,
                   int lz, int rz, int ly, int ry, int lx, int rx)
{

  for (int k=0; k<ldz; k++)
    {
      for (int j=0; j<ldy; j++)
        {
          for (int i=0; i<ldx; i++)
            {
              Speed_X[k][j][i] = sin(2.*PI * (j+0.5)/((ldy)));

            }

        }

    }

}
