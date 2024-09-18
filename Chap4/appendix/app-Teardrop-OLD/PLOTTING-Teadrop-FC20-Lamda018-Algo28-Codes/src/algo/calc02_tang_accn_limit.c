// FILE: calc02_tang_accn_limit.c

#include <stdio.h>

// INCLUDED FOR THE FUNCTION DEFINITIONS
#include "curves/c_accelern.h"
#include "curves/c_position.h"
#include "curves/c_velocity.h"
#include "common/c_min_max_int_dbl_in_array.h"

#include "algo/calc02_tang_accn_limit.h"

// ==================================================================
double fxn_get_alpha (double u)
// ==================================================================
{
  double alpha;

  // USING VELOCITY FUNCTION  DEFINED IN EQUATION (8)
  // double temp1 = fxn_cvel_x (u);
  // double temp2 = fxn_cvel_r (u);

  // USING ACCELERATION FUNCTION
  double temp1 = fxn_cacc_x (u);
  double temp2 = fxn_cacc_r (u);

  alpha = (temp1/temp2);

  return (alpha);
}

// ==================================================================
double fxn_get_beta (double u)
// ==================================================================
{
  double beta;

  // USING VELOCITY FUNCTION DEFINED IN EQUATION (8)
  // double temp1 = fxn_cvel_y (u);
  // double temp2 = fxn_cvel_r (u);

  // USING ACCELERATION FUNCTION
  double temp1 = fxn_cacc_y (u);
  double temp2 = fxn_cacc_r (u);

  beta = (temp1/temp2);

  return (beta);
}

// ==================================================================
/*
FROM EQUATION (10)
accn_x = (alpha)*(accn_t) - (beta)*(accn_n);
accn_y = (beta)*(accn_t) + (alpha)*(accn_n);

accn_t = ((alpha)*(accn_x) + (beta)*(accn_y))/(alpha*alpha + beta*beta);
acct_n = ((alpha)*(accn_y) - (beta)*(accn_x))/(alpha*alpha + beta*beta);

FROM EQUATION (15)
CHECK01 AND CHECK02 BELOW
accn_t = (1.0/alpha)*(accn_x) + (beta/alpha)*(accn_n);
accn_t = (1.0/beta )*(accn_y) - (alpha/beta)*(accn_n);

*/

// TANGENTIAL ACCELERATION
// ==================================================================
double fxn_get_curr_tang_accn (double u)
// =================================================================
{

double curr_tang_accn;

// DEFINED USING EQUATION (8)
double alpha = fxn_get_alpha (u);
double beta  = fxn_get_beta (u);

// USING ACCELERATION FUNCTION
// EFROM QUATION (15)
double cacc_x = fxn_cacc_x (u);    // ax IN EQUATION 15
double cacc_y = fxn_cacc_y (u);    // ay IN EQUATION 15

double temp1 = ((alpha)*(cacc_x) + (beta)*(cacc_y));
double temp2 = (alpha*alpha + beta*beta);
curr_tang_accn = (temp1/temp2);

return(curr_tang_accn);
}

// NORMAL ACCELERATION
// ==================================================================
double fxn_get_curr_norm_accn (double u)
// ==================================================================
{

double curr_norm_accn;

// USING VELOCITY FUNCTION
double alpha = fxn_get_alpha (u);
double beta = fxn_get_beta (u);

// DEFINED USING EQUATION (15)
double cacc_x = fxn_cacc_x (u);
double cacc_y = fxn_cacc_y (u);

double temp1 = ((alpha)*(cacc_y) - (beta)*(cacc_x));
double temp2 = (alpha * alpha + beta * beta);

curr_norm_accn = (temp1/temp2);

return(curr_norm_accn);
}


// ==================================================================
double fxn_get_max_tang_accn (double u)
// ==================================================================
{
  double max_tang_accn;
  double alpha = fxn_get_alpha (u);
  double beta  = fxn_get_beta  (u);
  double curr_accn_norm = fxn_get_curr_norm_accn (u);
  double ACCN_MAX_X = 30.0;
  double ACCN_MAX_Y = 30.0;

  // EQUATION (16)
  double temp1 = (ACCN_MAX_X/fabs(alpha)) + (beta/alpha)*curr_accn_norm;
  double temp2 = (ACCN_MAX_Y/fabs(beta))  - (alpha/beta)*curr_accn_norm;

  double arr_max_tang_accn[2];
  arr_max_tang_accn[0] = temp1;
  arr_max_tang_accn[1] = temp2;

  // FOR MAXIMUM, GET THE MINIMUM OF temp1 AND temp2
  max_tang_accn = fxn_get_min_element_arraydoubles (arr_max_tang_accn, 2);

  // DEBUG PRINT
  // printf ("A temp1 = %12.6lf temp2 = %12.6lf max_tang_accn = %12.6lf \n",
  //        temp1, temp2, max_tang_accn);

  return (max_tang_accn);
}

