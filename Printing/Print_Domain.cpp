/*******************************************
 * Author: Michail Georgiou
 *  Last Modified: Time-stamp: <2014-07-02 16:02:12 mike_georgiou>
 *
 *
Print_Domain.cpp -- This function will save the domain
information into three separated binary files.
*
* Written on Wednesday, 11 June 2014.
********************************************/

#include<iostream>
#include<fstream>

using namespace std;

void Print_Domain(double dx, double* dy, double dz,
                  int ldx, int ldy, int ldz)
{

  ofstream  outfile_x, outfile_y, outfile_z, outfile_dx,outfile_dy, outfile_dz;
  outfile_x.open("./Printing/Postprocessing/x.bin",ios::out | ios::binary);
  outfile_y.open("./Printing/Postprocessing/y.bin",ios::out | ios::binary);
  outfile_z.open("./Printing/Postprocessing/z.bin",ios::out | ios::binary);

  outfile_dx.open("./Printing/Postprocessing/dx.bin",ios::out | ios::binary);
  outfile_dy.open("./Printing/Postprocessing/dy.bin",ios::out | ios::binary);
  outfile_dz.open("./Printing/Postprocessing/dz.bin",ios::out | ios::binary);


  // Writing the X coordinantes
  double x_local=-3.*dx;
  for (int i = -3; i < ldx+3; i++)
    {
      x_local+=dx/2.;
      outfile_x.write( (char*)&x_local,sizeof(double));
      x_local+=dx/2.;
    }

  // Writing the Y coordinates
  double y_local=-1.-2.*dy[0];
  for (int j = -1; j < ldy+1; j++)
    {
      y_local+=dy[j];
      outfile_y.write( (char*)&y_local,sizeof(double));
      y_local+=dy[j];
    }

  //Writing the  Z coordinates
  double z_local=-3.*dz;
  for (int k = -3; k < ldz+3; k++)
    {
      z_local+=dz/2.;
      outfile_z.write( (char*)&z_local,sizeof(double));
      z_local+=dz/2.;
    }



  // Writing the dX coordinantes
  for (int i = -3; i < ldx+3; i++)
    {
      outfile_dx.write( (char*)&dx,sizeof(double));
    }

  // Writing the dY coordinates
  for (int j = -1; j < ldy+1; j++)
    {
      outfile_dy.write( (char*)&dy[j],sizeof(double));
    }


  //Writing the  dZ coordinates
  for (int k = -3; k < ldz+3; k++)
    {
      outfile_dz.write( (char*)&dz,sizeof(double));
    }
  





}
