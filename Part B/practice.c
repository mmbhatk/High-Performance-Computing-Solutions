#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char* argv[])
{
	int i, rank, size, msg, data[10];

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	msg = rank + 10;

	MPI_Gather(&msg, 1, MPI_INT, data, 1, MPI_INT, 0, MPI_COMM_WORLD);

	if(rank == 0)
		for(i = 1; i < size; i++)
			printf("\nFrom [%d]: %d", i, data[i]);
	MPI_Finalize();
}
