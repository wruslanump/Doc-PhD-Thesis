# include <stdio.h>
# include <limits.h> 
# include <float.h>
int main(void) {

    double largeDouble  = 3.123456789E+6;
    double smallDouble  = 1.123456789E-18;      // BELOW MACHINE  EPSILON 
    double machepFactor = 1.8765E+10;           // A LARGE POSITIVE NUMBER
 
    printf("ADDITION OF SMALL NUMBER BELOW MACHINE EPSILON \n");
    printf("  largeDouble   %.12e \n", largeDouble); 
    printf("+ smallDouble   %.12e \n", smallDouble);
    printf("=               %.12e \n", (largeDouble + smallDouble));
    
    double uplargeDouble = (machepFactor)*largeDouble;
    double upsmallDouble = (machepFactor)*smallDouble;
    
    printf("\n");
    printf("uplargeDouble   %.12e \n", uplargeDouble);    
    printf("upsmallDouble   %.12e \n", upsmallDouble);    
    
    double the_SUM_01 = (uplargeDouble + upsmallDouble);
    double the_SUM_02 = (the_SUM_01)/(machepFactor);
 
    printf("the_SUM_01 =    %.12e \n", the_SUM_01);      
    printf("the_SUM_02 =    %.12e \n", the_SUM_02); 
 
    return(0);
}
/*
COMPILATION
wruslan@HP-Laptop-01:~$ 
gcc -o Resolving-machine-epsilon.cx Resolving-machine-epsilon.c 

EXECUTION
wruslan@HP-Laptop-01:~$ ./Resolving-machine-epsilon.cx 

ADDITION OF SMALL NUMBER BELOW MACHINE EPSILON 
  largeDouble   3.123456789000e+06 
+ smallDouble   1.123456789000e-18 
=               3.123456789000e+06 

uplargeDouble   5.861166664558e+16 
upsmallDouble   2.108166664558e-08 
the_SUM_01 =    5.861166664558e+16 
the_SUM_02 =    3.123456789000e+06 

wruslan@HP-Laptop-01:~$ 
*/

