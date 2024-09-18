// File: c_position.h

// =======================================================
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
                      
FILE *FHdata_parametric_cposition;
FILE *FHdata_parametric_u_next;

double fxn_cpos_x(double u); 
double fxn_cpos_y(double u);
double fxn_cpos_r(double u);
double fxn_cpos_magn(double u); 
double fxn_cpos_uvect_x(double u);
double fxn_cpos_uvect_y(double u); 
double fxn_cpos_theta_rad(double u); 
double fxn_cpos_theta_deg(double u);
double fxn_cpos_epsilon(double u, double u_next);
double fxn_cpos_rho (double u);

double arc_u_points[21]; // AVOID WARNINGS INSTEAD OF arc_u_points[];
double arc_x_points[21];
double arc_y_points[21]; 

double fxn_c_radiuscurvature_rho_at_u(double u);
double fxn_c_epsilon_for_arc_u_to_u_next (double u, double u_next, double arc_u_points[], double arc_x_points[],
                                   double arc_y_points[]);

char* get_datetime_stamp(void);
char *get_time_stamp (void);

void write_header_cposition_data(FILE* FHdata_curve_cposition); // TO FILE
void write_data_parametric_cposition(double cu_step, double cu_next, double cu);
void write_header_u_next_data (FILE* FHdata_parametric_u_next);
void write_data_parametric_cu_next(double cu_step, double cu_next, double cu, double ct_interpol);

double fxn_calc_eps_use_paramcurve (double u, double u_next);
// returns (eps)

double fxn_calc_rho_use_paramcurve (double u, double u_next);
// returns (rho)

double fxn_calc_chordlength_use_paramcurve (double u, double u_next);
// returns (chordlength)

double fxn_calc_deltaS_use_rho_eps (double u, double u_next);
// returns (deltaS)

double fxn_calc_rad_to_deg(double angle_rad);
double fxn_calc_deg_to_rad(double angle_deg);

double fxn_calc_arc_length (int N, double u, double u_next, double chord_length, double eps, double rho);
double fxn_calc_arc_theta  (int N, double u, double chord_length, double eps, double rho);
double fxn_calc_arc_area   (int N, double u, double chord_length, double eps, double rho);



// ==================================================================
// ALHAMDULILLAH WRY.
// ==================================================================