// ==================================================================
double fxn_get_min_tang_accn (double u)
// ==================================================================
{

  double min_tang_accn;
  double alpha = fxn_get_alpha (u);
  double beta  = fxn_get_beta  (u);
  double curr_accn_norm = fxn_get_curr_norm_accn (u);
  double ACCN_MAX_X = 30.0;
  double ACCN_MAX_Y = 30.0;

  // EQUATION (17)
  double temp1 = -(ACCN_MAX_X/fabs(alpha)) + (beta/alpha)*curr_accn_norm;
  double temp2 = -(ACCN_MAX_Y/fabs(beta))  - (alpha/beta)*curr_accn_norm;

  double arr_min_tang_accn[2];
  arr_min_tang_accn[0] = temp1;
  arr_min_tang_accn[1] = temp2;

  // FOR MINIMUM, GET THE MAXIMUM OF temp1 AND temp2
  min_tang_accn = fxn_get_max_element_arraydoubles(arr_min_tang_accn, 2);

  // DEBUG PRINT
  // printf ("B temp1 = %12.6lf temp2 = %12.6lf min_tang_accn = %12.6lf \n", temp1,
  //        temp2, min_tang_accn);

  return (min_tang_accn);

}

// ==================================================================
void proc_writeheader_data_calc_tang_accn (FILE* FHdata_calc_tang_accn)
// ==================================================================
{

  fprintf (FHdata_calc_tang_accn,
           "# DTStamp_FHdata_calc_accn_t (tangential acceleration) %s \n",
           get_datetime_stamp ());

  fprintf (FHdata_calc_tang_accn,
           "# N[1] rtime[2], u[3], u_next[4], curr_alpha[5], curr_beta[6], "
           "curr_norm_accn[7], "
           "min_tang_accn[8], curr_tang_accn[9], max_tang_accn[10] eps[11] "
           "rho[12] check_tang_accn[13] \n");

}

// ==================================================================
void proc_writefooter_data_calc_tang_accn (FILE* FHdata_calc_tang_accn)
// ==================================================================
{

  fprintf (FHdata_calc_tang_accn,
           "# N[1] rtime[2], u[3], u_next[4], curr_alpha[5], curr_beta[6], "
           "curr_norm_accn[7], "
           "min_tang_accn[8], curr_tang_accn[9], max_tang_accn[10] eps[11] "
           "rho[12] check_tang_accn[13] \n");

   fprintf (FHdata_calc_tang_accn,
            "# DTStamp_FHdata_calc_tang_accn (tangential acceleration) %s \n",
            get_datetime_stamp ());

}

// ==================================================================
void proc_write_calc_tang_accn (FILE* FHdata_calc_tang_accn, int N, double curr_tang_accn,
                        double rtime, double u, double u_next)
// ==================================================================
{

      double curr_alpha = fxn_get_alpha (u);
      double curr_beta  = fxn_get_beta (u);

      // double curr_tang_accn = fxn_get_curr_tang_accn (u);
      double curr_norm_accn = fxn_get_curr_norm_accn (u);

      double min_tang_accn = fxn_get_min_tang_accn (u);
      double max_tang_accn = fxn_get_max_tang_accn (u);

      double eps = fxn_cpos_epsilon(u, u_next);
      double rho = fxn_cpos_rho(u);

      double check_tang_accn = fabs(sqrt(pow(curr_tang_accn, 2.0) + pow(curr_norm_accn, 2.0)));


      fprintf (FHdata_calc_tang_accn,
               "%6d %12.6lf %12.9lf %12.9lf %12.9lf %12.9lf %21.18lf %13.9lf "
               "%13.9lf %13.9lf %18.15lf %12.6lf %18.15lf \n",
               N, rtime, u, u_next, curr_alpha, curr_beta, curr_norm_accn,
               min_tang_accn, curr_tang_accn, max_tang_accn, eps, rho, check_tang_accn);

}

// ==================================================================
// ALHAMDULILLAH 3 TIMES
// ==================================================================

