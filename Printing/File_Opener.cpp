/*******************************************
 * Author: Michail Georgiou 
*  Last Modified: Time-stamp: <2014-08-07 11:23:32 mike_georgiou>   
*
*
File_Opener.cpp -- This code will return files to output the desired data
*
* Written on Thursday,  7 August 2014.
********************************************/


#include"../Residuals/Residuals.h"
#include"../Residuals/Residuals-inl.h"

using namespace std;
#include<sstream>
#include <fstream>

void File_Opener(const char* name, const char *a,
                 int time_index, ofstream* file)
{

  stringstream ss;
  string directory = "./Printing/Postprocessing/";

  string format = ".bin";
  string finalName;
  ss<<directory<<name<<a<<time_index<<format;
  finalName = ss.str();
  
  
  file->open(finalName,ios::out | ios::binary);

}
