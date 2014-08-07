/*******************************************
 * Author: Michail Georgiou 
*  Last Modified: Time-stamp: <2014-07-02 13:50:12 mike_georgiou>   
*
*
Pressure_Update.cpp -- This function will compute the P^{n+1} that
is necessary for the updating of the velocity.
*
* Written on Wednesday, 28 May 2014.
********************************************/

void Pressure_Update(double*** pressure, double*** pressure_old,
		     double*** potential, 
		     int ldx, int ldy, int ldz,
		     int left_x, int right_x,
		     int left_y, int right_y,
		     int left_z, int right_z)
{


for (int k = -left_z; k < ldz+right_z; k++){
  for (int j = -left_y; j < ldy+right_y; j++){
    for (int i = -left_x; i < ldx+right_x; i++){
      

      pressure[k][j][i] = 0.*pressure_old[k][j][i] + potential[k][j][i];


    }
  }	    
 }   



}
