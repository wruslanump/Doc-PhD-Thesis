// FILE: c_accelern.c

#include <math.h>         // For pow()
#include "c_accelern.h"

double const PI_cacc = 3.141592653589793238;

// ==================================================================
// X-ACCELERN COMPONENT
// ==================================================================
double fxn_cacc_x(double u)
  {
/*
  // ELLIPSE D2X
  double scaleup = 11.0;
  double k = (2.0 * PI_cacc);
  // double  x    = sin(k*u);
  // double dx_du = (+k)*cos(k*u);
  double d2x_du2 = (-k)*(+k)*sin(k*u);
  return (scaleup)*(d2x_du2);
*/


  /*
 // ===============================
 // RIBBON100L - D2X

    // set xrange [-1.0:+6.0] GnuPlot
    // set yrange [-1.0:+6.0] Gnuplot
    // RANGE FOR t = [-2.00, +2.00] equivalent to u = [0.00, 1.00]
    double t = 4.0*(u - 0.50); // TRANSORMATION EQUATION

    double scaleup = 10.0;
    // double x = (t*t);
    // double dx_du = 2*(t);
    double d2x_du2 = 2;
    return (scaleup)*(d2x_du2);

 // ===============================
*/

  // TEARDROP D2X
  double scaleup = 1.0;
  return (scaleup)*( + 900.0 - 1800.0*pow(u, 1.0) );

  // =======================================
/*
  // HYPOTROCOID D2X
  double scaleup = 1.0;   // 1.0 IS GOOD (OTHERS BAD)
  double k = (6.0*PI_cacc);                                     // RANGE
  // double x = (  2*cos(k*u)      + 5*cos(2*k*u/3));                  // X
  // double dx_du = ( -2*k*sin(k*u)    - 5*(2*k/3)*sin(2*k*u/3) );        // DX
  double d2x_du2 = ( -2*k*k*cos(k*u)  - 5*(2*k/3)*(2*k/3)*cos(2*k*u/3) ); // D2X
  return (scaleup)*(d2x_du2);
*/
  // ========================================
/*
  // EPICYCLOID D2X
  double scaleup = 10.0;
  double k = (2.0 * PI_cacc);
  double small = 1.0e-10;
  // double x =  (5*cos(k*u + small) - cos(5*k*u - small));     // X
  // double dx = ( -5*k*sin(k*u + small) + (5*k)*sin(5*k*u - small));         // DX
  double d2x =   ( -5*k*k*cos(k*u + small) + (5*k)*(5*k)*cos(5*k*u - small));  // D2X
  return (scaleup)*(d2x);
*/
// =========================================
/*
  // ASTEPI D2X = ASTROID D2X + EPICYCLOID D2X
  double scaleup = 10.0;
  double k = (2.0 * PI_cacc);
  double small = 1.0e-10;

  double d2x_ast = -4.0*(3.0)*(2.0)*k*k*pow(sin(k*u), 1.0);
  double d2x_epi = -5.0*k*k*cos(k*u + small) + (5.0*k)*(5.0*k)*cos(5*k*u - small);
  double d2x = d2x_ast + d2x_epi;
  return (scaleup)*(d2x);
*/
// ==========================================
/*
  double fxn_get_d2x_snailshell (double u);

  // SNAHYP D2X = (10)*SNAILSHELL D2X + HYPOTROCOID D2X
  double scaleup = 10.0;
  double k = (4.0 * PI_cacc);
  double small = 1.0e-10;
  double d2x_sna = (10)*fxn_get_d2x_snailshell(u);  // FUNCTION CALL
  double d2x_hyp = ( -2*k*k*cos(k*u)  - 5*(2*k/3)*(2*k/3)*cos(2*k*u/3) );
  double d2x = d2x_sna + d2x_hyp;
  return (scaleup)*(d2x);
*/
// ==========================================
/*
  // CIRCLE D2X
  double scaleup = 79.0;
  double k = (2.0 * PI_cacc);
  // double  x    = sin(k*u);
  // double dx_du = (+k)*cos(k*u);
  double d2x_du2 = (-k)*(+k)*sin(k*u);
  return (scaleup)*(d2x_du2);
*/

// ==========================================
/*
  // LINE-POLYU D2X
  double scaleup = 1.0;
  // double polyu_x =  ( 150.0*pow(u, 1.0) + 150.0*pow(u, 2.0) );
  // double polyu_dx = ( 150.0 + 300.0*pow(u, 1.0) );
  double polyu_d2x = 300.0;
  return (scaleup)*(polyu_d2x);
*/
// ===========================================
/*
  // SKEWED ASTROID D2X
  double scaleup = 10.0;
  double k = (2.0*PI_cacc);
  // double x =   +4.0*pow(sin(k*u), 3.0);
  // double dx_du =  +4.0*(3.0)*k*pow(cos(k*u), 2.0);
  double d2x_du2 = -4.0*(3.0)*(2.0)*k*k*pow(sin(k*u), 1.0);
  return (scaleup)*(d2x_du2);
*/
// ============================================
/*
  // SNAILSHELL D2X
  double scaleup = 100.0;
  double k  = (3.0*PI_cacc);

  //  dx_du = (AX/M) + (BX/M) + (CX/M)
  double AXf = (2*k*k*u);
  double AXg = sin(2*k*u);
  double AX  = AXf*AXg;
  double dAXf = (2*k*k);
  double dAXg = 2*k*cos(2*k*u);
  double dAX = (AXf*dAXg + AXg*dAXf);

  double BXf = (-2*k*k*k*u*u);
  double BXg = cos(2*k*u);
  double BX  = BXf*BXg;
  double dBXf = (-4*k*k*k*u);
  double dBXg = -2*k*sin(2*k*u);
  double dBX = (BXf*dBXg + BXg*dBXf);

  double CX = (-8*k)*cos(2*k*u);
  double dCX = (16*k*k)*sin(2*k*u);

  double M = (k*k*k*k*u*u*u*u) + (8*k*u*k*u) + 16;
  double dM = (4*k*k*k*k*u*u*u) + (16*k*k*u);

  double d2AX = (AX*dM - M*dAX)/(M*M);
  double d2BX = (BX*dM - M*dBX)/(M*M);
  double d2CX = (CX*dM - M*dCX)/(M*M);

  // SNAILSHELL RETURN
  double d2x_du2 = d2AX + d2BX + d2CX;
  return (scaleup)*(d2x_du2);
*/
// =================================================
/*
  // BUTTERFLY D2X
  double scaleup = 10.0;
  double k = (2.0 * PI_cacc);

  // ==================
  double AX  = -k*pow(sin(k*u),2)*exp(cos(k*u));
  double AXf = -k*pow(sin(k*u), 2);
  double AXg = exp(cos(k*u));
  double dAXf_du = -2*k*sin(k*u)*k;
  double dAXg_du = -sin(k*u)*k*exp(cos(k*u));

  double dAX_du = AXf*dAXg_du + AXg*dAXf_du;

  // =================
  double BX  = +8*k*sin(k*u)*sin(4*k*u);
  double BXf = +8*k*sin(k*u);
  double BXg = sin(4*k*u);
  double dBXf_du = +8*k*k*cos(k*u);
  double dBXg_du = +4*k*sin(4*k*u);

  double dBX_du = BXf*dBXg_du + BXg*dBXf_du;

  // =================
  double CX  = -5*(k/12)*sin(k*u)*cos(k*u/12)*pow(sin(k*u/12), 4);
  double CXf  = -5*(k/12)*sin(k*u)*cos(k*u/12);
  double CXff = -5*(k/12)*sin(k*u);
  double CXfg = cos(k*u/12);
  double dCXff_du = -5*(k/12)*k*cos(k*u);
  double dCXfg_du = -(k / 12) * sin (k * u / 12);
  double dCXf_du = CXff*dCXfg_du + CXfg*dCXff_du;

  double CXg = pow(sin(k*u/12), 4);
  double dCXg_du = (k/12)*cos(k*u/12)*4*pow(sin(k*u/12), 3);

  double dCX_du = CXf*dCXg_du + CXg*dCXf_du;

  // =================
  double DX  = k*cos(k*u)*exp(cos(k*u));
  double DXf = k*cos(k*u);
  double DXg = exp(cos(k*u));
  double dDXf_du = -k*k*sin(k*u);
  double dDXg_du = -k*sin(k*u)*exp(cos(k*u));

  double dDX_du = DXf*dDXg_du + DXg*dDXf_du;

  // =================
  double EX  = -2*k*cos(k*u)*cos(4*k*u);
  double EXf = -2*k*cos(k*u);
  double EXg = cos(4*k*u);
  double dEXf_du = 2*k*k*sin(k*u);
  double dEXg_du = -4*k*sin(4*k*u);

  double dEX_du = EXf*dEXg_du + EXg*dEXf_du;

  // =================
  double FX  = -k*cos(k*u)*pow(sin(k*u/12), 5);
  double FXf = -k*cos(k*u);
  double FXg = pow(sin(k*u/12), 5);
  double dFXf_du = +k*k*sin(k*u);
  double dFXg_du = 5*pow(sin(k*u/12),4)*cos(k*u/12)*(k/12);

  double dFX_du = FXf*dFXg_du + FXg*dFXf_du;

  // RETURN FOR BUTTERFLY
  // ====================
  double d2x_du2 = dAX_du + dBX_du + dCX_du + dDX_du + dEX_du + dFX_du;
  return (scaleup)*(d2x_du2);
*/
  // ======================================

}

