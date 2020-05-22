
// call with mpirun -np 4 ./hello_world
// compile with  mpicxx -o hello_world hello_world.cpp

#include <mpi.h>
#include <stdio.h>
#include <iostream>

const int N = 1000;

int main(int argc, char *argv[]) {
    // All code from here on is run in parrallel on each CPU
    MPI_Init(&argc, &argv);
    int rank;
    int size;
    double product = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);


    
    int nthreads, tid;
    int i, n=16, chunk=4;
    double a[N],b[N];
    double dotprod=0;

    int start = rank * (static_cast<double>(N)/size);
    int end = (rank + 1) * (static_cast<double>(N)/size) - 1;

    //Initialize a and b for dot product calculation
    for (i = 0; i < N; i++) 
    {
        a[i]=1.23;
        b[i]=4.56;
    }

    /* Fork a team of threads with each thread having a private tid variable */
    for (i = start; i <= end; i++) 
    {
        dotprod = dotprod + a[i] * b[i];
    }

    // Print out what each processor has calculated
    std::cout << "Proc: " << rank << " calculated: " << dotprod << std::endl;

    /* All threads join master thread then terminate all message passing */ 
    MPI_Reduce(&dotprod, &product, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Finalize();

    // rank zero is just to run this last bit on code on a single processor
    // otherwise it will still be exicuted on all processors since the program is duplicated
    if (rank == 0)
    {
        printf("Dot product of the two vectors is %g\n", product);
        if (product >= 5608.7 && product <= 5608.9) //target is 5608.8
            printf("You seem to be calculating things correctly\n");
    }
    return 0;
}
