// FILE: c_velocity.c

#include <math.h>         // For pow()
#include "c_velocity.h"

double const PI_cvel = 3.141592653589793238;

// ==============================================
// X-VELOCITY COMPONENT
// ==============================================
double fxn_cvel_x(double u)
  {

/*
  // ELLIPSE DX
  double scaleup = 11.0;
  double k = (2.0*PI_cvel);
  // double x = sin(k*u);
  double dx_du = k*cos(k*u);
  return (scaleup)*(dx_du);
*/
    /*
    // ===============================
    // RIBBON100L - DX

     // set xrange [-1.0:+6.0] GnuPlot
     // set yrange [-1.0:+6.0] Gnuplot
     // RANGE FOR t = [-2.00, +2.00] equivalent to u = [0.00, 1.00]
     double t = 4.0*(u - 0.50); // TRANSORMATION EQUATION

     double scaleup = 10.0;
     // double x = (t*t);
     double dx_du = 2*(t);
     return (scaleup)*(dx_du);

  */
 // ===============================


  // TEARDROP DX
  double scaleup = 1.0;
  return (scaleup)*( -150.0 + 900.0*pow(u, 1.0) - 900.0*pow(u, 2.0) );

  // ============================
/*
  // HYPOTROCOID DX
  double scaleup = 1.0;  // 1.0 IS GOOD (OTHERS BAD)
  double k = (6.0*PI_cvel);                            // RANGE
  // double x = (2*cos(k*u) + 5*cos(2*k*u/3));                // X
  double dx_du = ( -2*k*sin(k*u) - (5*2*k/3)*sin(2*k*u/3) );   // DX
  return (scaleup)*(dx_du);
*/
  // =============================
/*
  // EPICYCLOID DX
  double scaleup = 10.0;
  double k = (2.0 * PI_cvel);
  double small = 1.0e-10;
  // double x =  (5*cos(k*u + small) - cos(5*k*u - small));     // X
  double dx =  ( -5*k*sin(k*u + small) + (5*k)*sin(5*k*u - small));         // DX
  return (scaleup)*(dx);
*/
// ==============================
/*
// ASTEPI DX = ASTROID DX + EPICYCLOID DX
  double scaleup = 10.0;
  double k = (2.0 * PI_cvel);
  double small = 1.0e-10;

  // double x_ast = +4.0* pow(sin (k*u), 3.0);
  double dx_ast = +4.0*(3.0)*k*pow(cos (k*u), 2.0);
  // double x_epi = +5.0*cos(k*u + small) - cos(5*k*u - small);
  double dx_epi = -5.0*k*sin(k*u + small) + (5.0*k)*sin(5*k*u - small);
  double dx = dx_ast + dx_epi;
  return (scaleup)*(dx);
*/
// ================================
/*
  double fxn_get_dx_snailshell (double u);

  // SNAHYP DX = SNAILSHELL DX + HYPOTROCOID DX
  double scaleup = 10.0;
  double k = (4.0 * PI_cvel);
  double small = 1.0e-10;
  double dx_sna = (10)*fxn_get_dx_snailshell(u);  // FUNCTION CALL ****
  double dx_hyp = ( -2*k*sin(k*u) - (5*2*k/3)*sin(2*k*u/3) );
  double dx = dx_sna + dx_hyp;
  return (scaleup)*(dx);
*/
// =================================

  /*
  // CIRCLE DX
  double scaleup = 79.0;
  double k = (2.0*PI_cvel);
  // double x = sin(k*u);
  double dx_du = k*cos(k*u);
  return (scaleup)*(dx_du);
*/
// =================================
/*
  // LINE-POLYU DX
  double scaleup = 1.0;
  // double polyu_x = ( 150.0*pow(u, 1.0) + 150.0*pow(u, 2.0) );
  double polyu_dx = ( 150.0 + 300.0*pow(u, 1.0) );
  return (scaleup)*(polyu_dx);
*/
// =================================
/*
  // SKEWED ASTROID DX
  double scaleup = 10.0;
  double k = (2.0*PI_cvel);
  // double x =   +4.0*pow(sin(k*u), 3.0);
     double dx_du =  +4.0*(3.0)*k*pow(cos(k*u), 2.0);
  // double d2x_du2 = -4.0*(3.0)*(2.0)*k*k*pow(sin(k*u), 1.0);
  return (scaleup)*(dx_du);
*/
// ==================================
/*
  // SNAILSHELL DX
  double scaleup = 100.0;
  double k       = (3.0*PI_cvel);

  double fxtu = sin (2 * k * u); // DIFFERENT
  double d_fxtdu = 2 * k * cos (2 * k * u);
  double gxtu = (k * k * u * u + 4.0);
  double d_gxtdu = 2 * k * k * u;
  // SNAILSHELL RESULT QUOTIENT RULE
  double dx_du = ((fxtu * d_gxtdu) - (gxtu * d_fxtdu)) / (gxtu * gxtu);
  return (scaleup)*(dx_du);
*/
// ===================================
/*
  // BUTTERFLY DX
  double scaleup = 10.0;
  double k       = (2.0*PI_cvel);

  double fxtu    = sin(k*u);   // DIFFERENT
  double d_fxtdu = k*cos(k*u);
  double gxtu    = exp(cos(k*u)) - 2*cos(4*k*u) - pow(sin(k*u/12), 5.0);
  double d_gxtdu = - k*sin(k*u)*exp(cos(k*u)) + 8*k*sin(4*k*u) - 5*pow(sin(k*u/12), 4.0)*(k/12)*cos(k*u/12);
  // BUTTERFLY RESULT PRODUCT RULE
  double dx_du   = (fxtu * d_gxtdu) + (gxtu * d_fxtdu);
  return (scaleup)*(dx_du);
*/

  }