// ==================================================================
// Y-ACCELERN COMPONENT
// ==================================================================
double fxn_cacc_y(double u)
  {

/*
  // ELLIPSE D2Y
  double scaleup = 51.0;
  double k = (2.0*PI_cacc);
  // double y     = cos(k*u);
  // double dy_du = (-k)*sin(k*u);
  double d2y_du2  = (+k)*(-k)*cos(k*u);
  return (scaleup)*(d2y_du2);
*/

 // ===============================
 // RIBBON100L - D2Y
/*
  // set xrange [-1.0:+6.0] GnuPlot
  // set yrange [-1.0:+6.0] Gnuplot
  // RANGE FOR t = [-2.00, +2.00] equivalent to u = [0.00, 1.00]
  double t = 4.0*(u - 0.50); // TRANSORMATION EQUATION

  double scaleup = 10.0;
  // double y = (t*t*t) - 3*(t) + 3;
  // double dy_du = 3*(t*t) - 3;
  double d2y_du2 = 6*(t);
  return (scaleup)*(d2y_du2);

*/
 // ===============================

  // TEARDROP D2Y
  double scaleup = 1.0;
  return (scaleup)*(+ 300.0 );

  // ===============================================
/*
  // HYPOTROCOID D2Y
  double scaleup = 1.0; // 1.0 IS GOOD (OTHERS BAD)
  double k = (6.0*PI_cacc);                                    // RANGE
  // double y = (  2*sin(k*u)     - 5*sin(2*k*u/3));                   // Y
  // double dy_du = (  2*k*cos(k*u)   - 5*(2*k/3)*cos(2*k*u/3) );          // DY
  double d2y_du2 = ( -2*k*k*sin(k*u) + 5*(2*k/3)*(2*k/3)*sin(2*k*u/3) );     // D2Y
  return (scaleup)*(d2y_du2);
*/
  // ==============================================
/*
  // EPICYCLOID D2Y
  double scaleup = 10.0;
  double k = (2.0*PI_cacc);                     // RANGE
  double small = 1.0e-10;
  // double y = (5*sin(k*u + small) - sin(5*k*u - small) );   // Y
  // double dy = ( 5*k*cos(k*u + small) - (5*k)*cos(5*k*u - small) );    // DY
  double d2y = ( -5*k*k*sin(k*u + small) + (5*k)*(5*k)*sin(5*k*u - small) );  // D2Y
  return (scaleup)*(d2y);
*/
// ==============================================
/*
  // ASTEPI D2Y = ASTROID D2Y + EPICYCLOID D2Y
  double scaleup = 10.0;
  double k = (2.0 * PI_cacc);
  double small = 1.0e-10;

  double d2y_ast = -4.0*(3.0)*(2.0)*k*k*pow(cos(k*u), 1.0);
  double d2y_epi = -5.0*k*k*sin(k*u + small) + (5*k)*(5*k)*sin(5*k*u - small);
  double d2y = d2y_ast + d2y_epi;
  return (scaleup)*(d2y);
*/
// ==============================================
/*
  double fxn_get_d2y_snailshell (double u);

  // SNAHYP D2Y = (10) SNAILSHELL D2Y + HYPOTROCOID D2Y
  double scaleup = 10.0;
  double k = (4.0 * PI_cacc);
  double small = 1.0e-10;
  double d2y_sna = (10)*fxn_get_d2y_snailshell(u);  // FUNCTION CALL
  double d2y_hyp = ( -2*k*k*sin(k*u) + 5*(2*k/3)*(2*k/3)*sin(2*k*u/3) );
  double d2y = d2y_sna + d2y_hyp;
  return (scaleup)*(d2y);
*/
// ==============================================
/*
  // CIRCLE D2Y
  double scaleup = 79.0;
  double k = (2.0*PI_cacc);
  // double y     = cos(k*u);
  // double dy_du = (-k)*sin(k*u);
  double d2y_du2  = (+k)*(-k)*cos(k*u);
  return (scaleup)*(d2y_du2);
*/
// ==============================================
/*
  // LINE-POLYU D2Y
  double scaleup = 1.0;
  // double polyu_y =  ( 150.0*pow(u, 1.0) + 150.0*pow(u, 2.0) );
  // double polyu_dy = ( 150.0 + 300.0*pow(u, 1.0) );
  double polyu_d2y = 300.0;
  return (scaleup)*(polyu_d2y);
*/
// =============================================
/*
  // SKEWED ASTROID D2Y
  double scaleup = 25.0;
  double k = (2.0*PI_cacc);
  // double y   = +4.0*pow(cos(k*u), 3.0);
  // double dy_du  = -4.0*(3.0)*k*pow(sin(k*u), 2.0);
  double d2y_du2 = -4.0*(3.0)*(2.0)*k*k*pow(cos(k*u), 1.0);
  return (scaleup)*(d2y_du2);
*/
// ===============================================
/*
    // SNAILSHELL D2Y
    double scaleup = 100.0;
    double k = (3.0*PI_cacc);

    // dy_du = (AY/M) + (BY/M) + (CY/M)
    double AYf = (2*k*k*u);
    double AYg = cos(2*k*u);
    double AY  = AYf*AYg;

    double dAYf = (2*k*k);
    double dAYg = -2*k*sin(2*k*u);
    double dAY = (AYf*dAYg + AYg*dAYf);

    double BYf = (2*k*k*k*u*u);
    double BYg = sin(2*k*u);
    double BY  = BYf*BYg;

    double dBYf = (4*k*k*k*u);
    double dBYg = 2*k*cos(2*k*u);
    double dBY = (BYf*dBYg + BYg*dBYf);

    double CY = (8*k)*sin(2*k*u);
    double dCY = (16*k*k)*cos(2*k*u);

    double M = (k*k*k*k*u*u*u*u) + (8*k*u*k*u) + 16;
    double dM = (4*k*k*k*k*u*u*u) + (16*k*k*u);

    double d2AY = (AY*dM - M*dAY)/(M*M);
    double d2BY = (BY*dM - M*dBY)/(M*M);
    double d2CY = (CY*dM - M*dCY)/(M*M);

    // SNAILSHELL RETURN
    double d2y_du2 = d2AY + d2BY + d2CY;
    return (scaleup)*(d2y_du2);

*/
// ==============================================
/*
  // BUTTERFLY D2Y
  double scaleup = 10.0;
  double k = (2.0 * PI_cacc);

  // ==================
  double AY  = -k*cos(k*u)*exp(cos(k*u));
  double AYf = -k*cos(k*u);
  double AYg = exp(cos(k*u));
  double dAYf_du = k*k*sin(k*u);
  double dAYg_du = -k*sin(k*u)*exp(cos(k*u));

  double dAY_du = AYf*dAYg_du + AYg*dAYf_du;

  // =================
  double BY  = +8*k*cos(k*u)*sin(4*k*u);
  double BYf = +8*k*cos(k*u);
  double BYg = sin(4*k*u);
  double dBYf_du = -8*k*k*sin(k*u);
  double dBYg_du = +4*k*cos(4*k*u);

  double dBY_du = BYf*dBYg_du + BYg*dBYf_du;

  // =================
  double CY   = -5*(k/12)*cos(k*u)*cos(k*u/12)*pow(sin(k*u/12), 4);
  double CYf  = -5*(k/12)*cos(k*u)*cos(k*u/12);
  double CYff = -5*(k/12)*cos(k*u);
  double CYfg = cos(k*u/12);
  double dCYff_du = +5*(k/12)*k*sin(k*u);
  double dCYfg_du = -(k/12)*sin(k*u/12);
  double dCYf_du = CYff*dCYfg_du + CYfg*dCYff_du;

  double CYg = pow(sin(k*u/12), 4);
  double dCYg_du = (k/12)*cos(k*u/12)*4*pow(sin(k*u/12), 3);

  double dCY_du = CYf*dCYg_du + CYg*dCYf_du;

  // =================
  double DY  = -k*sin(k*u)*exp(cos(k*u));
  double DYf = -k*sin(k*u);
  double DYg = exp(cos(k*u));
  double dDYf_du = -k*k*cos(k*u);
  double dDYg_du = -k*sin(k*u)*exp(cos(k*u));

  double dDY_du = DYf*dDYg_du + DYg*dDYf_du;

  // =================
  double EY  = +2*k*sin(k*u)*cos(4*k*u);
  double EYf = +2*k*sin(k*u);
  double EYg = cos(4*k*u);
  double dEYf_du = +2*k*k*cos(k*u);
  double dEYg_du = -4*k*sin(4*k*u);

  double dEY_du = EYf*dEYg_du + EYg*dEYf_du;

  // =================
  double FY  = +k*sin(k*u)*pow(sin(k*u/12), 5);
  double FYf = +k*sin(k*u);
  double FYg = pow(sin(k*u/12), 5);
  double dFYf_du = +k*k*cos(k*u);
  double dFYg_du = 5*pow(sin(k*u/12),4)*cos(k*u/12)*(k/12);

  double dFY_du = FYf*dFYg_du + FYg*dFYf_du;

  // RETURN FOR BUTTERFLY
  // ================
  double d2y_du2 = dAY_du + dBY_du + dCY_du + dDY_du + dEY_du + dFY_du;
  return (scaleup)*(d2y_du2);
*/
// =========================================

}

