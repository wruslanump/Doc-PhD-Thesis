// FILE: calc00_parametric_curve.h

#include <stdio.h> // For FILE definition

void proc_writeheader_data_raw_curve (FILE* FHdata_raw_curve);
void proc_writefooter_data_raw_curve (FILE* FHdata_raw_curve);

void proc_write_raw_curves (FILE* FHdata_raw_curve, double rtime, double u,
                            double u_next);




