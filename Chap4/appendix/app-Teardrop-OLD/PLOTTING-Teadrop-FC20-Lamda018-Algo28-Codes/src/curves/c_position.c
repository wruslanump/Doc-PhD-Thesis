
// FILE: c_position.c
#include <math.h>

#include "curves/c_position.h"
#include "curves/c_pos_epsilon.h"
#include "curves/c_pos_rho.h"

double const PI_cpos = 3.141592653589793238;

double cu_step;
double chorderror_tolerance;

// ==================================================================
// X-POSITION COMPONENT
// ==============================================
double fxn_cpos_x(double u) 
  {
/*
// ELLIPSE X
  double scaleup = 11.0;
  double k = (2.0 * PI_cpos);
  double x = sin(k*u);
  return (scaleup)*(x);
*/
    /*
    // ===============================
    // RIBBON100L - X AXIS
    // FOR RIBBON10L, CHANGE scaleup = 1.0 

  // set xrange [-1.0:+6.0] GnuPlot
  // set yrange [-1.0:+6.0] Gnuplot
  // RANGE FOR t = [-2.00, +2.00] equivalent to u = [0.00, 1.00]
  double t = 4.0*(u - 0.50); // TRANSORMATION EQUATION
 
  double scaleup = 10.0;
  double x = (t*t);
  return (scaleup)*(x);
*/
 // ===============================

 
  // TEARDROP X
  double scaleup = 1.0;
  return (scaleup)*( -150.0*pow(u, 1.0) + 450.0*pow(u, 2.0) - 300.0*pow(u, 3.0) );

// ================================
/*
  // HYPOTROCOID X
  double scaleup = 1.0;     // 1.0 IS GOOD (OTHERS BAD)
  double k = (6.0*PI_cpos);
  double x = (2*cos(k*u) + 5*cos(2*k*u/3));
  return (scaleup)*(x);
*/
// ================================
/*  
  // EPICYCLOID X
  double scaleup = 10.0;
  double k = (2.0 * PI_cpos);
  double small = 1.0e-10; 
  double x =  (5*cos(k*u + small) - cos(5*k*u - small));     // X
  return (scaleup)*(x);
*/
// =================================
/*
 // ASTEPI X = ASTROID X + EPICYCLOID X
  double scaleup = 10.0;
  double k = (2.0 * PI_cpos);
  double small = 1.0e-10;

  double x_ast = +4.0*pow(sin(k*u), 3.0);
  double x_epi = +5.0*cos(k*u + small) - cos(5*k*u - small); 
  double x = x_ast + x_epi;
  return (scaleup)*(x);
*/
// =================================
/*
  // SNAHYP X = SNAILSHELL X + HYPOTROCOID
  double scaleup = 10.0;
  double k = (4.0 * PI_cpos);
  double small = 1.0e-10;
  double x_sna = (4.0)*( sin(2*k*u) / (k*u*k*u + 4.0) );
  double x_hyp = (2*cos(k*u) + 5*cos(2*k*u/3));
  double x = x_sna + x_hyp;
  return (scaleup)*(x);
*/
// =================================
/* 
  // CIRCLE X
  double scaleup = 79.0;
  double k = (2.0 * PI_cpos);
  double x = sin(k*u);
  return (scaleup)*(x);
*/
// ==================================
/*
  // LINE-POLYU X
  double scaleup = 1.0;
  double polyu_x = ( 150.0*pow(u, 1.0) + 150.0*pow(u, 2.0) );
  return (scaleup)*(polyu_x);
*/
// ==================================
/*
    // https://en.wikipedia.org/wiki/Astroid
    // SKEWED ASTROID X
    double scaleup = 10.0;
    double k = (2.0 * PI_cpos);
    double x =   +4.0*pow(sin(k*u), 3.0);
    // double dx_du =  +4.0*(3.0)*k*pow(cos(k*u), 2.0);
    // double d2x_du2 = -4.0*(3.0)*(2.0)*k*k*pow(sin(k*u), 1.0);
    return (scaleup)*(x);
*/
  
// ===================================
/*
  // SNAILSHELL X
  double scaleup = 100.0;
  double k = (3.0*PI_cpos);
  double x = ( sin(2*k*u) / (k*u*k*u + 4.0) );
  return (scaleup)*(x);
*/
// ===================================
/* 
  // BUTTERFLY X
  double scaleup = 10.0;
  double k = (2.0*PI_cpos);
  double x = ( sin(k*u) * ( exp(cos(k*u))  - 2*cos(4*k*u) - pow(sin(k*u/12), 5.0) ));
  return (scaleup)*(x);
*/

} 
// ==================================================================
// Y-POSITION COMPONENT
// ==================================================================
double fxn_cpos_y (double u)
  {

/*

 // ELLIPSE Y
  double scaleup = 51.0;
  double k = (2.0 * PI_cpos);
  double y = cos(k*u);
  return (scaleup)*(y);
*/
  /* 
    
  // ===============================  
  // RIBBON100L - Y AXIS
  // set xrange [-1.0:+6.0] GnuPlot
  // set yrange [-1.0:+6.0] Gnuplot
  // RANGE FOR t = [-2.00, +2.00] equivalent to u = [0.00, 1.00]
  double t = 4.0*(u - 0.50); // TRANSORMATION EQUATION

  double scaleup = 10.0;
  double y = (t*t*t) - 3*(t) + 3;
  return (scaleup)*(y);

 // ===============================
*/
 
  // TEARDROP Y
  double scaleup = 1.0;
  return (scaleup)*( -150.0*pow(u, 1.0) + 150.0*pow(u, 2.0) );

  // =================================
/*
  // HYPOTROCOID Y
  double scaleup = 1.0;    // 1.0 IS GOOD (OTHERS BAD)
  double k = (6.0*PI_cpos);
  double y = (2*sin(k*u) - 5*sin(2*k*u/3));
  return (scaleup)*(y);
*/
  // ==================================  
/*
  // EPICYCLOID Y
  double scaleup = 10.0;
  double k = (2.0*PI_cpos);                      // RANGE
  double small = 1.0e-10;
  double y = ( 5*sin(k*u + small) - sin(5*k*u - small) );    // Y
  return (scaleup)*(y);
*/
// ==================================
/*
// ASTEPI Y = ASTROID Y + EPICYCLOID Y
  double scaleup = 10.0;
  double k = (2.0 * PI_cpos);
  double small = 1.0e-10;

  double y_ast = +4.0*pow(cos(k*u), 3.0);
  double y_epi = +5.0*sin(k*u + small) - sin(5*k*u - small) ;
  double y = y_ast + y_epi;
  return (scaleup)*(y);
*/
// ==================================
/*
  // SNAHYP Y = (10)*SNAILSHELL Y + HYPOTROCOID Y
  double scaleup = 10.0;
  double k = (4.0 * PI_cpos);
  double small = 1.0e-10;
  double y_sna = (10)*(cos(2*k*u) / (k*u*k*u + 4.0));
  double y_hyp = (2*sin(k*u) - 5*sin(2*k*u/3));
  double y = y_sna + y_hyp;
  return (scaleup)*(y);
*/
// ==================================
  /*
   // CIRCLE Y
    double scaleup = 79.0;
    double k = (2.0 * PI_cpos);
    double y = cos(k*u);
    return (scaleup)*(y);

*/
// ==================================
/*
  // LINE-POLYU Y
  double scaleup = 1.0;
  double polyu_y = ( 150.0*pow(u, 1.0) + 150.0*pow(u, 2.0) );
  return (scaleup)*(polyu_y);
*/
// ==================================
/*
  // SKEWED ASTROID Y
  double scaleup = 25.0;
  double k = (2.0*PI_cpos);
  double y   = +4.0*pow(cos(k*u), 3.0);
  // double dy_du  = -4.0*(3.0)*k*pow(sin(k*u), 2.0):
  // double d2y_du2 = -4.0*(3.0)*(2.0)*k*k*pow(cos(k*u), 1.0):
  return (scaleup)*(y);
*/
// ===================================
/*
  // SNAILSHELL Y
  double scaleup = 100.0;
  double k = (3.0*PI_cpos);
  double y = (cos(2*k*u) / (k*u*k*u + 4.0));
  return (scaleup)*(y);
*/
// ====================================
/*
  // BUTTERFLY Y
  double scaleup = 10.0;
  double k = (2.0*PI_cpos);
  double y = ( cos(k*u)*( exp(cos(k*u)) -2*cos(4*k*u) - pow(sin(k*u/12), 5.0)));
  return (scaleup)*(y);
*/
  
  }