// ==================================================================
// ACCELERN MAGNITUDE
// ==================================================================
double fxn_cacc_r (double u)
  {
  double temp_ax = fxn_cacc_x (u);
  double temp_ay = fxn_cacc_y (u);
  double temp_ar = sqrt(temp_ax*temp_ax + temp_ay*temp_ay);

  return ( fabs(temp_ar) );
  }

// =============================================
double fxn_get_d2x_snailshell (double u)
{

  // SNAILSHELL D2X
  double scaleup = 1.0;     // NO SCALEUP HERE
  double k  = (4.0*PI_cacc);

  //  dx_du = (AX/M) + (BX/M) + (CX/M)
  double AXf = (2*k*k*u);
  double AXg = sin(2*k*u);
  double AX  = AXf*AXg;
  double dAXf = (2*k*k);
  double dAXg = 2*k*cos(2*k*u);
  double dAX = (AXf*dAXg + AXg*dAXf);

  double BXf = (-2*k*k*k*u*u);
  double BXg = cos(2*k*u);
  double BX  = BXf*BXg;
  double dBXf = (-4*k*k*k*u);
  double dBXg = -2*k*sin(2*k*u);
  double dBX = (BXf*dBXg + BXg*dBXf);

  double CX = (-8*k)*cos(2*k*u);
  double dCX = (16*k*k)*sin(2*k*u);

  double M = (k*k*k*k*u*u*u*u) + (8*k*u*k*u) + 16;
  double dM = (4*k*k*k*k*u*u*u) + (16*k*k*u);

  double d2AX = (AX*dM - M*dAX)/(M*M);
  double d2BX = (BX*dM - M*dBX)/(M*M);
  double d2CX = (CX*dM - M*dCX)/(M*M);

  // SNAILSHELL RETURN
  double d2x_du2 = d2AX + d2BX + d2CX;
  return (scaleup)*(d2x_du2);

}

