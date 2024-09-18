# include <stdio.h>
# include <limits.h> 
# include <float.h>

int main(void) {

    printf("Minimum float  \t\t= %.12e \n", FLT_MIN);
    printf("Maximum float  \t\t= %.12e \n", FLT_MAX);
    
    printf("Minimum double \t\t= %.12e \n", DBL_MIN);
    printf("Maximum double \t\t= %.12e \n", DBL_MAX);
    
    printf("Minimum long double \t= %.12Le \n", LDBL_MIN);
    printf("Maximum long double \t= %.12Le \n", LDBL_MAX);
 
    printf("Minimum short       \t= %d \n", SHRT_MIN);
    printf("Maximun short       \t= %d \n", SHRT_MAX);
    printf("Maximum ushort      \t= %ud \n", USHRT_MAX);
 
    printf("Minimum int         \t= %d \n", INT_MIN);
    printf("Maximum int         \t= %d \n", INT_MAX);
    printf("Maximum uint        \t= %ud \n", UINT_MAX);

    printf("Minimum long int    \t= %li \n", LONG_MIN);
    printf("Maximum long int    \t= %li \n", LONG_MAX);
    printf("Maximum ulong int   \t= %lu \n", ULONG_MAX);

    return(0);
    
}

/*
COMPILATION
wruslan@HP-Laptop-01:~$ gcc -o ranges-numbers-c-code.cx ranges-numbers-c-code.c 

EXECUTION
wruslan@HP-Laptop-01:~$ ./ranges-numbers-c-code.cx 
Minimum float  		    = 1.175494350822e-38 
Maximum float  		    = 3.402823466385e+38 
Minimum double 		    = 2.225073858507e-308 
Maximum double 		    = 1.797693134862e+308 
Minimum long double 	= 3.362103143112e-4932 
Maximum long double 	= 1.189731495357e+4932 
Minimum short       	= -32768 
Maximun short       	= 32767 
Maximum ushort      	= 65535d 
Minimum int         	= -2147483648 
Maximum int         	= 2147483647 
Maximum uint        	= 4294967295d 
Minimum long int    	= -9223372036854775808 
Maximum long int    	= 9223372036854775807 
Maximum ulong int   	= 18446744073709551615 
wruslan@HP-Laptop-01:~$ 
*/

