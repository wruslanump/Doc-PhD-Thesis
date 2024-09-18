// FILE: calc04_integration_error.h

#include <stdio.h>


// ===================================

void proc_writeheader_data_calc_intgr_error (FILE *FHdata_calc_intgr_error);

void proc_writefooter_data_calc_intgr_error (FILE *FHdata_calc_intgr_error);

void proc_write_calc_intgr_error (FILE *FHdata_calc_intgr_error,
      double next_arc_length, double sum_arc_length,
      double next_arc_theta, double sum_arc_theta,
      double next_arc_area, double sum_arc_area,
      double rtime, double u, double u_next,
      double sum_deltaS, double sum_chordlength,
      double diff_arc_chord_length,
      double pcnt_diff_arc_chord_length);
