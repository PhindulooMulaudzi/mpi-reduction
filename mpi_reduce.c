#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <assert.h>
#include <time.h>

void initArray(int * data, const int size)  
{	
	int i = 0;
	for(i = 0; i <= size; i++){
		// create an data of ones since result is easy to determine, i.e. equal to size
		data[i] = 1;
	}
}
// Creates an array of random numbers. Each number has a value from 0 - 1
int main(int argc, char** argv) {

  int ArraySize = 10;
  int data[ArraySize];
  int nprocesses;
  int currentProcess;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &currentProcess);
  MPI_Comm_size(MPI_COMM_WORLD, &nprocesses);

  // Create a array of elements on all processes.
  initArray(data, ArraySize);
  
  // Sum the numbers locally
  float local_sum = 0;
  int i;
  for (i = 0; i < ArraySize; i++) {
    local_sum += data[i];
  }

  // Print the random numbers on each process
  printf("Local sum for process %d - %f\n",currentProcess, local_sum);

  // Reduce all of the local sums into the global sum
  float global_sum;
  MPI_Reduce(&local_sum, &global_sum, 1, MPI_FLOAT, MPI_SUM, 0,
             MPI_COMM_WORLD);

  // Print the result
  if (currentProcess == 0) {
    printf("Total sum = %f,\n", global_sum);
  }


  MPI_Finalize();
}