# include <stdio.h>
# include <limits.h> 
# include <float.h>
int main(void) {

    double largeDouble  = 3.123456789E+6;
    double smallDouble  = 1.123456789E-18;      // BELOW MACHINE  EPSILON 

    printf("\n(1) ADDITION OF SMALL NUMBER BELOW MACHINE EPSILON \n");
    printf("  largeDouble %.12e \n", largeDouble); 
    printf("+ smallDouble %.12e \n", smallDouble);
    printf("=             %.12e \n", (largeDouble + smallDouble));

    printf("\n(2) SUBTRACTION OF SMALL NUMBER BELOW MACHINE EPSILON \n");
    printf("  largeDouble %.12e \n", largeDouble); 
    printf("- smallDouble %.12e \n", smallDouble);
    printf("=             %.12e \n", (largeDouble - smallDouble));

    printf("\n(3) MULTIPLICATION BY SMALL NUMBER BELOW MACHINE EPSILON \n");
    printf("  largeDouble %.12e \n", largeDouble); 
    printf("* smallDouble %.12e \n", smallDouble);
    printf("=             %.12e \n", (largeDouble * smallDouble));

    printf("\n(4) DIVISION BY SMALL NUMBER BELOW MACHINE EPSILON \n");
    printf("  largeDouble %.12e \n", largeDouble); 
    printf("/ smallDouble %.12e \n", smallDouble);
    printf("=             %.12e \n", (largeDouble / smallDouble));

    return(0);
}
/*
COMPILATION
wruslan@HP-Laptop-01:~$ gcc -o fixing-machine-epsilon.cx fixing-machine-epsilon.c 

EXECUTION
wruslan@HP-Laptop-01:~$ ./fixing-machine-epsilon.cx 

(1) ADDITION OF SMALL NUMBER BELOW MACHINE EPSILON 
  largeDouble 3.123456789000e+06 
+ smallDouble 1.123456789000e-18 
=             3.123456789000e+06 

(2) SUBTRACTION OF SMALL NUMBER BELOW MACHINE EPSILON 
  largeDouble 3.123456789000e+06 
- smallDouble 1.123456789000e-18 
=             3.123456789000e+06 

(3) MULTIPLICATION BY SMALL NUMBER BELOW MACHINE EPSILON 
  largeDouble 3.123456789000e+06 
* smallDouble 1.123456789000e-18 
=             3.509068734750e-12 

(4) DIVISION BY SMALL NUMBER BELOW MACHINE EPSILON 
  largeDouble 3.123456789000e+06 
/ smallDouble 1.123456789000e-18 
=             2.780219782000e+24 

wruslan@HP-Laptop-01:~$ 
*/

