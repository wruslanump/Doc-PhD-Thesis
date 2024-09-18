// FILE: calc02_tang_accn_limit.h

#include <stdio.h>

double fxn_get_alpha (double u);
double fxn_get_beta (double u);

double fxn_get_min_element_array(double thearray[], int array_size);
double fxn_get_max_element_array(double thearray[], int array_size);

double fxn_get_max_tang_accn (double u);
double fxn_get_min_tang_accn (double u);

double fxn_get_curr_tang_accn (double u);
double fxn_get_curr_norm_accn (double u);

double fxn_get_check01_accn_t (double u);
double fxn_get_check02_accn_t (double u);

void proc_writeheader_data_calc_tang_accn (FILE *FHdata_calc_tang_accn);
void proc_writefooter_data_calc_tang_accn (FILE *FHdata_calc_tang_accn);

void proc_write_calc_tang_accn (FILE *FHdata_calc_tang_accn, int N, double curr_tang_accn, double rtime, double u,
                             double u_next);



