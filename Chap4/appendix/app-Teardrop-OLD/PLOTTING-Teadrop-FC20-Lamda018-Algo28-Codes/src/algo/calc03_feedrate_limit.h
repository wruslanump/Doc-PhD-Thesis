// FILE: calc03_feedrate_limit.h


/*
// ==================================================================
// GLOBAL VARIABLES FOR FEEDRATE LIMIT
// ==================================================================
// The feedrate should not exceed the command feedrate.
// Constraint based on the FRate_command specified by user.
double FRate_command;
double FRate_limit_1;

// Feedrate Constraint based on maximum X-Y axial velocities (30 mm/s).
double FRate_limit_2;
double xVee_max = 30.0;
double yVee_max = 30.0;
double alpha;  // varies with u
double beta;   // varies with u
// FRate_limit_2 is the fxn_minimum_of[xVee_max/abs(alpha), yVee_max/abs(beta)]
// where alpha = [dx(u)/dt]/[abs(dC(u)/dt)]
// where beta  = [dy(u)/dt]/[abs(dC(u)/dt)]

// Feedrate Constraint based on the contour accuracy
double FRate_limit_3;
// FRate_limit_3 = (2.0/t_interpol).abs[sqrt( 2.0*rho*eps - power(eps,2.0) )]

// Feedrate Constraint based on maximum X-Y axial accelerations (30 mm/s^2).
double FRate_limit_4;
// FRate_limit_4 is the fxn_minimum_of [C, D]
// where C = sqrt[lamda.rho.xAcc/abs(beta)]   Note: reverse alpha with beta
// where D = sqrt[lamda.rho.yAcc/abs(alpha)]
// where lamda is the safety factor (0.0 < lamda < 1.0 )

// Final Feedrate limit for a point on the curve is the minimum among the
// four(4) limits. [FRate_limit_1, FRate_limit_2, FRate_limit_3, FRate_limit_4]
double FRate_limit_net;
*/

#include <stdio.h>

double fxn_cvel_x(double u);
double fxn_cvel_y(double u);
double fxn_cvel_r(double u);
double fxn_cpos_rho(double u);
double fxn_cpos_epsilon (double u, double u_next);

double fxn_get_feedrate_limit      (double rtime, double u, double u_next, double FRate_command, double T_interpol, double rho, double eps, double lamda);
double get_algo_feedrate_limit_1   (double u, double FRate_command, double T_interpol, double rho, double eps, double lamda);
double get_algo_feedrate_limit_2   (double u, double FRate_command, double T_interpol, double rho, double eps, double lamda);
double get_algo_feedrate_limit_3   (double u, double u_next, double FRate_command, double T_interpol, double rho, double eps, double lamda);
double get_algo_feedrate_limit_4   (double u, double FRate_command, double T_interpol, double rho, double eps, double lamda);

void proc_writeheader_data_calc_frate_limit (FILE* FHdata_calc_frate_limit);
void proc_writefooter_data_calc_frate_limit (FILE* FHdata_calc_frate_limit);

void proc_write_calc_frate_limit (FILE *FHdata_calc_frate_limit, double rtime, double ru, double ru_next,
                             double FRate_command, double rT_interpol,
                             double rho_N, double eps_N, double lamda_N, double curr_frate);




// ==================================================================
// ALHAMDULILLAH 3 TIMES WRY
// ==================================================================

