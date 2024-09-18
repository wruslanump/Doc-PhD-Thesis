// FILE: calc01_lookahead_length.h

#include <stdio.h>

// ==================================================================
/*
The problem of parametric curve interpolation can be expressed as, given the
following 5 values:

(1) the parametric curve C (u) ;
(2) the command feedrate F;
(3) the interpolation period T;
(4) the current (k-th interpolation period) motion status:

// that is, feedrate f k
// and acceleration a k ;
// (5) the current reference point C (u k ) .

then calculate the reference point C (u k+1 ) for the next interpolation period.

And the result should be subject to machine dynamics constraints and chord error
tolerance [23] : The constraints comprise:

(6) Axial velocities and accelerations should be limited to avoid saturating the
drive; (7) The jerk should be limited to avoid the excitation of vibrations in
components in the machine assembly; (8) The chord error increases with feedrate
and curvature, so the feedrate should be limited to achieve high interpolation
accuracy, while the productivity should be kept as high as possible.

*/

// ==================================================================
// (1) the parametric curve C (u) ;
// double curr_u, curr_x, curr_y;
// curr_x(u) = ( -150.0*pow(u, 1.0) + 450.0*pow(u, 2.0) - 300.0*pow(u, 3.0) );
// curr_y(u) = ( -150.0*pow(u, 1.0) + 150.0*pow(u, 2.0) );

// (2) the command feedrate F;
// double command_frate = 20.0;

// (3) the interpolation period T;
// double t_interpol = 0.001; // 1 millisecond.

// (4) the current feedrate and current acceleration;
// double curr_frate;
// double curr_accn;

// (5) the current reference point C (u k ) .
// C(u) = (curr_x(u), curr_y(u))

// (6) Axial velocities and accelerations should be limited to avoid
// saturating the drive;

// FROM TABLE 1 Interpolator parameters
// x/y velocity limits     = 30.0 mm/s
// x/y acceleration limits = 30.0 mm/s2

// (7) The jerk should be limited to avoid the excitation of vibrations
// in components in the machine assembly;
// double curr_jerk;
// double max_jerk;

// FROM TABLE 1 Interpolator parameters
// jerk limit     = 200.0 mm/s2

// (8) The chord error increases with feedrate and curvature, so the feedrate
// should be limited to achieve high interpolation accuracy,
// while the productivity should be kept as high as possible.
// double curr_eps; // chord error
// double curr_rho; // curvature

// FROM TABLE 1 Interpolator parameters
// contour error tolerance = 0.01 um = 0.01E-6 = 1.0E-8

// A realtime interpolator cannot be based on a uniform segmentation of
// the curve according to the independent parameter u. It causes the length
// of the segment steps, delta-s = C(u(k+1)) - C(u(k)) to not be equal,
// but the tool transfers them in equal time intervals T. Thus, the
// feedrate along the curve is not constant. It will be jerky.

// The feedrate V(u) along the curve is defined by

//  V (u)  = ds / dt = (ds / du) (du / dt)

// =========================================================
// DEFINE FUNCTION PROTOTYPES
// =========================================================

int fxn_get_deceleration_profile (double u, double u_next, double csv_tang_accn,
                          double curr_tang_accn, double max_jerk,
                          double curr_frate);


double fxn_get_time_lookahead_length (double u, double u_next,
                          double csv_tang_accn, double curr_tang_accn,
                          double max_jerk,double curr_frate, int decn_profile);


void proc_writeheader_data_calc_t_look (FILE* FHdata_calc_t_look);
void proc_writefooter_data_calc_t_look (FILE* FHdata_calc_t_look);

void proc_write_calc_t_look (FILE *FHdata_calc_t_look, double rtime, double u,
                             double u_next, double curr_tang_accn,
                             double curr_frate, double csv_tang_accn, double max_jerk);


// ==========================================================
// ALHAMDULILLAH 3 TIMES.
// ==========================================================

