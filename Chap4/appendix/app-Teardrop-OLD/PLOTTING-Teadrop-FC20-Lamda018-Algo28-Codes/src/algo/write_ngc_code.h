// FILE: write_ngc_code.h

#include <stdio.h> // For FILE* type definition



void proc_writeheader_data_ngc_code (FILE* FHdata_ngc_code, char* CurveTypeDesc, double ngc_depth, double ngc_scale);

void proc_writefooter_data_ngc_code (FILE* FHdata_ngc_code);

void proc_write_data_ngc_code (FILE *FHdata_ngc_code, double rtime, double u,
                               double u_next, double t_interpol,
                               double curr_tang_accn, double curr_frate,
                               double curr_frate_limit, double ngc_depth,
                               double ngc_scale, double frate_cmd);