// ==============================================  
// R-POSITION VECTOR RADIUS OR MAGNITUDE
// ==============================================
double fxn_cpos_r (double u)
  {
  double temp_px = fxn_cpos_x (u);
  double temp_py = fxn_cpos_y (u);
  double temp_pr = sqrt(temp_px*temp_px + temp_py*temp_py);
  
  return ( fabs(temp_pr) ); 
  }


// ==============================================
double fxn_cpos_magn(double u) {
	return (fxn_cpos_r(u));
}


// X-POSITION UNIT VECTOR
// ==============================================
double fxn_cpos_uvect_x(double u) {
	return (fxn_cpos_x(u)/fxn_cpos_r(u));
}

// Y-POSITION UNIT VECTOR
// ==============================================
double fxn_cpos_uvect_y(double u) {
	return (fxn_cpos_y(u)/fxn_cpos_r(u));
}

// ANGLE POSITION VECTOR IN RADIANS COUNTER-CLOCKWISE 
// ==============================================
double fxn_cpos_theta_rad(double u) {
	return (atan(fxn_cpos_y(u)/fxn_cpos_x(u)));
}

// ANGLE POSITION VECTOR IN DEGREES 
// ===============================================
double fxn_cpos_theta_deg(double u) {
	return ( fxn_cpos_theta_rad(u)*(180.0/PI_cpos) );
}

