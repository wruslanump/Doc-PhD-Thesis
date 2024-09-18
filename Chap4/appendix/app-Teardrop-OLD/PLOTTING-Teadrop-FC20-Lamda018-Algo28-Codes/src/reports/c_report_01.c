// File: c_report_01.c

#include "c_report_01.h"

// wruslan@hpelbk8570w-debian10:~$ date
// Sun 08 Jan 2023 03:26:06 AM +08

// =================================================================
void proc_write_01_epsilon_processing_error_statistics (FILE *FHdata_02,
      char* CurveType, int N,
      int count_step1_ERROR_1, int count_step1_ERROR_2,
      int count_step2_ERROR_1, int count_step2_ERROR_2,
      int count_step2_ERROR_3, int count_step2_ERROR_4) 
// =================================================================
{

printf ("\n");  
printf ("%s (1) EPSILON PROCESSING ERRORS \n", CurveType);
printf ("%s STEP 1 ERRORS \n", CurveType);
printf ("%s count_step1_ERROR_1 = %10d \n", CurveType, count_step1_ERROR_1);
printf ("%s count_step1_ERROR_2 = %10d \n", CurveType, count_step1_ERROR_2);
printf ("%s STEP 2 ERRORS \n", CurveType);
printf ("%s count_step2_ERROR_1 = %10d \n", CurveType, count_step2_ERROR_1);
printf ("%s count_step2_ERROR_2 = %10d \n", CurveType, count_step2_ERROR_2);
printf ("%s count_step2_ERROR_3 = %10d \n", CurveType, count_step2_ERROR_3);
printf ("%s count_step2_ERROR_4 = %10d \n", CurveType, count_step2_ERROR_4);
printf("\n");

fprintf (FHdata_02, "\n");
fprintf (FHdata_02, "%s (1) EPSILON PROCESSING ERRORS \n", CurveType);
fprintf (FHdata_02, "%s STEP 1 ERRORS \n", CurveType);
fprintf (FHdata_02, "%s count_step1_ERROR_1 = %10d \n", CurveType, count_step1_ERROR_1);
fprintf (FHdata_02, "%s count_step1_ERROR_2 = %10d \n", CurveType, count_step1_ERROR_2);
fprintf (FHdata_02, "%s STEP 2 ERRORS \n", CurveType);
fprintf (FHdata_02, "%s count_step2_ERROR_1 = %10d \n", CurveType, count_step2_ERROR_1);
fprintf (FHdata_02, "%s count_step2_ERROR_2 = %10d \n", CurveType, count_step2_ERROR_2);
fprintf (FHdata_02, "%s count_step2_ERROR_3 = %10d \n", CurveType, count_step2_ERROR_3);
fprintf (FHdata_02, "%s count_step2_ERROR_4 = %10d \n", CurveType, count_step2_ERROR_4);
fprintf (FHdata_02, "\n");

}
// =================================================================
void proc_write_02_epsilon_count_range_value_statistics (FILE* FHdata_02,
      char* CurveType, int N,
      int cnt_eps_above_10E_6, double pcnt_above,
      int cnt_eps_betwn_10E_7_to_10E_6, double pcnt_10E_7,
      int cnt_eps_betwn_10E_8_to_10E_7, double pcnt_10E_8,
      int cnt_eps_betwn_10E_9_to_10E_8, double pcnt_10E_9,
      int cnt_eps_betwn_10E_10_to_10E_9, double pcnt_10E_10,
      int cnt_eps_below_10E_10, double pcnt_below,
      int cnt_eps_total_points, double pcnt_total )
