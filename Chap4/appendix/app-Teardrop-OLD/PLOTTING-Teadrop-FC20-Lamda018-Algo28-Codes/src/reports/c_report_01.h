// File: c_report_01.h
//
// #include "common/c_dtstamp.h" // HIRES DATE-TIME STAMP
#include <stdio.h>            // For FILE definition

// wruslan@hpelbk8570w-debian10:~$ date
// Sun 08 Jan 2023 03:26:06 AM +08

// =================================================================
void proc_write_01_epsilon_processing_error_statistics (FILE *FHdata_02,
      char *CurveType, int N,
      int count_step1_ERROR_1, int count_step1_ERROR_2,
      int count_step2_ERROR_1, int count_step2_ERROR_2,
      int count_step2_ERROR_3, int count_step2_ERROR_4);

// =================================================================
void proc_write_02_epsilon_count_range_value_statistics (FILE* FHdata_02,
      char* CurveType, int N,
      int cnt_eps_above_10E_6, double pcnt_above,
      int cnt_eps_betwn_10E_7_to_10E_6, double pcnt_10E_7,
      int cnt_eps_betwn_10E_8_to_10E_7, double pcnt_10E_8,
      int cnt_eps_betwn_10E_9_to_10E_8, double pcnt_10E_9,
      int cnt_eps_betwn_10E_10_to_10E_9, double pcnt_10E_10,
      int cnt_eps_below_10E_10, double pcnt_below,
      int cnt_eps_total_points, double pcnt_total );

// =================================================================
void proc_write_03_interpolated_point_statistics (FILE *FHdata_02,
      char *CurveType, int N, int count_before_step1_belowtol,
      double pcnt_before, int num_of_step1_processing, double pcnt_step1,
      int num_of_step2_processing);

// =================================================================
void proc_write_04_adjust_currfrate_to_currfrate_limit (FILE* FHdata_02,
      char *CurveType, int N,
      int count_rising_s_curve_points, double pcnt_rising,
      int count_frate_islower_fratelimit, double pcnt_lower,
      int count_frate_isequal_fratelimit, double pcnt_equal,
      int count_frate_ishigher_fratelimit, double pcnt_higher,
      int count_falling_s_curve_points, double pcnt_falling,
      double sum_percentages );

// =================================================================
void proc_write_05_write_epsilon_chord_error_statistics (FILE *FHdata_02,
      char *CurveType, int N, double min_eps, double avg_eps,
      double max_eps, double sum_eps, int line_mineps, double u_mineps,
      double x_mineps, double y_mineps, int line_maxeps, double u_maxeps,
      double x_maxeps, double y_maxeps);

// ==================================================================
void proc_write_06_write_radius_of_curvature_rho_statistics (FILE* FHdata_02,
      char *CurveType, int N,
      double min_rho, double avg_rho, double max_rho, double sum_rho,
      int line_minrho, double u_minrho, double x_minrho, double y_minrho,
      int line_maxrho, double u_maxrho, double x_maxrho, double y_maxrho );

// ==================================================================
void proc_write_07_write_tangential_acceleration_statistics (FILE* FHdata_02,
      char *CurveType, int N,
      double min_tangaccn, double avg_tangaccn, double max_tangaccn, double sum_tangaccn,
      int line_mintangaccn, double u_mintangaccn, double x_mintangaccn, double y_mintangaccn,
      int line_maxtangaccn, double u_maxtangaccn, double x_maxtangaccn, double y_maxtangaccn );

// ==================================================================
void proc_write_08_write_feedrate_statistics (FILE* FHdata_02,
      char *CurveType, int N,
      double min_frate, double avg_frate, double max_frate, double sum_frate,
      int line_minfrate, double u_minfrate, double x_minfrate, double y_minfrate,
      int line_maxfrate, double u_maxfrate, double x_maxfrate, double y_maxfrate );


void proc_write_09_write_algorithm_efficiency_statistics (
      FILE *FHdata_02, char *CurveType, int N, double sum_chordlength,
      double sum_eps, double sum_arc_length, double sum_arc_theta,
      double sum_arc_area, double diff_arc_chord_length, double pcnt_diff_arc_chord_length );

// ==================================================================
// ALHAMDULILLAH WRY.
// ==================================================================


