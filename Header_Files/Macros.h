/*  Last Modified Time-stamp: <2014-04-24 16:15:30 mike_georgiou> */ 
/* Definition of macros that will be used on the code */

//#include "Data.h"
#include <iostream>
#include <cstdlib>
#include <math.h>
using namespace std;

//1 Dynamic Memory Allocation Controller
#ifndef Alloc_Check 
#define  Alloc_Check(host_A_vec)					\
  if ((host_A_vec) == 0){						\
    cout << "Error: memory could not be allocated in this Array"<<endl;	\
    exit(1); }
#endif


#ifndef A
// Macros that "Converts" 1D array into 3D
#define A(z,y,x) ((z)*ldx*ldy + (y)*ldx + (x))	
#endif


#ifndef A_sp
// Macros that "Converts" 1D array into 3D
#define A_sp(z,y,x) ((z)*ldx*(ldy+2) + (y)*ldx + (x))	
#endif



/* I ll use these function to avoid multiple if statements close to the 
   boundaries in the X and Z Directions
*/

#ifndef A_Bound
#define A_Bound 

inline  int A_Boundary_ldz(int k,int ldz)
{
  if(k>=ldz){k=k-(ldz);}
  return k;
}

inline  int A_Boundary_0(int k,int ldz)
{
  if(k<0){ k= ldz+k;}
  return k;
}

#endif


#ifndef Periodic_Check
#define Periodic_Check
inline void Periodic_Bound_Check(int i, int *i_ref, int ldx)
{

	
	if (i<3)
	  {
	    i_ref[0]=A_Boundary_0(i_ref[0],ldx);
	    i_ref[1]=A_Boundary_0(i_ref[1],ldx);
	    i_ref[2]=A_Boundary_0(i_ref[2],ldx);	 
	  }

	if (i>ldx-4)
	  {
	    i_ref[3]=A_Boundary_ldz(i_ref[3],ldx);
	    i_ref[4]=A_Boundary_ldz(i_ref[4],ldx);
	    i_ref[5]=A_Boundary_ldz(i_ref[5],ldx);	 
	  }


}
#endif