// =================================================================
{

  
  printf ("%s (2) EPSILON COUNT RANGE VALUE STATISTICS \n", CurveType);
  printf ("%s cnt_eps_above_10E_6             = %10d  (%lf %%) \n", CurveType, cnt_eps_above_10E_6, pcnt_above);
  printf ("%s cnt_eps_betwn_10E_7_upto_10E_6  = %10d  (%lf %%) \n", CurveType, cnt_eps_betwn_10E_7_to_10E_6, pcnt_10E_7);
  printf ("%s cnt_eps_betwn_10E_8_upto_10E_7  = %10d  (%lf %%) \n", CurveType, cnt_eps_betwn_10E_8_to_10E_7, pcnt_10E_8);
  printf ("%s cnt_eps_betwn_10E_9_upto_10E_8  = %10d  (%lf %%) \n", CurveType, cnt_eps_betwn_10E_9_to_10E_8, pcnt_10E_9);
  printf ("%s cnt_eps_betwn_10E_10_upto_10E_9 = %10d  (%lf %%) \n", CurveType, cnt_eps_betwn_10E_10_to_10E_9, pcnt_10E_10);
  printf ("%s cnt_eps_below_10E_10            = %10d  (%lf %%) \n", CurveType, cnt_eps_below_10E_10, pcnt_below);
  printf ("%s cnt_eps_total_points processed  = %10d  (%lf %%) \n", CurveType, cnt_eps_total_points, pcnt_total);
  printf ("\n");

  fprintf (FHdata_02, "%s (2) EPSILON COUNT RANGE VALUE STATISTICS \n", CurveType);
  fprintf (FHdata_02, "%s cnt_eps_above_10E_6             = %10d  (%lf %%) \n", CurveType, cnt_eps_above_10E_6, pcnt_above);
  fprintf (FHdata_02, "%s cnt_eps_betwn_10E_7_upto_10E_6  = %10d  (%lf %%) \n", CurveType, cnt_eps_betwn_10E_7_to_10E_6, pcnt_10E_7);
  fprintf (FHdata_02, "%s cnt_eps_betwn_10E_8_upto_10E_7  = %10d  (%lf %%) \n", CurveType, cnt_eps_betwn_10E_8_to_10E_7, pcnt_10E_8);
  fprintf (FHdata_02, "%s cnt_eps_betwn_10E_9_upto_10E_8  = %10d  (%lf %%) \n", CurveType, cnt_eps_betwn_10E_9_to_10E_8, pcnt_10E_9);
  fprintf (FHdata_02, "%s cnt_eps_betwn_10E_10_upto_10E_9 = %10d  (%lf %%) \n", CurveType, cnt_eps_betwn_10E_10_to_10E_9, pcnt_10E_10);
  fprintf (FHdata_02, "%s cnt_eps_below_10E_10            = %10d  (%lf %%) \n", CurveType, cnt_eps_below_10E_10, pcnt_below);
  fprintf (FHdata_02, "%s cnt_eps_total_points processed  = %10d  (%lf %%) \n", CurveType, cnt_eps_total_points, pcnt_total);
  fprintf (FHdata_02, "\n");


}

// =================================================================
void proc_write_03_interpolated_point_statistics (FILE *FHdata_02,
      char *CurveType, int N, int count_before_step1_belowtol,
      double pcnt_before, int num_of_step1_processing, double pcnt_step1,
      int num_of_step2_processing)
// ==================================================================
{
 
  printf ("%s (3) INTERPOLATED POINT STATISTICS \n", CurveType);
  printf ("%s Count before step1, epsilon is already    below upper bound = %d ( %10.6lf  %%) \n", CurveType, count_before_step1_belowtol, pcnt_before);
  printf ("%s Count during step1, pushdown epsilon to   below upper bound = %d ( %10.6lf  %%) \n", CurveType, num_of_step1_processing, pcnt_step1);
  printf ("%s After step1 the interpolated points count below upper bound = %d (total interpolated points) \n", CurveType, num_of_step1_processing + count_before_step1_belowtol);
  printf ("%s Count during step2, pushup into range (lower , upper) bound = %d (total pushup points) \n", CurveType, num_of_step2_processing);
  printf ("\n");

  fprintf (FHdata_02, "%s (3) INTERPOLATED POINT STATISTICS \n", CurveType);
  fprintf (FHdata_02, "%s Count before step1, epsilon is already    below upper bound = %d ( %10.6lf  %%) \n", CurveType, count_before_step1_belowtol, pcnt_before);
  fprintf (FHdata_02, "%s Count during step1, pushdown epsilon to   below upper bound = %d ( %10.6lf  %%) \n", CurveType, num_of_step1_processing, pcnt_step1);
  fprintf (FHdata_02, "%s After step1 the interpolated points count below upper bound = %d (total interpolated points) \n", CurveType, num_of_step1_processing + count_before_step1_belowtol);
  fprintf (FHdata_02, "%s Count during step2, pushup into range (lower , upper) bound = %d (total pushup points) \n", CurveType, num_of_step2_processing);
  fprintf (FHdata_02, "\n");

}

// =================================================================
void proc_write_04_adjust_currfrate_to_currfrate_limit (FILE* FHdata_02,
      char *CurveType, int N, 
      int count_rising_s_curve_points, double pcnt_rising,
      int count_frate_islower_fratelimit, double pcnt_lower,
      int count_frate_isequal_fratelimit, double pcnt_equal,
      int count_frate_ishigher_fratelimit, double pcnt_higher,
      int count_falling_s_curve_points, double pcnt_falling,
      double sum_percentages )
