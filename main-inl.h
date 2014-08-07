#ifndef MAIN_INL_H
#define MAIN_INL_H

#include<iostream>
using namespace std;

inline void  Alloc_Check(double*** host_A_vec)
{
  if ((host_A_vec) == 0)
    {
      cout << "Error: memory could not be allocated in this Array"<<endl;
      exit(1);
    }
}


inline int A(int x, int ldx,
             int y, int ldy,
             int z, int ldz)
{
  return ((z)*ldx*ldy + (y)*ldx + (x));
}




#endif
