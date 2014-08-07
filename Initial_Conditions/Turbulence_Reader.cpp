/*******************************************
 * Author: Michail Georgiou 
*  Last Modified: Time-stamp: <2014-05-05 13:43:43 mike_georgiou>   
*
*
Turbulence_Initializer.cpp -- This function reads data regarding the
turbulent flow of my code
*
* Written on Monday,  5 May 2014.
********************************************/

#include <fstream>
#include <iostream>

using namespace std;

void Turbulence_Reader(double* Reynolds_wall)
{


  // Opening the .dat file to read the necessary information
  ifstream input("Turbulence_Input.txt", ifstream::in);

 
  //Reading the Data.
  if(input.is_open())
    {
      input>>*(Reynolds_wall);
    }
  else cout << "Unable to open file\n";  


  input.close();

}
