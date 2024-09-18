// FILE: calc03_feedrate_limit.c


#include <limits.h>   // perror()
#include <math.h>     // pow(), MUST COMPILE WITH LIBRARY -lm
#include <pthread.h>  // MUST COMPILE WITH LIBRARY -lpthread
#include <stdbool.h>  // boolean variables
#include <stdio.h>    // open(), printf(), fopen(), fprintf();
#include <stdlib.h>   // atoi(), system(), rand(),
#include <string.h>   // strtok(), strcpy()
#include <sys/time.h> // For local date-time with (microseconds)
#include <time.h>     // For high-res timer clock_gettime with (nanoseconds)
#include <unistd.h>   // getcwd()

// INCLUDED FOR THE FUNCTION DEFINITIONS
#include "curves/c_accelern.h"
#include "curves/c_position.h"
#include "curves/c_velocity.h"
#include "common/c_min_max_int_dbl_in_array.h"

#include "algo/calc03_feedrate_limit.h"

// #include "algo/write_calc_u_next.h"
// #include "algo/write_raw_curves.h"
// #include "algo/calc00_eps_rho.h"
// #include "algo/calc01_lookahead_length.h"
// #include "algo/calc02_tang_accn_limit.h"
// #include "algo/calc03_feedrate_limit.h"
#include "algo/calc04_integration_error.h"
// #include "algo/calc05_action_next_frate.h"
// #include "algo/calc06_decide_next_frate.h"

// GLOBAL VARIABLES
double eps_N;
double rho_N;
double lamda_N; // CONSTANT (0.0 : 1.0)
int rN;

double FRate_limit;
double FRate_limit_1;
double FRate_limit_2;
double FRate_limit_3;
double FRate_limit_4;

double Vel_alpha;
double Vel_beta;

// FROM TABLE 1
double xVee_max = 30.0;
double yVee_max = 30.0;
double xAcc_max = 30.0;
double yAcc_max = 30.0;

FILE *FHdata_calc_frate_limit;

// ==================================================================
double fxn_get_feedrate_limit (double rtime, double ru, double ru_next,  double FRate_command, double rT_interpol, double rho_N, double eps_N, double lamda_N)
// ==================================================================
{

// DEBUG 2 *************************
// printf ("%s ", CurveType );
// printf ("A9-TEA DEBUG 2 %5.3lf %12.9lf %12.9lf FRate_command = %10.6lf \n", rtime, ru, ru_next, FRate_command);


  eps_N = fxn_cpos_epsilon(ru, ru_next);
  rho_N = fxn_cpos_rho(ru);

  double arr_FRate_limit_net[4];
  arr_FRate_limit_net[0] = get_algo_feedrate_limit_1 (ru, FRate_command, rT_interpol, rho_N, eps_N, lamda_N);
  arr_FRate_limit_net[1] = get_algo_feedrate_limit_2 (ru, FRate_command, rT_interpol, rho_N, eps_N, lamda_N);
  arr_FRate_limit_net[2] = get_algo_feedrate_limit_3 (ru, ru_next, FRate_command, rT_interpol, rho_N, eps_N, lamda_N);
  arr_FRate_limit_net[3] = get_algo_feedrate_limit_4 (ru, FRate_command, rT_interpol, rho_N, eps_N, lamda_N);

  FRate_limit_1 = arr_FRate_limit_net[0];
  FRate_limit_2 = arr_FRate_limit_net[1];
  FRate_limit_3 = arr_FRate_limit_net[2];
  FRate_limit_4 = arr_FRate_limit_net[3];

  // MINIMUM OF 4 ELEMENTS
  FRate_limit = fxn_get_min_element_arraydoubles (arr_FRate_limit_net, 4);

// DEBUG 3 *************************
// printf ("%s ", CurveType );
// printf ("A9-TEA DEBUG 3 %5.3lf %12.9lf %12.9lf FRate_command = %10.6lf FRate_limit = %15.9lf \n", rtime, ru, ru_next, FRate_command, FRate_limit);

  // THE MINIMUM LIMIT RETURNED
  return (FRate_limit);
}

