#ifndef FUNCTION_VELOCITY_UPDATE_H
#define FUNCTIONS_VELOCITY_UPDATE_H


//i is the index of the first component of the interpolation and differentiation
//j is the index of the second   ''                   ''          ''
inline double Interpolation(double rho_right, double velocity_right,
                            double rho_left, double velocity_left)
{

  return        0.5*( rho_right * velocity_right+
                      rho_left * velocity_left  );
}


inline double Derivative(double pressure_right, double pressure_left,
                         double dx, int order)
{

  return 1./(order * dx)*( (pressure_right) - (pressure_left));

}

inline double Interpolation_Y(double rho_right, double velocity_right,
                              double dy_right,
                              double rho_left, double velocity_left,
                              double dy_left)

{
  // The coefficients for the interpolation in the non-uniform direction are
  //computed

  double denominator = dy_left+dy_right;
  double coefficients[2];

  coefficients[0]= dy_left/denominator; // right value
  coefficients[1]= dy_right/denominator;  // left value

  return
    coefficients[0]*( (rho_right) * (velocity_right))+
    coefficients[1]*( (rho_left) * (velocity_left));
}


inline double Derivative_Y(double value_right,double  dy_right,
                           double value_left, double dy_left)
{

  double denominator = dy_right+dy_left;

  return (value_right - value_left)/denominator;
}




#endif
