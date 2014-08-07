/*
 * tri_dag.h

 *
 *  Created on: Mar 25, 2013
 *      Author: paant
 */

#ifndef TRI_DAG_H_
#define TRI_DAG_H_


#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <errno.h>
#include <vector>



#include <fstream>
using namespace std;



void BCSG(double *sL, int *ijL, double *X, double *D, double *Pre,  double error, int L, int N, int& flag);



//Functions to be used throughout the computations//


double *dvector(int,int);                //This function allocates memmory for a vector with double values via the pointer to pointer method
int    *ivector(int,int);                //This function allocates memmory for a vector with integer values via the pointer to pointer method
double **matrix(int,int,int,int);	      //This function allocates memmory for a matrix with double values via the pointer to pointer method
void free_matrix(double **,int,int);     //This function deallocates memmory for a matrix with double values previously allocated with matrix()
void free_dvector(double *, int, int);   //This function deallocates memmory for a vector with double values previously allocated with dvector()
void nrerror(char error_text[]);	      //This function is the error function, used when "malloc" fails.
void free_ivector(int *, int , int );    //This function deallocates memmory for a vector with integer values previously allocated with ivector()

void nrerror(char error_text[]);


#endif /* TRI_DAG_H_ */
