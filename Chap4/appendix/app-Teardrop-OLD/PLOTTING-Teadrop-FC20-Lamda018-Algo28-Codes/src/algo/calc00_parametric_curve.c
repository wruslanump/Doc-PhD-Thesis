// FILE: calc00_parametric_curve.c

#include <stdio.h>

// INCLUDED FOR THE FUNCTION DEFINITIONS
#include "curves/c_position.h"
#include "curves/c_velocity.h"
#include "curves/c_accelern.h"

#include "algo/calc00_parametric_curve.h"

// ==================================================================
void proc_writeheader_data_raw_curve (FILE* FHdata_raw_curve)
// ==================================================================
{

  fprintf (FHdata_raw_curve,
           "# rtime[1], u[2], u_next[3], pos_x[4], pos_y[5], pos_r[6], "
           "vel_x[7], vel_y[8], vel_r[9], acc_x[10], acc_y[11], acc_r[12], eps[13], rho[14]\n");


  fprintf (FHdata_raw_curve, "# DTStamp_FHdata_raw_curve %s \n", get_datetime_stamp ());
}


// =================================================================
void proc_write_raw_curves (FILE *FHdata_raw_curve, double rtime, double u, double u_next)
// =================================================================
  {

      double pos_x = fxn_cpos_x (u);
      double pos_y = fxn_cpos_y (u);
      double pos_r = fxn_cpos_r (u);

      double vel_x = fxn_cvel_x (u);
      double vel_y = fxn_cvel_y (u);
      double vel_r = fxn_cvel_r (u);

      double acc_x = fxn_cacc_x (u);
      double acc_y = fxn_cacc_y (u);
      double acc_r = fxn_cacc_r (u);

      double eps = fxn_cpos_epsilon(u, u_next);
      double rho = fxn_cpos_rho(u);

      fprintf (FHdata_raw_curve,
               "%12.6lf %12.9lf %12.9lf %12.6lf %12.6lf %12.6lf  %12.6lf "
               "%12.6lf %12.6lf  %12.6lf %12.6lf %12.6lf %18.15lf %12.6lf  \n",
               rtime, u, u_next, pos_x, pos_y, pos_r, vel_x, vel_y, vel_r,
               acc_x, acc_y, acc_r, eps, rho);

  }

// ==================================================================
  void proc_writefooter_data_raw_curve (FILE *FHdata_raw_curve)
// ==================================================================
{

  fprintf (FHdata_raw_curve,
           "# rtime[1], u[2], u_next[3], pos_x[4], pos_y[5], pos_r[6], "
           "vel_x[7], vel_y[8], vel_r[9], acc_x[10], acc_y[11], acc_r[12], eps[13], rho[14] \n");


  fprintf (FHdata_raw_curve, "# DTStamp_FHdata_raw_curve %s \n", get_datetime_stamp ());
}

// ==================================================================
// ALHAMDULILLAH 3 TIMES WRY
// ==================================================================

