#include <iostream>

using namespace std;


void tridag (double* a, double* b, double* c, double* r, double* u, int n,
             double* gam, int& flag, int x, int z) {

  double bet;

  if (b[1] == 0.0) {  // then the system consists actually of N-1 equations
    cout << "ERROR 1 within the tridag solver, x= " << x << " z= "<< z<< endl;
    flag = 1;
  }

  bet = b[1] ;
  u[1] = r[1] / b[1] ;

  //Initialize gam
  for (int i=1; i<=n ; i++)
    gam[i] = 0. ;

  if (flag == 0)
    for (int j=2 ; j<=n ; j++) {                        
      // decomposition and forward substitution

      gam[j] = c[j-1] / bet;
      bet = b[j] - a[j] * gam[j] ;

      if (bet == 0.0) {
	cout << "ERROR 2 within the tridag solver, x= " << x << " z= "<< z<< endl;
        flag = 1;
      }

      u[j] = (r[j] - a[j]*u[j-1]) /bet ;

    }
  // backsubstitution
  for (int j=(n-1) ; j>=1 ; j--)                        
    u[j] -= gam [j+1] * u[j+1] ;

}
