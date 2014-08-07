/*******************************************
 * Author: Michail Georgiou
 *  Last Modified: Time-stamp: <2014-08-05 15:44:13 mike_georgiou>
 *
 *
data_reader.cpp -- This function will read the binary data and
    convert them into ascii.
    *
    * Written on Thursday, 24 July 2014.
    ********************************************/

#include"plane_data_creator.h"

void data_reader( double ***velocity,
                  string name, 
                  int ldx, int ldy, int ldz,
                  int left_x, int right_x,
                  int left_y, int right_y,
                  int left_z, int right_z)
                  
{


  string finalname;
  string format = ".bin";
  stringstream ss;

  ss<<name<<format;
  finalname = ss.str();

  // Reading the velocity x
  ifstream input_file;
  input_file.open(finalname, ios::in | ios:: binary);
  if(!input_file)
    {
      cout << "Cannot open file for input "<<name<<endl;
      exit (1);
    }
  input_file.seekg (0, input_file.end);
  int length_input = input_file.tellg();
  input_file.seekg (0, input_file.beg);



  int safety_parameter=0.;
  char value[8];
  for (int k = -left_z; k < ldz+right_z; k++){
    for (int j = -left_y; j < ldy+right_y; j++){
      for (int i = -left_x; i < ldx+right_x; i++){


        input_file.read(value,8);
        double result = *((double*) value);
        velocity[k][j][i]=result;

        safety_parameter+=8;
        if(safety_parameter>length_input)
          {
            cout << "Exceeded the length of the input_file file. Please check your inputs.\n";
            cout<<length_input<<" "<<safety_parameter<<endl;
            exit(1);
          }
      }
    }
  }
  input_file.close();


}
