// FILE: calc01_lookahead_length.c

#include <math.h>
#include <stdio.h>

// INCLUDED FOR THE FUNCTION DEFINITIONS
#include "curves/c_position.h"
#include "curves/c_velocity.h"
#include "curves/c_accelern.h"

#include "algo/calc01_lookahead_length.h"
#include "algo/calc02_tang_accn_limit.h"



// The dynamic lookahead length is calculated as the time required
// for a full stop.
// The number of lookahead points is the quotient of t_look divided
// by t_interpol.

// double curr_frate;   // Current feedrate (F_0)
// double curr_accn_t;  // Current tangential acceleration (accn_t_0)
// double accn_csv_t;   // Conservative tangential deceleration value

// double t_look;   // dynamic lookahead length (is time duration to full stop)
// double max_jerk;
// double profile_ctiteria;
// double u, u_next;

// ==================================================================
int fxn_get_deceleration_profile (double u, double u_next, double accn_csv_t,
                          double curr_accn_t, double max_jerk,
                          double curr_frate)
// ==================================================================
{
int profile;   // Value 0 for triangular, 1 for trapezoidal
double temp1 = (2.0)*(accn_csv_t)*(accn_csv_t) - (curr_accn_t)*(curr_accn_t);
double temp2 = (2.0)*(max_jerk);

double criteria = (temp1)/(temp2);

if (criteria < curr_frate)
   {
     profile = 1;  // TRAPEZOIDAL DECELERATION
   } else {
     profile = 0;  // TRIANGULAR DECELERATION
   }

return (profile);
}

// ==================================================================
double
fxn_get_time_lookahead_length (double u, double u_next, double csv_tang_accn,
                               double curr_tang_accn, double max_jerk,
                               double curr_frate, int decn_profile)

// ==================================================================
{

   double time_look;  // Time to decelerate to a full stop.


   if (decn_profile == 1) // TRAPEZOIDAL
   {
     double temp1 = (curr_frate / csv_tang_accn);
     double temp2 = (curr_tang_accn + csv_tang_accn) / (max_jerk);
     double temp3 = (curr_tang_accn * curr_tang_accn);
     double temp4 = (2.0)*(csv_tang_accn)*(max_jerk);

     time_look = temp1 + temp2 + (temp3/temp4);

   }


   if (decn_profile == 0) // TRIANGULAR
   {
     double temp1 = (4.0) * (curr_frate) * (max_jerk);
     double temp2 = (2.0) * (curr_tang_accn * curr_tang_accn);
     double temp3 = sqrt (temp1 + temp2);

     time_look = (curr_tang_accn + temp3)/(max_jerk);

   }

return (time_look);
}


// ==================================================================
void proc_writeheader_data_calc_t_look (FILE* FHdata_calc_t_look)
// ==================================================================
{

  fprintf (FHdata_calc_t_look,
           "# DTStamp_FHdata_calc_t_look (time_lookahead_length) %s \n",
           get_datetime_stamp ());

    fprintf (FHdata_calc_t_look,
    "# rtime[1], u[2], u_next[3], accn_csv_t[4], curr_accn_t[5], max_jerk[6], "
    "curr_frate[7], profile[8], t_look[9] eps[10] rho[11] min_tang_accn[12] max_tang_accn[13] \n");


}

// ==================================================================
void proc_writefooter_data_calc_t_look (FILE* FHdata_calc_t_look)
// ==================================================================
{

   fprintf (FHdata_calc_t_look,
    "# rtime[1], u[2], u_next[3], accn_csv_t[4], curr_accn_t[5], max_jerk[6], "
    "curr_frate[7], profile[8], t_look[9] eps[10] rho[11] min_tang_accn[12] max_tang_accn[13] \n");

   fprintf (FHdata_calc_t_look,
            "# DTStamp_FHdata_calc_t_look (time_lookahead_length) %s \n",
            get_datetime_stamp ());


}

// ==================================================================
void proc_write_calc_t_look (FILE *FHdata_calc_t_look, double rtime, double u,
                double u_next, double curr_tang_accn, double curr_frate,
                double csv_tang_accn, double max_jerk)

// ==================================================================
{

  int decn_profile = fxn_get_deceleration_profile (u, u_next, csv_tang_accn,
                                     curr_tang_accn, max_jerk, curr_frate);

  double time_look = fxn_get_time_lookahead_length (u, u_next, csv_tang_accn,
                                     curr_tang_accn, max_jerk, curr_frate, decn_profile);

  double eps = fxn_cpos_epsilon (u, u_next);
  double rho = fxn_cpos_rho (u);

  // CODES IN "algo/calc02_tang_accn_limit.h"
  double min_tang_accn = fxn_get_min_tang_accn (u);
  double max_tang_accn = fxn_get_max_tang_accn (u);


  fprintf (FHdata_calc_t_look,
           "%12.6lf %12.9lf %12.9lf %12.9lf %12.9lf %12.9lf %12.9lf %3d %12.6lf "
           "%18.15lf %12.6lf %12.6lf %12.6lf \n",
           rtime, u, u_next, csv_tang_accn, curr_tang_accn, max_jerk, curr_frate,
           decn_profile, time_look, eps, rho, min_tang_accn, max_tang_accn);


}

// ==================================================================
// ALHAMDULILLAH 3 TIMES WRY
// ==================================================================

