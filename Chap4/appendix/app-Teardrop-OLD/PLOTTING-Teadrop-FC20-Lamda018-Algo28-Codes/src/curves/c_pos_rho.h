
// File: c_pos_rho.h

#include <math.h> // for pow()

#include "c_velocity.h"
#include "c_accelern.h"

double fxn_c_radiuscurvature_rho_at_u(double u);

// ==================================================================
double fxn_c_radiuscurvature_rho_at_u(double u) {
// ==================================================================
// The curvature varies along the curve, so does the acceleration limits.

// USING THE ORIGINAL PARAMETRIC EQUATIONS (0 < u < 1)

// dx/du = -150 + 900*u - 900*u*u
// dy/du = -150 + 300*u

// d(dx/du)/du = + 900 -1800*u
// d(dy/du)/du = + 300
	
// REF: https://math24.net/curvature-radius.html
// USING THE FORMULA AT THE REF ABOVE
// From this definition it follows that the curvature at a point of a curve 
// characterizes the speed of rotation of the tangent of the curve at this point.
// Find the curvature (K) and radius of curvature (1/K) of the curve ....

// If a curve is defined in parametric form by the equations x = x(u), y = y(u)_
// then its curvature at any point is given by rho(x, y),

// rho = radiuscurvature = (1/curvature)
// curvature = (numerator / denominator)
// numerator   = fabs [(x')*(y'') - (y')*(x'')]
// denominator = [(x')*(x') + (y')*(y')] ^(3/2)

    // CALL THE ALREADY DEFINED FUNCTIONS
	// double x_prime       = fxn_dx_du(u); 
    // double y_prime       = fxn_dy_du(u); 
    // double x_doubleprime = fxn_ddx_du_du(u);
    // double y_doubleprime = fxn_ddy_du_du(u);
    
 	  double x_prime       = fxn_cvel_x(u);
    double y_prime       = fxn_cvel_y(u);
    double x_doubleprime = fxn_cacc_x(u);
    double y_doubleprime = fxn_cacc_y(u);
     

    double numerator = fabs ((x_prime)*(y_doubleprime) - (y_prime)*(x_doubleprime));
    double denominator = pow (((x_prime)*(x_prime) + (y_prime)*(y_prime)), 1.5);
    // double curvature  = (numerator/denominator);
    double rho_u      = (denominator/numerator); // Radius of curvature
    
	return (rho_u); 
}

// ==================================================================
// ALHAMDULILLAH 3 TIMES WRY
// ==================================================================

