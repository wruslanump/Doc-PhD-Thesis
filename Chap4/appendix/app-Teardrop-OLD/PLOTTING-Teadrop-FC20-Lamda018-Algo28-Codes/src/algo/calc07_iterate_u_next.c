// FILE: calc07_iterate_u_next.c

#include <stdio.h>

// INCLUDED FOR THE FUNCTION DEFINITIONS
#include "curves/c_accelern.h"
#include "curves/c_position.h"
#include "curves/c_velocity.h"

#include "algo/calc07_iterate_u_next.h"

double chorderror_tolerance;

FILE *FHdata_01;

double incr_ru_next;
double decr_ru_next;
double ru_next_ratio;

double ru_next_r1st;
double ru_next_r2nd;

// ==================================================================
void proc_writeheader_data_calc_u_next (FILE *FHdata_calc_u_next)
// ==================================================================
{

  fprintf (FHdata_calc_u_next, "# DTStamp_FHdata_calc_u_next %s \n",
           get_datetime_stamp ());

  fprintf (FHdata_calc_u_next,
           "#rtime[1] u[2] u_next[3] t_interpol[4] first_order[5] "
           "second_order[6] diff[7] pos_x[8] pos_y[9]pos_r[10] eps[11]rho[12] "
           "curr_tang_accn[13] curr_frate[14] frate_limit[15] "
           "x_frate[16] y_frate[17] frate_command[18], diff_frate[19]\n");
}

// ==================================================================
void proc_writefooter_data_calc_u_next (FILE *FHdata_calc_u_next)
// ==================================================================
{

  fprintf (FHdata_calc_u_next,
           "#rtime[1] u[2] u_next[3] t_interpol[4] first_order[5] "
           "second_order[6] diff[7] pos_x[8] pos_y[9]pos_r[10] eps[11]rho[12] "
           "curr_tang_accn[13] curr_frate[14] frate_limit[15] "
           "x_frate[16] y_frate[17] frate_command[18], diff_frate[19]\n");


  fprintf (FHdata_calc_u_next, "# DTStamp_FHdata_calc_u_next %s \n",
           get_datetime_stamp ());
}


// ==================================================================
void proc_write_calc_u_next (FILE *FHdata_calc_u_next, double rtime, double u,
                        double u_next, double t_interpol, double curr_tang_accn,
                        double curr_frate, double frate_limit, double frate_command)

// ==================================================================
{

  double first_order  = get_u_next_firstorder_runtime (rtime, u, u_next, t_interpol, frate_command);
  double second_order = get_u_next_secondorder_runtime (rtime, u, u_next, t_interpol, frate_command);
  double diff = (first_order - second_order);

  double cpos_x = fxn_cpos_x (u);
  double cpos_y = fxn_cpos_y (u);
  double cpos_r = fxn_cpos_r (u);

  double eps = fxn_cpos_epsilon (u, u_next);
  double rho = fxn_cpos_rho (u);

  // AVOID JITTER AT MAXIMUM FEEDRATE COMMAND
  if (curr_frate > frate_command)
    {
      curr_frate = frate_command;
    }
  // AVOID JITTER AT FEEDRATE LIMIT
  if (curr_frate > frate_limit)
    {
      curr_frate = frate_limit;
    }

  // USE CURR_FRATE (GOOD) FOR X AND Y FEEDRATE COMPONENTS
  double x_frate = curr_frate * (fxn_cvel_x (u) / fxn_cvel_r (u));
  double y_frate = curr_frate * (fxn_cvel_y (u) / fxn_cvel_r (u));
  double AFTER_diff_frate = (frate_limit - curr_frate);

  fprintf (FHdata_calc_u_next,
             "%5.3lf %12.9lf %12.9lf %6.3lf %.6e %.6e %.6e %.6e %.6e "
             "%.6e %.6e %.6e %.6e %.12e %.6e %.6e %.6e %.6e %.9e \n",
             rtime, u, u_next, t_interpol, first_order, second_order, diff, cpos_x,
             cpos_y, cpos_r, eps, rho, curr_tang_accn, curr_frate, frate_limit, x_frate, y_frate, frate_command, AFTER_diff_frate);
}


