// FILE: calc07_iterate_u_next.h

#include <stdio.h> // For FILE type definition

void proc_writeheader_data_calc_u_next (FILE* FHdata_calc_u_next); // HEADER
void proc_writefooter_data_calc_u_next (FILE* FHdata_calc_u_next); // FOOTER

double get_u_next_firstorder_runtime (double rtime, double ru, double ru_next, double rt_interpol, double frate_command);

double get_u_next_secondorder_runtime(double rtime, double ru, double ru_next, double rt_interpol, double frate_command);

void proc_write_calc_u_next (FILE *FHdata_calc_u_next, double rtime, double u,
                             double u_next, double t_interpol,
                             double curr_tang_accn, double curr_frate,
                             double frate_limit, double frate_command);

// FOR CALCULATION step1_unext
double fxn_get_u_next_with_constrained_eps (double u, double u_next,
                double uppertol_bound,
                int *count_step1_ERROR_1,
                int *count_step1_ERROR_2);

// FOR CALCULATION step2_unext
// CALL BY REFERENCE &, THEN RECEIVE BY POINTER *
double fxn_get_u_next_with_eps_both_bounded (double u, double u_next,
          double uppertol_bound, double lowertol_bound,
          int *count_step2_ERROR_1, int *count_step2_ERROR_2,
          int *count_step2_ERROR_3, int *count_step2_ERROR_4 );


