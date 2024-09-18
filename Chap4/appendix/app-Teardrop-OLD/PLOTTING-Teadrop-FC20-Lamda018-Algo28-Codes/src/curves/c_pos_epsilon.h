
// FILE: c_pos_epsilon.h

#include <math.h> // for pow()

// GLOBAL ARRAYS FOR SUBDIVISIONS BETWEEN u AND u_next
// ==================================================================
const int array_size1 = 21;
double arc_u_points[21]; // AVOID WARNINGS INSTEAD OF arc_u_points[];
double arc_x_points[21];
double arc_y_points[21]; 
double perpend_y_intercept[21];
double chord_x_commpoints[21];
double chord_y_commpoints[21]; 
double x_error[21];        
double y_error[21];        
double chord_error[21];   

double fxn_max_element_array(double thearray[], int array_size);
double fxn_min_element_array(double thearray[], int array_size);
void proc_initialize_zero_all_arc_arrays(int arr_size);
void proc_populate_arc_array_points(double u, double u_next, double  arc_u_points[], double arc_x_points[],  double arc_y_points[]) ;

double fxn_c_epsilon_for_arc_u_to_u_next(double u, double u_next, double  arc_u_points[], double arc_x_points[],  double arc_y_points[]);

// ==================================================================
double fxn_max_element_array(double thearray[], int array_size) {
// ==================================================================2021-12-15-WOM-function
    	int i;
    	double the_max;
    	the_max = thearray[0];
    	for (i = 1; i < array_size; i++) {
            if (thearray[i] > the_max) { 
               the_max = thearray[i];;
            }    		   
    	}
    	
return (the_max);
}

// ==================================================================
double fxn_min_element_array(double thearray[], int array_size) {  
// ==================================================================
    	int i;
    	double the_min;
    	the_min = thearray[0];
    	for (i = 1; i < array_size; i++) {
            if (thearray[i] < the_min) { 
               the_min = thearray[i];;
            }    		   
    	}
    	
return (the_min);
}  

// ==================================================================
void proc_initialize_zero_all_arc_arrays(int arr_size) {
// ==================================================================
	int j;
	for (j = 0; j <= arr_size-1; j++ ) {
		
		// GLOBAL ARRAYS
		arc_u_points[j] = 0.0;
		arc_x_points[j] = 0.0;
		arc_y_points[j] = 0.0;
        perpend_y_intercept[j] = 0.0;
		chord_x_commpoints[j]  = 0.0;
		chord_y_commpoints[j]  = 0.0; 
		x_error[j]    = 0.0;        
		y_error[j]    = 0.0;        
		chord_error[j] = 0.0;     		
	}

} 

// =================================================================
double fxn_x(double u) {
	return ( -150*pow(u, 1.0) + 450*pow(u, 2.0) - 300*pow(u, 3.0) ); 
} 
// =================================================================
double fxn_y(double u) {
	return ( -150*pow(u, 1.0) + 150*pow(u, 2.0) ); 
} 

// ==================================================================
void proc_populate_arc_array_points(double u, double u_next, double  arc_u_points[], double arc_x_points[],  double arc_y_points[]) {
// ==================================================================

    // IMPORTANT TO SET ZEROS
	proc_initialize_zero_all_arc_arrays(array_size1);
	
	// ENFORCE START-POINT OF CURVE-ARC INDEX [0]
	arc_u_points[0] = u;
	arc_x_points[0] = fxn_x(u);
	arc_y_points[0] = fxn_y(u);
	
	// Number of sub-divisions on curve-arc between [u:u_incr]
	int u_subdivisions = (array_size1 - 1);	
		
	// X-Y points for each subdivisions	built from start of curve-arc
	// Start index from [1] not [0]
	int j;
    for (j = 1; j <= array_size1-1; j++) {
	     arc_u_points[j] = arc_u_points[0] + j*(u_next/u_subdivisions);
	     arc_x_points[j] = fxn_x(arc_u_points[j]);
	     arc_y_points[j] = fxn_y(arc_u_points[j]);	     
	  }
	
    // ENFORCE END-POINT OF CURVE-ARC AT INDEX [array_size-1]
    arc_u_points[array_size1-1] = (u + u_next);
	  arc_x_points[array_size1-1] = fxn_x(u + u_next);
	  arc_y_points[array_size1-1] = fxn_y(u + u_next);
	
	// PRINT FOR CHECKING
	// for (j = 0; j < array_size1; j++) {
    //     printf("ARC ARRAYS  j, arc_u_points[j], arc_x_points[j], arc_y_points[j] [ %d]  %15.11lf  %15.11lf %15.11lf \n", j, arc_u_points[j], arc_x_points[j], arc_y_points[j]);
	// }

}

