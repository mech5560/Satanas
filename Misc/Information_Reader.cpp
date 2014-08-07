/*******************************************
 * Author: Michail Georgiou 
*  Last Modified: Time-stamp: <2014-08-06 11:32:37 mike_georgiou>   
*
*
Information_Reader.cpp -- In this program I will read information regarding the
    geometry of the domain, the grid, the cfl number, the tolerance of the
    Poisson solver etc.
*
* Written on Thursday, 31 July 2014.
********************************************/

#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

void Information_Reader(int *ldx,int *ldy, int *ldz,
                        double *cfl, double *tolerance, int *iterations,
                        double *time_total, int *printing_variable)
{

  fstream fin("Input_Main.man");
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
      stringstream(line)>>*cfl;
    }

  getline(fin, line);
  if(line[0] == '#')
    {
      getline(fin, line);
      stringstream(line)>>*tolerance;
    }

  getline(fin, line);
  if(line[0] == '#')
    {
      getline(fin, line);
      stringstream(line)>>*iterations;
    }

  getline(fin, line);
  if(line[0] == '#')
    {
      getline(fin, line);
      stringstream(line)>>*time_total;
    }


  getline(fin, line);
  if(line[0] == '#')
    {
      getline(fin, line);
      stringstream(line)>>*printing_variable;
    }




}
