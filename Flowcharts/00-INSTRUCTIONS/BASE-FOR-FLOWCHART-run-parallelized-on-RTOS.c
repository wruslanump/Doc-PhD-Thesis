
// File : 01-run-algorithm-current-min-mac.c

// wruslan@HPElBk8570w-rt-work:~/WOM-WRY-UMP-PhD/current$ date
// Sun 26 Dec 2021 01:07:30 PM +08

// PARALLEL RUNS HIRES TIMING
// TO CONTINUE AT proc_algo_position_min_max() function at same (step_u, u_next, u); 

// ********* To build a flowchart *****IMPORTANT
// ********** RUN Realtime OS ************************
// ********* Run parallel CPU writes (position, velocity, accelern) at same 
// ********* (step_u, u_next, u); 
// ********  Run parallel processing algorithms at same (step_u, u_next, u); 
// ********  Run live array buffers current 5 points forward / backwards
// at same (step_u, u_next, u); How for forward? Backwards OK.
// 
// ==================================================================
// PARAMETRIC CURVE FUNCTIONS AND VECTORS
// ==================================================================
// FOR POINT POSITION ON THE PARAMETRIC CURVE => C(u) = (x(u), y(u)) 
// FOR ANY 0.0 <= u <= 1.0
// x(u) = fxn_cpos_x(u) = ( -150*pow(u, 1.0) + 450*pow(u, 2.0) - 300*pow(u, 3.0) ); 
// y(u) = fxn_cpos_y(u) = ( -150*pow(u, 1.0) + 150*pow(u, 2.0) );

// dx(u)/du = fxn_cvel_x(u) = ( -150 + 900*pow(u, 1.0) - 900*pow(u, 2.0) ); 
// dy(u)/du = fxn_cvel_y(u) = ( -150 + 300*pow(u, 1.0) ); 

// d(dx(u)/du)/du = fxn_cacc_x(u) = ( 900 - 1800*pow(u, 1.0) ); 
// d(dy(u)/du)/du = fxn_cacc_y(u) = (300); 

// VECTOR cposition(u) = x(u) ^i + y(u) ^j
// VECTOR cvelocity(u) = dx(u)/du ^i + dy(u)/du ^j
// VECTOR caccelern(u) = d(dx(u)/du)/du ^i + d(dy(u)/du)/du ^j    

// cposition(u) = fxn_cpos_x(u) ^i + fxn_cpos_y(u) ^j
// cvelocity(u) = fxn_cvel_x(u) ^i + fxn_cvel_y(u) ^j
// caccelern(u) = fxn_cacc_x(u) ^i + fxn_cacc_y(u) ^j

// =======================================================

#include <stdio.h>  // open(), printf(), fopen(), fprintf();
#include <stdlib.h> // atoi(), system(), rand(), 
#include <string.h> // strtok(), strcpy()
#include <unistd.h>
#include <math.h>   // abs(), fabs(), sqrt()  
#include <stdbool.h> // boolean variables
#include <time.h>    // for random number seed srand()

// ORDER OF INCLUDE LOCAL HEADERS BELOW IS CRITICAL
// LATER FILES REQUIRE PREVIOUS FILES 



#include "include/cpos_rho.h"       // DONE
#include "include/cpos_epsilon.h"   // DONE

#include "include/cposition.h"      // DONE
#include "include/cvelocity.h"      // DONE
#include "include/caccelern.h"      // DONE

#include "include/algo_min_max.h"   // TO DO
#include "include/algo_decision.h"  // TO DO

#include "include/curve_datafiles.h"    // DONE
#include "include/run_datafiles.h"      // TO DO WITH DECISION ALGORITHM

#include "include/plot_2d_3d_polard_cposition.h" // DONE
#include "include/plot_2d_3d_polard_cvelocity.h" // PARTIALLY DONE
#include "include/plot_2d_3d_polard_caccelern.h" // TO DO

// FOR <math.h> MUST COMPILE WITH -lm LINK

// ==================================================================
// GLOBAL VARIABLES FOR MAIN PROGRAM
// ==================================================================
bool loop_u_done;

double u;          // General u parameter independent variable 
double u_incr;     // Used in general u increment calculations
double u_next;     // Used in decision making algorithm for next u value to process.
int    step_u;     // The integer number of incremental steps (jump) forward for u.
double u_start  = 0.000000; // Parameter u is strictly 0.0 <= u <= 1.0
double u_ended  = 1.000000;

