
// -- File	: nain_c_multithreading.c
// -- Date	: Wed 15 Jun 2022 02:09:23 PM +08
// -- Date : Sun 08 Jan 2023 03:26:06 AM +08 COMPLETED ALGORITHM ver 15
// -- Env	: Linux hpelbk8570w-debian10 4.19.0-23-rt-amd64
// -- #1 SMP PREEMPT RT Debian 4.19.269-1 (2022-12-20) x86_64 GNU/Linux
// -- Debian GNU/Linux 10 (buster)
// -- Author: WRY wruslandr@gmail.com
// 
// GNAT Studio Community 2021 (20210423) hosted on x86_64-pc-linux-gnu
// GNAT 9.3.0 targeting x86_64-linux-gnu
// SPARK Community 2021 (20210519)
// INSIDE GNAT STUDIO
// STEP 1. ON TOP MENU, Build => Clean => Clean All
// STEP 2. ON TOP MENU, Build => Project => Build All
// STEP 3. ON TOP MENU, Build => Run => "Select executable"
// ==================================================================

// CHANGE THESE FOR EVERY RUN.
// NAME OF PARAMETRIC CURVE
char CurveType[10] = "A20-SKWAST";
char CurveTypeDesc[80] = "SKEWED-ASTROID ALGO=20 SKIP STEP2 RUN-STEP1 RUN-ADJFR FRATECMD=20";

#include <limits.h>   // perror()
#include <math.h>     // pow(), MUST COMPILE WITH LIBRARY -lm
#include <pthread.h>  // MUST COMPILE WITH LIBRARY -lpthread
#include <stdbool.h>  // boolean variables
#include <stdio.h>    // open(), printf(), fopen(), fprintf();
#include <stdlib.h>   // atoi(), system(), rand(),
#include <string.h>   // strtok(), strcpy()
#include <sys/time.h> // For local date-time with (microseconds)
#include <time.h>     // For high-res timer clock_gettime with (nanoseconds)
#include <unistd.h>   // getcwd() CWD = current working directory

// ORDER OF INCLUDE LOCAL HEADERS BELOW IS CRITICAL
// LATER FILES REQUIRE AND USE PREVIOUS FILES
#include "common/c_dtstamp.h" // HIRES DATE-TIME STAMP
#include "common/c_min_max_int_dbl_in_array.h"
#include "common/c_parallel_port.h"  // FOR PC PARALLEL PORT
#include "common/c_random_int_dbl.h" // RANDOM NUMBERS

// INCLUDE CODES FOR FILE HANDLING
#include "files/module_open_close_files.h"

// INCLUDE CODES FOR PARAMETRIC CURVE
#include "curves/c_accelern.h"
#include "curves/c_position.h"
#include "curves/c_velocity.h"

// INCLUDE CODES FOR ALGORITHMS
#include "algo/calc00_parametric_curve.h"
#include "algo/calc01_lookahead_length.h"
#include "algo/calc02_tang_accn_limit.h"
#include "algo/calc03_feedrate_limit.h"
#include "algo/calc04_integration_error.h"
#include "algo/calc05_action_next_frate.h"
#include "algo/calc06_decide_next_frate.h"
#include "algo/calc07_iterate_u_next.h"
#include "algo/write_ngc_code.h"

// IMPLEMENTATION OF REALTIME CODES
#include "realtime/preempt_rt.h"

// IMPLEMENTATION OF pthread MULTI-THREADING
// https://stackoverflow.com/questions/15435087/how-to-set-pthread-max-stack-size
// https://stackoverflow.com/questions/4369078/relation-between-stack-limit-and-threads
// A thread's stack size is fixed at the time of thread creation.
// Only the main thread can dynamically grow its stack

// #include "pthread/pass_data_to_pthreads.h"
// #include "pthread/pthread_create_join.h"

// IMPLEMENTATION OF PARALLEL PORT HARDWARE
#include "parallel_pci/pci_parallel_port.h"
#include "parallel_usb/usb_parallel_port.h"

// Testing the use of Boost Library.
#include "cpp_codes/test_libboost.hpp"

#include "reports/c_report_01.h"

// ==================================================================
/*
The problem of parametric curve interpolation can be expressed as,
given the following five(5) values:

(1) the parametric curve C (u) ;
(2) the command feedrate F;
(3) the interpolation period T;
(4) the current (k-th interpolation period) motion status:
    that is, feedrate frate[k] and acceleration accn[k] ;
(5) the current reference point C(u[k]) .

then calculate the reference point C(u[k+1]) for the next interpolation period.

And the result should be subject to machine dynamics constraints
and chord error tolerance [23] : The constraints comprise:

(6) Axial velocities and accelerations should be limited to avoid
saturating the drive;

(7) The jerk should be limited to avoid the excitation of vibrations
in components in the machine assembly;

(8) The chord error increases with feedrate and curvature, so the
feedrate should be limited to achieve high interpolation accuracy,
while the productivity should be kept as high as possible.

(9) The interpolator plans S-shaped feedrate profiles at the beginning
and end of the parametric curve.

Machine epsilon (macheps) for 64-bit double = 1.11E-16 or 2.22E-16.

*/

// ==================================================================
// GLOBAL VARIABLES FOR MAIN PROGRAM
// ==================================================================

// VARIABLE FOR MARKING END OF LOOP (true/false)
bool loop_u_done = false;

// PARAMETER RANGE
double u_start = 0.000000000;
double u_ended = 1.000000000;

// TESTING AND DEBUGGING
// BY LIMITING POINTS INTERPOLATED
// double u_ended = 0.500000000;

// FOR FUNCTION CALL get_u_next_secondorder_parametric (....)
int N = 0;                 // Interpolation step number
double u = 0.0000000;      // parameter
double u_next = 0.0000000; // initial step (VALUE DOES NOT MATTER)

double rtime = 0.0;        // Cumulative runtime = (N*t_interpol) in seconds
double t_interpol = 0.001; // Interpolation time (period) = 1 ms per step.

// The interpolator parameters are set as shown in Table 1,
// and the command feedrate is 20 mm/s.
double frate_command = 20.0; // mm/s (REFERENCE VALUE)
// double const frate_command = 10.0; // mm/s
// double const frate_command = 25.0; // mm/s
// double const frate_command = 30.0; // mm/s
// double const frate_command = 40.0; // mm/s
// 
// The same interpolator parameters shown in Table 1 are used. The
// command feedrate is set as 2 mm/s. Table 2 shows the interpolation time
// for both curves using the controller.
// double frate_command = 2.0; // mm/s

double max_jerk = 200.0;   // Jerk limit mm/s2 as provided in Table 1.
double error_tol = 1.0E-6; // TAKE NOTE CHORD-ERROR TOLERANCE

