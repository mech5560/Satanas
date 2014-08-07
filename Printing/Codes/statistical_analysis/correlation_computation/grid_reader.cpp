/*******************************************
 * Author: Michail Georgiou
 *  Last Modified: Time-stamp: <2014-07-24 16:08:34 mike_georgiou>
 *
 *
data_reader.cpp -- This function will read all the necessary
information in order to produce the desired statistical quantities. 

*
* Written on Friday, 27 June 2014.
********************************************/
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

void grid_reader(int *ldx, int *ldy, int *ldz, 
                 int *time_step, int *final_time)
{

  fstream fin("Input_Statistics.man");
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


  getline(fin, line);
  if(line[0] == '#')
    {
      getline(fin, line);
      stringstream(line)>>*time_step;
    }

  getline(fin, line);
  if(line[0] == '#')
    {
      getline(fin, line);
      stringstream(line)>>*final_time;
    }

}
