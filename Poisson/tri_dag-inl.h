#include<cstdlib>
#include<iostream>

using namespace std;


#define FREE_ARG char*

#define NR_END 1
#ifndef TRI_DAG_INL_H
#define TRI_DAG_INL_H

void nrerror(const char error_text[])
/* Numerical Recipes standard error handler */
{
  fprintf(stderr,"Numerical Recipes run-time error...\n");
  fprintf(stderr,"%s\n",error_text);
  fprintf(stderr,"...now exiting to system...\n");
  exit(1);
}



int *ivector(int nl, int nh)
/* allocate an int vector with subscript range v[nl..nh] */
	{
	int *v;
	v=(int *)malloc((size_t) ((nh-nl+1)*sizeof(int)));
	if (!v) nrerror("allocation failure in ivector()");
	return v-nl;
}

//This function allocates memmory for an 1-d double vector via the pointer to
//pointer use//

double *dvector(int nl, int nh)
	{
			double *v;
	v=(double *)malloc((size_t) ((nh-nl+1)*sizeof(double)));
	if (!v) nrerror("allocation failure in dvector()");
	return v-nl;
}



//This function de-allocates memmory for the i-d double vector defined before//
void free_dvector(double *v,int nl,int nh)
	{

	free((char *) (v+nl));
}

// This function is the error handler//

void nrerror(char error_text[])
	{
	  fprintf (stderr,"run-time error...\n");
	  fprintf(stderr,"%s\n",error_text);
	  fprintf(stderr,"...now exiting to sytem...\n");
	  exit(1);
}

 //This function deallocates memmory previously allocated with ivector


void free_ivector(int *v, int nl, int nh)
/* free an int vector allocated with ivector() */
	{
	free((char *) (v+nl));
}



// This function allocates memory for a 2-D array via the
// pointer-to-pointer data type

double **matrix( int nrl, int nrh, int ncl, int nch )
	{

	   int i;
	   int nrow=nrh-nrl+1, ncol=nch-ncl+1;
	   double **m;

	   m = (double **)malloc( (size_t)( (nrow+NR_END)*sizeof(double *) ) );
	   if(!m) nrerror( " allocation failure 1 in matrix()" );
	   m += 1;
	   m -= nrl;

	   m[nrl] = (double *) malloc( (size_t)( (nrow*ncol+NR_END) *sizeof(double) ) );
	   if (!m[nrl]) nrerror( " allocation failure 2 in matrix()" );
	   m[nrl] += NR_END;
	   m[nrl] -= ncl;

	   for (i=nrl+1; i<=nrh; i++) m[i]=m[i-1]+ncol;
	   return m;
}

//This function allocates memmory for a 2-d integer matrix with the pointer to pointer data type

int **imatrix( int nrl, int nrh, int ncl, int nch )
	{

	   int i;
	   int nrow=nrh-nrl+1, ncol=nch-ncl+1;
	   int **m;

	   m = (int **)malloc( (size_t)( (nrow+NR_END)*sizeof(int *) ) );
	   if(!m) nrerror( " allocation failure 1 in matrix()" );
	   m += 1;
	   m -= nrl;

	   m[nrl] = (int *) malloc( (size_t)( (nrow*ncol+NR_END) *sizeof(int) ) );
	   if (!m[nrl]) nrerror( " allocation failure 2 in matrix()" );
	   m[nrl] += NR_END;
	   m[nrl] -= ncl;

	   for (i=nrl+1; i<=nrh; i++) m[i]=m[i-1]+ncol;
	   return m;
}



// This function deallocates memory previously allocated with "matrix"
//
void free_matrix( double **m, int nrl, int ncl )
	{

	   free( (char *) (m[nrl]+ncl-1) );
	   free( (char *) (m+nrl-1) );
}
  

//THis function deallocates memmory for an integer matrix
void free_imatrix( int **m, int nrl, int ncl )
{

   free( (char *) (m[nrl]+ncl-1) );
   free( (char *) (m+nrl-1) );
}

#endif
