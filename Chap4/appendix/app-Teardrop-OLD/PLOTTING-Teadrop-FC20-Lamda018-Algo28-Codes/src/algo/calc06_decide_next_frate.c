// FILE: calc06_decide_next_frate.c

#include <math.h>
#include <stdio.h>
#include <stdlib.h> // FOR exit(1)

FILE *FHdata_01;

#include "algo/calc06_decide_next_frate.h"
#include "common/c_random_int_dbl.h" // RANDOM NUMBERS

// REFERENCE Fig. 3. Algorithm for the feedrate lookahead module.
// ==================================================================
double fxn_get_root_N1(int N, double max_jerk, double t_interpol,
                     double curr_tang_accn, double curr_frate_limit,
                     double curr_frate)
// ==================================================================
{
    double root_N1;

    max_jerk = 200.0;
    t_interpol = 0.001;
    double tempA = (0.5)*(max_jerk)*(t_interpol)*(t_interpol);
    double tempB = tempA - (curr_tang_accn)*(t_interpol);
    double tempC = (curr_frate_limit - curr_frate);

    double dtmnant = (tempB * tempB) - (4.0) * (tempA) * (tempC);

    root_N1 = (-tempB + sqrt (dtmnant)) / (2.0) * (tempA);

    return (root_N1);
}
// ==================================================================
double fxn_get_root_N2(int N, double max_jerk, double t_interpol,
                     double curr_tang_accn, double curr_frate_limit,
                     double curr_frate)
// ==================================================================
{
    double root_N2;

    max_jerk = 200.0;
    t_interpol = 0.001;
    double tempA = (0.5)*(max_jerk)*(t_interpol)*(t_interpol);
    double tempB = tempA - (curr_tang_accn)*(t_interpol);
    double tempC = (curr_frate_limit - curr_frate);

    double dtmnant = (tempB * tempB) - (4.0) * (tempA) * (tempC);

    root_N2 = (-tempB - sqrt (dtmnant)) / (2.0) * (tempA);

    return (root_N2);
}
// ==================================================================
double fxn_get_determinant (int N, double max_jerk, double t_interpol,
                     double curr_tang_accn, double curr_frate_limit,
                     double curr_frate)
// ==================================================================
{
    double the_dtmnant;

    // QUADRATIC EQUATION TO SOLVE
    // The solutions of a quadratic equation ax2 + bx + c = 0 are given
    // by the quadratic formula x = [-b ± sqrt(b² - 4ac)] / (2a).

    // Equation (21) ==> tempA*(N*N) + tempB*N + tempC = 0

    max_jerk = 200.0;
    t_interpol = 0.001;
    double tempA = (0.5)*(max_jerk)*(t_interpol)*(t_interpol);
    double tempB = tempA - (curr_tang_accn)*(t_interpol);
    double tempC = (curr_frate_limit - curr_frate);

    // printf ("TMPABC: %15.9lf %15.9lf %15.9lf ", tempA, tempB, tempC);

    the_dtmnant = (tempB * tempB) - (4.0) * (tempA) * (tempC);

    // printf ("DTMNANT: %15.9lf ", the_dtmnant);


return (the_dtmnant);
}

// ==================================================================
int fxn_get_action_next_feedrate (int prev_frate_action, int N, double u,
                              double curr_frate_limit, double curr_frate,
                              double curr_tang_accn, double distS_look)
// ==================================================================
{
  int next_frate_action; // (-1 = decrease, 0 = no change, +1 = increase)

  // RUN EITHER CASE_A, CASE_B OR CASE_C
  if (curr_frate_limit > curr_frate) // CURR_FEEDRATE BELOW LIMIT
    {
      next_frate_action
        = proc_run_next_frate_case_A (prev_frate_action, N, u, curr_frate_limit,
                                      curr_frate, curr_tang_accn, distS_look);
    }
  else if (curr_frate_limit < curr_frate) // CURR_FEEDRATE ABOVE LIMIT
    {
      next_frate_action
        = proc_run_next_frate_case_B (prev_frate_action, N, u, curr_frate_limit,
                                      curr_frate, curr_tang_accn, distS_look);
    }
  else // CURR_FEEDRATE EQUALS FEEDRATE LIMIT (FEEDRATE REMAINS CONSTANT)
    {
      next_frate_action
        = proc_run_next_frate_case_C (prev_frate_action, N, u, curr_frate_limit,
                                      curr_frate, curr_tang_accn, distS_look);
    }

  return (next_frate_action);
}

