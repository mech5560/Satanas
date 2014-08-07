/*******************************************
 * Author: Michail Georgiou 
*  Last Modified: Time-stamp: <2014-08-07 09:14:13 mike_georgiou>   
*
*
Printing_RHS.cpp -- This function will save the rhs of the poisson equation
    in binary format.
*
* Written on Wednesday,  6 August 2014.
********************************************/

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <cstring>
#include <sstream>
using namespace std;


void Printing_RHS(double *rhs, int time_index,
                  int ldx, int ldy, int ldz,
                  const char* a)
{


  stringstream ss;

  string directory = "./Printing/Postprocessing/";
  string name = "rhs";
  string format = ".bin";
  string finalName;

  ss<<directory<<name<<a<<time_index<<format;
  finalName = ss.str();


   ofstream  outfile;
   outfile.open(finalName,ios::out | ios::binary);


for (int k = 0; k < ldz; k++){
  for (int j = 0; j < ldy; j++){
    for (int i = 0; i < ldx; i++){
      
      outfile.write( (char*)&rhs[k*ldy*ldx + j*ldx +i +1],sizeof(double));
    }
  }	    
 }   


}
