// FILE: calc05_action_next_frate.c

#include <stdio.h>
#include <math.h>     // FOR fabs()
#include <stdlib.h>   // FOR exit(1)

#include "algo/calc05_action_next_frate.h"

// ==================================================================
double fxn_get_frate_when_below_limit (double u, double u_next,
                                double curr_frate_limit, double curr_frate,
                                double max_jerk, double t_interpol)
// ==================================================================
{
  double next_frate;
  int countup = 0;

  while (curr_frate_limit > curr_frate) // increase frate
  {
       curr_frate = curr_frate + (max_jerk) * (t_interpol);
       countup = countup + 1;
  }

  next_frate = curr_frate;

  return (next_frate);
}

// ==================================================================
double fxn_get_frate_when_above_limit (double u, double u_next,
                                double curr_frate_limit, double curr_frate,
                                double max_jerk, double t_interpol)
// ==================================================================
{
  double next_frate;
  int countdown = 0;

  while (curr_frate_limit > curr_frate) // decrease frate
  {
       curr_frate = curr_frate - (max_jerk) * (t_interpol);
       countdown = countdown + 1;
  }

  next_frate = curr_frate;

  return (next_frate);
}


// ==================================================================
double fxn_get_frate_when_equal_limit (double u, double u_next,
                                double curr_frate_limit, double curr_frate,
                                double max_jerk, double t_interpol)
// ==================================================================
{
  double next_frate;

  next_frate = curr_frate;

  return (next_frate);
}



// ==================================================================
double fxn_get_value_next_tang_accn (double rtime, double u, double u_next,
                              double curr_tang_accn, int prev_frate_action,
                              int next_frate_action, double max_jerk,
                              double t_intpl)

// ==================================================================
{
  double next_tang_accn;

        // CASE 1: CONTINUE INCREASE ACCN AND INCREASE FEEDRARE
        // ====================================
        if ((prev_frate_action == +1)
         && (next_frate_action == +1))
        {
          next_tang_accn = curr_tang_accn + (max_jerk * t_intpl);

        // CASE 2: SWITCH ACCN TO DECELERATION AND DECREASE FEEDRATE
        // ====================================
        } else if ((prev_frate_action == +1)
                && (next_frate_action == -1))
        {
          next_tang_accn = - (max_jerk * t_intpl);

        // CASE 3: SWITCH INCREASE TO CONSTANT FEEDRATE
        // ====================================
        } else if ((prev_frate_action == +1)
                && (next_frate_action == 0))
        {
          next_tang_accn = 0.0;

        // CAEE 4: SWITCH DECELERATION TO ACCN AND INCREASE FEEDRATE
        // ====================================
        } else if ((prev_frate_action == -1)
                && (next_frate_action == +1))
        {
          next_tang_accn = + (max_jerk * t_intpl);

        // CASE 5: CONTINUE DECREASE ACCN AND DECREASE FEEDRATE
        // ====================================
        } else if ((prev_frate_action == -1)
                && (next_frate_action == -1))
        {
          next_tang_accn = curr_tang_accn - (max_jerk * t_intpl);

        // CASE 6: SWITCH DECREASE TO CONSTANT FEEDRATE
        // ====================================
        } else if ((prev_frate_action == -1)
               &&  (next_frate_action == 0))
        {
          next_tang_accn = 0.0;

        // CASE 7: SWITCH CONSTANT TO INCREASE FEEDRATE
        // ====================================
        } else if ((prev_frate_action == 0)
               &&  (next_frate_action == +1))
        {
          next_tang_accn = curr_tang_accn + (max_jerk * t_intpl);

        // CASE 8: SWITCH CONSTANT TO DECREASE FEEDRATE
        // ===================================
        } else if ((prev_frate_action == 0)
               &&  (next_frate_action == -1))
        {
          next_tang_accn = curr_tang_accn - (max_jerk * t_intpl);

        // CASE 9: MAINTAIN CONSTANT FEEDRATE
        // ===================================
        } else if ((prev_frate_action == 0)
               &&  (next_frate_action == 0))
        {
          next_tang_accn = 0.0;

        }
        // ===================================
        else
        {
          perror ("ERROR in frate_action\n");
        }

  return (next_tang_accn);
}

// ==================================================================
double fxn_get_value_next_frate (double rtime, double u, double u_next,
                          double next_tang_accn, double curr_frate,
                          int prev_frate_action, int next_frate_action,
                          double max_jerk, double t_intpl)

// ==================================================================
{

     double next_frate;

        // CASE 1: CONTINUE INCREASE FEEDRARE
        // ========================================
        if ((prev_frate_action == +1)
         && (next_frate_action == +1))
        {
          next_frate = curr_frate + fabs(next_tang_accn) * (t_intpl);

        // CASE 2: SWITCH INCREASE FEEDRATE TO DECREASE FEEDRATE
        // ========================================
        } else if ((prev_frate_action == +1)
                && (next_frate_action == -1))
        {
          next_frate = curr_frate - fabs(next_tang_accn) * (t_intpl);

        // CASE 3: SWITCH INCREASE FEEDRATE TO CONSTANT FEEDRATE
        // ====================================
        } else if ((prev_frate_action == +1)
                && (next_frate_action == 0))
        {
          next_frate = curr_frate;

        // CAEE 4: SWITCH DECREASE FEEDRATE TO INCREASE FEEDRATE
        // ====================================
        } else if ((prev_frate_action == -1)
                && (next_frate_action == +1))
        {
          next_frate = curr_frate + fabs(next_tang_accn) * (t_intpl);

        // CASE 5: CONTINUE DECREASE FEEDRATE
        // ====================================
        } else if ((prev_frate_action == -1)
                && (next_frate_action == -1))
        {
          next_frate = curr_frate - fabs((next_tang_accn)) * (t_intpl);

        // CASE 6: SWITCH DECREASE FEEDRATE TO CONSTANT FEEDRATE
        // ====================================
        } else if ((prev_frate_action == -1)
               &&  (next_frate_action == 0))
        {
          next_frate = curr_frate;

        // CASE 7: SWITCH CONSTANT FEEDRATE TO INCREASE FEEDRATE
        // ====================================
        } else if ((prev_frate_action == 0)
               &&  (next_frate_action == +1))
        {
          next_frate = curr_frate + fabs((next_tang_accn)) * (t_intpl);

        // CASE 8: SWITCH CONSTANT FEEDRATE TO DECREASE FEEDRATE
        // ===================================
        } else if ((prev_frate_action == 0)
               &&  (next_frate_action == -1))
        {
          next_frate = curr_frate - fabs((next_tang_accn)) * (t_intpl);

        // CASE 9: CONTINUE CONSTANT FEEDRATE
        // ====================================
        } else if ((prev_frate_action == 0)
               &&  (next_frate_action == 0))
        {
          next_frate = curr_frate;

        }
        else
        {
          perror ("ERROR in frate_action \n");
          exit(1);
        }

  return (next_frate);
}

// ==================================================================
// ALHAMDULILLAH 3 TIMES.
// ==================================================================

