#ifndef FUNCTIONS_FLUX_EVALUATION_H
#define FUNCTIONS_FLUX_EVALUATION_H


//i is the index of the first component of the interpolation and differentiation
//j is the index of the second   ''                   ''          ''
inline double Interpolation(double rho_right, double velocity_right,
                            double rho_left, double velocity_left)
{

  return    0.5*( rho_right * velocity_right+
                  rho_left * velocity_left  );
}


inline double Derivative(double pressure_right, double pressure_left,
                         double dx, int order)
{

  return 1./(order * dx)*( (pressure_right) - (pressure_left));

}
#endif