// ==================================================================
double get_vee_runtime(double ru, double ru_next, double rt_interpol) {
// ==================================================================

   double temp1 = pow (fxn_cpos_rho (ru), 2);
   double temp2 = (fxn_cpos_rho(ru) - fxn_cpos_epsilon(ru, ru_next));
   double temp3 = pow (temp2, 2);
   double temp4 = (fabs(sqrt(temp1 - temp3)));
   double the_rvee = 2*(temp4)/(rt_interpol);

   return (the_rvee);
}
// ==================================================================
double get_u_next_firstorder_runtime(double rtime, double ru, double ru_next, double rt_interpol, double frate_command) {
// ==================================================================

    double temp1 = frate_command;
    double temp2 = temp1 / fxn_cvel_r(ru);
    double ru_next1st = (rt_interpol)*(temp2);

    return (ru_next1st);
}

// ==================================================================
double fxn_increase_ru_next_closestto_epsilonlimit (double ru, double ru_next2nd) {
// ==================================================================
double the_incr_ru_next;

double ru_next = ru_next2nd;
double ru_nextstart = ru_next2nd;
double ru_nextend = 0.000000000000;
double eps_ru     = 0.000000000000;
int jump_delta    = 0;

double error_tolerance = 1.0E-6;

while (fxn_cpos_epsilon(ru, ru_next) <= error_tolerance ){ // LESS THAN

    ru_next = ru_next + incr_ru_next;  // PLUS INCREASE (DELTA IS GLOBAL)
    eps_ru  = fxn_cpos_epsilon(ru, ru_next);
    jump_delta = jump_delta + 1;
}

ru_nextend = (ru_next - incr_ru_next); // ONE STEP BEFORE EXITING LOOP
ru_next_ratio = (ru_nextend / ru_nextstart);    // GLOBAL unext_ratio

        the_incr_ru_next = ru_nextend;
return (the_incr_ru_next);
}

// ==================================================================
double fxn_decrease_ru_next_closestto_epsilonlimit (double ru, double ru_next2nd) {
// ==================================================================
double the_decr_ru_next;

double ru_next = ru_next2nd;
double ru_nextstart = ru_next2nd;
double ru_nextend = 0.000000000000;
double eps_ru     = 0.000000000000;
int jump_delta    = 0;

double error_tolerance = 1.0E-6;

while (fxn_cpos_epsilon(ru, ru_next) > error_tolerance) { // GREATER THAN

    ru_next = ru_next - decr_ru_next;  // MINUS DECREASE (DELTA IS GLOBAL)
    eps_ru  = fxn_cpos_epsilon(ru, ru_next);
    jump_delta = jump_delta + 1;
}

ru_nextend = (ru_next); // ONE STEP BEFORE EXITING LOOP
ru_next_ratio = (ru_nextend / ru_nextstart);    // GLOBAL u_step

        the_decr_ru_next = ru_nextend;
return (the_decr_ru_next);
}

// ==================================================================
double get_u_next_secondorder_runtime(double rtime, double ru, double ru_next, double rt_interpol, double frate_command) {
// ==================================================================

    double temp1 = (rt_interpol)*frate_command;
    double temp2 = pow (temp1, 2) / 2;
    double temp3 = fxn_cvel_r (ru);
    double temp4 = fxn_cacc_r (ru);
    double temp5 = pow (temp3, 3);


    ru_next_r1st = get_u_next_firstorder_runtime (rtime, ru, ru_next, rt_interpol, frate_command);
    ru_next_r2nd = ru_next_r1st - (temp2)*(temp4)/(temp5);

    return (ru_next_r2nd);
}

// ==================================================================
// CALCULATION FOR step1_unext IN MAIN
// ==================================================================
// GO TO REDUCE EPS TO BELOW TOLERANCE
double fxn_get_u_next_with_constrained_eps (double u, double u_next,
                double uppertol_bound,
                int *count_step1_ERROR_1,
                int *count_step1_ERROR_2)