// =============================================
double fxn_get_d2y_snailshell(double u)
{

    // SNAILSHELL D2Y
    double scaleup = 1.0;  // NO SCALEUP
    double k = (4.0*PI_cacc);

    // dy_du = (AY/M) + (BY/M) + (CY/M)
    double AYf = (2*k*k*u);
    double AYg = cos(2*k*u);
    double AY  = AYf*AYg;

    double dAYf = (2*k*k);
    double dAYg = -2*k*sin(2*k*u);
    double dAY = (AYf*dAYg + AYg*dAYf);

    double BYf = (2*k*k*k*u*u);
    double BYg = sin(2*k*u);
    double BY  = BYf*BYg;

    double dBYf = (4*k*k*k*u);
    double dBYg = 2*k*cos(2*k*u);
    double dBY = (BYf*dBYg + BYg*dBYf);

    double CY = (8*k)*sin(2*k*u);
    double dCY = (16*k*k)*cos(2*k*u);

    double M = (k*k*k*k*u*u*u*u) + (8*k*u*k*u) + 16;
    double dM = (4*k*k*k*k*u*u*u) + (16*k*k*u);

    double d2AY = (AY*dM - M*dAY)/(M*M);
    double d2BY = (BY*dM - M*dBY)/(M*M);
    double d2CY = (CY*dM - M*dCY)/(M*M);

    // SNAILSHELL RETURN
    double d2y_du2 = d2AY + d2BY + d2CY;
    return (scaleup)*(d2y_du2);

}

// ==================================================================
// ALHAMDULILLAH 3 TIMES
// ==================================================================
