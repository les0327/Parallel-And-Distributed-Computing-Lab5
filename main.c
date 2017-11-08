#include <stdio.h>
#include <omp.h>
#include "functions.h"

/**
 Parallel and distributed computing.
 Lab 5. Threads in OpenMP
 Lisovyi Volodymyr
 IO-53
 30.10.17
 F1: e = (A*B) + (C*(D*(MA*MD)))
 F2: ML = SORT(MF + MG*MH)
 F3: O = MAX(MP*MR)*T
 */
int main() {
    printf("Main start\n");

    omp_set_num_threads(2);
    #pragma omp parallel
    {
        #pragma omp sections
        {
            #pragma omp section
            {
                threadFunction1();
            }
            #pragma omp section
            {
                threadFunction2();
            }
            #pragma omp section
            {
                threadFunction3();
            }
        }
    };

    printf("Main finish\n");
    return 0;
}

