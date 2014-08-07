#ifndef VECTOR_CONSTRUCTOR_H
#define VECTOR_CONSTRUCTOR_H

inline void bubbleSort( int size,int array[][2])
{
  int swapped;
  int i;
  for (i = 1; i < size; i++)
    {
      swapped = 0;    //this flag is to check if the array is already sorted
      int j;
      for(j = 0; j < size - i; j++)
        {
          if(array[j][0] > array[j+1][0])
            {
              int temp = array[j][0];
              int temp1 = array[j][1];
              array[j][0] = array[j+1][0];
              array[j][1] = array[j+1][1];
              array[j+1][0] = temp;
              array[j+1][1] = temp1;
              swapped = 1;
            }
        }
      if(!swapped){
        break; //if it is sorted then stop
      }
    }
}



inline  int A_Boundary_ldz(int k,int ldz)
{
  if(k>=ldz){k=k-(ldz);}
  return k;
}

inline  int A_Boundary_0(int k,int ldz)
{
  if(k<0){ k= ldz+k;}
  return k;
}




inline void Periodic_Bound_Check(int i, int *i_ref, int ldx)
{

	
	if (i<3)
	  {
	    i_ref[0]=A_Boundary_0(i_ref[0],ldx);
	    i_ref[1]=A_Boundary_0(i_ref[1],ldx);
	    i_ref[2]=A_Boundary_0(i_ref[2],ldx);	 
	  }

	if (i>ldx-4)
	  {
	    i_ref[3]=A_Boundary_ldz(i_ref[3],ldx);
	    i_ref[4]=A_Boundary_ldz(i_ref[4],ldx);
	    i_ref[5]=A_Boundary_ldz(i_ref[5],ldx);	 
	  }


}


// Macros that "Converts" 1D array into 3D
#define A(z,y,x) ((z)*ldx*ldy + (y)*ldx + (x))	




#endif


