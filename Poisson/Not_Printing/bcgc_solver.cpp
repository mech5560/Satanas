/*  Last Modified Time-stamp: <2014-06-06 09:22:41 mike_georgiou> */ 
/*
 * tri_dag.cpp
 *
 *  Created on: Mar 25, 2013
 *      Author: paant
 */



# include "tri_dag.h"
# include "tri_dag-inl.h"

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>





/*  **********************************************************************************************

The function BCSG uses as inputs the following:

1) *sL :  	This vector stores the non-zero values of the matrix A in row index format. 


2) *ijL : 	This vector stores the positions of the elements of the matrix A.
3) *X :   	This is the guess value. Also, the algorithm stores the solution values in *X.
4) *D :  	This is the right hand-side vector b.
5) *Pre : 	This is the preconditioning vector.
6) error : 	This is the convergence criterion for the numerical algorithm. 
7) L : 	This is the integer the corresponds to the maximum number of iterations.
8) N : 	This is the dimension of the matrix A i.e. A is a NxN-matrix. */ 






void BCSG(double *sL, int *ijL, double *X, double *D, double *Pre,  double error, int L, int N, int& flag)

	{


	//First, define the integer indices that will be used by the algorithm

	int i,j,xx,k;



	//Next, allocate memmory for the vectors and matrices that will be used throughout the computations.

	double *r;
	r=dvector(1,N);


	double *r0;
	r0=dvector(1,N);





	double *r1;
	r1=dvector(0,L);
	for (i=0; i<=L; i++)
	{
		r1[i]=0.;
	}


	double *p1;
	p1=dvector(1,N);



	double *p2;
	p2=dvector(1,N);



	double *vv;
	vv=dvector(1,N);


	double *a;
	a=dvector(1,L);
	for (i=1; i<=L; i++)
	{
		a[i]=0.;
	}


	double *s1;
	s1=dvector(1,N);


	double *ns1;
	ns1=dvector(1,L);
	for (i=1; i<=L; i++)
	{
		ns1[i]=0.;
	}

	double *s2;
	s2=dvector(1,N);

	double *t;
	t=dvector(1,N);



	double *w;
	w=dvector(1,L);
	for (i=1; i<=L; i++)
	{
		w[i]=0.;
	}
	double *beta;
	beta=dvector(1,L);
	for (i=1; i<=L; i++)
	{
		beta[i]=0.;
	}

	double *glerror;
	glerror=dvector(1,L);
	for(i=1; i<=L; i++)
	{
		glerror[i]=0.;
	}



	//This vector corresponds to the  value  A*X, i.e. the multiplication of A with the initial guess.

	double *T;
	T=dvector(1,N);

	for(i=1; i<=N; i++)
	{
		T[i]=sL[i]*X[i];


	for(k=ijL[i]; k<=ijL[i+1]-1; k++)
	{

		xx=ijL[k];

		T[i] += X[xx]*sL[k];
		}

	}

	/* Error analysis: The BCGC algorithm imlpemented herein uses the l^1 norm as a termination criteria norm.

	In particular, if X^i denotes the solution computed at the step i, then the termination criteria is


				|| A*X^i-b || < error * ( || A || * || X^i || + || b || )                                           */


	//First, Compute the l^1-norm of the matrix A:


	int ELEMENTS = ijL[N+1]-1; // Number of elements of matrix A
	double A_norm=0;                  // A_norm will be used to compute the l^1 norm of matrix A

	for(i=1; i <= ELEMENTS; i++)
	{
		A_norm = A_norm  + fabs(sL[i])/N;
	}

	//Next, compute the l^1 norm of the vector b:

	double b_norm=0.;    //b_norm will be used to compute the l^1 norm of the vector b.

	for(i=1; i<= N; i++)
	{
		b_norm = b_norm  + fabs(D[i])/N;



	}


	// Next, proceed to the main Loop.





	//********************************************************************************************************
	//********************************************************************************************************
	// ****************************  Start of the Numerical Algorithm ****************************************



	for (j=0; j<=L; j++)
	{





	//***********************************FIRST ITERATION STEP j=0***************************************************
	if (j==0)

			{

	// First, compute the initial error

	for(i=1; i<=N; i++)
	{

		r[i] = D[i]-T[i];
		r0[i] = r[i];   //Set r0[]=r[]


	}


	// Next, compute the norm of the error. For this, we first compute the l^1 norm of the guess value X

	double X_norm=0;

	for(i=1; i<= N; i++)
	{
		X_norm = X_norm +fabs(X[i])/N;
	}



	// Now, compute the residual error
	
	double res_error=0.;
	
	for(i=1; i<=N; i++)
	{
	   res_error = res_error + fabs(r0[i])/N;
	}

	//Finally, compute the quantity  error * ( || A || * || X^i || + || b || )

	double converge=0.;

	converge = error*( A_norm*X_norm+b_norm);


	// //printf("\n INITIAL GUESS \n X_norm: %10f ",X_norm);
	// //printf("\n b_norm: %10f ",b_norm);
	// //printf("\n convergence parameter: %10f ", res_error);

	//Now, check the convergence criteria

	if ( res_error <= converge)
	 {


		  //Write solution vector

		for(i=1; i<=N; i++)
		{
			X[i]=X[i];
		}


		////printf("\n Initial guess is correct \n") ;

	//Deallocate memmory


	free_dvector(a,1,L);
	free_dvector(ns1, 1,L);
	free_dvector(w,1,L);
	free_dvector(beta,1,L);
	free_dvector(glerror, 1,L);
	free_dvector(r1,0,L);
	free_dvector(T,1,N);
	free_dvector(r,1,N);
	free_dvector(p1,1,N);
	free_dvector(p2,1,N);
	free_dvector(vv,1,N);
	free_dvector(s1,1,N);
	free_dvector(s2,1,N);
	free_dvector(t,1,N);
	free_dvector(r0,1,N);

	//Terminate the algorithm.

		break;
	}


	// Next, compute the inner product r0[i]*r[i]
	
	double inner_product=0.;
	
	for(i=1; i<=N; i++)
	{
	inner_product = inner_product+ r[i]*r[i];

	}

	r1[j]=inner_product;

	}
	

		





	//************************************************** Second step j=1******************

	if (j==1)
	{


	//First, compute the vector p1

		for (i=1; i<=N; i++)

		{

			p1[i]=r[i];

			}



	//Now, solve the system Pre*p2=p1






	for(i=1; i<=N; i++)
	{
		p2[i]=(1/Pre[i])*p1[i];
		
	}


	//Next cpmpute vv = A*p2

	for(i=1; i<=N; i++)
	{
		vv[i]=sL[i]*p2[i];

	for(k=ijL[i]; k<=ijL[i+1]-1; k++)
	{
		xx=ijL[k];
		
		vv[i] += p2[xx]*sL[k];
	}
	}

	// Compute vectors a and s1

	double rvv=0;
	for(i=1; i<=N; i++)
	{
		rvv += r0[i]*vv[i];
	}


	a[j]=r1[0]/rvv;




	for(i=1; i<=N; i++)
	{
		s1[i]=r[i]-a[j]*vv[i];

	}

	//Next, compute the intermediate convergence crtiterion

	double s1_norm=0.;

	for(i=1; i<=N; i++)
	{
	   s1_norm = s1_norm + fabs(s1[i])/N;

	}
	ns1[j]=s1_norm;

	
	//printf("\n 1ST HALF \n s1_norm: %10f ", s1_norm);


	//Next, check the convergence criterion

	if ( ns1[j] <= error)
	{


	   //Write the solution vector

		for(i=1; i<=N; i++)
		{
			X[i]=X[i]+a[j]*p2[i];
	}


	//printf("\n The BCSG algorithm converges in the half first step \n") ;


	//Deallocate memmory


	free_dvector(a,1,L);
	free_dvector(ns1, 1,L);
	free_dvector(w,1,L);
	free_dvector(beta,1,L);
	free_dvector(glerror, 1,L);
	free_dvector(r1,0,L);
	free_dvector(T,1,N);
	free_dvector(r,1,N);
	free_dvector(p1,1,N);
	free_dvector(p2,1,N);
	free_dvector(vv,1,N);
	free_dvector(s1,1,N);
	free_dvector(s2,1,N);
	free_dvector(t,1,N);
	free_dvector(r0,1,N);

	// Terminate the program
		break;
	}



	//Next, compute Pre*s2 = s1

		for(i=1; i<=N; i++)
	{
		s2[i]=(1/Pre[i])*s1[i];
	}

	
	//Next, compute t=A*s2
	
	for(i=1; i<=N; i++)
	{
		t[i]=sL[i]*s2[i];

	for(k=ijL[i]; k<=ijL[i+1]-1; k++)
	{
		xx=ijL[k];
		t[i] += s2[xx]*sL[k];
	}
	}



	//Next, compute the values of w, update X and r


	//First, compute w[i]

	double ts=0.,tt=0.;

	for(i=1; i<=N; i++)
	{
		ts +=t[i]*s1[i];
		tt +=t[i]*t[i];
	}

	w[j]=ts/tt;


	//Second, update X and r

	for(i=1; i<=N; i++)
	{
		X[i]=X[i]+a[j]*p2[i]+w[j]*s2[i];
		   r[i]=s1[i]-w[j]*t[i];
	 }

	//Next, check the convergence criteria

	double X_norm=0.;   //Set the initial value to zero


	//Compute the norm of updated solution X

	for(i=1; i<= N; i++)
	{
		X_norm = X_norm +fabs(X[i])/N;
	}

	// Now, compute the updated residual error

	double res_error=0.;   //Set the parameter to zero

	for(i=1; i<=N; i++)
	{
	   res_error = res_error + fabs(r[i])/N;
	}

	//Finally, compute the quantity  error * ( || A || * || X^i || + || b || )

	double converge=0.;   //Set converge parameter to zero

	//Update the error parameter

	converge = error*( A_norm*X_norm+b_norm);


	//printf("\n FIRST STEP \n X_norm: %10f ",X_norm);
	//printf("\n b_norm: %10f ",b_norm);

	//printf("\n convergence parameter: %10f ", res_error);


	//Check the convergence criteria

	if (res_error <= converge)
	{

		for(i=1; i<=N; i++)
	   {
		   X[i]=X[i];

	   }

	   //printf("\n The BCSG algorithm has converged in the first step\n");
	
	//Deallocate memmory
	
	free_dvector(a,1,L);
	free_dvector(ns1, 1,L);
	free_dvector(w,1,L);
	free_dvector(beta,1,L);
	free_dvector(glerror, 1,L);
	free_dvector(r1,0,L);
	free_dvector(T,1,N);
	free_dvector(r,1,N);
	free_dvector(p1,1,N);
	free_dvector(p2,1,N);
	free_dvector(vv,1,N);
	free_dvector(s1,1,N);
	free_dvector(s2,1,N);
	free_dvector(t,1,N);
	free_dvector(r0,1,N);
	//Terminate the algorithm
	break;
	}

	}


	//******************************** Main Loop j>1 **********************************
	if ((j>1)&&(j<L))
	{

	//First, update r1

		for(i=1; i<=N; i++)
	{
		r1[j-1] += r0[i]*r[i];

	}

	//Check orthogonality criteria

	if( r1[j-1]==0)
	{
		//printf("\n The BCGS has reached a non orthognal subspace\n");
		flag = 1;
		break;
	}

	//Next, compute beta
	beta[j-1]=(r1[j-1]/r1[j-2])*(a[j-1]/w[j-1]);



	// Next, update p1
	for(i=1; i<=N; i++)
	{
		p1[i]=r[i]+beta[j-1]*(p1[i]-w[j-1]*vv[i]);

	}

	//Next, update p2 via solving the system Pre*p2=p1

	for(i=1; i<=N; i++)
	{
		p2[i]=(1/Pre[i])*p1[i];

	}


	//Next, update vv=A*p2

	for(i=1; i<=N; i++)
	{
		vv[i]=sL[i]*p2[i];

	for(k=ijL[i]; k<=ijL[i+1]-1; k++)
	{
		xx=ijL[k];
		vv[i] += p2[xx]*sL[k];
	}
	}


	//Next, update a[]
	double  rvv=0;
	
	for(i=1; i<=N; i++)
	{
		rvv += (r0[i]*vv[i]);
	}
	a[j]=r1[j-1]/rvv;
	
	// and s1[]
	
	for(i=1; i<=N; i++)
	{
		s1[i]=r[i]-a[j]*vv[i];
		
	}

	//Now, check the intermediate convergence criteria


	//First, compute the l1 norm of s1
	double s1_norm=0;

	for(i=1; i<=N; i++)
	{
	   s1_norm = s1_norm + fabs(s1[i])/N;

	}

	//printf("\n SECOND STEP \n s1_norm: %10f ", s1_norm);	
	

	ns1[j]=s1_norm;

	//Next, check the convergence criteria

	if ( ns1[j]<=error)
	{

	   //Update the solution vector
		for(i=1; i<=N; i++)
		{
			X[i]=X[i]+a[j]*p2[i];

		}


	   //printf("\n The BCSG algorithm has converged in the prediction step \n");
	   //printf("\n In  %d  steps\n", j);

	//Deallocate memmory

	free_dvector(a,1,L);
	free_dvector(ns1, 1,L);
	free_dvector(w,1,L);
	free_dvector(beta,1,L);
	free_dvector(glerror, 1,L);
	free_dvector(r1,0,L);
	free_dvector(T,1,N);
	free_dvector(r,1,N);
	free_dvector(p1,1,N);
	free_dvector(p2,1,N);
	free_dvector(vv,1,N);
	free_dvector(s1,1,N);
	free_dvector(s2,1,N);
	free_dvector(t,1,N);
	free_dvector(r0,1,N);
	
	//Terminate the algorithm
	break;

	}
	
	
	//Next, update s2[] via solving the system Pre*s2=s1

	for(i=1; i<=N; i++)
	{
		s2[i]=(1/Pre[i])*s1[i];
		
	}

	//Next, update t=A*s2

	for(i=1; i<=N; i++)
	{
		t[i]=sL[i]*s2[i];

	for(k=ijL[i]; k<=ijL[i+1]-1; k++)
	{
		xx=ijL[k];
		t[i] += s2[xx]*sL[k];
	}
	}

	//Next, update w, X, and r

	double ts=0.;
	double tt=0.;
	for(i=1; i<=N; i++)
	{
		ts += t[i]*s1[i];
		tt	+= (t[i]*t[i]);
	}

	w[j]=ts/tt;


	for(i=1; i<=N; i++)
	{
		X[i]=X[i]+a[j]*p2[i]+w[j]*s2[i];
		 r[i]=s1[i]-w[j]*t[i] ;

	}

	//Next, check the convergence criteria

	double X_norm=0.;   //Set the initial value to zero


	//Compute the norm of updated solution X

	for(i=1; i<= N; i++)
	{
		X_norm = X_norm +fabs(X[i])/N;
	}

	// Now, compute the updated residual error

	double res_error=0.;   //Set the parameter to zero

	for(i=1; i<=N; i++)
	{
	   res_error = res_error + fabs(r[i])/N;
	}
		
	//Finally, compute the quantity  error * ( || A || * || X^i || + || b || )

	double converge=0;   //Set converge parameter to zero

	//Update the error parameter

	converge = error*( A_norm*X_norm+b_norm);

	//printf("\n X_norm: %10f ",X_norm);
	//printf("\n b_norm: %10f ",b_norm);

	//printf("\n convergence parameter: %10f ", res_error);

	if ( res_error <= converge )
	{

	//Write down solution

	   for(i=1; i<=N; i++)
	   {
		   X[i]=X[i];
	   }

  
  	   //printf("\n The BCSG algorithm has converged \n");
  	   //printf("\n In  %d  steps\n", j);

	//Deallocate memmory
	free_dvector(a,1,L);
	free_dvector(ns1, 1,L);
	free_dvector(w,1,L);
	free_dvector(beta,1,L);
	free_dvector(glerror, 1,L);
	free_dvector(r1,0,L);
	free_dvector(T,1,N);
	free_dvector(r,1,N);
	free_dvector(p1,1,N);
	free_dvector(p2,1,N);
	free_dvector(vv,1,N);
	free_dvector(s1,1,N);
	free_dvector(s2,1,N);
	free_dvector(t,1,N);
	free_dvector(r0,1,N);

	//Terminate the algorithm
	break;

	}

	}

	if (j==L)
	  {
	    printf("\n Non convergence to desired solution. Increase the number of  iterations  or change the initial guess \n");
	    flag = 1;

	//Deallocate memmory
	free_dvector(a,1,L);
	free_dvector(ns1, 1,L);
	free_dvector(w,1,L);
	free_dvector(beta,1,L);
	free_dvector(glerror, 1,L);
	free_dvector(r1,0,L);
	free_dvector(T,1,N);
	free_dvector(r,1,N);
	free_dvector(p1,1,N);
	free_dvector(p2,1,N);
	free_dvector(vv,1,N);
	free_dvector(s1,1,N);
	free_dvector(s2,1,N);
	free_dvector(t,1,N);
	free_dvector(r0,1,N);

	//Terminate the algorithm
		break;
	}


	   }



}




