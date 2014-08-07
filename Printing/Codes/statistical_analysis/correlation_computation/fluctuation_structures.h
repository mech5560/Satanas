#ifndef FLUCTUATION_STRUCTURES_H
#define FLUCTUATION_STRUCTURES_H

struct grid_information
{

  int
  ldx, ldy, ldz,

  //Ghost cells, they are always the same and for this reason i am
  //declaring them now
    left_x, right_x,
    left_y, right_y,
    left_z, right_z;
};

typedef struct grid_information grid_info;


struct variables
{
  double ***velocity_x, ***velocity_y, ***velocity_z,
    ***pressure;
};

typedef struct variables quantities;


struct var
{
  double
  *mean_x, *mean_y, *mean_z,*mean_p,
    ***fluct_x, ***fluct_y, ***fluct_z, ***fluct_p,
    
    *x, *y, *z;

};
typedef struct var data;


#endif
