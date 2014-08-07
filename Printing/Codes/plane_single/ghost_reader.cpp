/*******************************************
 * Author: Michail Georgiou 
*  Last Modified: Time-stamp: <2014-08-04 13:38:45 mike_georgiou>   
*
*
ghost_reader.cpp -- reading the ghost cells in each direction
*
* Written on Monday,  4 August 2014.
********************************************/

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;


void ghost_reader( int *left_x, int *right_x,
                   int *left_y, int *right_y,
                   int *left_z, int *right_z)
{

  fstream fin("Input_Ghost.man");
  string line;


  getline(fin, line);
  if(line[0] == '#')
    {
      getline(fin, line);
      stringstream(line)>>*left_x;
    }


  getline(fin, line);
  if(line[0] == '#')
    {
      getline(fin, line);
      stringstream(line)>>*right_x;
    }


  getline(fin, line);
  if(line[0] == '#')
    {
      getline(fin, line);
      stringstream(line)>>*left_y;
    }


  getline(fin, line);
  if(line[0] == '#')
    {
      getline(fin, line);
      stringstream(line)>>*right_y;
    }


  getline(fin, line);
  if(line[0] == '#')
    {
      getline(fin, line);
      stringstream(line)>>*left_z;
    }


  getline(fin, line);
  if(line[0] == '#')
    {
      getline(fin, line);
      stringstream(line)>>*right_z;
    }


}
