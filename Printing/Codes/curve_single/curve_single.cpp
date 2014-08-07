/*******************************************
 * Author: Michail Georgiou
 *  Last Modified: Time-stamp: <2014-08-07 12:57:03 mike_georgiou>
 *
 *
This program creates the necessary file from gnuplot to produce
surface plots

* Written on Friday,  6 June 2014.
********************************************/

#include"Vorticity_Computation.h"

int main(int argc, char** argv)
{


  int ldx, ldy, ldz;

  int safety_parameter=0.;
  double result; char value[8];


  int level_x;
  int level_y;
  int level_z;


  int curve_xxy;
  int curve_yxy;

  int curve_xxz;
  int curve_zxz;

  int curve_yyz;
  int curve_zyz;


  int ghost;
  File_Reader_Curve(&level_x, &level_y, &level_z,
                    &curve_xxy, &curve_yxy,
                    &curve_xxz, &curve_zxz,
                    &curve_yyz, &curve_zyz,
                    &ghost);

  read_grid(&ldx, &ldy, &ldz);

  cout<<ldx<<" "<<ldy<<" "<<ldz<<endl;
  cout<<level_x<<" "<<level_y<<" "<<level_z<<endl;
  cout<<curve_xxy<<" "<<curve_yxy<<endl;
  cout<<curve_xxz<<" "<<curve_zxz<<endl;
  cout<<curve_yyz<<" "<<curve_zyz<<endl;

  int time_index;
  cout<<"Please define the time you want to be printed \n";
  cin>>time_index;
  string name;
  cout<<"Please define the quantity that you want to be printed \n";
  cin>>name;


  //Allocating the necessary memory for the process
  double*** temp, *d2, *d1, *d3;

  int left_x, left_y,left_z, right_x, right_y, right_z;

  ghost_reader( &left_x, &right_x,
                &left_y, &right_y,
                &left_z, &right_z);


  temp=Matrix_Allocator(ldx, ldy, ldz,
                        left_x,right_x,
                        left_y,right_y,
                        left_z,right_z);

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


  d1=new double[ldx+left_x + right_x]; d1+=left_x;
  d2=new double[ldy+left_y + right_y]; d2+=left_y;
  d3=new double[ldz+left_z + right_z]; d3+=left_z;


  safety_parameter=0;
  for(int i=-left_x;i<ldx+right_x; i++)
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
  for(int j=-left_y;j<ldy+right_y; j++)
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
  for(int j=-left_z;j<ldz+right_z; j++)
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

  ss<<name<<time_index<<format;
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
  for (int k = -left_z; k < ldz+right_z; k++){
    for (int j = -left_y; j < ldy+right_y; j++){
      for (int i = -left_x; i < ldx+right_x; i++){


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
  if (ghost==1)
    {

      ss.str("");
      ss<<name<<"curve"<<time_index<<"xy1.dat";
      finalName=ss.str();
      ofstream output_file_xxy, output_file_yxy, output_file_zxy, output_file_pxy ;
      output_file_xxy.open(finalName,ios::out | ios:: binary);

      safety_parameter=0;

      for (int i = 0; i < ldx; i++){

        output_file_xxy<<d1[i]<<" "<<temp[level_z][curve_yxy][i]<<endl;
      }
      output_file_xxy.close();

      ss.str("");
      ss<<name<<"curve"<<time_index<<"xy2.dat";
      finalName=ss.str();
      output_file_xxy.open(finalName,ios::out | ios:: binary);


      safety_parameter=0;
      for (int j = 0; j < ldy; j++){


        output_file_xxy<<d2[j]<<" "<<temp[level_z][j][curve_xxy]<<endl;
      }

      output_file_xxy.close();




      ss.str("");
      ss<<name<<"curve"<<time_index<<"xz1.dat";
      finalName=ss.str();
      output_file_xxy.open(finalName,ios::out | ios:: binary);

      safety_parameter=0;

      for (int i = 0; i < ldx; i++){

        output_file_xxy<<d1[i]<<" "<<temp[curve_zxz][level_y][i]<<endl;
      }
      output_file_xxy.close();

      ss.str("");
      ss<<name<<"curve"<<time_index<<"xz2.dat";
      finalName=ss.str();
      output_file_xxy.open(finalName,ios::out | ios:: binary);

      safety_parameter=0;
      for (int j = 0; j < ldz; j++){


        output_file_xxy<<d3[j]<<" "<<temp[j][level_y][curve_xxz]<<endl;
      }

      output_file_xxy.close();




      ss.str("");
      ss<<name<<"curve"<<time_index<<"yz1.dat";
      finalName=ss.str();
      output_file_xxy.open(finalName,ios::out | ios:: binary);

      safety_parameter=0;

      for (int i = 0; i < ldy; i++){

        output_file_xxy<<d2[i]<<" "<<temp[curve_zyz][i][level_x]<<endl;
      }
      output_file_xxy.close();

      ss.str("");
      ss<<name<<"curve"<<time_index<<"yz2.dat";
      finalName=ss.str();
      output_file_xxy.open(finalName,ios::out | ios:: binary);


      safety_parameter=0;
      for (int i = 0; i < ldz; i++){

        output_file_xxy<<d3[i]<<" "<<temp[i][curve_yyz][level_x]<<endl;
      }

      output_file_xxy.close();

    }
  else if(ghost==2)
    {


      ss.str("");
      ss<<name<<"curve"<<time_index<<"xy1.dat";
      finalName=ss.str();
      ofstream output_file_xxy, output_file_yxy, output_file_zxy, output_file_pxy ;
      output_file_xxy.open(finalName,ios::out | ios:: binary);
      safety_parameter=0;

      for (int i = -left_x; i < ldx+right_x; i++){

        output_file_xxy<<d1[i]<<" "<<temp[level_z][curve_yxy][i]<<endl;
      }
      output_file_xxy.close();

      ss.str("");
      ss<<name<<"curve"<<time_index<<"xy2.dat";
      finalName=ss.str();
      output_file_xxy.open(finalName,ios::out | ios:: binary);

      safety_parameter=0;
      for (int j = -left_y; j < ldy+right_y; j++){


        output_file_xxy<<d2[j]<<" "<<temp[level_z][j][curve_xxy]<<endl;
      }

      output_file_xxy.close();

      ss.str("");
      ss<<name<<"curve"<<time_index<<"xz1.dat";
      finalName=ss.str();
      output_file_xxy.open(finalName,ios::out | ios:: binary);
      safety_parameter=0;

      for (int i = -left_x; i < ldx+right_x; i++){

        output_file_xxy<<d1[i]<<" "<<temp[curve_zxz][level_y][i]<<endl;
      }


      output_file_xxy.close();
      ss.str("");
      ss<<name<<"curve"<<time_index<<"xz2.dat";
      finalName=ss.str();
      output_file_xxy.open(finalName,ios::out | ios:: binary);
      safety_parameter=0;
      for (int j = -left_z; j < ldz+right_z; j++){


        output_file_xxy<<d3[j]<<" "<<temp[j][level_y][curve_xxz]<<endl;
      }

      output_file_xxy.close();



      ss.str("");
      ss<<name<<"curve"<<time_index<<"yz1.dat";
      finalName=ss.str();
      output_file_xxy.open(finalName,ios::out | ios:: binary);

      safety_parameter=0;

      for (int i = -left_y; i < ldy+right_y; i++){

        output_file_xxy<<d2[i]<<" "<<temp[curve_zyz][i][level_x]<<endl;
      }


      output_file_xxy.close();

      ss.str("");
      ss<<name<<"curve"<<time_index<<"yz2.dat";
      finalName=ss.str();
      output_file_xxy.open(finalName,ios::out | ios:: binary);

      safety_parameter=0;
      for (int i = -left_z; i < ldz+right_z; i++){

        output_file_xxy<<d3[i]<<" "<<temp[i][curve_yyz][level_x]<<endl;
      }

      output_file_xxy.close();

    }

  d1 -= left_x;
  d2 -= left_y;
  d3 -= left_z;

  delete[] d1;
  delete[] d2;
  delete[] d3;

  Free_Matrix(temp, left_x, left_y, left_z);

}
