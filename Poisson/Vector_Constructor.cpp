/*  Last Modified Time-stamp: <2014-08-05 16:13:02 mike_georgiou> */

/* I want to write a methodology that will give me the ability to sort the nze elements
   of the Poisson equation

   *******   Notes    **********

   - In this methodology I will define a structure that will contain.

   - A double array that will contain the coefficients that will be
   placed in the s_A 1D-array

   - An integer array[][2]that will contain the total position of each point A(k,j,i)
   and the initial position guess
*/

struct Constructor
{

  int Position[14][2];
  double Value [14];
  double Diagonal;
  double dy[3];
};

struct Constructor_Y
{

  int Position_Y[13][2];
  double Value_Y[13];
  double Diagonal;
  double dy_special[2];
};



#include "Vector_Constructor.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;



void Vector_Constructor(double *s_A, double *Precond_A, int *ij_A,
                        double Coefficients_Z[4], double Coefficients_X[4], double *Delta_Y,
                        int ldx, int ldy, int ldz, int Nze)
{


  struct Constructor General_Case;
  struct Constructor_Y Special_Case;

  int k_ref[6],i_ref[6];
  int Element_Counter;



  Element_Counter = ldz*ldy*ldx +2;

  ij_A[Element_Counter-1] = Nze+2;
  s_A[Element_Counter-1] = 0.;


  for (int k=0; k<ldz; k++){
    for (int j=0; j<ldy; j++){
      for (int i=0; i<ldx; i++){

        /* passing the stencil indices to the k_ref and i_ref arrays
           in order to treat the periodic B.C in the X and Z direction periodically*/

        for (int index=0; index<3; index++)
          {
            i_ref[index] = i-(3-index);
            i_ref[index+3] = i+(1+index);

            k_ref[index] = k-(3-index);
            k_ref[index+3] = k+(1+index);

          }

        /*Checking if I am close to the Boundaries in the X and Z directions*/
        Periodic_Bound_Check(k, k_ref, ldz);
        Periodic_Bound_Check(i, i_ref, ldx);

        if (j>0 && j<ldy-1)
          {

            /* Calculating the second derivatives coefficients in the non-uniform direction*/

            /*j-1 Coefficient*/
            General_Case.dy[0] = 1. /((2.*Delta_Y[j])
                                      *(Delta_Y[j] + Delta_Y[j-1]));


            /* j Coefficient*/
            General_Case.dy[1] = - (2.*Delta_Y[j] + Delta_Y[j+1] + Delta_Y[j-1])
              /(  (Delta_Y[j+1]+Delta_Y[j])
                  *(Delta_Y[j]+Delta_Y[j-1])
                  *(2.*Delta_Y[j]) );

            /*j+1 Coefficient*/
            General_Case.dy[2] = 1. /( (Delta_Y[j+1]+Delta_Y[j])
                                       *(2.*Delta_Y[j]));



            /*Defining the nze position in the A (square) matrix*/
            for (int index=0; index<3; index++)
              {

                /*k-3:k-1*/
                General_Case.Position[index][0] = A(k_ref[index],j,i) +1;
                General_Case.Position[index][1] = index;
                General_Case.Value[index] = Coefficients_Z[index];

                /*j-1 outside loop*/

                /*i-3:i-1*/
                General_Case.Position[index+4][0] = A(k,j,i_ref[index]) +1;
                General_Case.Position[index+4][1] = index+4;
                General_Case.Value[index+4] = Coefficients_X[index];

                /* Diagonal Element*/

                /*i+1:i+3*/
                General_Case.Position[index+7][0] = A(k,j,i_ref[index+3]) +1;
                General_Case.Position[index+7][1] = index+7;
                General_Case.Value[index+7] = Coefficients_X[2-index];

                /*j+1 outside loop*/

                /*k+1:k+3*/
                General_Case.Position[index+11][0] = A(k_ref[index+3],j,i) +1;
                General_Case.Position[index+11][1] = index+11;
                General_Case.Value[index+11] = Coefficients_Z[2-index];

              }


            /* j-1*/
            General_Case.Position[3][0] = A(k,j-1,i) +1;
            General_Case.Position[3][1] = 3;
            General_Case.Value[3] = General_Case.dy[0];


            /*j+1*/
            General_Case.Position[10][0] = A(k,j+1,i) +1;
            General_Case.Position[10][1] = 10;
            General_Case.Value[10] = General_Case.dy[2];

            General_Case.Diagonal = Coefficients_X[3] + Coefficients_Z[3]
              +General_Case.dy[1];


            /* Calling the sorting function */
            bubbleSort(14,General_Case.Position);


            /* Filling the first 1:Dim_A elements of the s_A vector with the
               diagonal elements */
            s_A[A(k,j,i)+1] = General_Case.Diagonal;

            /* Filling the Preconditioner vector with the diagonal Values of A*/
            Precond_A[A(k,j,i) + 1] =  General_Case.Diagonal;

            /* Filling the first 1:Dim_A elements of the ij_A vector with the
               position of the first off diagonal elements of each row*/
            ij_A [A(k,j,i)+1] = Element_Counter;


            /*
              Filling the Dim_A+2 : NZE  of the s_A and ij_A matrices with
              the off diagonal elements and their corresponding column indices
            */
            for (int index=0; index<14; index++)
              {
                /* Value of the Rest off-Diagonal Elements */
                s_A[Element_Counter +index] =
                  General_Case.Value[General_Case.Position[index][1]];

                /* Column index of the corresponding elements*/
                ij_A [Element_Counter + index] = General_Case.Position[index][0];
              }

            Element_Counter += 14;

          }

        else if(j==0)
          {

            Special_Case.dy_special[0] = -1./
              ( (2.*Delta_Y[j])
                *(Delta_Y[j+1] + Delta_Y[j]) );

            Special_Case.dy_special[1] = 1./
              ( (2.*Delta_Y[j])
                *(Delta_Y[j+1] + Delta_Y[j]) );



            for (int index=0; index<3; index++)
              {

                /*k-3:k-1*/
                Special_Case.Position_Y[index][0] = A(k_ref[index],j,i) +1;
                Special_Case.Position_Y[index][1] = index;
                Special_Case.Value_Y[index] = Coefficients_Z[index];

                /*i-3:i-1*/
                Special_Case.Position_Y[index+3][0] = A(k,j,i_ref[index]) +1;
                Special_Case.Position_Y[index+3][1] = index+3;
                Special_Case.Value_Y[index+3] = Coefficients_X[index];

                /* Diagonal Element*/

                /*i+1:i+3*/
                Special_Case.Position_Y[index+6][0] = A(k,j,i_ref[index+3]) +1;
                Special_Case.Position_Y[index+6][1] = index+6;
                Special_Case.Value_Y[index+6] = Coefficients_X[2-index];

                /*j+1 outside loop*/

                /*k+1:k+3*/
                Special_Case.Position_Y[index+10][0] = A(k_ref[index+3],j,i) +1;
                Special_Case.Position_Y[index+10][1] = index+10;
                Special_Case.Value_Y[index+10] = Coefficients_Z[2-index];

              }

            /*j+1*/
            Special_Case.Position_Y[9][0] = A(k,j+1,i) +1;
            Special_Case.Position_Y[9][1] = 9;
            Special_Case.Value_Y[9] = Special_Case.dy_special[1];


            /* Diagonal Element */

            Special_Case.Diagonal = Coefficients_X[3] + Coefficients_Z[3]
              +Special_Case.dy_special[0];



            /* Calling the Sorting Function*/
            bubbleSort(13,Special_Case.Position_Y);



            /* Filling the first 1:Element_Counter elements of the s_A vector with the
               diagonal elements */
            s_A[A(k,j,i)+1] = Special_Case.Diagonal;

            /* Filling the Preconditioner vector with the diagonal Values of A*/
            Precond_A[A(k,j,i) + 1] =  Special_Case.Diagonal;


            /* Filling the first 1:Element_Counter elements of the ij_A vector with the
               position of the first off diagonal elements of each row*/
            ij_A [A(k,j,i)+1] = Element_Counter;


            /*
              Filling the Element_Counter+2 : NZE  of the s_A and ij_A matrices with
              the off diagonal elements and their corresponding column indices
            */
            for (int index=0; index<13; index++)
              {
                /* Value of the Rest off-Diagonal Elements */
                s_A[Element_Counter +index] =
                  Special_Case.Value_Y[ Special_Case.Position_Y[index][1] ];

                /* Column index of the corresponding elements*/
                ij_A [Element_Counter + index] = Special_Case.Position_Y[index][0];
              }

            Element_Counter += 13;
          }

        else  if (j==ldy-1)
          {

            Special_Case.dy_special[0] = -1./
              ( 2.*Delta_Y[j]
                *(Delta_Y[j] + Delta_Y[j-1]) );

            Special_Case.dy_special[1] = 1./
              ( 2.*Delta_Y[j]
                *(Delta_Y[j] + Delta_Y[j-1]) );



            for (int index=0; index<3; index++)
              {
                /*k-3:k-1*/
                Special_Case.Position_Y[index][0] = A(k_ref[index],j,i) +1;
                Special_Case.Position_Y[index][1] = index;
                Special_Case.Value_Y[index] = Coefficients_Z[index];

                /*j-1 outside loop*/

                /*i-3:i-1*/
                Special_Case.Position_Y[index+4][0] = A(k,j,i_ref[index]) +1;
                Special_Case.Position_Y[index+4][1] = index+4;
                Special_Case.Value_Y[index+4] = Coefficients_X[index];

                /*i+1:i+3*/
                Special_Case.Position_Y[index+7][0] = A(k,j,i_ref[index+3]) +1;
                Special_Case.Position_Y[index+7][1] = index+7;
                Special_Case.Value_Y[index+7] = Coefficients_X[2-index];

                /*k+1:k+3*/
                Special_Case.Position_Y[index+10][0] = A(k_ref[index+3],j,i) +1;
                Special_Case.Position_Y[index+10][1] = index+10;
                Special_Case.Value_Y[index+10] = Coefficients_Z[2-index];
              }


            /* j-1*/
            Special_Case.Position_Y[3][0] = A(k,j-1,i) +1;
            Special_Case.Position_Y[3][1] = 3;
            Special_Case.Value_Y[3] = Special_Case.dy_special[1];


            /* Diagonal Element */
            Special_Case.Diagonal = Coefficients_X[3] + Coefficients_Z[3]
              +Special_Case.dy_special[0];



            /* Calling the sorting function*/
            bubbleSort(13,Special_Case.Position_Y);



            /* Filling the first 1:Element_Counter elements of the s_A vector with the
               diagonal elements */
            s_A[A(k,j,i)+1] = Special_Case.Diagonal;

            /* Filling the Preconditioner vector with the diagonal Values of A*/
            Precond_A[A(k,j,i) + 1] =   Special_Case.Diagonal;


            /* Filling the first 1:Element_Counter elements of the ij_A vector with the
               position of the first off diagonal elements of each row*/
            ij_A [A(k,j,i)+1] = Element_Counter;


            /*Filling the Dimension_A+2 : NZE  of the s_A and ij_A matrices with
              the off diagonal elements and their corresponding column indices*/



            for (int index=0; index<13; index++)
              {
                /* Value of the Rest off-Diagonal Elements */

                s_A[Element_Counter +index] =
                  Special_Case.Value_Y[ Special_Case.Position_Y[index][1] ];

                /* Column index of the corresponding elements*/
                ij_A [Element_Counter + index] = Special_Case.Position_Y[index][0];
              }

            Element_Counter+=13;
          }
        else {cout<<"Problem";}


      }

    }
  }

}