// POSITION CHORD ERROR = EPSILON  
// =================================================
double fxn_cpos_epsilon(double u, double u_next) {

   double the_epsilon = fxn_c_epsilon_for_arc_u_to_u_next(u, u_next, arc_u_points, arc_x_points,  arc_y_points);
	return (the_epsilon);
}

// POSITION RADIUS OF CURVATURE = RHO 
// =================================================
double fxn_cpos_rho(double u) {

    // FUNCTION DEFINED IN cpos_rho.h HEADER FILE
	return (fxn_c_radiuscurvature_rho_at_u(u)); 
}

// POSITION CURVATURE OF THE CURVE = K = (1.0/RHO)
// =================================================
double fxn_cpos_curvature(double u) {

 	return ( 1.0/fxn_cpos_rho(u) );
}

// ==================================================================
double fxn_calc_deltaS_use_rho_eps (double u, double u_next)
// ==================================================================
{
  double deltaS;

  double the_rho = fxn_cpos_rho(u + (u_next/2.0));
  double the_eps = fxn_cpos_epsilon(u, u_next);
  double temp1 = (the_rho*the_rho) - (the_rho - the_eps)*(the_rho - the_eps);
  deltaS = (2.0)*pow(temp1, 0.5);

  return (deltaS); // should be equivalent to chordlength
 } 
// ==================================================================
double fxn_calc_chordlength_use_paramcurve (double u, double u_next)
// ==================================================================
{
  double chordlength;
  double x1, x2, y1, y2;

  // Use param curve and geometry
  x1 = fxn_cpos_x (u);
  y1 = fxn_cpos_y (u);
  x2 = fxn_cpos_x(u+u_next);
  y2 = fxn_cpos_y(u+u_next);

  chordlength = fabs (sqrt (pow ((x2 - x1), 2.0) + pow ((y2 - y1), 2.0)));

  return (chordlength); // should be equivalent to deltaS
}

// ==================================================================
double fxn_calc_eps_use_paramcurve (double u, double u_next)
// ==================================================================
{
   double the_eps;

   // FULL CODES INSIDE:
   // curves/c_position.h and curves/c_pos_epsilon.h

   the_eps = fxn_cpos_epsilon(u, u_next);

   // Manual calculation geometrically using parametric curve.
   // Find position of chord endpoints (x1,y1) and (x2,y2) for parameter
   // at u and u+u_next, respectively.
   // Divide the chord into 20 linear segments of equal length.
   // At each point on the divided segment, construct a perpendicular
   // line to the chord. Find the intersection point of this perpendicular
   // line to the curve (arc). Calculate the distance from the point
   // on the chord to the curve. The value of epsilon is the maximum of
   // the 20 distances calculated.

   return (the_eps);
}

// ==================================================================
double fxn_calc_rho_use_paramcurve (double u, double u_next)
// ==================================================================
{
   double the_rho;

   // FULL CODES INSIDE:
   // curves/c_position.h and curves/c_pos_epsilon.h

   // REF: https://math24.net/curvature-radius.html
   // USING THE FORMULA AT THE REF ABOVE
   the_rho = fxn_cpos_rho(u);

   return (the_rho);

}
// ==================================================================
double fxn_calc_deg_to_rad(double angle_deg);
double fxn_calc_deg_to_rad(double angle_deg)
{
double result = angle_deg*(PI_cpos/180.0);
return(result);
}
// ==================================================================