double uppertol_bound = 10.00E-7; // meaning 1.0E(-6)
double lowertol_bound = 9.99E-7;
int count_eps_aboverange = 0; // For eps above uppertol_bound
int count_eps_withinrange = 0;
int count_eps_belowrange = 0; // For eps below lowertol_bound
int sum_eps_allranges = 0;
int count_before_step1_belowtol = 0;

// CALCULATIONS FOR U-NEXT BASED ON CHORD ERROR (EPSILON)
// STEP 1 PUSH DOWN EPS TO BELOW UPPERTOL_BOUND
double step1_unext = 0.0;
int num_of_step1_processing = 0;

// STEP 2 RAISE EPS TO BE IN RANGE (uppertol_bound ,lowertol_bound)
double step2_unext = 0.0;
int num_of_step2_processing = 0;
int count_error_step2 = 0;

// GLOBAL ERROR VARIABLES STATISTICS
// IN CODE: src/algo/calc07_iterate_u_next.c
// ERRORS IN STEP1
int count_step1_ERROR_1 = 0;
int count_step1_ERROR_2 = 0;

// ERRORS IN STEP2
int count_step2_ERROR_1 = 0;
int count_step2_ERROR_2 = 0;
int count_step2_ERROR_3 = 0;
int count_step2_ERROR_4 = 0;

// FINAL EPS CHORD-ERROR ACCOUNTING STATISTICS
int cnt_eps_above_10E_6 = 0; // uppertol_bound
int cnt_eps_betwn_10E_7_to_10E_6 = 0;
int cnt_eps_betwn_10E_8_to_10E_7 = 0;
int cnt_eps_betwn_10E_9_to_10E_8 = 0;
int cnt_eps_betwn_10E_10_to_10E_9 = 0;
int cnt_eps_below_10E_10 = 0;
int cnt_eps_total_points = 0;

int cnt_region_1 = 0;

// EQUATION (8) FOR FRATE UNIT VECTORS
double curr_alpha = 0.0; // x_frate(velocity) unit vector
double curr_beta = 0.0;  // y-frate(velocity) unit vector

// CURRENT VALUES BEFORE FEEDRATE DECISION (EQUATION 19)

double curr_norm_accn = 0.0; // Current normal acceleration
double curr_tang_accn = 0.0; // Current tangential acceleration
double curr_frate = 0.0;
double curr_deltaS = 0.0;

// CHANGES BECAUSE (rho_N, eps_N, lamda_N) CHANGES EVERY STEP
double curr_frate_limit = 0.0;
double diff_fratelimit = 100.0; // = (curr_frate_limit - curr_frate);

// FEEDRATE DECISION ACTION AND
// NEXT VARIABLE VALUES ACCORDING EQUATION (19)
int next_frate_action = 0; // DECISION VALUES = [+1, 0, -1]
int prev_frate_action = 0;

double next_tang_accn = 0.0;
double next_frate = 0.0;
double next_deltaS = 0.0;

double curr_eps = 0.0; // chord-error epsilon at N (u, u_next)
double next_eps = 0.0;

double curr_rho = 0.0; // rho = (1/radius of curvature) at N (u);
double next_rho = 0.0;
double lamda_N = 0.5; // A constant safety factor (0.0 : 1.0)

// FROM TABLE 1
double xVee_max; // = 30.0;
double yVee_max; // = 30.0;
double xAcc_max; // = 30.0;
double yAcc_max; // = 30.0;

double max_tang_accn;
double min_tang_accn;
double csv_tang_accn; // Conservative tangential acceleration;
// csv_tang_accn = 20.0;     // GIVES VALUE DECN PROFILE = 1 TRAPEZOIDAL
// csv_tang_accn = 65.0;     // GIVES VALUE DECN PROFILE = 0 TRIANGULAR
// NOTE: min_tang_accn is set to -(csv_tang_accn) when higher
// than the later.
int decn_profile; // DECELERATION PROFILE (+1 Trapezoid, -1 Triangular)

double criteria; // FOR COMPARISON BETWEEN curr_frate AND curr_frate_limit

// Chord length calculated using parametric curve using u, and u_next
//
double curr_chordlength; // Before u_next update
double next_chordlength; // After  u_next update

// deltaS calculated using rho and epsilon
// = fxn_calc_deltaS_use_rho_eps (u, u_next);
double curr_deltaS;
double next_deltaS;
// Diff Comparison = (next_deltaS - chord_length);
double diff_deltaS_chordlength;

// Chord length is calculated using (u, u_next) and parametric equation.
// Value value of chord_length is very close to curr_deltaS. Excellent.
// length(u, u_next) = point [x(u),y(u)] to point [x(u+u_next),y(u+u_next)]
double sum_chordlength = 0.0;
double sum_deltaS = 0.0;
// Diff Comparison = (sum_deltaS - sum_chordlength);
double diff_sum_deltaS_sum_chordlength;

// TERM t_look = time_look ==> The dynamic time lookahead length (time_look)
// is calculated as the "time" required for a full stop.
// TERM points_look ==> The number of lookahead points is the quotient
// of (time_look) divided by T, the interpolation period.
double time_look;   // Dynamic time lookahead length t_look
double points_look; // Number of points forward = time_look/t_interpol
double distS_look;  // ???

// TAYLOR'S RECURSIVE APPROXIMATION FOR u(t)
// FUNCTION: get_u_next_firstorder_runtime  (u, t_interpol, next_frate);
// FUNCTION: get_u_next_secondorder_runtime (u, t_interpol, next_frate);

double curr_unext1stOrder = 0.0;
double curr_unext2ndOrder = 0.0;
double next_unext1stOrder = 0.0;
double next_unext2ndOrder = 0.0;

double curr_xfrate = 0.0;
double curr_yfrate = 0.0;
double next_xfrate = 0.0;
double next_yfrate = 0.0;

// MUST ADJUST shape1 and shape2 TO MEET RISING S-CURVE SHAPE
// THE RISING S-CURVE for next_frate
// FUNCTION: = (curr_frate_limit)/pow ((1 + exp (-rsu * rshape1)), rshape2);
// (prefix r stands for rising)
// Planned Rising S-Curve for u = [u_start : end_u_rise]
// All parameters  below are adjustable.
double u_end_rise = 0.05; // GOOD 0.100
double rshape1 = 5.0;      // Shape factor of rising S-Curve
double rshape2 = 8.0;      // Shape factor of rising S-Curve
double ru1;                // = u_start;
double ru2;                // = end_u_rise;
// For linear parameter transformation (u) to (rsu)
double rsu1 = 0.00; // For linear parameter transformation (u) to (rsu)
double rsu2 = 3.00;
double rm, rkonst, rsu;

