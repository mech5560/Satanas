/*******************************************
 * Author: Michail Georgiou 
*  Last Modified: Time-stamp: <2014-07-02 16:09:40 mike_georgiou>   
*
*
File_Reader.cpp -- This function will read the number of
solution points from the Input.txt file
*
* Written on Friday, 27 June 2014.
********************************************/
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

void File_Reader_Curve(int* level_x, int* level_y, int* level_z,
		       int* curve_xxy, int* curve_yxy,
		       int* curve_xxz, int* curve_zxz,
		       int* curve_yyz, int* curve_zyz,
		       int* ghost)
{



  fstream fin("Input_Curve.man");
  string line;

      getline(fin, line);
      if(line[0] == '#')
	{      
	  getline(fin, line);  
	  stringstream(line)>>*level_x;}


      getline(fin, line);
      if(line[0] == '#')
	{
	  getline(fin, line);  
	  stringstream(line)>>*level_y;
	}
      
      
      getline(fin, line);
      if(line[0] == '#') 
	{
	  getline(fin, line);  
	  stringstream(line)>>*level_z;
	}


      getline(fin, line);
      if(line[0] == '#')
	{
	  getline(fin, line);  
	  stringstream(line)>>*curve_xxy;
	}


      getline(fin, line);
      if(line[0] == '#')
	{
	  getline(fin, line);  
	  stringstream(line)>>*curve_yxy;
	}

      getline(fin, line);
      if(line[0] == '#')
	{
	  getline(fin, line);  
	  stringstream(line)>>*curve_xxz;
	}

      getline(fin, line);
      if(line[0] == '#')
	{
	  getline(fin, line);  
	  stringstream(line)>>*curve_zxz;
	}


      getline(fin, line);
      if(line[0] == '#')
	{
	  getline(fin, line);  
	  stringstream(line)>>*curve_yyz;
	}

      getline(fin, line);
      if(line[0] == '#')
	{
	  getline(fin, line);  
	  stringstream(line)>>*curve_zyz;
	}


      getline(fin, line);
      if(line[0] == '#')
	{
	  getline(fin, line);  
	  stringstream(line)>>*ghost;
	}




}
