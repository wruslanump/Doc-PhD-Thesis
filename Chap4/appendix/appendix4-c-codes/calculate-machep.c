# include <stdio.h>

int main(void) {

    float         floatMachep   = 1.0;
    double        doubleMachep  = 1.0;
    long double   longDblMachep = 1.0;
    
    while (1.0 + floatMachep/2.0 != 1.0) {
        floatMachep /= 2.0;
    }
    printf("Machine Epsilon for float type  \t= %.19e \n", floatMachep);
    
    while (1.0 + doubleMachep/2.0 != 1.0) {
        doubleMachep /= 2.0;
    }
    printf("Machine Epsilon for double type \t= %.19e \n", doubleMachep);
    
    while (1.0 + longDblMachep/2.0 != 1.0) {
        longDblMachep /= 2.0;
    }
    printf("Machine Epsilon for long double type \t= %.19Le \n", longDblMachep);

    return(0);
    
}




