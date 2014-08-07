/*******************************************
 * Author: Michail Georgiou
 *  Last Modified: Time-stamp: <2014-07-01 10:25:08 mike_georgiou>
 *
 *
This program creates the necessary file from gnuplot to produce
surface plots

* Written on Friday,  6 June 2014.
********************************************/

#include"Vorticity_Computation.h"

int main(int argc, char** argv)
{

  int ldx, ldy, ldz;   int safety_parameter=0.;
  double result; char value[8];
  int level_x=0;
  int level_y=0;
  int level_z=0;
  //Number of solution points, varying for every case
  ldx=64; ldy=64; ldz=64;

  File_Reader(&level_x, &level_y, &level_z);

  cout<<level_x<<" "<<level_y<<" "<<level_z<<endl;


  int time_index;
  cout<<"Please define the time you want to be printed \n";
  cin>>time_index;


  //Allocating the necessary memory for the process
  double*** temp, *d2, *d1, *d3, ***temp2, ***temp3, ***press;

  temp=Matrix_Allocator(ldx, ldy, ldz,
                        0,0,0,0,0,0);

  temp2=Matrix_Allocator(ldx, ldy, ldz,
                        0,0,0,0,0,0);


  temp3=Matrix_Allocator(ldx, ldy, ldz,
                        0,0,0,0,0,0);

  press=Matrix_Allocator(ldx, ldy, ldz,
                        0,0,0,0,0,0);



  stringstream ss;

  string format = ".bin";
  string finalName;


      ifstream grid_1 ("x.bin", ios::in | ios:: binary);
      if(!grid_1)
        {
          cout << "Cannot open file for grid1 input.\n";
          return 1;
        }
      grid_1.seekg (0, grid_1.end);
      int length_grid1 = grid_1.tellg();
      grid_1.seekg (0, grid_1.beg);


      ifstream grid_2 ("y.bin", ios::in | ios:: binary);
      if(!grid_2)
        {
          cout << "Cannot open file for grid2input.\n";
          return 1;
        }
      grid_2.seekg (0, grid_2.end);
      int length_grid2 = grid_2.tellg();
      grid_2.seekg (0, grid_2.beg);


      ifstream grid_3 ("z.bin", ios::in | ios:: binary);
      if(!grid_2)
        {
          cout << "Cannot open file for grid3input.\n";
          return 1;
        }
      grid_3.seekg (0, grid_3.end);
      int length_grid3 = grid_3.tellg();
      grid_3.seekg (0, grid_3.beg);


      d1=new double[ldx];
      d2=new double[ldy];
      d3=new double[ldz];

      safety_parameter=0;
      for(int i=0;i<ldx; i++)
        {
          grid_1.read(value,8);
          result = *((double*) value);
          d1[i]=result;

          safety_parameter+=8;
          if(safety_parameter>length_grid1)
            {
              cout << "Exceeded the length of the grid_1 file. Please check your inputs.\n";
              cout<<length_grid1<<" "<<safety_parameter<<endl;
              return 1;
            }

        }

      safety_parameter=0;
      for(int j=0;j<ldy; j++)
        {

          grid_2.read(value,8);
          result = *((double*) value);
          d2[j]=result;
          safety_parameter+=8;
          if(safety_parameter>length_grid2)
            {
              cout << "Exceeded the length of the grid_2 file. Please check your inputs.\n";
              cout<<length_grid2<<" "<<safety_parameter<<endl;
              return 1;
            }

        }

      safety_parameter=0;
      for(int j=0;j<ldz; j++)
        {

          grid_3.read(value,8);
          result = *((double*) value);
          d3[j]=result;
          safety_parameter+=8;
          if(safety_parameter>length_grid3)
            {
              cout << "Exceeded the length of the grid_2 file. Please check your inputs.\n";
              cout<<length_grid3<<" "<<safety_parameter<<endl;
              return 1;
            }

        }

  ss<<"wx"<<time_index<<format;
  finalName = ss.str();

  ifstream input_file_x;
  input_file_x.open(finalName, ios::in | ios:: binary);
  if(!input_file_x)
    {
      cout << "Cannot open file for input X.\n";
      return 1;
    }
  input_file_x.seekg (0, input_file_x.end);
  int length_input = input_file_x.tellg();
  input_file_x.seekg (0, input_file_x.beg);



  safety_parameter=0.;
  for (int k = 0; k < ldz; k++){
    for (int j = 0; j < ldy; j++){
      for (int i = 0; i < ldx; i++){


        input_file_x.read(value,8);
        result = *((double*) value);
        temp[k][j][i]=result;

        safety_parameter+=8;
        if(safety_parameter>length_input)
          {
            cout << "Exceeded the length of the input_file file. Please check your inputs.\n";
            cout<<length_input<<" "<<safety_parameter<<endl;
            return 1;
          }
      }
    }
  }

  ss.str("");
  ss<<"wy"<<time_index<<format;
  finalName = ss.str();


  ifstream input_file_y;
  input_file_y.open(finalName, ios::in | ios:: binary);
  if(!input_file_y)
    {
      cout << "Cannot open file for input Y.\n";
      return 1;
    }
  input_file_y.seekg (0, input_file_y.end);
  length_input = input_file_y.tellg();
  input_file_y.seekg (0, input_file_y.beg);



  safety_parameter=0.;
  for (int k = 0; k < ldz; k++){
    for (int j = 0; j < ldy; j++){
      for (int i = 0; i < ldx; i++){


        input_file_y.read(value,8);
        result = *((double*) value);
        temp2[k][j][i]=result;

        safety_parameter+=8;
        if(safety_parameter>length_input)
          {
            cout << "Exceeded the length of the input_file file. Please check your inputs.\n";
            cout<<length_input<<" "<<safety_parameter<<endl;
            return 1;
          }
      }
    }
  }


  ss.str("");
  ss<<"wz"<<time_index<<format;
  finalName = ss.str();


  ifstream input_file_z;
  input_file_z.open(finalName, ios::in | ios:: binary);
  if(!input_file_z)
    {
      cout << "Cannot open file for input Z.\n";
      return 1;
    }
  input_file_z.seekg (0, input_file_z.end);
  length_input = input_file_z.tellg();
  input_file_z.seekg (0, input_file_z.beg);



  safety_parameter=0.;
  for (int k = 0; k < ldz; k++){
    for (int j = 0; j < ldy; j++){
      for (int i = 0; i < ldx; i++){


        input_file_z.read(value,8);
        result = *((double*) value);
        temp3[k][j][i]=result;

        safety_parameter+=8;
        if(safety_parameter>length_input)
          {
            cout << "Exceeded the length of the input_file file. Please check your inputs.\n";
            cout<<length_input<<" "<<safety_parameter<<endl;
            return 1;
          }
      }
    }
  }

  ss.str("");
  ss<<"P"<<time_index<<format;
  finalName = ss.str();


  ifstream input_file_p;
  input_file_p.open(finalName, ios::in | ios:: binary);
  if(!input_file_p)
    {
      cout << "Cannot open file for input Z.\n";
      return 1;
    }
  input_file_p.seekg (0, input_file_p.end);
  length_input = input_file_p.tellg();
  input_file_p.seekg (0, input_file_p.beg);



  safety_parameter=0.;
  for (int k = 0; k < ldz; k++){
    for (int j = 0; j < ldy; j++){
      for (int i = 0; i < ldx; i++){


        input_file_p.read(value,8);
        result = *((double*) value);
        press[k][j][i]=result;

        safety_parameter+=8;
        if(safety_parameter>length_input)
          {
            cout << "Exceeded the length of the input_file file. Please check your inputs.\n";
            cout<<length_input<<" "<<safety_parameter<<endl;
            return 1;
          }
      }
    }
  }


  ss.str("");
  ss<<"wx"<<time_index<<"xy.dat";
  finalName=ss.str();
  ofstream output_file_xxy, output_file_yxy, output_file_zxy, output_file_pxy ;
  output_file_xxy.open(finalName,ios::out | ios:: binary);

  ss.str("");
  ss<<"wy"<<time_index<<"xy.dat";
  finalName=ss.str();
  output_file_yxy.open(finalName,ios::out | ios:: binary);

  ss.str("");
  ss<<"wz"<<time_index<<"xy.dat";
  finalName=ss.str();
  output_file_zxy.open(finalName,ios::out | ios:: binary);

      safety_parameter=0;
      for (int j = 0; j < ldy; j++){
        for (int i = 0; i < ldx; i++){

          output_file_xxy<<d1[i]<<" "<<d2[j]<<" "<<temp[level_z][j][i]<<endl;
          output_file_yxy<<d1[i]<<" "<<d2[j]<<" "<<temp2[level_z][j][i]<<endl;
          output_file_zxy<<d1[i]<<" "<<d2[j]<<" "<<temp3[level_z][j][i]<<endl;

        }

        output_file_xxy<<endl;
        output_file_yxy<<endl;
        output_file_zxy<<endl;

      }

      output_file_xxy.close();
      output_file_yxy.close();
      output_file_zxy.close();


  ss.str("");
  ss<<"wx"<<time_index<<"xz.dat";
  finalName=ss.str();
  ofstream output_file_xxz, output_file_yxz, output_file_zxz, output_file_pxz ;
  output_file_xxz.open(finalName,ios::out | ios:: binary);

  ss.str("");
  ss<<"wy"<<time_index<<"xz.dat";
  finalName=ss.str();
  output_file_yxz.open(finalName,ios::out | ios:: binary);

  ss.str("");
  ss<<"wz"<<time_index<<"xz.dat";
  finalName=ss.str();
  output_file_zxz.open(finalName,ios::out | ios:: binary);


      safety_parameter=0;
      for (int j = 0; j < ldy; j++){
        for (int i = 0; i < ldx; i++){

          output_file_xxz<<d1[i]<<" "<<d3[j]<<" "<<temp[j][level_y][i]<<endl;
          output_file_yxz<<d1[i]<<" "<<d3[j]<<" "<<temp2[j][level_y][i]<<endl;
          output_file_zxz<<d1[i]<<" "<<d3[j]<<" "<<temp3[j][level_y][i]<<endl;        

}
        output_file_xxz<<endl;
        output_file_yxz<<endl;
        output_file_zxz<<endl;

      }
      output_file_xxz.close();
      output_file_yxz.close();
      output_file_zxz.close();



  ss.str("");
  ss<<"wx"<<time_index<<"yz.dat";
  finalName=ss.str();
  ofstream output_file_xyz, output_file_yyz, output_file_zyz,
    output_file_pyz;

  output_file_xyz.open(finalName,ios::out | ios:: binary);

  ss.str("");
  ss<<"wy"<<time_index<<"yz.dat";
  finalName=ss.str();
  output_file_yyz.open(finalName,ios::out | ios:: binary);

  ss.str("");
  ss<<"wz"<<time_index<<"yz.dat";
  finalName=ss.str();
  output_file_zyz.open(finalName,ios::out | ios:: binary);

  ss.str("");
  ss<<"P"<<time_index<<"yz.dat";
  finalName=ss.str();
  output_file_pyz.open(finalName,ios::out | ios:: binary);


      safety_parameter=0;
      for (int j = 0; j < ldy; j++){
        for (int i = 0; i < ldx; i++){

          output_file_xyz<<d3[i]<<" "<<d2[j]<<" "<<temp[i][j][level_x]<<endl;
          output_file_yyz<<d3[i]<<" "<<d2[j]<<" "<<temp2[i][j][level_x]<<endl;
          output_file_zyz<<d3[i]<<" "<<d2[j]<<" "<<temp3[i][j][level_x]<<endl;

	}
        output_file_xyz<<endl;
        output_file_yyz<<endl;
        output_file_zyz<<endl;

      }
      output_file_xyz.close();
      output_file_yyz.close();
      output_file_zyz.close();






      delete []d1;
      delete []d2;
      delete []d3;


  Free_Matrix(temp,0,0,0);
  Free_Matrix(temp2,0,0,0);
  Free_Matrix(temp3,0,0,0);
  Free_Matrix(press,0,0,0);
}
