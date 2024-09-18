
// FILE: module_open_close_files.h

#include "common/c_dtstamp.h" // HIRES DATE-TIME STAMP
#include <stdio.h>            // For FILE definition

/*
FILE type is defined in <stdio.h> and you need to include it in each file
that uses it.
*/

// DECLARE FILE HANDLES
FILE *FHdata_01; // FOR TESTING
FILE *FHdata_02; // FOR TESTING

FILE *FHdata_raw_curve;
FILE *FHdata_calc_u_next;
FILE *FHdata_calc_tang_accn;
FILE *FHdata_calc_t_look;
FILE *FHdata_calc_frate_limit;
FILE *FHdata_calc_intgr_error;
FILE *FHdata_ngc_code;



// DECLARE FUNCTION PROTOTYPES
FILE *fxn_open_data_01 (void);
FILE *fxn_open_data_02 (void);
FILE *fxn_open_data_raw_curve (void);
FILE *fxn_open_data_calc_u_next (void);
FILE *fxn_open_data_calc_tang_accn (void);
FILE *fxn_open_data_calc_t_look (void);
FILE *fxn_open_data_calc_frate_limit (void);
FILE *fxn_open_data_calc_intgr_error (void);
FILE *fxn_open_data_ngc_code (void);


void proc_open_all_files (void);

// DECLARE FUNCTION PROTOTYPES
void proc_writeheader_data_01 (void);
void proc_writeheader_data_02 (void);
void proc_writeheader_data_raw_curve (FILE* FHdata_raw_curve);
void proc_writeheader_data_calc_u_next (FILE* FHdata_calc_unext);
void proc_writeheader_data_calc_tang_accn (FILE* FHdata_calc_tang_accn);
void proc_writeheader_data_calc_t_look (FILE* FHdata_calc_t_look);
void proc_writeheader_data_calc_frate_limit (FILE* FHdata_calc_frate_limit);
void proc_writeheader_data_calc_intgr_error (FILE* FHdata_calc_intgr_error);
void proc_writeheader_data_ngc_code (FILE* FHdata_ngc_code, char* CurveTypeDesc, double ngc_depth, double ngc_scale);

void proc_writeheader_all_files (void);

void proc_writefooter_data_01 (void);
void proc_writefooter_data_02 (void);
void proc_writefooter_data_raw_curve (FILE* FHdata_raw_curve);
void proc_writefooter_data_calc_u_next (FILE* FHdata_calc_u_next);
void proc_writefooter_data_calc_tang_accn (FILE* FHdata_calc_tang_accn);
void proc_writefooter_data_calc_t_look (FILE* FHdata_calc_t_look);
void proc_writefooter_data_calc_frate_limit (FILE* FHdata_calc_frate_limit);
void proc_writefooter_data_calc_intgr_error (FILE* FHdata_calc_intgr_error);
void proc_writefooter_data_ngc_code (FILE *FHdata_ngc_code);

void proc_writefooter_all_files (void);

// DECLARE FUNCTION PROTOTYPES
int fxn_close_data_01 (void);
int fxn_close_data_02 (void);
int fxn_close_data_raw_curve (void);
int fxn_close_data_calc_u_next (void);
int fxn_close_data_calc_tang_accn (void);
int fxn_close_data_calc_t_look (void);
int fxn_close_data_calc_frate_limit (void);
int fxn_close_data_calc_intgr_error (void);
int fxn_close_data_ngc_code (void);

void proc_close_all_files (void);

// ==================================================================
FILE* fxn_open_data_01 (void) {
// ==================================================================
  return (fopen ("./data/data_01.txt", "w+"));
}

// ==================================================================
FILE* fxn_open_data_02 (void) {
// ==================================================================
  return (fopen ("./data/data_02.txt", "w+"));
}


// ==================================================================
FILE* fxn_open_data_raw_curve (void) {
// ==================================================================
  return (fopen ("./data/data_raw_curve.txt", "w+"));
}


// ==================================================================
FILE* fxn_open_data_calc_u_next (void) {
// ==================================================================
  return (fopen ("./data/data_calc_u_next.txt", "w+"));
}

// ==================================================================
FILE* fxn_open_data_calc_tang_accn (void) {
// ==================================================================
  return (fopen ("./data/data_calc_tang_accn.txt", "w+"));
}

// ==================================================================
FILE* fxn_open_data_calc_t_look (void) {
// ==================================================================
  return (fopen ("./data/data_calc_t_look.txt", "w+"));
}

// ==================================================================
FILE *fxn_open_data_calc_frate_limit (void) {
// ==================================================================
  return (fopen ("./data/data_calc_frate_limit.txt", "w+"));
}

// ==================================================================
FILE *fxn_open_data_calc_intgr_error (void) {
// ==================================================================
  return (fopen ("./data/data_calc_intgr_error.txt", "w+"));
}

// ==================================================================
FILE *fxn_open_data_ngc_code (void) {
// ==================================================================
  return (fopen ("./ngcode/data_ngcode.ngc", "w+"));
}


