// FILE: c_min_max_int_dbl_in_array.c

#include <stdio.h>
#include <math.h>

#include "c_min_max_int_dbl_in_array.h"

// ==================================================================
double fxn_get_max_element_arraydoubles(double thearray[], int array_size) {
// ==================================================================
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
double fxn_get_min_element_arraydoubles(double thearray[], int array_size) {
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
int fxn_get_max_element_arrayints(int thearray[], int array_size) {
// ==================================================================
        int i;
        int the_max;
        the_max = thearray[0];
        for (i = 1; i < array_size; i++) {
            if (thearray[i] > the_max) {
               the_max = thearray[i];;
            }
        }

return (the_max);
}

// ==================================================================
int fxn_get_min_element_arrayints(int thearray[], int array_size) {
// ==================================================================
        int i;
        int the_min;
        the_min = thearray[0];
        for (i = 1; i < array_size; i++) {
            if (thearray[i] < the_min) {
               the_min = thearray[i];;
            }
        }

return (the_min);
}

// ==================================================================
// ALHAMDULILLAH 3 TIMES
// ==================================================================