// ==================================================================
double fxn_c_epsilon_for_arc_u_to_u_next(double u, double u_next, double  arc_u_points[], double arc_x_points[],  double arc_y_points[]) {
// ==================================================================
  int j, k;
	double the_epsilon = 0.0; // Initialize
	//printf("CHECK CHORD ENDPOINTS u, u_incr %15.11lf %15.11lf \n", u, u_next);

  // FILL UP THE ARC ARRAYS BETWEEN u AND u_next
  proc_populate_arc_array_points(u, u_next, arc_u_points, arc_x_points,  arc_y_points); 
    
  // FOR TESTING ONLY
  // proc_populate_arc_array_points(0.160, 0.000100, arc_u_points, arc_x_points,  arc_y_points); 

  // SLOPE FOR THE CHORD (STRAIGHT LINE) BETWEEN u AND u_next
	double deta_y = arc_y_points[array_size1-1] - arc_y_points[0];   // CORRECT
	double deta_x = arc_x_points[array_size1-1] - arc_x_points[0];   // CORRECT
	double chord_slope = deta_y/deta_x;

	// USING CHORD LINE Y-INTERCEPT FOR LINE (x1,y1) TO (x2, y2)
	// y_intercept1 = y1 - slope * x1;
	// y_intercept2 = y2 - slope * x2;

	// CALCULATE CHORD LINE Y-INTERCEPT 
	double chord_y_intercept = arc_y_points[array_size1-1] - (chord_slope)*arc_x_points[array_size1-1];

	// CALCULATE PERPENDICULAR LINE SLOPE TO THE CHORD 
	double perpend_slope = (-1.0/chord_slope);  

	// CALCULATE THE CROSSING POINT (x_comm, y_comm) OF PERPENDICULAR LINE TO THE CHORD LINE
	// SATISFYING THE PERPENDICULAR LINE EQUATION FOR THE CURVE POINT (x, y)
	// END POINTS OF CHORD ARE [0] AND [10] SO CALCULATE (1 .. 9) ONLY
	for (j = 0; j < array_size1; j++) {   
		
		perpend_y_intercept[j] = arc_y_points[j] - (perpend_slope)*(arc_x_points[j]); 
		chord_x_commpoints[j] = (perpend_y_intercept[j] - chord_y_intercept)/(chord_slope - perpend_slope);
		chord_y_commpoints[j] = (chord_slope)*(chord_x_commpoints[j]) + chord_y_intercept;
	  
		// FOR CHECKING	
		// printf("[%d]   %15.11lf %15.11lf %15.11lf \n", j, perpend_y_intercept[j], chord_x_commpoints[j], chord_y_commpoints[j]);
	} 

	for (k = 1; k < array_size1-1; k++) {   

		x_error[k] = (arc_x_points[k] - chord_x_commpoints[k]);
		y_error[k] = (arc_y_points[k] - chord_y_commpoints[k]);
		chord_error[k] = fabs(sqrt(x_error[k]*x_error[k] + y_error[k]*y_error[k]));
		
// FOR CHECKING
// printf("%15.6lf [%d] %15.12lf %15.12lf %15.12lf  %15.12lf %15.12lf %15.12lf %15.12lf \n", u+k*(u_next/20.0), k, arc_x_points[k], arc_y_points[k], chord_x_commpoints[k], chord_y_commpoints[k], x_error[k], y_error[k], chord_error[k]);
		
    } 

    // ENFORCE CURVE-ARC AND CHORD-LINE CROSSING POINTS
    x_error[0]  = 0.0;  y_error[0]  = 0.0;  chord_error[0]  = 0.0;
    x_error[array_size1-1] = 0.0;  y_error[array_size1-1] = 0.0;  chord_error[array_size1-1] = 0.0;

	  the_epsilon = fxn_max_element_array(chord_error, array_size1); 

return (the_epsilon);
}

// ==================================================================
// ALHAMDULILLAH 3 TIMES WRY
// ==================================================================

