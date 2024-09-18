// FILE: c_accelern.h

// =======================================================
#include <limits.h>   // perror()
#include <math.h>     // pow(), MUST COMPILE WITH LIBRARY -lm
#include <pthread.h>  // MUST COMPILE WITH LIBRARY -lpthread
#include <stdbool.h>  // boolean variables
#include <stdio.h>    // open(), printf(), fopen(), fprintf();
#include <stdlib.h>   // atoi(), system(), rand(),
#include <string.h>   // strtok(), strcpy()
#include <sys/time.h> // For local date-time with (microseconds)
#include <time.h>     // For high-res timer clock_gettime with (nanoseconds)
#include <unistd.h>   // getcwd()

double fxn_cacc_x (double u);
double fxn_cacc_y (double u);
double fxn_cacc_r (double u);
