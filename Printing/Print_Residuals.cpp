/*******************************************
 * Author: Michail Georgiou 
*  Last Modified: Time-stamp: <2014-08-07 11:23:08 mike_georgiou>   
*
*
Print_Residuals.cpp -- This code will print the  components of the velocity
residuals
*
* Written on Thursday,  7 August 2014.
********************************************/

#include"../Residuals/Residuals.h"
#include"../Residuals/Residuals-inl.h"
#include <fstream>
void File_Opener(const char* a, const char*, int time_index, ofstream* file);

void Print_Residuals(double*** velocity_x,
                     double*** velocity_y,
                     double*** velocity_z,
                     double*** flux_x, double*** flux_y,
                     double*** flux_z,
                     double*** temperature,
                     double*** eddy_viscosity,
                     double Reynolds,
                     double dx, double* dy, double dz,
                     int ldx, int ldy, int ldz,
                     double* explicit_term,
                     int time_index,
                     const char* a)
{


  ofstream  outfile[6];
  File_Opener("convx", a, time_index, &outfile[0]);
  File_Opener("viscx", a, time_index, &outfile[1]);
  File_Opener("convy", a, time_index, &outfile[2]);
  File_Opener("viscy", a, time_index, &outfile[3]);
  File_Opener("convz", a, time_index, &outfile[4]);
  File_Opener("viscz", a, time_index, &outfile[5]);




for (int k = 0; k < ldz; k++){
  for (int j = 0; j < ldy; j++){
    for (int i = 0; i < ldx; i++){
      


  //Computing the convection term of the residuals by calling the
  //Convection Term
  double  convection= Convection_Term(velocity_x,
                                      flux_x, flux_y,flux_z,
                                      dx, dy, dz,
                                      i, j, k);


  //Viscous Term XX
  double viscous_components[3];
  viscous_components[0] =
    Viscous_Component_XX(velocity_x,velocity_y,
                         velocity_z,
                         temperature,
                         eddy_viscosity,
                         Reynolds,
                         dx, dy, dz,
                         i, j, k);

  //Viscous Term XY
  viscous_components[1] =
    Viscous_Component_XY_Implicit(velocity_x,velocity_y,
                                  temperature,
                                  eddy_viscosity,
                                  Reynolds,
                                  dx, dy,
                                  i, j, k,
                                  explicit_term);
  //Viscous Term XY
  viscous_components[2] =
    Viscous_Component_XZ(velocity_x,velocity_z,
                         temperature,
                         eddy_viscosity,
                         Reynolds,
                         dx, dz,
                         i, j, k);
  double viscous_total=0.;
  for (int vi=0; vi<3; vi++)
    viscous_total+=viscous_components[vi];

      outfile[0].write( (char*)&convection,sizeof(double));
      outfile[1].write( (char*)&viscous_total,sizeof(double));



      //Ycomponent
      convection= Convection_Term(velocity_y,
                                  flux_x, flux_y,flux_z,
                                  dx, dy, dz,
                                  i, j, k);


  //Viscous Term YX
  viscous_components[0]=
    Viscous_Component_YX(velocity_x, velocity_y,
                         temperature,
                         eddy_viscosity,
                         Reynolds,
                         dx, dy,
                         i, j, k);

  //Viscous Term YY
  viscous_components[1]=
    Viscous_Component_YY_Implicit(velocity_x, velocity_y,
                                  velocity_z,
                                  temperature,
                                  eddy_viscosity,
                                  Reynolds,
                                  dx, dy,dz,
                                  i, j, k,
                                  explicit_term);


  //Viscous Term YZ
  viscous_components[2]=
    Viscous_Component_YZ(velocity_y, velocity_z,
                         temperature,
                         eddy_viscosity,
                         Reynolds,
                         dy,dz,
                         i, j, k);


  viscous_total=0.;
  for(int index=0; index<3; index++)
    viscous_total += viscous_components[index];


      outfile[2].write( (char*)&convection,sizeof(double));
      outfile[3].write( (char*)&viscous_total,sizeof(double));


  //Computing the convection term of the residuals by calling the
   convection= Convection_Term(velocity_z,
                                     flux_x, flux_y,flux_z,
                                     dx, dy, dz,
                                     i, j, k);

  //Viscous_Term_ZX
  viscous_components[0]=
    Viscous_Component_ZX(velocity_x, velocity_z,
                         temperature,
                         eddy_viscosity,
                         Reynolds,
                         dx, dz,
                         i, j, k);

  //Viscous Term ZY
  viscous_components[1]=
    Viscous_Component_ZY_Implicit(velocity_y, velocity_z,
                                  temperature,
                                  eddy_viscosity,
                                  Reynolds,
                                  dy,dz,
                                  i, j, k,
                                  explicit_term);


  //Viscous Term ZZ
  viscous_components[2]=
    Viscous_Component_ZZ(velocity_x, velocity_y,
                         velocity_z,
                         temperature,
                         eddy_viscosity,
                         Reynolds,
                         dx, dy, dz,
                         i, j, k);


  viscous_total=0.;
  for(int index=0; index<3; index++)
    viscous_total += viscous_components[index];

      outfile[4].write( (char*)&convection,sizeof(double));
      outfile[5].write( (char*)&viscous_total,sizeof(double));

    }
  }	    
 }   
//closing the files
 for (int vi=0; vi<6; vi++)
   outfile[vi].close();



}