// ==============================================
// Y-VELOCITY COMPONENT
// ==============================================
double fxn_cvel_y(double u)
  {

/*
  // ELLIPSE DY
  double scaleup = 51.0;
  double k = (2.0*PI_cvel);
  // double  y = cos(k*u);
  double dy_du = -k*sin(k*u);
  return (scaleup)*(dy_du);

*/

/*
// ===============================
 // RIBBON100L - DY

  // set xrange [-1.0:+6.0] GnuPlot
  // set yrange [-1.0:+6.0] Gnuplot
  // RANGE FOR t = [-2.00, +2.00] equivalent to u = [0.00, 1.00]
  double t = 4.0*(u - 0.50); // TRANSORMATION EQUATION

  double scaleup = 10.0;
  // double y = (t*t*t) - 3*(t) + 3;
  double dy_du = 3*(t*t) - 3;
  return (scaleup)*(dy_du);

 // ===============================

*/

  // TEARDROP DY
  double scaleup = 1.0;
  return (scaleup)*( -150.0 + 300.0*pow(u, 1.0) );

  // ===========================================
/*
  // HYPOTROCOID DY
  double scaleup = 1.0;  // 1.0 IS GOOD (OTHERS BAD)
  double k = (6.0*PI_cvel);                          // RANGE
  double y = (2*sin(k*u) - 5*sin(2*k*u/3));           // Y
  double dy_du = ( 2*k*cos(k*u) - (5*2*k/3)*cos(2*k*u/3) );  // DY
  return (scaleup)*(dy_du);
*/
  // ============================================
/*
  // EPICYCLOID DY
  double scaleup = 10.0;
  double k = (2.0*PI_cvel);                      // RANGE
  double small = 1.0e-10;
  // double y = (5*sin(k*u + small) - sin(5*k*u - small) );   // Y
  double dy =  ( 5*k*cos(k*u + small) - (5*k)*cos(5*k*u - small) );    // DY
  return (scaleup)*(dy);
*/
  // ============================================
/*
  // ASTEPI DY = ASTROID DY + EPICYCLOID DY
  double scaleup = 10.0;
  double k = (2.0 * PI_cvel);
  double small = 1.0e-10;

  double dy_ast = -4.0*(3.0)*k*pow(sin(k*u), 2.0);
  double dy_epi = 5*k*cos(k*u + small) - (5*k)*cos(5*k*u - small);
  double dy = dy_ast + dy_epi;
  return (scaleup)*(dy);
*/
// ============================================

/*
  double fxn_get_dy_snailshell (double u);

  // SNAHYP DY = SNAILSHELL DY + HYPOTROCOID DY
  double scaleup = 10.0;
  double k = (4.0 * PI_cvel);
  double small = 1.0e-10;
  double dy_sna = (10)*fxn_get_dy_snailshell(u);  // FUNCTION  CALL
  double dy_hyp = ( -2*k*sin(k*u) - (5*2*k/3)*sin(2*k*u/3) );
  double dy = dy_sna + dy_hyp;
  return (scaleup)*(dy);
*/
// ============================================
/*
  // CIRCLE DY
  double scaleup = 79.0;
  double k = (2.0*PI_cvel);
  // double  y = cos(k*u);
  double dy_du = -k*sin(k*u);
  return (scaleup)*(dy_du);
*/
// ============================================
/*
  // LINE-POLYU DY
  double scaleup = 1.0;
  // double polyu_y =  ( 150.0*pow(u, 1.0) + 150.0*pow(u, 2.0) );
  double polyu_dy = ( 150.0 + 300.0*pow(u, 1.0) );
  return (scaleup)*(polyu_dy);
*/
// ============================================
/*
  // SKEWED ASTROID DY
  double scaleup = 25.0;
  double k = (2.0*PI_cvel);
  // double y   = +4.0*pow(cos(k*u), 3.0);
  double dy_du  = -4.0*(3.0)*k*pow(sin(k*u), 2.0);
  // double d2y_du2 = -4.0*(3.0)*(2.0)*k*k*pow(cos(k*u), 1.0);
  return (scaleup)*(dy_du);
*/
// =============================================
/*
  // SNAILSHELL DY
  double scaleup = 100.0;
  double k       = (3.0*PI_cvel);

  double fytu    = cos(2*k*u);   // DIFFERENT
  double d_fytdu = -2*k*sin(2*k*u);
  double gytu    = (k*k*u*u + 4.0);
  double d_gytdu = 2*k*k*u;

  // SNAILSHELL RESULT QUOTIENT RULE
  double dy_du   = ( (fytu * d_gytdu) - (gytu * d_fytdu) )/( gytu*gytu );
  return (scaleup)*(dy_du);
*/
// ===================================================
/*
  // BUTTERFLY DY
  double scaleup = 10.0;
  double k       = (2.0*PI_cvel);

  double fytu    = cos(k*u);  // DIFFERENT
  double d_fytdu = -k*sin(k*u);
  double gytu    = exp(cos(k*u)) - 2*cos(4*k*u) - pow(sin(k*u/12), 5.0);
  double d_gytdu = - k*sin(k*u)*exp(cos(k*u)) + 8*k*sin(4*k*u) - 5*pow(sin(k*u/12), 4.0)*(k/12)*cos(k*u/12);

  // BUTTERFLY RESULT PRODUCT RULE
  double dy_du   = (fytu * d_gytdu) + (gytu * d_fytdu);
  return (scaleup)*(dy_du);
*/
  // ===================================================

}

