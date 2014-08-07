/*******************************************
 * Author: Michail Georgiou
 *  Last Modified: Time-stamp: <2014-07-24 14:02:40 mike_georgiou>
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

void File_Reader(int* level_x, int* level_y, int* level_z, int* ghost)
{



  fstream fin("Input_Contour.man");
  string line;


  getline(fin, line);
  if(line[0] == '#')
    {
      getline(fin, line);
      stringstream(line)>>*level_x;
    }


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
      stringstream(line)>>*ghost;
    }


}