// ==================================================================
double get_algo_feedrate_limit_1 ( double ru, double FRate_command, double rT_interpol, double rho_N, double eps_N, double lamda_N)
// ==================================================================
{

// PROBLEM IS HERE   ********* ALTERNATING ************* FRate_command WHY?
// printf ("A9-TEA DEBUG 4.1 %12.9lf FRate_command = %10.6lf FRate_limit_1 = %15.9lf \n", ru, FRate_command, FRate_limit_1);


FRate_limit_1 = FRate_command;

// DEBUG PRINT
 // printf("(here-3) -FRate_command = %6.e \n", FRate_command);
 //  printf("(here-4) -FRate_limit_1 = %6.e \n", FRate_limit_1);



// DEBUG 4 *************************
// printf ("%s ", CurveType );
// printf ("A9-TEA DEBUG 4.2 %12.9lf FRate_command = %10.6lf FRate_limit_1 = %15.9lf \n", ru, FRate_command, FRate_limit_1);

  return (FRate_limit_1);

  // return (30.000);
}

// ==================================================================
double get_algo_feedrate_limit_2 (double ru, double FRate_command, double rT_interpol, double rho_N, double eps_N, double lamda_N)
// ==================================================================
{

  // printf ("A9-TEA DEBUG 5.1 %12.9lf FRate_command = %10.6lf FRate_Limit_2 = %15.9lf \n", ru, FRate_command, FRate_limit_2);

  Vel_alpha = fxn_cvel_x(ru) /fxn_cvel_r(ru);
  Vel_beta  = fxn_cvel_y(ru) /fxn_cvel_r(ru);

  double temp1 = xVee_max / fabs(Vel_alpha);
  double temp2 = yVee_max / fabs(Vel_beta);

  double arr_FRate_limit_2[2];
  arr_FRate_limit_2[0] = temp1;
  arr_FRate_limit_2[1] = temp2;

  // MINIMUM OF 2 ELEMENTS
  FRate_limit_2 = fxn_get_min_element_arraydoubles (arr_FRate_limit_2, 2);


// DEBUG 5 *************************
// printf ("%s ", CurveType );
// printf ("A9-TEA DEBUG 5.2 %12.9lf FRate_command = %10.6lf FRate_Limit_2 = %15.9lf \n", ru, FRate_command, FRate_limit_2);


  return (FRate_limit_2);
}

// ==================================================================
double get_algo_feedrate_limit_3 ( double ru, double ru_next, double FRate_command, double rT_interpol, double rho_N, double eps_N, double lamda_N)
// ==================================================================
{
  // DEBUG 6 *************************
  // printf ("A9-TEA DEBUG 6.1 %12.9lf FRate_command = %10.6lf FRate_Limit_3 = %15.9lf \n", ru, FRate_command, FRate_limit_3);

  double eps = fxn_cpos_epsilon (ru, ru_next);
  double rho = fxn_cpos_rho(ru);

  // USING HALF CHORD-LENGTH
  double temp1 = fabs ( sqrt((2.0*rho*eps) - (eps*eps)) );
  double temp2 = (2.0 / rT_interpol) * temp1;

  FRate_limit_3 = temp2;

// DEBUG 6 *************************
// printf ("%s ", CurveType );
// printf ("A9-TEA DEBUG 6.2 %12.9lf FRate_command = %10.6lf FRate_Limit_3 = %15.9lf \n", ru, FRate_command, FRate_limit_3);


  return (FRate_limit_3);
}

// ==================================================================
double get_algo_feedrate_limit_4  (double ru, double FRate_command, double rT_interpol, double rho_N, double eps_N, double lamda_N)
// ==================================================================
{

  // DEBUG 7 *************************
  // printf ("%s ", CurveType );
  // printf ("A9-TEA DEBUG 7.1 %12.9lf FRate_command = %10.6lf FRate_Limit_4 = %15.9lf \n", ru, FRate_command, FRate_limit_4);


  Vel_alpha = fxn_cvel_x(ru) /fxn_cvel_r(ru);
  Vel_beta  = fxn_cvel_y(ru) /fxn_cvel_r(ru);
  rho_N = fxn_cpos_rho(ru);

  double theC = sqrt (lamda_N * rho_N * xAcc_max / fabs (Vel_beta));  // GLOBAL xAcc_max
  double theD = sqrt (lamda_N * rho_N * yAcc_max / fabs (Vel_alpha)); // GLOBAL yAcc_max

  double arr_FRate_limit_4[2];
  arr_FRate_limit_4[0] = theC;
  arr_FRate_limit_4[1] = theD;

  // MINIMUM OF 2 ELEMENTS
  FRate_limit_4 = fxn_get_min_element_arraydoubles (arr_FRate_limit_4, 2);

// DEBUG 7 *************************
// printf ("%s ", CurveType );
// printf ("A9-TEA DEBUG 7.2 %12.9lf FRate_command = %10.6lf FRate_Limit_4 = %15.9lf \n", ru, FRate_command, FRate_limit_4);

  return (FRate_limit_4);
}