// MUST ADJUST shape1 and shape2 TO MEET FALLING S-CURVE SHAPE
// THE FALLING S-CURVE for next_frate
// FUNCTION: curr_frate_limit*(1 - 1/pow((1 + exp(-fsu*fshape1)), fshape2));
// prefix (f stands for falling)
// Planned Falling S-Curve for u = [start_u_fall : u_ended]
// All parameters  below are adjustable.
double u_start_fall = 0.95; // GOOD 0.95, 0.998
double fshape1 = 5.0;        // Shape factor of falling S-Curve
double fshape2 = 8.0; // Shape factor of falling S-curve // GOOD 8.00, 10.0
double fu1;           // = u_start_fall;
double fu2;           // = u_ended;
// For linear parameter transformation (u) to (fsu)
double fsu1 = 0.00;
double fsu2 = 3.00; // GOOD 3.00, 2.00
double fm, fkonst, fsu;

// FOR WRITING TO NGC G-CODE FILE
double ngc_depth = 2.0;
// ANY SCALING TO BE DONE AS SOURCE src/curves/c_position.c
// THIS MAINTAINS THE ERROR TOLERANCE 10(-6)
double ngc_scale = 1.0;

// STATISTICS COUNTING TOTAL POINTS,
// ABOVE_TOL_POINTS, BELOW_TOL_POINTS
int count_total_points = 0;
int already_belowtol_points = 0;
int count_abovetol_points = 0;
int count_belowtol_points = 0;
double pcnt_abovetol = 0.0;
double pcnt_belowtol = 0.0;

// STATISTICS ALGORITHM EXECUTION VALUES
// (MIN, MAX, LINENO_MAX, LINENO_MAX )

double max_frate = 0.0;
double min_frate = 0.0;
double u_maxfrate = 0.0;
double u_minfrate = 0.0;
double x_maxfrate = 0.0;
double x_minfrate = 0.0;
double y_maxfrate = 0.0;
double y_minfrate = 0.0;
int line_maxfrate = 0;
int line_minfrate = 0;
double sum_frate = 0.0;
double avg_frate = 0.0;

double max_tangaccn = 0.0;
double min_tangaccn = 0.0;
double u_maxtangaccn = 0.0;
double u_mintangaccn = 0.0;
double x_maxtangaccn = 0.0;
double x_mintangaccn = 0.0;
double y_maxtangaccn = 0.0;
double y_mintangaccn = 0.0;
int line_maxtangaccn = 0;
int line_mintangaccn = 0;
double sum_tangaccn = 0.0;
double avg_tangaccn = 0.0;

double max_rho = 0.0;
double min_rho = 0.0;
double u_maxrho = 0.0;
double u_minrho = 0.0;
double x_maxrho = 0.0;
double x_minrho = 0.0;
double y_maxrho = 0.0;
double y_minrho = 0.0;
int line_maxrho = 0;
int line_minrho = 0;
double sum_rho = 0.0;
double avg_rho = 0.0;

double max_eps = 0.0;
double min_eps = 0.0;
double u_maxeps = 0.0;
double u_mineps = 0.0;
double x_maxeps = 0.0;
double x_mineps = 0.0;
double y_maxeps = 0.0;
double y_mineps = 0.0;
int line_maxeps = 0;
int line_mineps = 0;
double sum_eps = 0.0;
double avg_eps = 0.0;

// REPORT S-CURVE RISING & FALLING
// ================================
int count_rising_s_curve_points = 0;
int count_falling_s_curve_points = 0;

// REPORT PROCESSING CURR_FRATE VS CURR_FRATE_LIMIT
// ================================================
int count_frate_islower_fratelimit = 0;  // CASE 1
int count_frate_ishigher_fratelimit = 0; // CASE 2
int count_frate_isequal_fratelimit = 0;  // CASE 3

// INTERPOLATED POINTS ACCOUNTING
double pcnt_rising = 0.0;
double pcnt_lower = 0.0;
double pcnt_equal = 0.0;
double pcnt_higher = 0.0;
double pcnt_falling = 0.0;
double sum_percentages = 0.0;
double pcnt_already_belowtol = 0.0;

