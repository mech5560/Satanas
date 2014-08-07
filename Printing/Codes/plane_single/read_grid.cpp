/*******************************************
 * Author: Michail Georgiou
 *  Last Modified: Time-stamp: <2014-07-30 09:49:52 mike_georgiou>
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

void read_grid(int* ldx, int* ldy, int* ldz)
{



  fstream fin("Input_Grid.man");
  string line;


  getline(fin, line);
  if(line[0] == '#')
    {
      getline(fin, line);
      stringstream(line)>>*ldx;
    }


  getline(fin, line);
  if(line[0] == '#')
    {
      getline(fin, line);
      stringstream(line)>>*ldy;
    }

  getline(fin, line);
  if(line[0] == '#')
    {
      getline(fin, line);
      stringstream(line)>>*ldz;
    }

}
