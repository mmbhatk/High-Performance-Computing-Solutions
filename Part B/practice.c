#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char* argv[])
{
	int i, rank, size, value, sum = 0;
	MPI_Status status;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if(rank == 0)
	{
		for(i = 1; i < size; i++)
		{
			MPI_Recv(&value, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
			sum += value;
		}
		printf("\n[%d] Sum = %d\n", i, sum);
	}
	else
		MPI_Send(&rank, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);

	MPI_Finalize();
}