// ==================================================================
{

   double inp_u_next = u_next;
   double out_u_next;
   double theta = 0.999999;

   double inp_eps = fxn_cpos_epsilon(u, u_next);

   while (inp_eps > uppertol_bound)
   {

    // REDUCE u_next
    u_next  = u_next*theta;
    inp_eps = fxn_cpos_epsilon(u, u_next);   // IMPT CALL TO EPSILON

    theta = theta - 0.000001;

   }

   out_u_next = u_next;

   // CHECK NO 1
   if (out_u_next > inp_u_next)
   {
      // ERROR out_u_next SHOULD BE SMALLER THAN inp_u_next because REDUCE
      printf ("\nERROR: STEP 1, ERROR_1: inp_u_next = %12.9lf inp_u_out = %12.9lf \n", inp_u_next, out_u_next);
      *count_step1_ERROR_1 += 1;

   }

   // CHECK NO 2
   double check_eps = fxn_cpos_epsilon(u, out_u_next);
   if (check_eps > uppertol_bound)
   {
      // ERROR IN CONSTRAINING eps BELOW error_tolerance.
      printf ("\nERROR: STEP 1, ERROR_2: check_eps = %12.9lf uppertol_bound %12.9lf \n", check_eps, uppertol_bound);
      *count_step1_ERROR_2 += 1;

   }

// NOTICE RETURN IS NOT eps BUT u_next HAHAHA.
return (out_u_next);

}

// CALCULATION FOR step2_unext IN MAIN
// ==================================================================
double fxn_get_u_next_with_eps_both_bounded (
          double u, double u_next, double uppertol_bound, double lowertol_bound,
          int *count_step2_ERROR_1, int *count_step2_ERROR_2,
          int *count_step2_ERROR_3, int *count_step2_ERROR_4 )
// ==================================================================
{
  double step2_unext = u_next;   // SETTING FOR TEST ONLY
  double inp_u_next  = u_next;
  double out_u_next;
  double theta = 1.0000000;

  // GET INITIAL EPSILON
  double inp_eps = fxn_cpos_epsilon (u, u_next);

  // RUN A WHILE LOOP ALGORITHM
  while  (inp_eps < lowertol_bound)
   {

    // INCREASE u_next INCREMENTALLY
    u_next = u_next * theta;

    // IMPT CALL TO EPSILON
    inp_eps = fxn_cpos_epsilon(u, u_next);

    // INCREMENTAL VALUE (1E-7)
    // MUST BE SMALLER THAN UPPER BOUND TOLERANCE
    theta = theta + 0.0000001;

   }

  // LOOP EXITS WHEN CONDITION (inp_eps < lowertol_bound) FAILS.
  // MEANING inp_eps > lowertol_bound. This is what we want.
  // IMPT: (u_next IS THE VALUE AT EXIt OF while (...) loop
  out_u_next = u_next;


   // CHECK THAT EPS IS BELOW UPPERTOL_BOUND
   double check_eps = fxn_cpos_epsilon(u, out_u_next);
   if (check_eps > uppertol_bound)
     {
      printf ("\nERROR: STEP 2, ERROR 1: FAILED UPPER BOUND : check_eps = %12.9lf out_u_next = %12.9lf \n", check_eps, out_u_next);
      *count_step2_ERROR_1 += 1;

      }

   // CHECK THAT EPS IS ABOVE LOWERTOL_BOUND
   if (check_eps < lowertol_bound)
     {
      printf ("\nERROR: STEP 2, ERROR 2: FAILED LOWER BOUND : check_eps = %12.9lf out_u_next = %12.9lf \n", check_eps, out_u_next);
      *count_step2_ERROR_2 += 1;


      }

   // CHECK THAT BOTH CONDITIONS ARE TRUE SIMULTANEOUSLY
   if ( (check_eps < uppertol_bound) && (check_eps > lowertol_bound) )
     {
       // Important theory.
       // If check_eps is good, so the corresponding out_u_next is also good.
       // Note we ASSIGN out_u_next AS OUTPUT and NOT the corresponding check_eps.
       step2_unext = out_u_next;

     } else  {
          printf ("\nERROR: STEP 2, ERROR 3: FAILED BOTH UPPER AND LOWER BOUNDS.\n");
          *count_step2_ERROR_3 += 1;
     }

  // NOTE: *count_step2_ERROR_4 RESERVED FOR FUTURE USE

  // RETURN ONLY WHEN PASS BOTH BOUNDS
  return (step2_unext);

}

// ==================================================================
// ALHAMDULILLAH 3 TIMES WRY
// ==================================================================
