#ifndef ALLOCATE_INL_H
#define ALLOCATE_INL_H
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



#endif
