// call with mpirun -np 4 ./hello_world
// compile with  mpicxx -o hello_world hello_world.cpp

#include <iostream>
#include <mpi.h>

int main(int argc, char** argv) {
  // Initialisation
  int size, rank;
  MPI_Init(&argc, &argv);
  // Reading size and rank

  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  // Printing
  std::cout << "Hello world, from process #" << rank << std::endl;
  
  // Finalisation
  MPI_Finalize();

  return 0;
}