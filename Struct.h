/*  Last Modified Time-stamp: <2014-06-20 17:21:25 mike_georgiou> */ 
#ifndef STRUCT_H
#define STRUCT_H

struct Arrays{
  double
  *dy, *y,

    ***velocity_x, ***velocity_y, ***velocity_z,
    ***velocity_x_new, ***velocity_y_new, ***velocity_z_new,
    ***velocity_x_tilda, ***velocity_y_tilda, ***velocity_z_tilda,

    ***flux_x, ***flux_y, ***flux_z,
    ***flux_x_new, ***flux_y_new, ***flux_z_new,

    ***rho, ***rho_new, ***rho_old,

    ***pressure, ***pressure_old, ***potential,

    ***temperature, ***temperature_new, ***temperature_avg,

    ***residual_x_old, ***residual_y_old, ***residual_z_old,
    ***residual_y, ***residual_z, ***residual_x,

    ***eddy_viscosity;



};


typedef   struct Arrays Ar;
#endif