// ==================================================================
void proc_writeheader_data_calc_frate_limit (FILE* FHdata_calc_frate_limit)
// ==================================================================
{

  fprintf (FHdata_calc_frate_limit,
           "# DTStamp_FHdata_calc_frate_limit (feedrate limit) %s \n",
           get_datetime_stamp ());

  fprintf (FHdata_calc_frate_limit,
           "# rtime[1], u[2], u_next[3], FRate_limit_1[4], FRate_limit_2[5], "
           "FRate_limit_3[6], FRate_limit_4[7], FRate_limit[8], curr_frate[9], "
           "BEFORE_diff_frate[[10], eps_N[11], rho_N[12] \n");

}

// ==================================================================
void proc_writefooter_data_calc_frate_limit (FILE* FHdata_calc_frate_limit)
// ==================================================================
{

   fprintf (FHdata_calc_frate_limit,
           "# rtime[1], u[2], u_next[3], FRate_limit_1[4], FRate_limit_2[5], "
           "FRate_limit_3[6], FRate_limit_4[7], FRate_limit[8], curr_frate[9], "
           "BEFORE_diff_frate[[10], eps_N[11], rho_N[12] \n");

   fprintf (FHdata_calc_frate_limit,
            "# DTStamp_FHdata_calc_frate_limit (feedrate limit) %s \n",
            get_datetime_stamp ());

}


// ==================================================================
void proc_write_calc_frate_limit (FILE *FHdata_calc_frate_limit, double rtime,
                             double ru, double ru_next, double FRate_command,
                             double rT_interpol, double rho_N, double eps_N,
                             double lamda_N,
                             double curr_frate)
// ==================================================================
{

  eps_N = fxn_cpos_epsilon(ru, ru_next);
  rho_N = fxn_cpos_rho(ru);

  double arr_FRate_limit_net[4];
  arr_FRate_limit_net[0] = get_algo_feedrate_limit_1 (ru, FRate_command, rT_interpol, rho_N, eps_N, lamda_N);
  arr_FRate_limit_net[1] = get_algo_feedrate_limit_2 (ru, FRate_command, rT_interpol, rho_N, eps_N, lamda_N);
  arr_FRate_limit_net[2] = get_algo_feedrate_limit_3 (ru, ru_next, FRate_command, rT_interpol, rho_N, eps_N, lamda_N);
  arr_FRate_limit_net[3] = get_algo_feedrate_limit_4 (ru, FRate_command, rT_interpol, rho_N, eps_N, lamda_N);

  FRate_limit_1 = arr_FRate_limit_net[0];
  FRate_limit_2 = arr_FRate_limit_net[1];
  FRate_limit_3 = arr_FRate_limit_net[2];
  FRate_limit_4 = arr_FRate_limit_net[3];

  // MINIMUM OF 4 ELEMENTS
  FRate_limit = fxn_get_min_element_arraydoubles (arr_FRate_limit_net, 4);

  // DEBUG PRINT
  // printf("(here-1) -FRate_command = %6.e \n", FRate_command);
  // printf("(here-2) -FRate_limit_1 = %6.e \n", FRate_limit_1);

  double BEFORE_diff_frate = (FRate_limit - curr_frate);

  fprintf (FHdata_calc_frate_limit,
                "%12.6lf %12.9lf %12.9lf %15.9lf %15.9lf %15.9lf %15.9lf %15.9lf %15.9lf %15.9lf %18.15lf %15.6lf \n",
                rtime, ru, ru_next, FRate_limit_1, FRate_limit_2, FRate_limit_3, FRate_limit_4, FRate_limit, curr_frate, BEFORE_diff_frate, eps_N, rho_N);

}

// ==================================================================
// ALHAMDULILLAH 3 TIMES WRY
// ==================================================================