// START MAIN PROGRAM
// ==================================================================
int
main (int argc, char *argv[])
{ // START MAIN PROGRAM
  // ==================================================================
  WRY_starting_salutation ();

  // OPEN ALL FILES
  proc_open_all_files ();
  proc_writeheader_all_files ();

  // FOR WRITING TO HEADER OF NGC G-CODE FILE ONLY (PASS 2 PARAMETERS)
  proc_writeheader_data_ngc_code (FHdata_ngc_code, CurveTypeDesc, ngc_depth,
                                  ngc_scale);

  start_timer (1);
  DTStamp ();
  printf ("Start while loop \n");

  // ================================================================
  // WHILE PARAMETRIC LOOP U IS NOT DONE
  // ================================================================
  while (!loop_u_done)
    {

      // THE METHOD TO AVOID CONFUSION IS AS FOLLOWS
      // IN THIS LOOP, EACH CALCULATION COMPUTES A "next_variable" USING
      // THE "curr_variable". THEN AT END OF LOOP, EACH "next_variable"
      // IS ASSIGNED BACK TO "curr_variable". SO IN THE NEXT LOOP ITERATION
      // IT USES THE "curr_variable" AGAIN.

      // **********************************************
      // DISPLAY TO SCREEN.
      printf ("%s ", CurveType);
      printf (
        " %5.3lf %12.9lf %12.9lf %6.3lf %.6e  %.6e  %.6e  %7.3lf %7.3lf "
        "%7.3lf  %.6e %10.6lf %10.6lf %10.6lf %10.6lf %12.9lf %10.6lf %10.6lf %6.2lf",
        rtime, u, u_next, t_interpol, curr_unext1stOrder, curr_unext2ndOrder,
        (curr_unext1stOrder - curr_unext2ndOrder), fxn_cpos_x (u),
        fxn_cpos_y (u), fxn_cpos_r (u), curr_eps, curr_rho, curr_tang_accn,
        curr_frate_limit, curr_frate, (curr_frate_limit - curr_frate), curr_xfrate, curr_yfrate, frate_command);

      // WRITE TO FILE 01 FOR DEBUGGING
      fprintf (FHdata_01, "%s ", CurveType);
      fprintf (
        FHdata_01,
        " %5.3lf %12.9lf %12.9lf %6.3lf %.12e %.12e %.12e %7.3lf %7.3lf "
        "%7.3lf %.12e %10.6lf %10.6lf %10.6lf %10.6lf %12.9lf %10.6lf %10.6lf %6.2lf",
        rtime, u, u_next, t_interpol, curr_unext1stOrder, curr_unext2ndOrder,
        (curr_unext1stOrder - curr_unext2ndOrder), fxn_cpos_x (u),
        fxn_cpos_y (u), fxn_cpos_r (u), curr_eps, curr_rho, curr_tang_accn,
        curr_frate_limit, curr_frate, (curr_frate_limit - curr_frate), curr_xfrate, curr_yfrate, frate_command);

      // ================================================================
      // FEEDRATE CURR_FRATE - CALCULATE RUN STATISTICS CURRENT STEP
      // ================================================================
      // GET MAX EPS
      if (curr_frate > max_frate)
        {
          max_frate = curr_frate;
          u_maxfrate = u;
          x_maxfrate = fxn_cpos_x (u);
          y_maxfrate = fxn_cpos_y (u);
          line_maxfrate = (int)(rtime * 1000);
        }
      // GET MIN EPS
      if (curr_frate < min_frate)
        {
          min_frate = curr_frate;
          u_minfrate = u;
          x_minfrate = fxn_cpos_x (u);
          y_minfrate = fxn_cpos_y (u);
          line_minfrate = (int)(rtime * 1000);
        }
      // RUNNING AVERAGE FRATE
      sum_frate = sum_frate + curr_frate;
      if (count_total_points == 0)
        {
          avg_frate = (sum_frate);
        }
      else
        {
          avg_frate = (sum_frate / count_total_points);
        }

      // ================================================================
      // CHORD ERROR EPS - CALCULATE RUN STATISTICS CURRENT STEP
      // ================================================================
      // GET MAX EPS
      if (curr_eps > max_eps)
        {
          max_eps = curr_eps;
          u_maxeps = u;
          x_maxeps = fxn_cpos_x (u);
          y_maxeps = fxn_cpos_y (u);
          line_maxeps = (int)(rtime * 1000);
        }
      // GET MIN EPS
      if (curr_eps < min_eps)
        {
          min_eps = curr_eps;
          u_mineps = u;
          x_mineps = fxn_cpos_x (u);
          y_mineps = fxn_cpos_y (u);
          line_mineps = (int)(rtime * 1000);
        }
      // RUNNING AVERAGE EPS
      sum_eps = sum_eps + curr_eps;
      if (count_total_points == 0)
        {
          avg_eps = (sum_eps);
        }
      else
        {
          avg_eps = (sum_eps / count_total_points);
        }

      // ================================================================
      // RADIUS OF CURVATURE RHO - CALCULATE RUN STATISTICS CURRENT STEP
      // ================================================================
      if (curr_rho > max_rho)
        {
          max_rho = curr_rho;
          u_maxrho = u;
          x_maxrho = fxn_cpos_x (u);
          y_maxrho = fxn_cpos_y (u);
          line_maxrho = (int)(rtime * 1000);
        }

      if (curr_rho < min_rho)
        {
          min_rho = curr_rho;
          u_minrho = u;
          x_minrho = fxn_cpos_x (u);
          y_minrho = fxn_cpos_y (u);
          line_minrho = (int)(rtime * 1000);
        }

      sum_rho = sum_rho + curr_rho;
      if (count_total_points == 0)
        {
          avg_rho = (sum_rho);
        }
      else
        {
          avg_rho = (sum_rho / count_total_points);
        }

      // ================================================================
      // TANGENTIAL ACCELERATION - CALCULATE RUN STATISTICS CURRENT STEP
      // ================================================================
      if (curr_tang_accn > max_tangaccn)
        {
          max_tangaccn = curr_tang_accn;
          u_maxtangaccn = u;
          x_maxtangaccn = fxn_cpos_x (u);
          y_maxtangaccn = fxn_cpos_y (u);
          line_maxtangaccn = (int)(rtime * 1000);
        }

      if (curr_tang_accn < min_tangaccn)
        {
          min_tangaccn = curr_tang_accn;
          u_mintangaccn = u;
          x_mintangaccn = fxn_cpos_x (u);
          y_mintangaccn = fxn_cpos_y (u);
          line_mintangaccn = (int)(rtime * 1000);
        }

      sum_tangaccn = sum_tangaccn + curr_tang_accn;
      if (count_total_points == 0)
        {
          avg_tangaccn = (sum_tangaccn);
        }
      else
        {
          avg_tangaccn = (sum_tangaccn / count_total_points);
        }
      // ==============================================================

      // ===========================================================
      // (1) GET ACCELERATION LIMITS FROM FUNCTION
      // ===========================================================
      // CODES: #include "algo/calc02_tang_accn_limit.h"
      min_tang_accn = fxn_get_min_tang_accn (u);
      max_tang_accn = fxn_get_max_tang_accn (u);

      // So the dynamic lookahead length is calculated as the "time" required
      // for a full stop.

      // The conservative tangent deceleration is set to the minimum value
      // among axial acceleration limits, it is used as the maximum
      // deceleration value and results in the conservative lookahead length.

      // CHANGES IN csv_tang_accn DUE TO CHANGES IN alpha, beta IN EQN (16)(17)
      csv_tang_accn = -(min_tang_accn);

      // printf ("%12.6lf ", min_tang_accn);
      // printf ("%12.6lf ", max_tang_accn);

      // (2) GET DECELERATION PROFILE FROM FUNCTION
      // ===========================================================
      // CODES: #include "algo/calc01_lookahead_length.c"

      decn_profile = fxn_get_deceleration_profile (
        u, u_next, csv_tang_accn, curr_tang_accn, max_jerk, curr_frate);

      // printf ("profile %3d ", decn_profile);

      // (3) GET LOOKAHEAD LENGTH (time_look) BASED ON decn_profile
      // ===========================================================
      // CODES: #include "algo/calc01_lookahead_length.c"
      // The number of lookahead points is the quotient of time_look
      // divided by t_interpol.

      time_look = fxn_get_time_lookahead_length (u, u_next, csv_tang_accn,
                                                 curr_tang_accn, max_jerk,
                                                 curr_frate, decn_profile);

      // ASSUME S_look = distS_look BELOW
      points_look = (time_look) / (t_interpol); // POINTS LOOKAHEAD
      distS_look = (time_look) * (curr_frate);  // DISTANCE LOOKAHEAD ???

      // printf ("%12.6lf ", time_look);
      // printf ("%12.6lf ", points_look);
      // printf ("%12.6lf | ", distS_look);

      // (4) GET CURRENT FEEDRATE LIMIT
      // ===========================================================
      // CODES: #include "algo/calc03_feedrate_limit.c"
      // NOTE: CALCULATE LIMIT USING frate_command AND NOT THE curr_frate
      // curr_frate_limit = MINIMUM OF 4 values:
      // (FRate_limit_1, FRate_limit_2, FRate_limit_3, FRate_limit_4)
      // NOTE: double frate_command = 20.0; // mm/s CONSTANT
      /*
            // DEBUG 1 **************************************
            printf ("==========================================\n");
            printf ("%s Start DEBUG 1 codeline 586 main, N = %6d \n", CurveType,
         N ); printf ("%s DEBUG 1 codeline 587 main - TO EXECUTE
         fxn_get_feedrate_limit, N = %6d \n", CurveType, N );
      */
      // ***********  IMPORTANT ***********************
      curr_frate_limit = fxn_get_feedrate_limit (rtime, u, u_next,
                                  frate_command, t_interpol,
                                  curr_rho, curr_eps, lamda_N);
           
      // ===========================================================
      // (5.1) PLAN RISING FEEDRATE S-CURVE BEGINNING OF PARAMETRIC CURVE
      // FROM FEEDRATE ZERO TO FEEDRATE curr_frate_limit (curr_frate??)
      // RISING S-CURVE SECTION OF PARAMETRIC CURVE
      // ============================================================
      if (u <= u_end_rise)
        {
          count_rising_s_curve_points = count_rising_s_curve_points + 1;

          // FOR DEBUGGING
          // printf ("\n%s u =      %12.9lf FRRise-S-curve at codeline 623 main
          // \n", CurveType, u);

          printf (" RiseScurve ");
          fprintf (FHdata_01, " FRRise-S-curve ");

          double curr_frate_0 = curr_frate;

          // Convert parameter(u) to S-Curve parameter (rsu) linear relation
          // rsu = (rm)*(u) + rkonst ==> linear equation (y = mx + c)
          ru1 = u_start;
          ru2 = u_end_rise;
          rm = (rsu2 - rsu1) / (ru2 - ru1); // slope value
          rkonst = rsu2 - (rm)*ru2;         // constant value

          // Transformation equation becomes
          rsu = (rm) * (u) + rkonst;

          // ITERATION WILL REACH VALUE curr_frate_limit AT TOP
          // OF S-CURVE WHEN VALUE rsu = 3.0
          next_frate
            = (curr_frate_limit) / pow ((1 + exp (-rsu * rshape1)), rshape2);

          next_tang_accn = (next_frate - curr_frate_0) / t_interpol;
          if (next_tang_accn > max_tang_accn)
            {
              next_tang_accn = max_tang_accn;
            }

          if (next_tang_accn < min_tang_accn)
            {
              next_tang_accn = min_tang_accn;
            }

          curr_frate = next_frate;
          curr_tang_accn = next_tang_accn;

        } // END RISING S-CURVE

      // =============================================================
      // (5.2) COMPUTE MIDDLE SECTION OF PARAMETRIC CURVE
      // =============================================================
      if (u > u_end_rise && u <= u_start_fall)
        {

          // =========================================================
          // CASE 1 : CURRENT FEEDRATE BELOW LIMIT
          // =========================================================
          if (curr_frate < curr_frate_limit) // frate below limit
            {
              count_frate_islower_fratelimit += 1;

              printf (" FRBelowLimit ");
              fprintf (FHdata_01, " Case-FRBelow-Limit ");

              double omega = 0.0;
              double curr_tang_accn_0 = curr_tang_accn;
              double curr_frate_0 = curr_frate;

// START BYPASS
              while (curr_frate < curr_frate_limit) // INCREASE curr_frate
                {
                  curr_frate = curr_frate
                               + fabs (omega * max_jerk) * pow (t_interpol, 2);
                  omega = omega + 0.0001;   // GOOD VALUE
                }
// END BYPASS

              // GO ONE STEP BACK TO MAKE next_frate VALUE
              // JUST BELOW curr_frate_limit = THE LIMIT
              next_frate
                = curr_frate - fabs (omega * max_jerk) * pow (t_interpol, 2);
              next_tang_accn = (next_frate - curr_frate_0) / t_interpol;

              if (next_frate == curr_frate_0) // NO CHANGE IN curr_frate
                {
                  next_tang_accn = 0.0;
                }

              if (next_tang_accn > max_tang_accn) // STAY WITHIN ACCN LIMIT
                {
                  next_tang_accn = max_tang_accn;
                }

              if (next_tang_accn < min_tang_accn) // STAY WITHIN ACCN LIMIT
                {
                  next_tang_accn = min_tang_accn;
                }

            } // END CASE 1 :

          // =========================================================
          // CASE 2 : curr_frate ABOVE curr_frate_limit
          // =========================================================
          else if (curr_frate > curr_frate_limit) // frate above limit
            {

              count_frate_ishigher_fratelimit += 1;

              // FOR DEBUGGING
              // printf ("\n%s u =       %12.9lf Case-FRAbove-Limit at codeline
              // 725 main \n", CurveType, u);

              printf (" FRAboveLimit ");
              fprintf (FHdata_01, " Case-FRAbove-Limit ");

              double omega = 0.0;
              double curr_frate0 = curr_frate;

// START BYPASS

              // DECREASE curr_frate
              while (curr_frate > curr_frate_limit)
                {
                  curr_frate = curr_frate
                               - fabs (omega * max_jerk) * pow (t_interpol, 2);
                  omega = omega + 0.0001;   // GOOD VALUE
                }
// END BYPASS

              // MAKE next_frate JUST BELOW curr_frate_limit
              // Already automatically done as the while..loop exits.
              next_frate = curr_frate;
              next_tang_accn = (next_frate - curr_frate0) / t_interpol;

              if (next_frate == curr_frate0) // NO CHANGE IN curr_frate FRATE
                {
                  next_tang_accn = 0.0;
                }

              if (next_tang_accn > max_tang_accn) // STAY WITHIN ACCN LIMIT
                {
                  next_tang_accn = max_tang_accn;
                }

              if (next_tang_accn < min_tang_accn) // STAY WITHIN ACCN LIMIT
                {
                  next_tang_accn = min_tang_accn;
                }

            } // END CASE B :

          // ==========================================================
          // CASE 3 : curr_frate EQUALS curr_frate_limit
          // ==========================================================
          if (curr_frate == curr_frate_limit)
            {

              count_frate_isequal_fratelimit += 1;

              // FOR DEBUGGING
              // printf ("%s u =       %12.lf Case-FREqual-Limit at codeline 773
              // main \n", CurveType, u);

              printf ("FREqual-Limit ");
              fprintf (FHdata_01, " Case-FREqual-Limit");

              next_frate = curr_frate;
              next_tang_accn = curr_tang_accn;

            } // END CASE C

        } // END if (u...)

      // ============================================================
      // (5.3) PLAN FALLING FEEDRATE S-CURVE AT END OF PARAMETRIC CURVE
      // FROM FEEDRATE VALUE curr_frate  TO  VALUE ZER0
      // ============================================================
      if (u > u_start_fall && u <= u_ended)
        {

          count_falling_s_curve_points = count_falling_s_curve_points + 1;

          // FOR DEBUGGING
          // printf ("\n%s u =       %12.9lf FRFall-S-curve at codeline 796 main
          // \n", CurveType, u);

          printf (" FallScurve ");
          fprintf (FHdata_01, " FRFall-S-curve ");

          // Convert parameter(u) to S-Curve parameter (fsu) linear relation
          // fsu = (fm)*(u) + ykonst ==> linear equation (y = mx + c)
          fu1 = u_start_fall;
          fu2 = u_ended;
          fm = (fsu2 - fsu1) / (fu2 - fu1);
          fkonst = fsu2 - (fm)*fu2;

          // Transformation u to fsu equation becomes
          fsu = (fm) * (u) + fkonst;

          // ITERATION WILL REDUCE next_frate TO REACH VALUE ZERO
          // OF S-CURVE WHEN VALUE OF su = 3.0
          next_frate = curr_frate_limit
                       * (1 - 1 / pow ((1 + exp (-fsu * fshape1)), fshape2));
          next_tang_accn = (next_frate - curr_frate) / t_interpol;

          if (next_tang_accn > max_tang_accn)
            {
              next_tang_accn = max_tang_accn;
            }
          if (next_tang_accn < min_tang_accn)
            {
              next_tang_accn = min_tang_accn;
            }

        } // END FALLING S-CURVE

      // ============================================================
      // (8) CALCULATE NEXT SERVO REFERENCE POINT C(u + u_next)
      // RECURSIVE TAYLOR'S APPROXIMATION FOR u(t)
      // NEED TO SEND CURRENT FRATE TO USE IN U_NEXT SECOND ORDER CALCULATION
      // ============================================================

      // USING UNIT VELOCITY VECTOR COMPONENTS FOR X-FEEDRATE AND Y-FEEDRATE
      next_xfrate = next_frate * (fxn_cvel_x (u) / fxn_cvel_r (u));
      next_yfrate = next_frate * (fxn_cvel_y (u) / fxn_cvel_r (u));

      // FIRST ORDER TAYLOR'S RECURSIVE APPROXIMATION FOR U_NEXT
      next_unext1stOrder = get_u_next_firstorder_runtime (
        rtime, u, u_next, t_interpol, frate_command);

      // FIRST ORDER TAYLOR'S RECURSIVE APPROXIMATION FOR U_NEXT
      next_unext2ndOrder = get_u_next_secondorder_runtime (
        rtime, u, u_next, t_interpol, frate_command);

      // GET THE NEXT u_next (INCREMENT IN PARAMETER u) USING next_frate
      u_next = get_u_next_secondorder_runtime (rtime, u, u_next, t_interpol,
                                               frate_command);

      // COUNTING POINTS ABOVE AND BELOW TOLERANCE EPS
      count_total_points = count_total_points + 1;

     
      // *************************************************
      // STEP 1 PUSH DOWN EPS TO BELOW UPPERTOL_BOUND
      // *************************************************
      // GET THE NEXT u_next SUCH THAT epsilon IS BELOW ERROR TOLERANCE.
      // CODE LOCATION: src/algo/calc07_iterate_u_next.c

      if (fxn_cpos_epsilon (u, u_next) > uppertol_bound)
        {
          // CAPTURE NUMBER OF POINTS WRETE EPS IS ABOVE TOLERANCE
          count_abovetol_points = count_abovetol_points + 1;

          // GO TO REDUCE EPS TO BELOW TOLERANCE
          step1_unext = fxn_get_u_next_with_constrained_eps (
               u, u_next, uppertol_bound, &count_step1_ERROR_1,
               &count_step1_ERROR_2);

          num_of_step1_processing += 1;

          // NEW VALUE u_next UPDATED  **************** IMPORTANT
          u_next = step1_unext;
        }
      else
        { // BEFORE STEP 1, EPS ALREADY BELOW uppertol_bound
          count_before_step1_belowtol += 1;
        }

      // IF EPS IS ALREADY BELOW TOL (BYPASS IF LOOP ABOVE)
      // ALSO TO CONFIRM THAT THE IF..LOOP ABOVE WORKS AND NOW
      count_belowtol_points = count_belowtol_points + 1;

      // **********************************************************
      // STEP 2 RAISE EPS TO RANGE (uppertol_bound ,lowertol_bound)
      // **********************************************************
      // GET THE NEXT u_next SUCH THAT eps IS WITHIN RANGE
      // CODE LOCATION: src/algo/calc07_iterate_u_next.c

      if (curr_eps > uppertol_bound)
        {
          count_eps_aboverange += 1;
        }
      else if ((curr_eps < uppertol_bound) && (curr_eps > lowertol_bound))
        {
          count_eps_withinrange += 1;
        }
      else if (curr_eps < lowertol_bound)
        {
          count_eps_belowrange += 1; // INCREMENT COUNT
        }
 // END BYPASS STEP 1

 /* // START BYPASS STEP 2        
          // RAISE THIS EPS TO BE INSIDE RANGE SUCH THAT
          // (uppertol_bound < curr_eps < lowertol_bound)
          // ******************************************************
          // FUNCTION CALL BY REFERENCE - USE & AS MEMORY ADDRESS
          // GO TO RAISE EPS TO RANGE (uppertol_bound, lowertol_bound)
          step2_unext = fxn_get_u_next_with_eps_both_bounded (
            u, u_next, uppertol_bound, lowertol_bound, &count_step2_ERROR_1,
            &count_step2_ERROR_2, &count_step2_ERROR_3, &count_step2_ERROR_4);

          num_of_step2_processing += 1;

          // NEW VALUE u_next UPDATED *************** IMPORTANT
          u_next = step2_unext;

          }
      else
        {
          printf (
            "ERROR IN MAIN: COUNTING EPS POINTS step2_unext CALCULATION.\n");
          count_error_step2 += 1;
        }
*/

      // ********************************************
      // ALWAYS GURANTEE u MOVES FORWARD (ALWAYS POSITIVE)
      u_next = fabs (u_next);

      // ============================================================
      // (6) AFTER NEW u_next, COMPARE next_deltaS AND next_chord_length
      // ============================================================

      // COMPARE next_deltaS WITH next_chordlength
      // CODES INSIDE: curves/c_position.c
      next_deltaS = fxn_calc_deltaS_use_rho_eps (u, u_next);
      next_chordlength = fxn_calc_chordlength_use_paramcurve (u, u_next);
      diff_deltaS_chordlength = (next_deltaS - next_chordlength);

      // COMPARE sum_deltaS WITH sum_chordlength
      sum_deltaS = sum_deltaS + next_deltaS;
      sum_chordlength = sum_chordlength + next_chordlength;
      diff_sum_deltaS_sum_chordlength = (sum_deltaS - sum_chordlength);

      // ============================================================
      // (7) GET EPSILON AND RHO FROM PARAMETRIC FUNCTION
      // ============================================================
      // AFTER OBTAINING u_next VALUE CALCULATE NEXT EPSILON
      // CODES INSIDE: curves/c_position.c AND curves/c_pos_epsilon.h
      next_eps = fxn_cpos_epsilon (u, u_next);

      // DEBUGGING
      // printf ("next_eps = %.9e \n", next_eps);

      // GET RHO = RECIPROCAL RADIUS OF CURVATURE
      // CODES INSIDE: curves/c_position.c AND curves/c_pos_rho.h
      next_rho = fxn_cpos_rho (u + u_next);

      // ===========================================================
      // (8) FINAL EPS CHORD-ERROR ACCOUNTING STATISTICS
      // ===========================================================
      if (next_eps >= 1.0E-6)
        {
          cnt_eps_above_10E_6 += 1;
        }
      else if ((next_eps < 1.0E-6) && (next_eps >= 1.0E-7))
        {
          cnt_eps_betwn_10E_7_to_10E_6 += 1;
        }
      else if ((next_eps < 1.0E-7) && (next_eps >= 1.0E-8))
        {
          cnt_eps_betwn_10E_8_to_10E_7 += 1;
        }
      else if ((next_eps < 1.0E-8) && (next_eps >= 1.0E-9))
        {
          cnt_eps_betwn_10E_9_to_10E_8 += 1;
        }
      else if ((next_eps < 1.0E-9) && (next_eps >= 1.0E-10))
        {
          cnt_eps_betwn_10E_10_to_10E_9 += 1;
        }
      else if (next_eps < 1.0E-10)
        {
          cnt_eps_below_10E_10 += 1;
        }
      else
        {
          printf (" ERROR: IN CHECKING EPS FINAL STATISTICS. \n ");
        }

      // FOR EPS STATISTICS TOTAL COUNTS PROCESSED
      cnt_eps_total_points += 1;

      // ============================================================

      // END DEBUG PRINT  **************** IMPT *************
      printf ("\n"); // TEMP
      fprintf (FHdata_01, "\n");

      // WRITE TO FILE BEFORE INCREMENT LOOP
      proc_write_raw_curves (FHdata_raw_curve, rtime, u, u_next);
      proc_write_calc_tang_accn (FHdata_calc_tang_accn, N, curr_tang_accn,
                                 rtime, u, u_next);
      proc_write_calc_t_look (FHdata_calc_t_look, rtime, u, u_next,
                              curr_tang_accn, curr_frate, csv_tang_accn,
                              max_jerk);
      proc_write_calc_frate_limit (FHdata_calc_frate_limit, rtime, u, u_next,
                                   curr_frate, t_interpol, curr_rho, curr_eps,
                                   lamda_N, curr_frate);

      proc_write_calc_intgr_error (FHdata_calc_intgr_error, rtime, u, u_next,
                                   sum_deltaS, sum_chordlength);
      proc_write_calc_u_next (FHdata_calc_u_next, rtime, u, u_next, t_interpol,
                              curr_tang_accn, curr_frate, curr_frate_limit,
                              frate_command);

      // WRITE TO GCODE FILE INSIDE FOLDER: ngcode
      // FILENAME: data_ngc_code.ngc
      proc_write_data_ngc_code (FHdata_ngc_code, rtime, u, u_next, t_interpol,
                                curr_tang_accn, curr_frate, curr_frate_limit,
                                ngc_depth, ngc_scale, frate_command);

      // ============================================================
      // INCREMENT THE WHILE PARAMETER LOOP: while (!loop_u_done)
      // IMPORTANT FOR LAST U-NEXT
      double u_beforelast = u;

      u = u + u_next;
      N = N + 1;
      rtime = N * t_interpol;

      // VARIABLE VALUES FOR THE NEXT LOOP ITERATION
      prev_frate_action = next_frate_action;
      curr_tang_accn = next_tang_accn;

      curr_unext1stOrder = next_unext1stOrder;
      curr_unext2ndOrder = next_unext2ndOrder;

      curr_frate = next_frate;
      curr_xfrate = next_xfrate;
      curr_yfrate = next_yfrate;

      curr_deltaS = next_deltaS;
      curr_chordlength = next_chordlength;
      curr_eps = next_eps;
      curr_rho = next_rho;

      // ============================================================
      // CHECK FOR LAST LINE WHERE u_ended = 1.000000000;
      // ============================================================
      if (u >= u_ended)
        {

          loop_u_done = true; // NOW LOOP U IS DONE

          u_next = (u_ended - u_beforelast); // LAST INCREMENT
          u = u_ended; // FORCE u BACKWARD TO EXACT END POINT
          N = N;       // LAST LINE NUMBER
          rtime = N * t_interpol;

          next_tang_accn = 0.0; // DOUBLE
          next_frate = 0.0;
          next_deltaS = fxn_calc_deltaS_use_rho_eps (u_beforelast, u_next);
          next_chordlength
            = fxn_calc_chordlength_use_paramcurve (u_beforelast, u_next);
          next_eps = fxn_cpos_epsilon (u_beforelast, u_next);
          next_rho = fxn_cpos_rho (u_beforelast + u_next / 2.0);

          // VARIABLE VALUES FOR RECORD OF LAST LINE IN FILE
          // prev_frate_action = next_frate_action;
          curr_tang_accn = next_tang_accn;
          curr_frate = next_frate;
          curr_deltaS = next_deltaS;
          curr_chordlength = next_chordlength;
          curr_eps = next_eps;
          curr_rho = next_rho;

          // WRITE LAST LINE TO FILE
          proc_write_raw_curves (FHdata_raw_curve, rtime, u, u_next);
          proc_write_calc_tang_accn (FHdata_calc_tang_accn, N, curr_tang_accn,
                                     rtime, u, u_next);
          proc_write_calc_t_look (FHdata_calc_t_look, rtime, u, u_next,
                                  curr_tang_accn, curr_frate, csv_tang_accn,
                                  max_jerk);
          proc_write_calc_frate_limit (FHdata_calc_frate_limit, rtime, u,
                                       u_next, frate_command, t_interpol,
                                       curr_rho, curr_eps, lamda_N, curr_frate);

          proc_write_calc_intgr_error (FHdata_calc_intgr_error, rtime, u,
                                       u_next, sum_deltaS, sum_chordlength);
          proc_write_calc_u_next (FHdata_calc_u_next, rtime, u, u_next,
                                  t_interpol, curr_tang_accn, curr_frate,
                                  curr_frate_limit, frate_command);

          // DISPLAY TO SCREEN.
          printf ("%s ", CurveType);
          printf (
            " %5.3lf %12.9lf %12.9lf %6.3lf %.6e  %.6e  %.6e  %7.3lf %7.3lf "
            "%7.3lf  %.6e %10.6lf %10.6lf %10.6lf %10.6lf %12.9lf %10.6lf %10.6lf  "
            "Ended\n",
            rtime, u, u_next, t_interpol, curr_unext1stOrder,
            curr_unext2ndOrder, (curr_unext1stOrder - curr_unext2ndOrder),
            fxn_cpos_x (u), fxn_cpos_y (u), fxn_cpos_r (u), curr_eps, curr_rho,
            curr_tang_accn, curr_frate_limit, curr_frate, diff_fratelimit, curr_xfrate,
            curr_yfrate);

          // WRITE TO FILE 01 FOR DEBUGGING
          fprintf (FHdata_01, "%s ", CurveType);
          fprintf (FHdata_01,
                   " %5.3lf %12.9lf %12.9lf %6.3lf %.12e %.12e %.12e %7.3lf "
                   " %7.3lf %7.3lf %.12e %10.6lf %10.6lf %10.6lf %10.6lf %12.9lf "
                   " %10.6lf %10.6lf Ended.\n",
                   rtime, u, u_next, t_interpol, curr_unext1stOrder,
                   curr_unext2ndOrder,
                   (curr_unext1stOrder - curr_unext2ndOrder), fxn_cpos_x (u),
                   fxn_cpos_y (u), fxn_cpos_r (u), curr_eps, curr_rho,
                   curr_tang_accn, curr_frate,  curr_frate_limit, diff_fratelimit, curr_xfrate,
                   curr_yfrate);

          // WRITE TO GCODE FILE INSIDE FOLDER: ngcode
          // FILENAME: data_ngc_code.ngc
          proc_write_data_ngc_code (
            FHdata_ngc_code, rtime, u, u_next, t_interpol, curr_tang_accn,
            curr_frate, curr_frate_limit, ngc_depth, ngc_scale, frate_command);

        } // END IF LAST LINE

    } // END WHILE LOOP

  // ================================================================
  DTStamp ();
  printf ("Ended while loop \n");
  stop_timer (1);

  // CALCULATIONS FOR RUN REPORT STATISTICS
  already_belowtol_points = count_total_points - count_abovetol_points;
  pcnt_abovetol = (double)(100.0 * count_abovetol_points / N);
  pcnt_belowtol = (double)(100.0 * count_belowtol_points / N);
  pcnt_already_belowtol = (double)(100.0 * already_belowtol_points / N);
  pcnt_rising = (double)(100.0 * count_rising_s_curve_points / N);
  pcnt_lower = (double)(100.0 * count_frate_islower_fratelimit / N);
  pcnt_equal = (double)(100.0 * count_frate_isequal_fratelimit / N);
  pcnt_higher = (double)(100.0 * count_frate_ishigher_fratelimit / N);
  pcnt_falling = (double)(100.0 * count_falling_s_curve_points / N);
  sum_percentages
    = pcnt_rising + pcnt_lower + pcnt_equal + pcnt_higher + pcnt_falling;
  sum_eps_allranges
    = count_eps_aboverange + count_eps_withinrange + count_eps_belowrange;
  double pcnt_before
    = (double)(100.0 * count_before_step1_belowtol / sum_eps_allranges);
  double pcnt_step1
    = (double)(100.0 * num_of_step1_processing / sum_eps_allranges);

  double pcnt_above = (100.0 * cnt_eps_above_10E_6 / cnt_eps_total_points);
  double pcnt_10E_7
    = (100.0 * cnt_eps_betwn_10E_7_to_10E_6 / cnt_eps_total_points);
  double pcnt_10E_8
    = (100.0 * cnt_eps_betwn_10E_8_to_10E_7 / cnt_eps_total_points);
  double pcnt_10E_9
    = (100.0 * cnt_eps_betwn_10E_9_to_10E_8 / cnt_eps_total_points);
  double pcnt_10E_10
    = (100.0 * cnt_eps_betwn_10E_10_to_10E_9 / cnt_eps_total_points);
  double pcnt_below = (100.0 * cnt_eps_below_10E_10 / cnt_eps_total_points);
  double pcnt_total = (100.0 * cnt_eps_total_points / N);

  DTStamp ();
  printf ("Write run report statistics to screen and file. \n");
  // DTStamp ();
  fprintf (FHdata_02, "Write run report statistics to screen and file. \n");

  // =================================================================
  proc_write_01_epsilon_processing_error_statistics (FHdata_02, CurveType, N, 
       count_step1_ERROR_1, count_step1_ERROR_2,
       count_step2_ERROR_1, count_step2_ERROR_2, 
       count_step2_ERROR_3, count_step2_ERROR_4);

  // ==================================================================
  proc_write_02_epsilon_count_range_value_statistics (FHdata_02, CurveType, N,
        cnt_eps_above_10E_6, pcnt_above,
        cnt_eps_betwn_10E_7_to_10E_6, pcnt_10E_7,
        cnt_eps_betwn_10E_8_to_10E_7, pcnt_10E_8,
        cnt_eps_betwn_10E_9_to_10E_8, pcnt_10E_9,
        cnt_eps_betwn_10E_10_to_10E_9, pcnt_10E_10,
        cnt_eps_below_10E_10, pcnt_below,
        cnt_eps_total_points, pcnt_total );

  // =================================================================
  proc_write_03_interpolated_point_statistics (
    FHdata_02, CurveType, N, count_before_step1_belowtol, pcnt_before,
    num_of_step1_processing, pcnt_step1, num_of_step2_processing);

  // =================================================================
  proc_write_04_adjust_currfrate_to_currfrate_limit (
    FHdata_02, CurveType, N, count_rising_s_curve_points, pcnt_rising,
    count_frate_islower_fratelimit, pcnt_lower, count_frate_isequal_fratelimit,
    pcnt_equal, count_frate_ishigher_fratelimit, pcnt_higher,
    count_falling_s_curve_points, pcnt_falling, sum_percentages);

  // ==================================================================
  proc_write_05_write_epsilon_chord_error_statistics (
    FHdata_02, CurveType, N, min_eps, avg_eps, max_eps, sum_eps, line_mineps,
    u_mineps, x_mineps, y_mineps, line_maxeps, u_maxeps, x_maxeps, y_maxeps);

  // ==================================================================
  proc_write_06_write_radius_of_curvature_rho_statistics (
    FHdata_02, CurveType, N, min_rho, avg_rho, max_rho, sum_rho, line_minrho,
    u_minrho, x_minrho, y_minrho, line_maxrho, u_maxrho, x_maxrho, y_maxrho);

  // ==================================================================
  proc_write_07_write_tangential_acceleration_statistics (
    FHdata_02, CurveType, N, min_tangaccn, avg_tangaccn, max_tangaccn,
    sum_tangaccn, line_mintangaccn, u_mintangaccn, x_mintangaccn, y_mintangaccn,
    line_maxtangaccn, u_maxtangaccn, x_maxtangaccn, y_maxtangaccn);

  // ==================================================================
  proc_write_08_write_feedrate_statistics (
    FHdata_02, CurveType, N, min_frate, avg_frate, max_frate, sum_frate,
    line_minfrate, u_minfrate, x_minfrate, y_minfrate, line_maxfrate,
    u_maxfrate, x_maxfrate, y_maxfrate);

  // ==================================================================

  // ================================================================
  // WRITE ALL FOOTER FILES
  proc_writefooter_all_files ();

  // WRITE NGC codes footer
  proc_writefooter_data_ngc_code (FHdata_ngc_code);

  // CLOSE ALL FILES
  proc_close_all_files ();

  // =======================================================
  // printf ("BEGIN TESTING \n");
  // =========================================================

  
  // printf ("ENDED TESTING \n");
  // ==================================================================

  total_program_duration ();
  WRY_ending_salutation ();
  return (0);
}
// ==================================================================
// ALHAMDULILLAH 3 TIMES.
// ==================================================================
/*



*/
// ==================================================================
