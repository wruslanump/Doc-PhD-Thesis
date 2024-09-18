# include <stdio.h>
# include <limits.h> 
# include <float.h>

int main(void) {
 
    
     double A = 1.0;
     double B = 1.0;
     int count_greater = 0;
     int count_lesser  = 0;
     int count_equal   = 0;
 
 for (int i = 0; i < 10; i++) {
  
     if ( (A - B) > 0.0 ) {
         count_greater = count_greater + 1 ;
         printf("A_is_GREATER_than_B = %.12e %.12e %.12e %d\n", A, B, (A-B), count_greater); 
     } else if ( (A - B) < 0.0 ) {
         count_lesser = count_lesser + 1 ;
         printf("A_is_LESSER_than_B  = %.12e %.12e %.12e %d\n", A, B, (A-B), count_lesser); 
     } else if ( (A - B) == 0.0) {
         count_equal = count_equal + 1 ;
         printf("A_is_EQUAL_to_B     = %.12e %.12e %.12e %d\n", A, B, (A-B), count_equal); 
     } else { 
         printf("ERROR. This is nonsense. \n"); 
     }  
  
     A = A/1.1157;
     B = 28.157*A/28.156;
 
 } 
 
     
   
}
/*
COMPILATION


EXECUTION

wruslan@HP-Laptop-01:~$ 
*/