// ==================================================================
{

// WRITE TO SCREEN  
printf ("%s (4) ADJUST (INCR/DECR) CURR_FRATE TO CALCULATED CURR_FRATE_LIMIT \n", CurveType);
printf ("%s Count_rising_s_curve_points     = %d \t(%12.6lf %%) \n", CurveType, count_rising_s_curve_points, pcnt_rising );
printf ("%s Count_frate_islower_fratelimit  = %d \t(%12.6lf %%) \n", CurveType, count_frate_islower_fratelimit, pcnt_lower);
printf ("%s Count_frate_isequal_fratelimit  = %d \t(%12.6lf %%) \n", CurveType, count_frate_isequal_fratelimit, pcnt_equal);
printf ("%s Count_frate_ishigher_fratelimit = %d \t(%12.6lf %%) \n", CurveType, count_frate_ishigher_fratelimit, pcnt_higher);
printf ("%s Count_falling_s_curve_points    = %d \t(%12.6lf %%) \n", CurveType, count_falling_s_curve_points, pcnt_falling);
printf ("%s Total interpolated points       = %d \t(%12.6lf %%) \n", CurveType, N, sum_percentages);
printf("\n");

// WRITE TO FILE
fprintf (FHdata_02,"%s (4) ADJUST (INCR/DECR) CURR_FRATE TO CALCULATED CURR_FRATE_LIMIT \n", CurveType);
fprintf (FHdata_02, "%s Count_rising_s_curve_points     = %d \t(%12.6lf %%) \n", CurveType, count_rising_s_curve_points, pcnt_rising );
fprintf (FHdata_02, "%s Count_frate_islower_fratelimit  = %d \t(%12.6lf %%) \n", CurveType, count_frate_islower_fratelimit, pcnt_lower);
fprintf (FHdata_02, "%s Count_frate_isequal_fratelimit  = %d \t(%12.6lf %%) \n", CurveType, count_frate_isequal_fratelimit, pcnt_equal);
fprintf (FHdata_02, "%s Count_frate_ishigher_fratelimit = %d \t(%12.6lf %%) \n", CurveType, count_frate_ishigher_fratelimit, pcnt_higher);
fprintf (FHdata_02, "%s Count_falling_s_curve_points    = %d \t(%12.6lf %%) \n", CurveType, count_falling_s_curve_points, pcnt_falling);
fprintf (FHdata_02, "%s Total interpolated points       = %d \t(%12.6lf %%) \n", CurveType, N, sum_percentages);
fprintf (FHdata_02, "\n");
 

}

// =================================================================
void proc_write_05_write_epsilon_chord_error_statistics (FILE* FHdata_02,
      char *CurveType, int N, 
      double min_eps, double avg_eps, double max_eps, double sum_eps,
      int line_mineps, double u_mineps, double x_mineps, double y_mineps,
      int line_maxeps, double u_maxeps, double x_maxeps, double y_maxeps )
      
// ==================================================================
{

// WRITE TO SCREEN  

printf ("%s (5) CHORD ERROR (CURR_EPS) VARIABLE VALUE STATISTICS \n", CurveType);
printf ("%s eps (min_eps, avg_eps, max_eps, sum_eps) = ( %.6e, %.6e, %.6e %.6e )\n", CurveType, min_eps, avg_eps, max_eps, sum_eps);
printf ("%s At min_eps (line_mineps, u_mineps, x_mineps, y_mineps) = ( %6d %.6e %.6e %.6e )\n", CurveType, line_mineps, u_mineps, x_mineps, y_mineps);
printf ("%s At max_eps (line_maxeps, u_maxeps, x_maxeps, y_maxeps) = ( %6d %.6e %.6e %.6e )\n", CurveType, line_maxeps, u_maxeps, x_maxeps, y_maxeps);
printf("\n");

// WRITE TO FILE  

fprintf (FHdata_02, "%s (5) CHORD ERROR (CURR_EPS) VARIABLE VALUE STATISTICS \n", CurveType);
fprintf (FHdata_02, "%s eps (min_eps, avg_eps, max_eps, sum_eps) = ( %.6e, %.6e, %.6e %.6e )\n", CurveType, min_eps, avg_eps, max_eps, sum_eps);
fprintf (FHdata_02, "%s At min_eps (line_mineps, u_mineps, x_mineps, y_mineps) = ( %6d %.6e %.6e %.6e )\n", CurveType, line_mineps, u_mineps, x_mineps, y_mineps);
fprintf (FHdata_02, "%s At max_eps (line_maxeps, u_maxeps, x_maxeps, y_maxeps) = ( %6d %.6e %.6e %.6e )\n", CurveType, line_maxeps, u_maxeps, x_maxeps, y_maxeps);
fprintf (FHdata_02, "\n");


}

