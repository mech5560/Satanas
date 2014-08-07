/*******************************************
 * Author: Michail Georgiou
 *  Last Modified: Time-stamp: <2014-06-24 08:42:29 mike_georgiou>
 *
 *
Vorticity_Computation.cpp -- This program computes compute the three
components of the vorticity in the domain and it will store them into
output binary files
*
* Written on Wednesday, 11 June 2014.
********************************************/

#include"Vorticity_Computation.h"

int main(int argc, char** argv)
{

  double ***velocity_x, ***velocity_y, ***velocity_z, *dx, *dy, *dz;

  // These are the number of solution points in each direction and
  // they need to be changed for every particular case.
  int ldx=64; int ldy=64; int ldz=64;


  //Allocating Memory for the introduced data.
  velocity_x=Matrix_Allocator(ldx,ldy,ldz,
                              3,3,1,1,3,3);

  velocity_y=Matrix_Allocator(ldx,ldy,ldz,
                              3,3,1,1,3,3);

  velocity_z=Matrix_Allocator(ldx,ldy,ldz,
                              3,3,1,1,3,3);

  dx= new double[ldx+6]; dx+=3;
  dy= new double[ldy+2]; dy+=1; 
  dz= new double[ldz+6]; dz+=3;


  string input_data[3];

  stringstream ss;
  string format = ".bin";
  string finalName[9];
  ofstream  outfile[3];
  ifstream infile[3],domain[3];

  int time_index;
  cout<<"Please define the time step that you want the quantities to";
  cout<<"be computed\n";
  cin>>time_index;


  // Creating the output files
  string name[3];
  name[0]="wx";
  name[1]="wy";
  name[2]="wz";

  //reading the input files
  string data[3], space[3];
  data[0]="X"; data[1]="Y"; data[2]="Z";

  space[0]="dx"; space[1]="dy"; space[2]="dz";
  //Opening the necessary files
  for(int vi=0; vi<3; vi++)
    {

      //Opening the output file that the vorticities will be placed.
      ss<<name[vi]<<time_index<<format;
      finalName[vi]= ss.str();
      outfile[vi].open(finalName[vi],ios::out | ios::binary);
      ss.str("");

      //Opening the files that contain the velocities
      ss<<data[vi]<<time_index<<format;
      finalName[3+vi]= ss.str();
      infile[vi].open(finalName[3+vi],ios::in | ios::binary);
      ss.str("");

      //Opening the files that contain the domain info
      ss<<space[vi]<<format;
      finalName[6+vi]= ss.str();
      domain[vi].open(finalName[6+vi],ios::in | ios::binary);
      ss.str("");

    }

  //Reading the domain info
  double result; char value[8];
  for (int i=-3; i<ldx+3; i++)
    {
      domain[0].read(value,8);
      result = *((double*) value);
      dx[i]=result;
    }

  for (int i=-1; i<ldy+1; i++)
    {
      domain[1].read(value,8);
      result = *((double*) value);
      dy[i]=result;
    }

  for (int i=-3; i<ldz+3; i++)
    {
      domain[2].read(value,8);
      result = *((double*) value);
      dz[i]=result;
    }

  //Reading the velocity data
  for(int k=-3; k<ldz+3; k++){
    for(int j=-1; j<ldy+1; j++){
      for(int i=-3; i<ldx+3; i++){

        infile[0].read(value,8);
        result = *((double*) value);
        velocity_x[k][j][i]=result;

        infile[1].read(value,8);
        result = *((double*) value);
        velocity_y[k][j][i]=result;

        infile[2].read(value,8);
        result = *((double*) value);
        velocity_z[k][j][i]=result;

      }
    }
  }


//Computing the vorticities.
double   u_over_y, u_over_z, v_over_x, v_over_z, w_over_x, w_over_y;
double dy_total=0.;
double derivative_components[2];
for (int k = 0; k < ldz; k++){
  for (int j = 0; j < ldy; j++){
    for (int i = 0; i < ldx; i++){

      //computing dy
      dy_total=dy[j-1]+2.*dy[j]+dy[j+1];
      //computing the du/dy
      u_over_y = Derivative(velocity_x[k][j+1][i],
                            velocity_x[k][j-1][i],
                            dy_total,1);

      //computing the du/dz
      derivative_components[0]= 4./3.*Derivative(velocity_x[k+1][j][i],
                                                 velocity_x[k-1][j][i],
                                                 dz[k],2);
      derivative_components[1]= -1./3.*Derivative(velocity_x[k+2][j][i],
                                                  velocity_x[k-2][j][i],
                                                  dz[k],4);

      //Initializing the quantity to be filled
      u_over_z = 0.;
      for(int vi=0; vi<2; vi++)
        u_over_z+= derivative_components[vi];


      //Computing the dv/dx
      derivative_components[0]= 4./3.*Derivative(velocity_y[k][j][i+1],
                                                 velocity_y[k][j][i-1],
                                                 dx[i],2);
      derivative_components[1]= -1./3.*Derivative(velocity_y[k][j][i+2],
                                                  velocity_y[k][j][i-2],
                                                  dx[i],4);

      //Initializing the quantity to be filled
      v_over_x = 0.;
      for(int vi=0; vi<2; vi++)
        v_over_x+= derivative_components[vi];


      //computing the dv/dz
      derivative_components[0]= 4./3.*Derivative(velocity_y[k+1][j][i],
                                                 velocity_y[k-1][j][i],
                                                 dz[k],2);
      derivative_components[1]= -1./3.*Derivative(velocity_y[k+2][j][i],
                                                  velocity_y[k-2][j][i],
                                                  dz[k],4);

      //Initializing the quantity to be filled
      v_over_z = 0.;
      for(int vi=0; vi<2; vi++)
        v_over_z+= derivative_components[vi];


      //Computing the dw/dx
      derivative_components[0]= 4./3.*Derivative(velocity_z[k][j][i+1],
                                                 velocity_z[k][j][i-1],
                                                 dx[i],2);
      derivative_components[1]= -1./3.*Derivative(velocity_z[k][j][i+2],
                                                  velocity_z[k][j][i-2],
                                                  dx[i],4);

      w_over_x = 0.;
      for(int vi=0; vi<2; vi++)
        w_over_x+= derivative_components[vi];

      //computing dw/dy
      //computing the du/dy
      w_over_y = Derivative(velocity_z[k][j+1][i],
                            velocity_z[k][j-1][i],
                            dy_total,1);

      double omega[3];

      //omega_x
      omega[0] = w_over_y-v_over_z;
      //omega_y
      omega[1] = u_over_z-w_over_x;
      //omega_z
      omega[2] = v_over_x-u_over_y;


      //Writing  the vorticities
      for (int vi=0; vi<3; vi++)
        outfile[vi].write( (char*)&omega[vi],sizeof(double));

    }
  }
 }

 Free_Matrix(velocity_x,3,1,3);
 Free_Matrix(velocity_y,3,1,3);
 Free_Matrix(velocity_z,3,1,3);

 delete [] &dx[-3];
 delete [] &dy[-1];
 delete [] &dz[-3];

}
