/*******************************************
 * Author: Michail Georgiou
 *  Last Modified: Time-stamp: <2014-07-02 16:22:42 mike_georgiou>
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

  cout<<level_x<<" "<<level_y<<" "<<level_z<<endl;
  cout<<curve_xxy<<" "<<curve_yxy<<endl;
  cout<<curve_xxz<<" "<<curve_zxz<<endl;
  cout<<curve_yyz<<" "<<curve_zyz<<endl;

  //Number of solution points, varying for every case
  ldx=64; ldy=64; ldz=64;

  int time_index;
  cout<<"Please define the time you want to be printed \n";
  cin>>time_index;


  //Allocating the necessary memory for the process
  double*** temp, *d2, *d1, *d3, ***temp2, ***temp3, ***press;

  temp=Matrix_Allocator(ldx, ldy, ldz,
                        3,3,1,1,3,3);

  temp2=Matrix_Allocator(ldx, ldy, ldz,
                        3,3,1,1,3,3);


  temp3=Matrix_Allocator(ldx, ldy, ldz,
                        3,3,1,1,3,3);

  press=Matrix_Allocator(ldx, ldy, ldz,
                        3,3,1,1,3,3);



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


      d1=new double[ldx+6]; d1+=3;
      d2=new double[ldy+2]; d2+=1;
      d3=new double[ldz+6]; d3+=3;

      safety_parameter=0;
      for(int i=-3;i<ldx+3; i++)
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
      for(int j=-1;j<ldy+1; j++)
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
      for(int j=-3;j<ldz+3; j++)
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

  ss<<"X"<<time_index<<format;
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
  for (int k = -3; k < ldz+3; k++){
    for (int j = -1; j < ldy+1; j++){
      for (int i = -3; i < ldx+3; i++){


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
  ss<<"Y"<<time_index<<format;
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
  for (int k = -3; k < ldz+3; k++){
    for (int j = -1; j < ldy+1; j++){
      for (int i = -3; i < ldx+3; i++){


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
  ss<<"Z"<<time_index<<format;
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
  for (int k = -3; k < ldz+3; k++){
    for (int j = -1; j < ldy+1; j++){
      for (int i = -3; i < ldx+3; i++){


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
  for (int k = -3; k < ldz+3; k++){
    for (int j = -1; j < ldy+1; j++){
      for (int i = -3; i < ldx+3; i++){


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
  if (ghost==1)
    {

  ss.str("");
  ss<<"Xcurve"<<time_index<<"xy1.dat";
  finalName=ss.str();
  ofstream output_file_xxy, output_file_yxy, output_file_zxy, output_file_pxy ;
  output_file_xxy.open(finalName,ios::out | ios:: binary);

  ss.str("");
  ss<<"Ycurve"<<time_index<<"xy1.dat";
  finalName=ss.str();
  output_file_yxy.open(finalName,ios::out | ios:: binary);

  ss.str("");
  ss<<"Zcurve"<<time_index<<"xy1.dat";
  finalName=ss.str();
  output_file_zxy.open(finalName,ios::out | ios:: binary);

  ss.str("");
  ss<<"Pcurve"<<time_index<<"xy1.dat";
  finalName=ss.str();
  output_file_pxy.open(finalName,ios::out | ios:: binary);


      safety_parameter=0;

        for (int i = 0; i < ldx; i++){

          output_file_xxy<<d1[i]<<" "<<temp[level_z][curve_yxy][i]<<endl;
          output_file_yxy<<d1[i]<<" "<<temp2[level_z][curve_yxy][i]<<endl;
          output_file_zxy<<d1[i]<<" "<<temp3[level_z][curve_yxy][i]<<endl;
          output_file_pxy<<d1[i]<<" "<<press[level_z][curve_yxy][i]<<endl;
        }


      output_file_xxy.close();
      output_file_yxy.close();
      output_file_zxy.close();
      output_file_pxy.close();


  ss.str("");
  ss<<"Xcurve"<<time_index<<"xy2.dat";
  finalName=ss.str();
  output_file_xxy.open(finalName,ios::out | ios:: binary);

  ss.str("");
  ss<<"Ycurve"<<time_index<<"xy2.dat";
  finalName=ss.str();
  output_file_yxy.open(finalName,ios::out | ios:: binary);

  ss.str("");
  ss<<"Zcurve"<<time_index<<"xy2.dat";
  finalName=ss.str();
  output_file_zxy.open(finalName,ios::out | ios:: binary);

  ss.str("");
  ss<<"Pcurve"<<time_index<<"xy2.dat";
  finalName=ss.str();
  output_file_pxy.open(finalName,ios::out | ios:: binary);


      safety_parameter=0;
      for (int j = 0; j < ldy; j++){


          output_file_xxy<<d2[j]<<" "<<temp[level_z][j][curve_xxy]<<endl;
          output_file_yxy<<d2[j]<<" "<<temp2[level_z][j][curve_xxy]<<endl;
          output_file_zxy<<d2[j]<<" "<<temp3[level_z][j][curve_xxy]<<endl;
          output_file_pxy<<d2[j]<<" "<<press[level_z][j][curve_xxy]<<endl;
      }

      output_file_xxy.close();
      output_file_yxy.close();
      output_file_zxy.close();
      output_file_pxy.close();





  ss.str("");
  ss<<"Xcurve"<<time_index<<"xz1.dat";
  finalName=ss.str();
  output_file_xxy.open(finalName,ios::out | ios:: binary);

  ss.str("");
  ss<<"Ycurve"<<time_index<<"xz1.dat";
  finalName=ss.str();
  output_file_yxy.open(finalName,ios::out | ios:: binary);

  ss.str("");
  ss<<"Zcurve"<<time_index<<"xz1.dat";
  finalName=ss.str();
  output_file_zxy.open(finalName,ios::out | ios:: binary);

  ss.str("");
  ss<<"Pcurve"<<time_index<<"xz1.dat";
  finalName=ss.str();
  output_file_pxy.open(finalName,ios::out | ios:: binary);


      safety_parameter=0;

        for (int i = 0; i < ldx; i++){

          output_file_xxy<<d1[i]<<" "<<temp[curve_zxz][level_y][i]<<endl;
          output_file_yxy<<d1[i]<<" "<<temp2[curve_zxz][level_y][i]<<endl;
          output_file_zxy<<d1[i]<<" "<<temp3[curve_zxz][level_y][i]<<endl;
          output_file_pxy<<d1[i]<<" "<<press[curve_zxz][level_y][i]<<endl;
        }


      output_file_xxy.close();
      output_file_yxy.close();
      output_file_zxy.close();
      output_file_pxy.close();


  ss.str("");
  ss<<"Xcurve"<<time_index<<"xz2.dat";
  finalName=ss.str();
  output_file_xxy.open(finalName,ios::out | ios:: binary);

  ss.str("");
  ss<<"Ycurve"<<time_index<<"xz2.dat";
  finalName=ss.str();
  output_file_yxy.open(finalName,ios::out | ios:: binary);

  ss.str("");
  ss<<"Zcurve"<<time_index<<"xz2.dat";
  finalName=ss.str();
  output_file_zxy.open(finalName,ios::out | ios:: binary);

  ss.str("");
  ss<<"Pcurve"<<time_index<<"xz2.dat";
  finalName=ss.str();
  output_file_pxy.open(finalName,ios::out | ios:: binary);


      safety_parameter=0;
      for (int j = 0; j < ldz; j++){


          output_file_xxy<<d3[j]<<" "<<temp[j][level_y][curve_xxz]<<endl;
          output_file_yxy<<d3[j]<<" "<<temp2[j][level_y][curve_xxz]<<endl;
          output_file_zxy<<d3[j]<<" "<<temp3[j][level_y][curve_xxz]<<endl;
          output_file_pxy<<d3[j]<<" "<<press[j][level_y][curve_xxz]<<endl;
      }

      output_file_xxy.close();
      output_file_yxy.close();
      output_file_zxy.close();
      output_file_pxy.close();




  ss.str("");
  ss<<"Xcurve"<<time_index<<"yz1.dat";
  finalName=ss.str();
  output_file_xxy.open(finalName,ios::out | ios:: binary);

  ss.str("");
  ss<<"Ycurve"<<time_index<<"yz1.dat";
  finalName=ss.str();
  output_file_yxy.open(finalName,ios::out | ios:: binary);

  ss.str("");
  ss<<"Zcurve"<<time_index<<"yz1.dat";
  finalName=ss.str();
  output_file_zxy.open(finalName,ios::out | ios:: binary);

  ss.str("");
  ss<<"Pcurve"<<time_index<<"yz1.dat";
  finalName=ss.str();
  output_file_pxy.open(finalName,ios::out | ios:: binary);


      safety_parameter=0;

        for (int i = 0; i < ldy; i++){

          output_file_xxy<<d2[i]<<" "<<temp[curve_zyz][i][level_x]<<endl;
          output_file_yxy<<d2[i]<<" "<<temp2[curve_zyz][i][level_x]<<endl;
          output_file_zxy<<d2[i]<<" "<<temp3[curve_zyz][i][level_x]<<endl;
          output_file_pxy<<d2[i]<<" "<<press[curve_zyz][i][level_x]<<endl;
        }


      output_file_xxy.close();
      output_file_yxy.close();
      output_file_zxy.close();
      output_file_pxy.close();


  ss.str("");
  ss<<"Xcurve"<<time_index<<"yz2.dat";
  finalName=ss.str();
  output_file_xxy.open(finalName,ios::out | ios:: binary);

  ss.str("");
  ss<<"Ycurve"<<time_index<<"yz2.dat";
  finalName=ss.str();
  output_file_yxy.open(finalName,ios::out | ios:: binary);

  ss.str("");
  ss<<"Zcurve"<<time_index<<"yz2.dat";
  finalName=ss.str();
  output_file_zxy.open(finalName,ios::out | ios:: binary);

  ss.str("");
  ss<<"Pcurve"<<time_index<<"yz2.dat";
  finalName=ss.str();
  output_file_pxy.open(finalName,ios::out | ios:: binary);


      safety_parameter=0;
      for (int i = 0; i < ldz; i++){

          output_file_xxy<<d3[i]<<" "<<temp[i][curve_yyz][level_x]<<endl;
          output_file_yxy<<d3[i]<<" "<<temp2[i][curve_yyz][level_x]<<endl;
          output_file_zxy<<d3[i]<<" "<<temp3[i][curve_yyz][level_x]<<endl;
          output_file_pxy<<d3[i]<<" "<<press[i][curve_yyz][level_x]<<endl;
      }

      output_file_xxy.close();
      output_file_yxy.close();
      output_file_zxy.close();
      output_file_pxy.close();
    }
  else if(ghost==2)
    {


  ss.str("");
  ss<<"Xcurve"<<time_index<<"xy1.dat";
  finalName=ss.str();
  ofstream output_file_xxy, output_file_yxy, output_file_zxy, output_file_pxy ;
  output_file_xxy.open(finalName,ios::out | ios:: binary);

  ss.str("");
  ss<<"Ycurve"<<time_index<<"xy1.dat";
  finalName=ss.str();
  output_file_yxy.open(finalName,ios::out | ios:: binary);

  ss.str("");
  ss<<"Zcurve"<<time_index<<"xy1.dat";
  finalName=ss.str();
  output_file_zxy.open(finalName,ios::out | ios:: binary);

  ss.str("");
  ss<<"Pcurve"<<time_index<<"xy1.dat";
  finalName=ss.str();
  output_file_pxy.open(finalName,ios::out | ios:: binary);


      safety_parameter=0;

        for (int i = -3; i < ldx+3; i++){

          output_file_xxy<<d1[i]<<" "<<temp[level_z][curve_yxy][i]<<endl;
          output_file_yxy<<d1[i]<<" "<<temp2[level_z][curve_yxy][i]<<endl;
          output_file_zxy<<d1[i]<<" "<<temp3[level_z][curve_yxy][i]<<endl;
          output_file_pxy<<d1[i]<<" "<<press[level_z][curve_yxy][i]<<endl;
        }


      output_file_xxy.close();
      output_file_yxy.close();
      output_file_zxy.close();
      output_file_pxy.close();


  ss.str("");
  ss<<"Xcurve"<<time_index<<"xy2.dat";
  finalName=ss.str();
  output_file_xxy.open(finalName,ios::out | ios:: binary);

  ss.str("");
  ss<<"Ycurve"<<time_index<<"xy2.dat";
  finalName=ss.str();
  output_file_yxy.open(finalName,ios::out | ios:: binary);

  ss.str("");
  ss<<"Zcurve"<<time_index<<"xy2.dat";
  finalName=ss.str();
  output_file_zxy.open(finalName,ios::out | ios:: binary);

  ss.str("");
  ss<<"Pcurve"<<time_index<<"xy2.dat";
  finalName=ss.str();
  output_file_pxy.open(finalName,ios::out | ios:: binary);


      safety_parameter=0;
      for (int j = -1; j < ldy+1; j++){


          output_file_xxy<<d2[j]<<" "<<temp[level_z][j][curve_xxy]<<endl;
          output_file_yxy<<d2[j]<<" "<<temp2[level_z][j][curve_xxy]<<endl;
          output_file_zxy<<d2[j]<<" "<<temp3[level_z][j][curve_xxy]<<endl;
          output_file_pxy<<d2[j]<<" "<<press[level_z][j][curve_xxy]<<endl;
      }

      output_file_xxy.close();
      output_file_yxy.close();
      output_file_zxy.close();
      output_file_pxy.close();





  ss.str("");
  ss<<"Xcurve"<<time_index<<"xz1.dat";
  finalName=ss.str();
  output_file_xxy.open(finalName,ios::out | ios:: binary);

  ss.str("");
  ss<<"Ycurve"<<time_index<<"xz1.dat";
  finalName=ss.str();
  output_file_yxy.open(finalName,ios::out | ios:: binary);

  ss.str("");
  ss<<"Zcurve"<<time_index<<"xz1.dat";
  finalName=ss.str();
  output_file_zxy.open(finalName,ios::out | ios:: binary);

  ss.str("");
  ss<<"Pcurve"<<time_index<<"xz1.dat";
  finalName=ss.str();
  output_file_pxy.open(finalName,ios::out | ios:: binary);


      safety_parameter=0;

        for (int i = -3; i < ldx+3; i++){

          output_file_xxy<<d1[i]<<" "<<temp[curve_zxz][level_y][i]<<endl;
          output_file_yxy<<d1[i]<<" "<<temp2[curve_zxz][level_y][i]<<endl;
          output_file_zxy<<d1[i]<<" "<<temp3[curve_zxz][level_y][i]<<endl;
          output_file_pxy<<d1[i]<<" "<<press[curve_zxz][level_y][i]<<endl;
        }


      output_file_xxy.close();
      output_file_yxy.close();
      output_file_zxy.close();
      output_file_pxy.close();


  ss.str("");
  ss<<"Xcurve"<<time_index<<"xz2.dat";
  finalName=ss.str();
  output_file_xxy.open(finalName,ios::out | ios:: binary);

  ss.str("");
  ss<<"Ycurve"<<time_index<<"xz2.dat";
  finalName=ss.str();
  output_file_yxy.open(finalName,ios::out | ios:: binary);

  ss.str("");
  ss<<"Zcurve"<<time_index<<"xz2.dat";
  finalName=ss.str();
  output_file_zxy.open(finalName,ios::out | ios:: binary);

  ss.str("");
  ss<<"Pcurve"<<time_index<<"xz2.dat";
  finalName=ss.str();
  output_file_pxy.open(finalName,ios::out | ios:: binary);


      safety_parameter=0;
      for (int j = -3; j < ldz+3; j++){


          output_file_xxy<<d3[j]<<" "<<temp[j][level_y][curve_xxz]<<endl;
          output_file_yxy<<d3[j]<<" "<<temp2[j][level_y][curve_xxz]<<endl;
          output_file_zxy<<d3[j]<<" "<<temp3[j][level_y][curve_xxz]<<endl;
          output_file_pxy<<d3[j]<<" "<<press[j][level_y][curve_xxz]<<endl;
      }

      output_file_xxy.close();
      output_file_yxy.close();
      output_file_zxy.close();
      output_file_pxy.close();




  ss.str("");
  ss<<"Xcurve"<<time_index<<"yz1.dat";
  finalName=ss.str();
  output_file_xxy.open(finalName,ios::out | ios:: binary);

  ss.str("");
  ss<<"Ycurve"<<time_index<<"yz1.dat";
  finalName=ss.str();
  output_file_yxy.open(finalName,ios::out | ios:: binary);

  ss.str("");
  ss<<"Zcurve"<<time_index<<"yz1.dat";
  finalName=ss.str();
  output_file_zxy.open(finalName,ios::out | ios:: binary);

  ss.str("");
  ss<<"Pcurve"<<time_index<<"yz1.dat";
  finalName=ss.str();
  output_file_pxy.open(finalName,ios::out | ios:: binary);


      safety_parameter=0;

        for (int i = -1; i < ldy+1; i++){

          output_file_xxy<<d2[i]<<" "<<temp[curve_zyz][i][level_x]<<endl;
          output_file_yxy<<d2[i]<<" "<<temp2[curve_zyz][i][level_x]<<endl;
          output_file_zxy<<d2[i]<<" "<<temp3[curve_zyz][i][level_x]<<endl;
          output_file_pxy<<d2[i]<<" "<<press[curve_zyz][i][level_x]<<endl;
        }


      output_file_xxy.close();
      output_file_yxy.close();
      output_file_zxy.close();
      output_file_pxy.close();


  ss.str("");
  ss<<"Xcurve"<<time_index<<"yz2.dat";
  finalName=ss.str();
  output_file_xxy.open(finalName,ios::out | ios:: binary);

  ss.str("");
  ss<<"Ycurve"<<time_index<<"yz2.dat";
  finalName=ss.str();
  output_file_yxy.open(finalName,ios::out | ios:: binary);

  ss.str("");
  ss<<"Zcurve"<<time_index<<"yz2.dat";
  finalName=ss.str();
  output_file_zxy.open(finalName,ios::out | ios:: binary);

  ss.str("");
  ss<<"Pcurve"<<time_index<<"yz2.dat";
  finalName=ss.str();
  output_file_pxy.open(finalName,ios::out | ios:: binary);


      safety_parameter=0;
      for (int i = -3; i < ldz+3; i++){

          output_file_xxy<<d3[i]<<" "<<temp[i][curve_yyz][level_x]<<endl;
          output_file_yxy<<d3[i]<<" "<<temp2[i][curve_yyz][level_x]<<endl;
          output_file_zxy<<d3[i]<<" "<<temp3[i][curve_yyz][level_x]<<endl;
          output_file_pxy<<d3[i]<<" "<<press[i][curve_yyz][level_x]<<endl;
      }

      output_file_xxy.close();
      output_file_yxy.close();
      output_file_zxy.close();
      output_file_pxy.close();

    }

      d1 -= 3;
      d2 -= 1;
      d3 -= 3;

      delete[] d1;
      delete[] d2;
      delete[] d3;

      Free_Matrix(temp,3,1,3);
      Free_Matrix(temp2,3,1,3);
      Free_Matrix(temp3,3,1,3);
      Free_Matrix(press,3,1,3);

}