// ==================================================================
void proc_write_06_write_radius_of_curvature_rho_statistics (FILE* FHdata_02,
      char *CurveType, int N, 
      double min_rho, double avg_rho, double max_rho, double sum_rho,
      int line_minrho, double u_minrho, double x_minrho, double y_minrho,
      int line_maxrho, double u_maxrho, double x_maxrho, double y_maxrho )
// ==================================================================
{

// WRITE TO SCREEN

printf ("%s (6) RADIUS OF CURVATURE (CURR_RHO) VARIABLE VALUE STATISTICS \n", CurveType);
printf ("%s rho (min, avg, max, sum) = ( %.6e, %.6e, %.6e %.6e )\n", CurveType, min_rho, avg_rho, max_rho, sum_rho);
printf ("%s At min_rho (line_minrho, u_minrho, x_minrho, y_minrho) = ( %6d %.6e %.6e %.6e )\n", CurveType, line_minrho, u_minrho, x_minrho, y_minrho);
printf ("%s At max_rho (line_maxrho, u_maxrho, x_maxrho, y_maxrho) = ( %6d %.6e %.6e %.6e )\n", CurveType, line_maxrho, u_maxrho, x_maxrho, y_maxrho);
printf("\n");

// WRITE TO FILE

fprintf (FHdata_02, "%s (6) RADIUS OF CURVATURE (CURR_RHO) VARIABLE VALUE STATISTICS \n", CurveType);
fprintf (FHdata_02, "%s rho (min, avg, max, sum) = ( %.6e, %.6e, %.6e %.6e )\n", CurveType, min_rho, avg_rho, max_rho, sum_rho);
fprintf (FHdata_02, "%s At min_rho (line_minrho, u_minrho, x_minrho, y_minrho) = ( %6d %.6e %.6e %.6e )\n", CurveType, line_minrho, u_minrho, x_minrho, y_minrho);
fprintf (FHdata_02, "%s At max_rho (line_maxrho, u_maxrho, x_maxrho, y_maxrho) = ( %6d %.6e %.6e %.6e )\n", CurveType, line_maxrho, u_maxrho, x_maxrho, y_maxrho);
fprintf (FHdata_02, "\n");

}
// ==================================================================
void proc_write_07_write_tangential_acceleration_statistics (FILE* FHdata_02,
      char *CurveType, int N, 
      double min_tangaccn, double avg_tangaccn, double max_tangaccn, double sum_tangaccn,
      int line_mintangaccn, double u_mintangaccn, double x_mintangaccn, double y_mintangaccn, 
      int line_maxtangaccn, double u_maxtangaccn, double x_maxtangaccn, double y_maxtangaccn )
      
// ==================================================================
{

// WRITE TO SCREEN

printf ("%s (7) TANGENTIAL ACCELERATION (CURR_TANG_ACCN) VARIABLE VALUE STATISTICS \n", CurveType);
printf ("%s tangaccn (min, avg, max, sum) = ( %.6e, %.6e, %.6e %.6e )\n", CurveType, min_tangaccn, avg_tangaccn, max_tangaccn, sum_tangaccn);
printf ("%s At min_tangaccn (line_mintangaccn, u_mintangaccn, x_mintangaccn, y_mintangaccn) = ( %6d %.6e %.6e %.6e )\n", CurveType, line_mintangaccn, u_mintangaccn, x_maxtangaccn, y_mintangaccn);
printf ("%s At max-tangaccn (line_maxtangaccn, u_maxtangaccn, x_maxtangaccn, y_maxtangaccn) = ( %6d %.6e %.6e %.6e )\n", CurveType, line_maxtangaccn, u_maxtangaccn, y_maxtangaccn, y_maxtangaccn);
printf ("\n");

// WRITE TO FILE

fprintf (FHdata_02, "%s (7) TANGENTIAL ACCELERATION (CURR_TANG_ACCN) VARIABLE VALUE STATISTICS \n", CurveType);
fprintf (FHdata_02, "%s tangaccn (min, avg, max, sum) = ( %.6e, %.6e, %.6e %.6e )\n", CurveType, min_tangaccn, avg_tangaccn, max_tangaccn, sum_tangaccn);
fprintf (FHdata_02, "%s At min_tangaccn (line_mintangaccn, u_mintangaccn, x_mintangaccn, y_mintangaccn) = ( %6d %.6e %.6e %.6e )\n", CurveType, line_mintangaccn, u_mintangaccn, x_mintangaccn, y_mintangaccn);
fprintf (FHdata_02, "%s At max_tangaccn (line_maxtangaccn, u_maxtangaccn, x_maxtangaccn, y_maxtangaccn) = ( %6d %.6e %.6e %.6e )\n", CurveType, line_maxtangaccn, u_maxtangaccn, x_maxtangaccn, y_maxtangaccn);
fprintf (FHdata_02, "\n");

}

