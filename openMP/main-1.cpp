#include <omp.h>
#include <stdio.h>

const int N = 1000;

int main(int argc, char *argv[]) {

    int nthreads, tid;
    int i, n=16, chunk=4;
    double a[N],b[N];
    double dotprod=0;

    //Initialize a and b for dot product calculation
    for (i = 0; i < N; i++) {
        a[i]=1.23;
        b[i]=4.56;
    }

    /* Fork a team of threads with each thread having a private tid variable */
    #pragma omp parallel private(tid)
    {
        //#pragma omp for
        // fix for dot product calculation
        #pragma omp for reduction(+:dotprod)
        for (i = 0; i<N; i++) {
            dotprod = dotprod + a[i] * b[i];
        }

/////////////The following is left for debugging assistance////////////
        /* Obtain and print thread id */
        tid = omp_get_thread_num();
        printf("Hello World from thread = %d\n", tid);

        /* Only master thread does this */
        if (tid == 0)
        {
            nthreads = omp_get_num_threads();
            printf("Number of threads = %d\n", nthreads);
        }

    }  /* All threads join master thread and terminate */

    printf("Dot product of the two vectors is %g\n", dotprod);
    if (dotprod >= 5608.7 && dotprod <= 5608.9) //target is 5608.8
        printf("You seem to be calculating things correctly\n");

    return 0;
}