// ==================================================================
int proc_run_next_frate_case_A (int prev_frate_action, int N, double u,
                            double curr_frate_limit, double curr_frate,
                            double curr_tang_accn, double distS_look)
// ==================================================================
{
  int next_frate_action_A;

  printf ("%6d INSIDE CASE A ", N);

 fprintf (FHdata_01, "%6d INSIDE CASE A ", N);

  if (curr_tang_accn > 0.0)
    {

      double max_jerk = 200.0;
      double t_interpol = 0.001;

      double dtmnant = fxn_get_determinant (N, max_jerk, t_interpol,
                     curr_tang_accn, curr_frate_limit,
                     curr_frate);

      printf ("DTM %12.9lf ", dtmnant);

    if (dtmnant > 0.0)
       {

           double root_N1 = fxn_get_root_N1 (N, max_jerk, t_interpol,
                        curr_tang_accn, curr_frate_limit,
                        curr_frate);

           double root_N2 = fxn_get_root_N2 (N, max_jerk, t_interpol,
                        curr_tang_accn, curr_frate_limit,
                        curr_frate);

           printf ("N1 %12.9lf ", root_N1);
           printf ("N2 %12.9lf ", root_N2);


        // TEMPORARY
        // where SN is the total distance that will be travelled
        // in N interpolation periods.
        // HA HA HA. MUST ACCUMULATE





        double SN1  = 0.5; // TEMPORARY
        double SN2  = 2.0; // TEMPORARY

        if (SN1 > distS_look)
           {
             // CASE A.1 (Feedrate up, Acceleration up)
             next_frate_action_A = +1;
           }
        else if (SN2 > distS_look)
           {
             // CASE A.2 (Feedrate down, Acceleration down)
             next_frate_action_A = -1;
           }
        else
           {
             // CASE A.1 (Feedrate up, Acceleration up)
             next_frate_action_A = +1;
           }

        }
    else
       {
         // CASE A.1 (Feedrate up, Acceleration up)
         next_frate_action_A = +1;
       }

    }
  else if (curr_tang_accn < 0.0)
    {
      // CASE A.3 (Feedrate up, Acceleration up)
      next_frate_action_A = +1;
    }
  else
    {
      // CASE A.4 (Feedrate up, Acceleration up)
      next_frate_action_A = +1;
    }


  // TESTING ONLY
  next_frate_action_A = random_integer(-1 , 2);

  // TEMPORARY
  // next_frate_action_A = +1;

    return (next_frate_action_A);
}

// ==================================================================
int proc_run_next_frate_case_B (int prev_frate_action, int N, double u,
                            double curr_frate_limit, double curr_frate,
                            double curr_tang_accn, double distS_look)
// ==================================================================
{
int next_frate_action_B;

     printf ("%6d INSIDE CASE B ", N);

     fprintf (FHdata_01, "%6d INSIDE CASE B ", N);

     // TESTING ONLY
     next_frate_action_B = random_integer (-1, 2);


    // TESTING HERE  TO FIX HERE <<<============================***********
    // next_frate_action_B = -1;


return (next_frate_action_B);
}

// ==================================================================
int proc_run_next_frate_case_C (int prev_frate_action, int N, double u,
                            double curr_frate_limit, double curr_frate,
                            double curr_tang_accn, double distS_look)
// ==================================================================
{
  int next_frate_action_C;

  printf ("%6d INSIDE CASE C ", N);

  fprintf (FHdata_01, "%6d INSIDE CASE C ", N);

  // TESTING ONLY USING RANDOM NUMBER
  // next_frate_action_C = random_integer(-1 , 2);

  // NO CHANGE IN FEEDRATE (MAINTAIN PREVIOUS FEEDRATE)
  next_frate_action_C = 0;

  return (next_frate_action_C);
}

// ==================================================================
// ALHAMDULILLAH 3 TIMES
// ==================================================================
