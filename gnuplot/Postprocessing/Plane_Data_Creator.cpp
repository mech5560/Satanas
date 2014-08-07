/*******************************************
 * Author: Michail Georgiou
 *  Last Modified: Time-stamp: <2014-06-11 18:58:42 mike_georgiou>
 *
 *
This program creates the necessary file from gnuplot to produce
surface plots

* Written on Friday,  6 June 2014.
********************************************/
#include<iostream>
#include <stdlib.h>     /* strtol */
#include<fstream>
#include<stdio.h>
#include <cstdlib>

double *** Matrix_Allocator(int ldx, int ldy, int ldz,
                            int x_left,int x_right,
                            int y_left,int y_right,
                            int z_left,int z_right);


void Free_Matrix(double ***pA,
                 int x_left, int y_left, int z_left);


using namespace std;

int main(int argc, char** argv) {

  char* input, *output, *domain[2];
  int N[3];

  // Reading the name of the input.bin and the output.dat
      input = argv[1];
      domain[0] = argv[2];
      domain[1] = argv[3];

      output = argv[4];

      //Reads the information about the grid domain.
      // strtol converts a  string into an integer
      N[0]=strtol(argv[5],NULL,0);
      N[1]=strtol(argv[6],NULL,0);
      N[2]=strtol(argv[7],NULL,0);

      int index=strtol(argv[8],NULL,0);
      int plane=strtol(argv[9],NULL,0);


      ifstream input_file (input, ios::in | ios:: binary);
      if(!input_file)
        {
          cout << "Cannot open file for input.\n";
          return 1;
        }


      ifstream grid_1 (domain[0], ios::in | ios:: binary);
      if(!grid_1)
        {
          cout << "Cannot open file for input.\n";
          return 1;
        }


      ifstream grid_2 (domain[1], ios::in | ios:: binary);
      if(!grid_2)
        {
          cout << "Cannot open file for input.\n";
          return 1;
        }


      ofstream output_file(output, ios::out);
      if(!output_file)
        {
          cout << "Cannot open file for output.\n";
          return 1;
        }



      //Allocating the necessary memory for the process
      double*** temp, *d2, *d1;
      temp=Matrix_Allocator(N[0],N[1],N[2],
			    0,0,0,0,0,0);


      if(index==1) // Printing the XY plane
	{
	  d2=new double[N[1]];
	  d1=new double[N[0]];


	  for(int k=0;k<N[1]; k++)
	    grid_2>>d2[k];

	  for(int i=0;i<N[0]; i++)
	    grid_1>>d1[i];


	  for (int k = 0; k < N[2]; k++){
	    for (int j = 0; j < N[1]; j++){
	      for (int i = 0; i < N[0]; i++){
		
		input_file>>temp[k][j][i];
	      }
	    }	    
	  }   

	  //Creating the output file
	  for (int j = 0; j < N[1]; j++){
	    for (int i = 0; i < N[0]; i++){
      	      output_file<<d1[i]<<" "<<d2[j]<<" "<<temp[plane][j][i]<<endl;
	    }
	    output_file<<endl;
	  }	    

	  delete[] d2;
	  delete[] d1;
	}
      if(index==2) // Printing the XZ plane
	{
	  d2=new double[N[2]];
	  d1=new double[N[0]];


	  for(int k=0;k<N[2]; k++)
	    grid_2>>d2[k];

	  for(int i=0;i<N[0]; i++)
	    grid_1>>d1[i];


	  for (int k = 0; k < N[2]; k++){
	    for (int j = 0; j < N[1]; j++){
	      for (int i = 0; i < N[0]; i++){
		
		input_file>>temp[k][j][i];
	      }
	    }	    
	  }   

	  //Creating the output file
	  for (int j = 0; j < N[2]; j++){
	    for (int i = 0; i < N[0]; i++){
      	      output_file<<d1[i]<<" "<<d2[j]<<" "<<temp[j][plane][i]<<endl;
	    }
	  }	    

	  delete[] d2;
	  delete[] d1;
	}
      if(index==3) // Printing the YZ plane
	{
	  d2=new double[N[2]];
	  d1=new double[N[1]];


	  for(int k=0;k<N[2]; k++)
	    grid_2>>d2[k];

	  for(int i=0;i<N[1]; i++)
	    grid_1>>d1[i];


	  for (int k = 0; k < N[2]; k++){
	    for (int j = 0; j < N[1]; j++){
	      for (int i = 0; i < N[0]; i++){
		
		input_file>>temp[k][j][i];
	      }
	    }	    
	  }   

	  //Creating the output file
	  for (int j = 0; j < N[2]; j++){
	    for (int i = 0; i < N[1]; i++){
      	      output_file<<d1[i]<<" "<<d2[j]<<" "<<temp[j][plane][i]<<endl;
	    }
	  }	    

	  delete[] d2;
	  delete[] d1;
	}
      Free_Matrix(temp,0,0,0);
 }