// ==================================================================
void proc_write_08_write_feedrate_statistics (FILE* FHdata_02,
      char *CurveType, int N, 
      double min_frate, double avg_frate, double max_frate, double sum_frate,
      int line_minfrate, double u_minfrate, double x_minfrate, double y_minfrate, 
      int line_maxfrate, double u_maxfrate, double x_maxfrate, double y_maxfrate )
// ==================================================================
{

// WRITE TO SCREEN

printf ("%s (8) FEEDRATE (CURR_FRATE) VARIABLE VALUE STATISTICS \n", CurveType);
printf ("%s frate (min, avg, max, sum) = ( %.6e, %.6e, %.6e %.6e )\n", CurveType, min_frate, avg_frate, max_frate, sum_frate);
printf ("%s At min_frate (line_minfrate, u_minfrate, x_minfrate, y_minfrate) = ( %6d %.6e %.6e %.6e )\n", CurveType, line_minfrate, u_minfrate, x_minfrate, y_minfrate);
printf ("%s At max_frate (line_maxfrate, u_maxfrate, x_maxfrate, y_maxfrate) = ( %6d %.6e %.6e %.6e )\n", CurveType, line_maxfrate, u_maxfrate, x_maxfrate, y_maxfrate);
printf ("\n");

// WRITE TO FILE

fprintf (FHdata_02, "%s (8) FEEDRATE (CURR_FRATE) VARIABLE VALUE STATISTICS \n", CurveType);
fprintf (FHdata_02, "%s frate (min, avg, max, sum) = ( %.6e, %.6e, %.6e %.6e )\n", CurveType, min_frate, avg_frate, max_frate, sum_frate);
fprintf (FHdata_02, "%s At min_frate (line_minfrate, u_minfrate, x_minfrate, y_minfrate) = ( %6d %.6e %.6e %.6e )\n", CurveType, line_minfrate, u_minfrate, x_minfrate, y_minfrate);
fprintf (FHdata_02, "%s At max_frate (line_maxfrate, u_maxfrate, x_maxfrate, y_maxfrate) = ( %6d %.6e %.6e %.6e )\n", CurveType, line_maxfrate, u_maxfrate, x_maxfrate, y_maxfrate);
fprintf (FHdata_02, "\n");

}