// ==============================================
// VELOCITY MAGNITUDE
// ==============================================
double fxn_cvel_r (double u)
  {
  double temp_vx = fxn_cvel_x (u);
  double temp_vy = fxn_cvel_y (u);
  double temp_vr = sqrt(temp_vx*temp_vx + temp_vy*temp_vy);

  return ( fabs(temp_vr) );
  }
// ===================================================


// ==============================================
double fxn_get_dx_snailshell (double u)
{

  double scaleup = 1.0;     // NO SCALEUP HERE (UNITY)
  double k = (4.0*PI_cvel); // CONSTANT ONLY

  double fxtu = sin (2*k*u); // DIFFERENT
  double d_fxtdu = 2 * k * cos (2 * k * u);
  double gxtu = (k * k * u * u + 4.0);
  double d_gxtdu = 2 * k * k * u;
  // SNAILSHELL RESULT QUOTIENT RULE
  double dx_du = ((fxtu * d_gxtdu) - (gxtu * d_fxtdu)) / (gxtu * gxtu);
  return (scaleup)*(dx_du);

}

// =============================================
double fxn_get_dy_snailshell(double u)
{

  double scaleup = 1.0;
  double k       = (4.0*PI_cvel);

  double fytu    = cos(2*k*u);   // DIFFERENT
  double d_fytdu = -2*k*sin(2*k*u);
  double gytu    = (k*k*u*u + 4.0);
  double d_gytdu = 2*k*k*u;
  // SNAILSHELL RESULT QUOTIENT RULE
  double dy_du   = ( (fytu * d_gytdu) - (gytu * d_fytdu) )/( gytu*gytu );
  return (scaleup)*(dy_du);

}

// =========================================================
// ALHAMDULILLAH 3 TIMES
// =========================================================