double fxn_calc_rad_to_deg(double angle_rad)
{
	double result = angle_rad*(180.0/PI_cpos);
return(result);
}

// REFERENCE:
// https://www.engineersedge.com/math/circular_segment_equation_and_calculator__13796.htm
// ==================================================================
double fxn_calc_arc_length(int N, double u, double u_next, double chord_length, double eps, double rho)
// ==================================================================
{

  // LOCAL VARIABLES
  double arc_length = 0.0;

  // CHECK INPUT PARAMETERS
  // printf ("GOOD FXN DEBUG: N \t\t\t= %d \n", N);
  // printf ("GOOD FXN DEBUG: u \t\t\t= %lf \n", u);
  // printf ("GOOD FXN DEBUG: u_next \t\t= %lf \n", u_next);
  // 
  // printf ("GOOD FXN DEBUG: chord_length \t\t= %.12e \n", chord_length);
  // printf ("GOOD FXN DEBUG: eps \t\t\t= %.12e \n", eps);
  // printf ("GOOD FXN DEBUG: rho \t\t\t= %.12e \n", rho);


  // RAW GEOMETRIC CALCULATION ARC LENGTH OF PARAMETRIC CURVES
   double dx_du = fxn_cvel_x(u);
   double dy_du = fxn_cvel_y(u);
   double sumsquare = (dx_du)*(dx_du) + (dy_du)*(dy_du);
   double arc_length0 = (u_next)*sqrt(sumsquare);

// printf("arc_length0 \t\t\t= %.12e \n", arc_length0);
// isnan (arc_length0) 
//      ? printf ("arc_length0 is NaN \t\t= Not a Number \n") 
//      : printf ("arc_length0 is \t\t= REAL \n");
   
   arc_length = fabs(arc_length0);
  
return (arc_length);
}

// ==================================================================
double fxn_calc_arc_theta(int N, double u, double chord_length, double eps, double rho)
// ===================================================================
{
  // CHECK INCOMING VALUES
  // printf("GOOD arc_theta: chord_length \t\t= %.12e \n", chord_length);
  // printf("GOOD arc_theta: eps \t\t\t= %.12e \n", eps);
  // printf("GOOD arc_theta: rho \t\t\t= %.12e \n", rho);
     
   double arc_theta = 0.0; 
   double arg_arcsine = chord_length/(2.0*rho);
  
   // printf("DEBUG: arg_arcsine = %lf \n", arg_arcsine );
   if ( (arg_arcsine < -1.0) || (arg_arcsine > +1.0) ) 
   {
      printf("ERROR ERROR ERROR: Angle_theta: arg_arcsine is out of range [-1.0 : +1.0] arg_arcsine = %.12e \n", arg_arcsine );
   } else {
      arc_theta = 2.0*asin(arg_arcsine);
      // printf("GOOD FXN OUTPUT: Angle arc_theta \t= %.12e (rad) \n", arc_theta);
   }

return(arc_theta);
}


// ==================================================================
double fxn_calc_arc_area(int N, double u, double chord_length, double eps, double rho)
// ===================================================================
{

   // CHECK INCOMING VALUES
   // printf("GOOD arc_area: chord_length \t\t= %.12e \n", chord_length);
   // printf("GOOD arc_area: eps \t\t\t= %.12e \n", eps);
   // printf("GOOD arc_area: rho \t\t\t= %.12e \n", rho);

   double arc_area = 0.0;

   // CALLING A FUNCTION
   double arc_theta = fxn_calc_arc_theta(N, u, chord_length, eps, rho);
   // printf("GOOD arc_area: arc_theta \t\t= %.12e \n", arc_theta);
   // printf("GOOD arc_area: sin(arc_theta) \t\t= %.12e \n", sin(arc_theta));

   double DIFF = arc_theta - sin (arc_theta);
   // printf ("GOOD arc_area: DIFF \t\t\t= %.12e \n", DIFF);
   // printf ("GOOD arc_area: rho*rho/2 \t\t= %.12e \n", rho*rho/2);
      
   // CALC ARC AREA
   arc_area = (rho*rho)/2 * (DIFF);
   // printf("GOOD FXN OUTPUT: arc_area \t\t= %.12e (mm2) \n", arc_area);
   
  
return(arc_area);
}




// ==================================================================
// ALHAMDULILLAH WRY.
// ==================================================================