// ===================================================================
void
proc_write_09_write_algorithm_efficiency_statistics (
  FILE *FHdata_02, char *CurveType, int N, double sum_chordlength,
  double sum_eps, double sum_arc_length, double sum_arc_theta,
  double sum_arc_area, double diff_arc_chord_length, double pcnt_diff_arc_chord_length )

  {

// WRITE TO SCREEN
printf ("%s (9) ALGORITHM EXECUTION STATISTICS \n", CurveType);
printf ("\n");
printf ("%s TOTAL-INTERPOLATED-POINTS          =  %d    \n", CurveType, N);
printf ("%s SUM-CHORD-ERROR-(mm)               =  %.12e \n", CurveType, sum_eps);
printf ("%s SUM-CHORD-ERROR/TOT-INTERPOL-PNTS  =  %.12e \n", CurveType, sum_eps/(N-1));
printf ("\n");
printf ("%s SUM-ARC-LENGTH-(mm)                =  %.12e \n", CurveType, sum_arc_length);
printf ("%s SUM-CHORD-LENGTH-(mm)              =  %.12e \n", CurveType, sum_chordlength);
printf ("%s DIFF-ARC-LENGTH-CHORD-LENGTH-(mm)  =  %.12e \n", CurveType, diff_arc_chord_length);
printf ("%s PCNT-DIFF-ARC-CHORD-LENGTH         =  %.12e \n", CurveType, pcnt_diff_arc_chord_length);
printf ("\n");
printf ("%s SUM-CHORD-ERROR/SUM-CHORD-LENGTH   =  %.12e \n", CurveType, sum_eps/sum_chordlength);
printf ("\n");
printf ("%s SUM-ARC-THETA-(rad)                =  %.12e \n", CurveType, sum_arc_theta);
printf ("%s SUM-ARC-AREA-(mm2)                 =  %.12e \n", CurveType, sum_arc_area);
printf ("\n");
printf ("%s SUM-ARC-AREA/SUM-CHORD-LENGTH      =  %.12e \n", CurveType, sum_eps/sum_chordlength);
printf ("\n");
printf ("%s AVG-CHORD-ERROR-(mm)               =  %.12e \n", CurveType, sum_eps/(N-1));
printf ("%s AVG-ARC-LENGTH-(mm)                =  %.12e \n", CurveType, sum_arc_length/(N-1));
printf ("%s AVG-CHORD-LENGTH-(mm)              =  %.12e \n", CurveType, sum_chordlength/(N-1));
printf ("%s AVG-ARC-THETA-(rad)                =  %.12e \n", CurveType, sum_arc_theta/(N-1));
printf ("%s AVG-ARC-AREA-(mm2)                 =  %.12e \n", CurveType, sum_arc_area/(N-1));
printf ("\n");
  
// WRITE TO FILE
fprintf (FHdata_02, "%s (9) ALGORITHM EXECUTION STATISTICS \n", CurveType);
fprintf (FHdata_02, "\n");
fprintf (FHdata_02, "%s TOTAL-INTERPOLATED-POINTS          =  %d    \n", CurveType, N);
fprintf (FHdata_02, "%s SUM-CHORD-ERROR-(mm)               =  %.12e \n", CurveType, sum_eps);
fprintf (FHdata_02, "%s SUM-CHORD-ERROR/TOT-INTERPOL-PNTS  =  %.12e \n", CurveType, sum_eps/(N-1));
fprintf (FHdata_02, "\n");
fprintf (FHdata_02, "%s SUM-ARC-LENGTH-(mm)                =  %.12e \n", CurveType, sum_arc_length);
fprintf (FHdata_02, "%s SUM-CHORD-LENGTH-(mm)              =  %.12e \n", CurveType, sum_chordlength);
fprintf (FHdata_02, "%s DIFF-ARC-LENGTH-CHORD-LENGTH-(mm)  =  %.12e \n", CurveType, diff_arc_chord_length);
fprintf (FHdata_02, "%s PCNT-DIFF-ARC-CHORD-LENGTH         =  %.12e \n", CurveType, pcnt_diff_arc_chord_length);
fprintf (FHdata_02, "\n");
fprintf (FHdata_02, "%s SUM-CHORD-ERROR/SUM-CHORD-LENGTH   =  %.12e \n", CurveType, sum_eps/sum_chordlength);
fprintf (FHdata_02, "\n");
fprintf (FHdata_02, "%s SUM-ARC-THETA-(rad)                =  %.12e \n", CurveType, sum_arc_theta);
fprintf (FHdata_02, "%s SUM-ARC-AREA-(mm2)                 =  %.12e \n", CurveType, sum_arc_area);
fprintf (FHdata_02, "\n");
fprintf (FHdata_02, "%s SUM-ARC-AREA/SUM-CHORD-LENGTH      =  %.12e \n", CurveType, sum_eps/sum_chordlength);
fprintf (FHdata_02, "\n");
fprintf (FHdata_02, "%s AVG-CHORD-ERROR-(mm)               =  %.12e \n", CurveType, sum_eps/(N-1));
fprintf (FHdata_02, "%s AVG-ARC-LENGTH-(mm)                =  %.12e \n", CurveType, sum_arc_length/(N-1));
fprintf (FHdata_02, "%s AVG-CHORD-LENGTH-(mm)              =  %.12e \n", CurveType, sum_chordlength/(N-1));
fprintf (FHdata_02, "%s AVG-ARC-THETA-(rad)                =  %.12e \n", CurveType, sum_arc_theta/(N-1));
fprintf (FHdata_02, "%s AVG-ARC-AREA-(mm2)                 =  %.12e \n", CurveType, sum_arc_area/(N-1));
fprintf (FHdata_02, "\n");
  
}

// ==================================================================
// ALHAMDULILLAH 3 TIMES WRY.
// ==================================================================