// ==================================================================
void proc_open_all_files (void) {
// ==================================================================

  FHdata_01 = fxn_open_data_01 ();
  FHdata_02 = fxn_open_data_02 ();
  FHdata_raw_curve = fxn_open_data_raw_curve ();
  FHdata_calc_u_next = fxn_open_data_calc_u_next ();
  FHdata_calc_tang_accn = fxn_open_data_calc_tang_accn ();
  FHdata_calc_t_look = fxn_open_data_calc_t_look ();
  FHdata_calc_frate_limit = fxn_open_data_calc_frate_limit ();
  FHdata_calc_intgr_error = fxn_open_data_calc_intgr_error ();
  FHdata_ngc_code = fxn_open_data_ngc_code ();
  
}

// ==================================================================
void proc_writeheader_data_01 (void) {
// ==================================================================
  fprintf (FHdata_01, "# DTStamp_FHdata_01 %s \n", get_datetime_stamp ());
  fprintf (FHdata_01, "# Testing data 01 \n");
  
}

// ==================================================================
void proc_writefooter_data_01 (void) {
// ==================================================================
  fprintf (FHdata_01, "# Testing data 01 \n");
  fprintf (FHdata_01, "# DTStamp_FHdata_01 %s \n", get_datetime_stamp ());
}

// ==================================================================
void proc_writeheader_data_02 (void) {
// ==================================================================
  fprintf (FHdata_02, "# DTStamp_FHdata_02 %s \n", get_datetime_stamp ());
  fprintf (FHdata_02, "# Testing data 02 \n");
}

// ==================================================================
void proc_writefooter_data_02 (void) {
// ==================================================================
  fprintf (FHdata_02, "# Testing data 01 \n");
  fprintf (FHdata_02, "# DTStamp_FHdata_02 %s \n", get_datetime_stamp ());

}

// ==================================================================
void proc_writeheader_all_files (void) {
// ==================================================================

   proc_writeheader_data_01 ();
   proc_writeheader_data_02 ();
   proc_writeheader_data_raw_curve (FHdata_raw_curve);
   proc_writeheader_data_calc_u_next (FHdata_calc_u_next);
   proc_writeheader_data_calc_tang_accn (FHdata_calc_tang_accn);
   proc_writeheader_data_calc_t_look (FHdata_calc_t_look);
   proc_writeheader_data_calc_frate_limit (FHdata_calc_frate_limit);
   proc_writeheader_data_calc_intgr_error (FHdata_calc_intgr_error);

   
 }

// ==================================================================
void proc_writefooter_all_files (void) {
// ==================================================================

   proc_writefooter_data_01 ();
   proc_writefooter_data_02 ();
   proc_writefooter_data_raw_curve (FHdata_raw_curve);
   proc_writefooter_data_calc_u_next (FHdata_calc_u_next);
   proc_writefooter_data_calc_tang_accn (FHdata_calc_tang_accn);
   proc_writefooter_data_calc_t_look (FHdata_calc_t_look);
   proc_writefooter_data_calc_frate_limit (FHdata_calc_frate_limit);
   proc_writefooter_data_calc_intgr_error (FHdata_calc_intgr_error);
   
}


// ==================================================================
int fxn_close_data_01 (void) {
  // ==================================================================
  return (fclose (FHdata_01));
}

// ==================================================================
int fxn_close_data_02 (void) {
// ==================================================================
  return (fclose (FHdata_02));
}

// ==================================================================
int fxn_close_data_raw_curve (void) {
// ==================================================================
  return (fclose (FHdata_raw_curve));
}


// ==================================================================
int fxn_close_data_calc_u_next (void) {
// ==================================================================
  return (fclose (FHdata_calc_u_next));
}

// ==================================================================
int fxn_close_data_calc_tang_accn (void) {
// ==================================================================
  return (fclose (FHdata_calc_tang_accn));
}

// ==================================================================
int fxn_close_data_calc_t_look (void) {
// ==================================================================
  return (fclose (FHdata_calc_t_look));
}

// ==================================================================
int fxn_close_data_calc_frate_limit (void) {
// ==================================================================
  return (fclose (FHdata_calc_frate_limit));
}

// ==================================================================
int fxn_close_data_calc_intgr_error (void) {
// ==================================================================
  return (fclose (FHdata_calc_intgr_error));
}


// ==================================================================
int fxn_close_data_ngc_code (void) {
// ==================================================================
  return (fclose (FHdata_ngc_code));
}

// ==================================================================
void proc_close_all_files (void) {
// ==================================================================

  // Can check for success or close failures based on int returned
  int closefile_01 = fxn_close_data_01 ();
  int closefile_02 = fxn_close_data_02 ();
  int closefile_raw_curve = fxn_close_data_raw_curve ();
  int closefile_calc_u_next = fxn_close_data_calc_u_next ();
  int closefile_calc_tang_accn = fxn_close_data_calc_tang_accn ();
  int closefile_calc_t_look = fxn_close_data_calc_t_look ();
  int closefile_calc_frate_limit = fxn_close_data_calc_frate_limit ();
  int closefile_calc_intgr_error = fxn_close_data_calc_intgr_error ();
  int closefile_ngc_code = fxn_close_data_ngc_code ();
  
  }

// ==================================================================
// ALHAMDULILLAH 3 TIMES WRY
// ==================================================================

