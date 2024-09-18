// FILE: write_ngc_code.c

#include <stdio.h> // For FILE*

// INCLUDED FOR THE FUNCTION DEFINITIONS
#include "curves/c_accelern.h"
#include "curves/c_position.h"
#include "curves/c_velocity.h"

#include "algo/write_ngc_code.h"

// ==================================================================
/*
F Followed by a numerical value to define the feed rate. The magnitude and value
of which will be determined by the feed mode setting

*/

// ==================================================================
void proc_writeheader_data_ngc_code (FILE* FHdata_ngc_code, char* CurveTypeDesc, double ngc_depth, double ngc_scale)
// ==================================================================
{

fprintf (FHdata_ngc_code, "( DTStamp FHdata_ngc_code %s )\n",
           get_datetime_stamp ());

fprintf (FHdata_ngc_code, "( Bismillah 3 times WRY )\n");
fprintf (FHdata_ngc_code, "( ==== %s , PARAMETRIC CURVE ==== )\n", CurveTypeDesc);

fprintf (FHdata_ngc_code, "#<depth>=%f \n", ngc_depth);
fprintf (FHdata_ngc_code, "#<scale>=%f \n", ngc_scale);
fprintf (FHdata_ngc_code, "G21 G90 G64 G40 \n");
fprintf (FHdata_ngc_code, "G00 Z3.0 \n");
fprintf (FHdata_ngc_code, "( engraving ) \n");
fprintf (FHdata_ngc_code, "G17 \n");
fprintf (FHdata_ngc_code, "M3 S10000 \n");

// MOVE FAST HOME TO START POINT OF CURVE (FAST JOG)
// NEED TO GET POINT (x(0), y(0)) AT INITIAL u = 0
double this_u = 0.000000000;
double init_x = fxn_cpos_x (this_u);
double init_y = fxn_cpos_y (this_u);

// ACTUAL RUN G-CODE
fprintf (FHdata_ngc_code, "G00 F300 X[%12.6f ] Y[%12.6f] (# u= %.9lf Go linear fast F500 to initial point#) \n", init_x, init_y, this_u);
fprintf (FHdata_ngc_code, "G01 F100.0 Z[-2.0] \n");
fprintf (FHdata_ngc_code, "( BEGIN ====================== ) \n");



}

// ==================================================================
void
proc_writefooter_data_ngc_code (FILE *FHdata_ngc_code)
// ==================================================================
{

fprintf (FHdata_ngc_code, "G01 F100.0 Z[3.0] \n");
fprintf (FHdata_ngc_code, "M5 \n");
fprintf (FHdata_ngc_code, "M2 \n");
fprintf (FHdata_ngc_code, "( END ====================== ) \n");
fprintf (FHdata_ngc_code, "( Alhamdulillah 3 times WRY.)\n");
fprintf (FHdata_ngc_code, "( DTStamp FHdata_ngc_code %s )\n", get_datetime_stamp ());

}

// ==================================================================
void proc_write_data_ngc_code (FILE *FHdata_ngc_code, double rtime, double u,
                          double u_next, double t_interpol,
                          double curr_tang_accn, double curr_frate,
                          double curr_frate_limit, double ngc_depth, double ngc_scale, double frate_cmd)
// ==================================================================
{
  int N = (int) (1000)*rtime;

  double cpos_x = fxn_cpos_x (u);
  double cpos_y = fxn_cpos_y (u);
  double cpos_r = fxn_cpos_r (u);

  double eps = fxn_cpos_epsilon (u, u_next);
  double rho = fxn_cpos_rho (u);

  // AVOID JITTER AT MAXIMUM FEEDRATE COMMAND
  if (curr_frate > frate_cmd)
    {
      curr_frate = frate_cmd;
    }

  // AVOID JITTER AT FEEDRATE LIMIT
  if (curr_frate > curr_frate_limit)
    {
      curr_frate = curr_frate_limit;
    }

  // TO SOLVE STARTING FEEDRATE AND ENDING FEEDRATE BEING TOO SLOW
  // NEED TO TEST IN LINUXCNC SIMULATION (SETTING A MINIMUM FEEDRATE)
  if (curr_frate < 3.0)
    {
      curr_frate = 3.0;
    }

  // USE CURR_FRATE (GOOD) FOR X AND Y FEEDRATE COMPONENTS (UNIT VECTORS)
  double x_frate = curr_frate * (fxn_cvel_x (u) / fxn_cvel_r (u));
  double y_frate = curr_frate * (fxn_cvel_y (u) / fxn_cvel_r (u));

  // CHECK
  double calc_frate = sqrt (x_frate*x_frate + y_frate*y_frate);
  double frdiff = (curr_frate_limit - curr_frate);

  // ACTUAL RUN G-CODE
  fprintf (FHdata_ngc_code, "G01 F%12.6f X[%12.6f] Y[%12.6f] (#u= %.9lf eps= %.12lf Xfrate= %9.6f Yfrate= %9.6f frlimit= %9.6f frdiff= %12.9f frcmd= %6.3f #) \n", curr_frate, (cpos_x*ngc_scale), (cpos_y*ngc_scale), u, eps, x_frate, y_frate, fabs(curr_frate_limit), frdiff, frate_cmd);

}

// ==================================================================
// ALHAMDULILLAH 3 TIMES WRY
// ==================================================================
