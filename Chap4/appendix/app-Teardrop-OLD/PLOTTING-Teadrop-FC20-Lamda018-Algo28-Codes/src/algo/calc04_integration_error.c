// FILE: calc04_integration_error.c

#include <stdio.h>

// INCLUDED FOR THE FUNCTION DEFINITIONS
#include "curves/c_accelern.h"
#include "curves/c_position.h"
#include "curves/c_velocity.h"
#include "common/c_min_max_int_dbl_in_array.h"
#include "common/c_random_int_dbl.h"


// ==================================================================
void proc_writeheader_data_calc_intgr_error (FILE* FHdata_calc_intgr_error)
// ==================================================================
{

  fprintf (FHdata_calc_intgr_error,
           "# DTStamp_FHdata_calc_intgr_error (integration error) %s \n",
           get_datetime_stamp ());

fprintf (FHdata_calc_intgr_error,
           "# rtime[1], u[2], u_next[3], pos_x[4], pos_y[5], pos_r[6], "
           "deltaS[7], chordlength[8], diff_length[9], sum_deltaS[10], "
           "sum_chordlength[11], diff_sum[12], eps[13], rho[14]\n");


}

// ==================================================================
void proc_writefooter_data_calc_intgr_error (FILE* FHdata_calc_intgr_error)
// ==================================================================
{

  fprintf (FHdata_calc_intgr_error,
           "# rtime[1], u[2], u_next[3], pos_x[4], pos_y[5], pos_r[6] "
           "deltaS[7], chordlength[8], diff_length[9], sum_deltaS[10], "
           "sum_chordlength[11], diff_sum[12], eps[13], rho[14]\n");

  fprintf (FHdata_calc_intgr_error,
           "# DTStamp_FHdata_calc_intgr_error (integration error) %s \n",
           get_datetime_stamp ());

}

// ==================================================================
void proc_write_calc_intgr_error (FILE *FHdata_calc_intgr_error,
      double next_arc_length, double sum_arc_length,
      double next_arc_theta, double sum_arc_theta,
      double next_arc_area, double sum_arc_area,                          
      double rtime, double u, double u_next, 
      double sum_deltaS, double sum_chordlength)

// ==================================================================
{

  double the_x = fxn_cpos_x (u);
  double the_y = fxn_cpos_y (u);
  double the_r = fxn_cpos_r (u);
  
  double deltaS = fxn_calc_deltaS_use_rho_eps (u, u_next);
  double chordlength = fxn_calc_chordlength_use_paramcurve(u, u_next);
  double diff_length = deltaS - chordlength;
  double the_sum_deltaS = sum_deltaS + deltaS;
  double the_sum_chordlength = sum_chordlength + chordlength;
  double diff_sum = sum_deltaS - sum_chordlength;
  double the_eps = fxn_cpos_epsilon (u, u_next);
  double the_rho = fxn_cpos_rho(u);


  fprintf (FHdata_calc_intgr_error,
           " %.12e, %.12e, %.12e, %.12e, %.12e, %.12e  \t"
           " %5.3lf %12.9lf %12.9lf %9.6lf %9.6lf %9.6lf %12.9lf %12.9lf "
           " %12.9lf %12.9lf %12.9lf %12.9lf %15.12lf %12.6lf \n",
           next_arc_length, sum_arc_length, next_arc_theta, sum_arc_theta, next_arc_area, sum_arc_area,
           rtime, u, u_next, the_x, the_y, the_r, deltaS, chordlength,
           diff_length, sum_deltaS, sum_chordlength,diff_sum,the_eps,the_rho);

}


// ==================================================================
// ALHAMDULILLAH 3 TIMES.
// ==================================================================