/* INTERPRETATION EXAMPLE 
Consider the sequence u = (0.00, 0.01, 0.02, .. 1.00) with fixed u_incr = 0.01 .
Assume in the the algorithm, that at a certain u point, the decision is to set 
the number of steps forward (jump) for u is 3. So step_u = 3

    u_next = (step_u)*(u_incr);
    u = u + u_next;   
      
This new u is next point to be processed. Note that the type step_u is integer
while u_next is double.
*/

// ==================================================================
int main(int argc, char *argv[]) {
// ==================================================================
printf("Bismillah \n");

    // OPEN DATA FILES FOR WRITING (REPLACE PREVIOUS DATA)
    // OPEN THE PARAMETRIC CURVE DATAFILES
    FHdata_curve_cposition = fopen("data_curve_cposition.txt", "w+");
    FHdata_curve_cvelocity = fopen("data_curve_cvelocity.txt", "w+");
    FHdata_curve_caccelern = fopen("data_curve_caccelern.txt", "w+");
    
    // OPEN THE RUN DATAFILES
    FHdata_run_rposition = fopen("data_run_rposition.txt", "w+");
    FHdata_run_rvelocity = fopen("data_run_rvelocity.txt", "w+");
    FHdata_run_raccelern = fopen("data_run_raccelern.txt", "w+");
  	
  	// RUN ONLY ONCE
  	// For current 54-min-max variables (18 x 3) cpos, cvel and cacc.
  	proc_initialize_all_zeros_for_min_max(); 
  	
  	
	// NOTE: FOR EACH VECTOR DEBUG PRINT TO SCREEN, 
	// THERE ARE 4 LOCATIONS TO ENABLE debug print (UNCOMMENT). 
	// PART 1/4 UNTIL PART 4/4
	// UNCOMMENT EACH OF THE APPROPRIATE VECTORS. 
	// VECTORS ARE (POSITION, VELOCITY, ACCELERN)
	
	// PRINT TO SCREEN - PART 1/4 (FOR DEBUGGING)
	// print_header_cposition_data(FHdata_curve_cposition); 
 	// print_header_cvelocity_data(FHdata_curve_cvelocity); 
 	// print_header_caccelern_data(FHdata_curve_caccelern);
 	
 	// WRITE TO FILE (NO NEED TO DISABLE)
	write_header_cposition_data(FHdata_curve_cposition); 
    write_header_cvelocity_data(FHdata_curve_cvelocity);
    write_header_caccelern_data(FHdata_curve_caccelern);
 
	// PROCESS LOOP USING VECTOR-VALUED PARAMETER CURVE EQUATION
	// INITIALIZE 
		loop_u_done = false;
		u = 0.00000000;
		u_incr = 0.00017;   // FIXED BUT CHANGEABLE TO SEE EFFECTS
		
    // INTEGER STEPS THAT DETERMINES u_next ON THE CURVE
		step_u = 1;      // DEFAULT BUT CHANGEABLE BY DECISION ALGORITHM
		u_next = (step_u)*(u_incr); 

	// ==============================================================
    // WHILE LOOP U IS NOT DONE 
    // ==============================================================
    while (! loop_u_done) {   
          
        // BASED ON PARAMETRIC CURVE, PROCESS FUNCTIONS AT POINT u
        // ========================================================== 
        
        // PRINT TO SCREEN - PART 2/4
        // print_data_curve_cposition(step_u, u_next, u);  
        // print_data_curve_cvelocity(step_u, u_next, u);
        // print_data_curve_caccelern(step_u, u_next, u);
		
		// WRITE TO FILE (NO NEED TO DISABLE)   
		write_data_curve_cposition(step_u, u_next, u); 
		write_data_curve_cvelocity(step_u, u_next, u);
		write_data_curve_caccelern(step_u, u_next, u);
        
        // BASED ON ALGORITHM, PROCESS FUNCTIONS AT POINT u
        // THEN RUN CNC MACHINE TO THE NEXT (x, y) POINT 
        // ========================================================== 
        // write_data_runtime_rposition(step_u, u_next, u);
        // write_data_runtime_rvelocity(step_u, u_next, u);
        // write_data_runtime_raccelern(step_u, u_next, u);

		// DATA COMPARISONS PARAMETRIC CURVE VERSUS RUNTIME
		// ==========================================================
		// compare_curve_vs_runtime_data_position(step_u, u_next, u);
		// compare_curve_vs_runtime_data_velocity(step_u, u_next, u);
		// compare_curve_vs_runtime_data_accelern(step_u, u_next, u);

        // ALGORITHM DECIDES ON step_u (INTEGER)
        // ==========================================================
        // AS AN EXAMPLE ONLY, CALL A DECISION ALGORITHM
        // SEE HEADER algorithm_decision.h
        
        // Inside header algo_min_max.h
        proc_algo_min_max(step_u, u_next, u);  
        
        // Inside header algo_decision.h
        step_u = fxn_test_decision(step_u, u_next, u, fxn_cpos_x(u));  
        
        // FORCE TEST CONSTANT STEP_U = 1 TO SEE EFFECT ON epsilon(u)
        // FOR u VERSUS epsilon(u) PLOT 
        // step_u = 1;
             
        // UTILIZE NEWLY FOUND step_u FROM ALGORITHM     
        u_next = (step_u)*(u_incr);   
        u = u + u_next;
  
        // LOOP ALREADY PASSED OVER END-POINT, PROCESS JUST LAST POINT
        // ==========================================================
	    if (u >= u_ended) {  
	    	loop_u_done = true; // NOW LOOP U IS DONE 
	        u = u_ended; 		// FORCE u BACKWARD TO EXACT END POINT  
	        u_next = 0.00000;   // NO MORE INCREMENT
	        step_u = 0;			// NUMBER OF STEPS OF u_incr JUMP
	                 
            // PRINT TO SCREEN - PART 3/4 (FOR DEBUGGING)
            // print_data_curve_cposition(step_u, u_next, u);  
            // print_data_curve_cvelocity(step_u, u_next, u);
            // print_data_curve_caccelern(step_u, u_next, u);
            
            // WRITE TO FILE (NO NEED TO DISABLE)
        	write_data_curve_cposition(step_u, u_next, u);  
        	write_data_curve_cvelocity(step_u, u_next, u);
        	write_data_curve_caccelern(step_u, u_next, u);
     
        } // END IF
 
    } // END WHILE LOOP
    // =============================================================
   
    // CLOSING HEADER SAME AS OPENING HEADER FOR DATA COLUMNS
    
    // PRINT TO SCREEN  - PART 4/4  (FOR DEBUGGING)
 	// print_header_cposition_data(FHdata_curve_cposition); 
 	// print_header_cvelocity_data(FHdata_curve_cvelocity); 
 	// print_header_caccelern_data(FHdata_curve_caccelern);
 	
 	// WRITE TO FILE (NO NEED TO DISABLE)
	write_header_cposition_data(FHdata_curve_cposition); 
    write_header_cvelocity_data(FHdata_curve_cvelocity);
    write_header_caccelern_data(FHdata_curve_caccelern);

    // CLOSE CURVE DATA FILES
	fclose(FHdata_curve_cposition);
	fclose(FHdata_curve_cvelocity);
	fclose(FHdata_curve_caccelern);
	
	// CLOSE RUN DATA FILES
	fclose(FHdata_run_rposition);
	fclose(FHdata_run_rvelocity);
	fclose(FHdata_run_raccelern);
	

printf("=========== START PLOTTING HERE \n");

	// POSITION VECTOR PLOTS FROM 
	// DATAFILE "data_curve_cposition.txt" 
//	plot2D_data_curve_cposition();  // DONE
//	plot3D_data_curve_cposition();  // DONE
//	polarD_data_curve_cposition();  // DONE
    
	// VELOCITY VECTOR PLOTS
	// DATAFILE "data_curve_cvelocity.txt" 
	// plot2D_data_curve_cvelocity();  // DONE
	plot3D_data_curve_cvelocity();
	polarD_data_curve_cvelocity();
	
    // ACCELERN VECTOR PLOTS
    // DATAFILE "data_curve_caccelern.txt"
	plot2D_data_curve_caccelern();
	plot3D_data_curve_caccelern();
	polarD_data_curve_caccelern();

printf("=========== ENDED PLOTTING HERE \n");  

printf ("Alhamdulillah. \n");
return (0);
}

// ==================================================================



